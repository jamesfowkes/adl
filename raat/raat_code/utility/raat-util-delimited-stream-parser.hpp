#ifndef _DELIMITED_STREAM_PARSER_H_
#define _DELIMITED_STREAM_PARSER_H_

typedef void (*PARSER_CALLBACK)(char * s);

typedef enum parser_state
{
    PARSER_STATE_WAITING,
    PARSER_STATE_PARSING,
    PARSER_STATE_ERROR,
    PARSER_STATE_OVERFLOW
} PARSER_STATE;

class DelimitedStreamParser
{
public:
    DelimitedStreamParser(char start, char end, raat_string_buffer& buffer, PARSER_CALLBACK on_parsed_cb);
    void run(char c);
    PARSER_STATE state();

private:
    bool add_to_buffer(char c);
    void reset();
    void set_state(PARSER_STATE new_state);
    
    char m_start;
    char m_end;
    raat_string_buffer * m_pbuffer;
    PARSER_CALLBACK m_on_parsed_cb;
    uint16_t m_write_index;
    PARSER_STATE m_state;
};

#endif