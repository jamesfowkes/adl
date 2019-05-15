#include "raat.hpp"
#include "raat-buffer.hpp"

#include "http-get-server.hpp"

static void get_url(char * url, char const * req)
{
	while (*req != ' ') { req++; }
	req++;

	while (*req != ' ') { *url++ = *req++; }
	*url = '\0';
}

static const char DEVICE_URL[] PROGRAM_MEMORY = "/device/";
static const char PARAM_URL[] PROGRAM_MEMORY = "/param/";
static const char MODULE_URL[] PROGRAM_MEMORY = "/module/";

static http_get_handler s_raat_handlers[] = 
{
    {DEVICE_URL, raat_add_incoming_command},
    {PARAM_URL, raat_add_incoming_command},
    {MODULE_URL, raat_add_incoming_command},
    {NULL, NULL}
};

HTTPGetServer::HTTPGetServer(bool handle_raat_commands) :
	m_current_response(m_response, 256),
	m_handle_raat_commands(handle_raat_commands)
{

}

void HTTPGetServer::reset()
{

}

void HTTPGetServer::setup()
{
    this->reset();
}

http_get_handler * HTTPGetServer::match_handler_url(char const * const url, http_get_handler * handlers)
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

void HTTPGetServer::handle_req(http_get_handler * handlers, char const * const recvd)
{
	char url[64];
	bool handled = false;

	http_get_handler * handler;
	m_current_response.attach(m_response, 256);

	if ((recvd[0] == 'G') && (recvd[1] == 'E') && (recvd[2] == 'T'))
	{
		get_url(url, recvd);

		if (m_handle_raat_commands)
		{
			if ((handler = HTTPGetServer::match_handler_url(url, s_raat_handlers)))
			{
				handler->fn(url);
				handled = true;
			}
		}

		if (!handled)
		{
			if ((handler = HTTPGetServer::match_handler_url(url, handlers)))
			{
				handler->fn(url);
				handled = true;
			}
		}
	}

	if (!handled)
	{
		raat_logln(LOG_RAAT, "URL %s not handled", url);
	}

	m_current_response.detach();
}

char * HTTPGetServer::get_response()
{
	return m_response;
}
