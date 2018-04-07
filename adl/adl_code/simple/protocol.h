class ProtocolHandler: public ProtocolHandlerBase
{
public:
	ProtocolHandler();
	bool process(char * simple);
	void write_reply(char * buffer, char const * const reply, uint8_t reply_length);
};
