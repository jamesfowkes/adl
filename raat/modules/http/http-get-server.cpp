/*
 * C/C++ Includes
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"
#include "raat-buffer.hpp"
#include "raat-logging.hpp"

#include "http-get-server.hpp"

/*
 * Defines, typedefs, constants
 */

static const char DEVICE_URL[] PROGRAM_MEMORY = "/device/";
static const char PARAM_URL[] PROGRAM_MEMORY = "/param/";
static const char MODULE_URL[] PROGRAM_MEMORY = "/module/";

/*
 * Private Variables
 */


static http_get_handler s_raat_handlers[] = 
{
    {DEVICE_URL, NULL},
    {PARAM_URL, NULL},
    {MODULE_URL, NULL},
    {NULL, NULL}
};

/*
 * Private Functions
 */

static void get_url(char * url, char const * req)
{
	while (*req != ' ') { req++; }
	req++;

	while (*req != ' ') { *url++ = *req++; }
	*url = '\0';
}

/*
 * Class Functions
 */

HTTPGetServer::HTTPGetServer(raat_http_handlers const * const p_raat_http_handlers) :
	m_current_response(m_response, HTTP_SERVER_RESPONSE_SIZE),
	m_handle_raat_commands((bool)p_raat_http_handlers)
{
	if (p_raat_http_handlers)
	{
		s_raat_handlers[0].fn = p_raat_http_handlers->device_handler;
		s_raat_handlers[1].fn = p_raat_http_handlers->param_handler;
		s_raat_handlers[2].fn = p_raat_http_handlers->module_handler;
	}

}

void HTTPGetServer::reset()
{

}

void HTTPGetServer::setup()
{
    this->reset();
}

http_get_handler const * HTTPGetServer::match_handler_url(
	char const * const url, http_get_handler const * const handlers
)
{
	uint8_t i = 0;
	uint16_t handler_url_len;

	const uint16_t url_len = strlen(url);

	while (handlers[i].fn)
	{
		handler_url_len = raat_board_strlen_progmem(handlers[i].url);
		if ((url_len >= handler_url_len) && (raat_board_strncmp_progmem(url, handlers[i].url, handler_url_len) == 0))
		{
			return &handlers[i];
		}
		i++;
	}
	return NULL;
}

void HTTPGetServer::set_response_code(char const * const code)
{
	m_current_response.writeStringP(PSTR("HTTP/1.1 "));
	m_current_response.writeString(code);
	m_current_response.writeStringP(PSTR("\r\n"));
}

void HTTPGetServer::set_response_code_P(char const * const code)
{
	m_current_response.writeStringP(PSTR("HTTP/1.1 "));
	m_current_response.writeStringP(code);
	m_current_response.writeStringP(PSTR("\r\n"));
}

void HTTPGetServer::set_header(char const * const field, char const * const value)
{
	m_current_response.writeString(field);
	m_current_response.writeStringP(PSTR(": "));
	m_current_response.writeString(value);
	m_current_response.writeStringP(PSTR("\r\n"));
}

void HTTPGetServer::set_header_P(char const * const field, char const * const value)
{
	m_current_response.writeStringP(field);
	m_current_response.writeStringP(PSTR(": "));
	m_current_response.writeStringP(value);
	m_current_response.writeStringP(PSTR("\r\n"));
}

void HTTPGetServer::finish_headers()
{
	m_current_response.writeStringP(PSTR("\r\n"));	
}

void HTTPGetServer::add_body(char const * const body)
{
	m_current_response.writeString(body);
}

void HTTPGetServer::add_body_P(char const * const body)
{
	m_current_response.writeStringP(body);
}

void HTTPGetServer::handle_req(http_get_handler const * const handlers, char const * const recvd)
{
	char url[64];
	bool handled = false;

	http_get_handler const * handler;
	m_current_response.attach(m_response, HTTP_SERVER_RESPONSE_SIZE);

	if (handlers && (recvd[0] == 'G') && (recvd[1] == 'E') && (recvd[2] == 'T'))
	{
		get_url(url, recvd);

		if (m_handle_raat_commands)
		{
			if ((handler = HTTPGetServer::match_handler_url(url, s_raat_handlers)))
			{
				uint8_t match_length = raat_board_strlen_progmem(handler->url);
				handler->fn(url, url+match_length);
				handled = true;
			}
		}

		if (!handled)
		{
			if ((handler = HTTPGetServer::match_handler_url(url, handlers)))
			{
				uint8_t match_length = raat_board_strlen_progmem(handler->url);
				handler->fn(url, url+match_length);
				handled = true;
			}
		}
	}

	if (!handled)
	{
		raat_logln_P(LOG_RAAT, PSTR("URL %s not handled"), url);
	}

	m_current_response.detach();
}

char * HTTPGetServer::get_response()
{
	return m_response;
}
