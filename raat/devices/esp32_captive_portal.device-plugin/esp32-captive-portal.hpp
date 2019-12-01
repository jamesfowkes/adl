#ifndef _ESP32_CAPTIVE_PORTAL_H_
#define _ESP32_CAPTIVE_PORTAL_H_

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>

class ESP32CaptivePortal : public DeviceBase
{
public:
    ESP32CaptivePortal(bool debug, char const * const default_ap_name, char const * const default_ap_pwd);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);

    void reset_portal();

private:
    WiFiManager m_wifi_manager;
    bool m_debug_wifi_manager;

    char m_ap_name[32];
    char m_ap_pwd[32];

    RAAT_NV_LOCATION m_ap_name_eeprom_location;
    RAAT_NV_LOCATION m_ap_pwd_eeprom_location;
};

// Expected to be implemented by userspace code
void esp32_on_captive_portal_ready_callback(WiFiManager * pManager);

#endif
