#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "definements.hpp"
#include "Handler.hpp"

class Webserver
{
public:
    Webserver()
    {
    }

    void setup(Handler *handler, AsyncWebServer *server)
    {
        this->handler = handler;
        this->server = server;
#pragma region HTTP handler
        server->on("/", HTTP_GET, [handler](AsyncWebServerRequest *request) { handler->onIndex(request); });
        server->on("/colors", HTTP_GET, [handler](AsyncWebServerRequest *request) { handler->onColors(request); });
        server->on("/display", HTTP_GET, [handler](AsyncWebServerRequest *request) { handler->onCustom(request); });
        //server->on("/envcolors", HTTP_GET, [handler](AsyncWebServerRequest *request){handler->onEnvColors(request);});
        server->on("/blink", HTTP_GET, [handler](AsyncWebServerRequest *request) { handler->onBlink(request); });
        //server->on("/env", HTTP_GET, [handler](AsyncWebServerRequest *request){handler->onEnv(request);});
        //server->on("/times", HTTP_GET, [handler](AsyncWebServerRequest *request){handler->onTimes(request);});

        server->onNotFound([](AsyncWebServerRequest *request) { request->send(404); });
        server->begin();
        Serial.println("HTTP server started");
#pragma endregion
    }

private:
    Handler *handler;
    AsyncWebServer *server;
};