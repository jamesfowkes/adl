#include <stdint.h>
#include <string.h>

#include "raat.h"
#include "raat-buffer.h"

#include "http-get-server.h"

static HTTPGetServer s_server(false);

static void send_standard_erm_response()
{
    s_server.set_response_code("200 OK");
    s_server.set_header("Access-Control-Allow-Origin", "*");
    s_server.finish_headers();
}

static void relay_req_on(char const * const url)
{
	(void)url;
	digitalWrite(2, HIGH);
	send_standard_erm_response();
}

static void relay_req_off(char const * const url)
{
	(void)url;
	digitalWrite(2, LOW);
	send_standard_erm_response();
}

static http_get_handler s_handlers[] = 
{
    {"/d2/on", relay_req_on},
    {"/d2/off", relay_req_off},
    {"", NULL}
};

void ethernet_packet_handler(char * req)
{
	s_server.handle_req(s_handlers, req);
}

char * ethernet_response_provider()
{
	return s_server.get_response();
}

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    pinMode(2, OUTPUT);
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}
