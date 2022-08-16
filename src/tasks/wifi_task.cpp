#include "wifi_task.h"
// This include must be in the cpp file because the library is badly written
#include <AsyncElegantOTA.h>

const char* ssid = "Michael's Jungle 2.4";
const char* password = "BotanicInterior1898";

void StartWiFiTask(void *args)
{
    Serial.println("Starting WiFi task...");
    AsyncWebServer server(80);
    WiFi.mode(WIFI_STA);
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

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hi! I am ESP32."); });

    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    server.begin();
    Serial.println("HTTP server started");

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
