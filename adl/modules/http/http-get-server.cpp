#include "adl.h"
#include "adl-buffer.h"

#include "http-get-server.h"

static void get_url(char * url, char const * req)
{
	while (*req != ' ') { req++; }
	req++;

	while (*req != ' ') { *url++ = *req++; }
	*url = '\0';
}

static http_get_handler s_adl_handlers[] = 
{
    {"/device/", adl_add_incoming_command},
    {"/param/", adl_add_incoming_command},
    {"/module/", adl_add_incoming_command},
    {"", NULL}
};

HTTPGetServer::HTTPGetServer(bool handle_adl_commands) :
	m_current_response(m_response, 256),
	m_handle_adl_commands(handle_adl_commands)
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
		handler_url_len = strlen(handlers[i].url);
		if ((url_len >= handler_url_len) && (strncmp(url, handlers[i].url, handler_url_len) == 0))
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

void HTTPGetServer::set_header(char const * const field, char const * const value)
{
	m_current_response.writeString(field);
	m_current_response.writeStringP(PSTR(": "));
	m_current_response.writeString(value);
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

void HTTPGetServer::handle_req(http_get_handler * handlers, char const * const recvd)
{
	char url[64];
	bool handled = false;

	http_get_handler * handler;
	m_current_response.attach(m_response, 256);

	if ((recvd[0] == 'G') && (recvd[1] == 'E') && (recvd[2] == 'T'))
	{
		get_url(url, recvd);

		if (m_handle_adl_commands)
		{
			if ((handler = HTTPGetServer::match_handler_url(url, s_adl_handlers)))
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
		adl_logln(LOG_ADL, "URL %s not handled", url);
	}

	m_current_response.detach();
}

char * HTTPGetServer::get_response()
{
	return m_response;
}
