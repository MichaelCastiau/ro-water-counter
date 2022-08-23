#include "wifi_task.h"
// This include must be in the cpp file because the library is badly written
#include <AsyncElegantOTA.h>
#include <HTTPClient.h>
#include <DNSServer.h>
#include <WiFiServer.h>
#include "../assets/portal.hpp"
#include "../config.h"

const char *ssid = "Michael's Jungle 2.4";
const char *password = "BotanicInterior1898";
const static String SERVER_PATH = "https://maker.ifttt.com/trigger/ro_water_filled/json/with/key/" + String(WEBHOOKS_KEY);

extern QueueHandle_t doneLitersQueue;

int sendWebhooksRequest(double litersFilled);

void StartWiFiTask(void *args)
{
    static IPAddress apIP(8, 8, 8, 8);
    static IPAddress netMsk(255, 255, 255, 0);

    Serial.println("Starting WiFi task...");

    AsyncWebServer server(80);
    DNSServer dns;

    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname("ro-water-counter");

    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP("RO Water Counter");
    dns.start(53, "*", apIP);

    WiFi.begin(ssid, password);
   
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", htmlPortal); });

    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    server.begin();
    Serial.println("HTTP server started");

    for (;;)
    {
        if (uxQueueMessagesWaiting(doneLitersQueue) > 0)
        {
            double litersFilled = 0.0;
            xQueueReceive(doneLitersQueue, (void *)&litersFilled, pdMS_TO_TICKS(50));

            int responseCode, counter = 0;

            while (responseCode != 200 && counter < 5)
            {
                responseCode = sendWebhooksRequest(litersFilled);
                vTaskDelay(2000);
                ++counter;
            }
        }

        dns.processNextRequest();

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int sendWebhooksRequest(double litersFilled)
{
    HTTPClient http;
    const String liters = String(round(litersFilled * 100) / 100);
    String data = "{\"liters\":" + liters + "}";
    http.begin(SERVER_PATH);
    http.addHeader("Content-Type", "application/json");

    Serial.printf("Sending POST request with data %s\n", data.c_str());
    const int responseCode = http.POST(data); // We don't care about the result, this is fire and forget
    Serial.printf("Responsecode: %i\n", responseCode);
    http.end();

    return responseCode;
}
