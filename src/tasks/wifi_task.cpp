#include "wifi_task.h"
// This include must be in the cpp file because the library is badly written
#include <AsyncElegantOTA.h>
#include <HTTPClient.h>
#include <DNSServer.h>
#include <WiFiServer.h>
#include "../assets/portal.hpp"
#include "../config.h"
#include "../models/WSMessage.h"

const char *ssid = "Michael's Jungle 2.4";
const char *password = "BotanicInterior1898";
const static String SERVER_PATH = "https://maker.ifttt.com/trigger/ro_water_filled/json/with/key/" + String(WEBHOOKS_KEY);

extern QueueHandle_t doneLitersQueue;
extern EventGroupHandle_t wiFiEventGroup;
extern QueueHandle_t toWSQueue;

int sendWebhooksRequest(double litersFilled);

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len);

void StartWiFiTask(void *args)
{
    static IPAddress apIP(8, 8, 8, 8);
    static IPAddress netMsk(255, 255, 255, 0);

    Serial.println("Starting WiFi task...");

    AsyncWebServer server(80);
    AsyncWebSocket ws("/ws");
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

    xEventGroupSetBits(wiFiEventGroup, WIFI_CONNECTED);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", htmlPortal); });

    ws.onEvent(onEvent);
    server.addHandler(&ws);
    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    server.begin();
    Serial.println("HTTP server started");

    volatile WSMessage message = {.flowRate = 0, .litersFilled = 0, .count = 0, .targetLiters = 0, .is_running = 0};

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

        if (uxQueueMessagesWaiting(toWSQueue) > 0)
        {
            WSMessage newMessage;
            xQueueReceive(toWSQueue, (void *)&newMessage, pdMS_TO_TICKS(50));

            if (newMessage.targetLiters > 0)
                message.targetLiters = newMessage.targetLiters;

            message.flowRate = newMessage.flowRate;
            message.litersFilled = newMessage.litersFilled;
            message.count = newMessage.count;

            char buffer[100];
            sprintf(buffer, "{\"flowRate\":%f,\"litersFilled\":%f, \"count\": %i, \"targetLiters\":%f, \"isRunning\":%i}", message.flowRate, message.litersFilled, message.count, message.targetLiters);
            ws.textAll(buffer);
        }

        ws.cleanupClients();
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

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}