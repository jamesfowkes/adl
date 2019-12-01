/*
 * ESP32 Includes
 */

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"
#include "esp32-captive-portal.hpp"

/*
 * Private Functions
 */

static void check_pwd_length(char * pwd)
{
    if (pwd)
    {
        if (strlen(pwd) <= 8)
        {
            raat_logln(LOG_RAAT, "Warning: password length <= 8 chars");
        }
    }
}

/*
 * Class Functions
 */

ESP32CaptivePortal::ESP32CaptivePortal(bool debug, char const * const default_ap_name, char const * const default_ap_pwd) :
    m_debug_wifi_manager(debug)
{
    m_ap_name_eeprom_location.size = 32;
    m_ap_pwd_eeprom_location.size = 32;
    raat_nv_alloc(m_ap_name_eeprom_location);
    raat_nv_alloc(m_ap_pwd_eeprom_location);

    strncpy(m_ap_name, default_ap_name, 32);
    strncpy(m_ap_pwd, default_ap_pwd, 32);
}

void ESP32CaptivePortal::setup()
{
    raat_nv_load(m_ap_name, m_ap_name_eeprom_location);
    raat_nv_load(m_ap_pwd, m_ap_pwd_eeprom_location);

    this->m_wifi_manager.setDebugOutput(m_debug_wifi_manager);
    this->m_wifi_manager.setAPCallback(esp32_on_captive_portal_ready_callback);

    check_pwd_length(m_ap_pwd);

    if (strlen(m_ap_name) && strlen(m_ap_pwd))
    {
        this->m_wifi_manager.autoConnect(m_ap_name, m_ap_pwd);
    }
    else if (strlen(m_ap_name))
    {
        this->m_wifi_manager.autoConnect(m_ap_name);
    }
    else
    {
        // AP name defaults to ESP<chipID>
        this->m_wifi_manager.autoConnect(); 
    }
}

void ESP32CaptivePortal::reset()
{

}

void ESP32CaptivePortal::reset_portal()
{    
    raat_logln(LOG_RAAT, "Disconnecting WiFi...");
    WiFi.disconnect(true);
    WiFi.begin("0","0");
    delay(3000);
    raat_logln(LOG_RAAT, "Restarting...");
    ESP.restart();
    delay(1000);
}

uint16_t ESP32CaptivePortal::command_handler(char const * const command, char * reply)
{
    uint16_t reply_length = 0;

    if (command[0] == 'R')
    {
        this->reset_portal();
        strcpy(reply, "ROK");
        reply_length = 3;
    }

    return reply_length;
}
