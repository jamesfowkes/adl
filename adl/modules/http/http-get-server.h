#ifndef _ADL_HTTP_GET_SERVER_H_
#define _ADL_HTTP_GET_SERVER_H_

typedef void (*http_get_response_fn)(char const * const url);

typedef struct
{
    char const * const url;
    http_get_response_fn fn;
} http_get_handler;

class HTTPGetServer
{
public:
    HTTPGetServer(bool handle_adl_commands);
    void setup();
    void reset();

    void handle_req(http_get_handler * handlers, char const * const recvd);
    void set_response_code(char const * const code);
    void set_header(char const * const field, char const * const value);
    void finish_headers();
    void add_body(char const * const body);
    http_get_handler * match_handler_url(char const * const url, http_get_handler * handlers);
    char * get_response();

private:
    char m_response[256];
    ADLBuffer m_current_response;

    bool m_handle_adl_commands;
};

#ifndef max
#define max(a,b) ((a > b) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) ((a < b) ? (a) : (b))
#endif

#endif
