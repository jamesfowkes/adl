#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>

#include "server.h"

class ESP32CaptivePortal
{
public:
    ESP32CaptivePortal(bool debug);
    void setup();
    void reset();
    void tick();
    uint16_t command_handler(char const * const command, char * reply);

private:
    WiFiManager m_wifi_manager;
    bool m_debug_wifi_manager;

    char m_ap_name[32];
    char m_ap_pwd[32];

    RAAT_NV_LOCATION m_ap_name_eeprom_location;
    RAAT_NV_LOCATION m_ap_pwd_eeprom_location;
}

// Expected to be implemented by userspace code
void esp32_on_captive_portal_ready_callback(WiFiManager * pManager);
