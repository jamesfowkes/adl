class ProtocolHandler: public ProtocolHandlerBase
{
public:
	ProtocolHandler();
	void process(char * simple);
	void write_reply(char * buffer, char const * const reply, uint8_t reply_length);
};
