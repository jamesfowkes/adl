#ifndef _RAAT_HTTP_GET_SERVER_H_
#define _RAAT_HTTP_GET_SERVER_H_

#ifndef HTTP_SERVER_RESPONSE_SIZE
#define HTTP_SERVER_RESPONSE_SIZE (64)
#endif

typedef void (*http_get_response_fn)(char const * const url, char const * const additional);

typedef struct _http_get_handler
{
    char const * const url;
    http_get_response_fn fn;
} http_get_handler;

typedef struct _raat_http_handlers
{
    http_get_response_fn device_handler;
    http_get_response_fn param_handler;
    http_get_response_fn module_handler;
} raat_http_handlers;

class HTTPGetServer
{
public:
    HTTPGetServer(raat_http_handlers const * const p_raat_http_handlers);
    void setup();
    void reset();

    void handle_req(http_get_handler const * const handlers, char const * const recvd);

    void set_response_code(char const * const code);
    void set_response_code_P(char const * const code);

    void set_header(char const * const field, char const * const value);
    void set_header_P(char const * const field, char const * const value);

    void finish_headers();
    
    void add_body(char const * const body);
    void add_body_P(char const * const body);

    http_get_handler const * match_handler_url(char const * const url, http_get_handler const * const handlers);
    char * get_response();

private:
    char m_response[HTTP_SERVER_RESPONSE_SIZE];
    RAATBuffer m_current_response;

    bool m_handle_raat_commands;
};

#ifndef max
#define max(a,b) ((a > b) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) ((a < b) ? (a) : (b))
#endif

#endif
