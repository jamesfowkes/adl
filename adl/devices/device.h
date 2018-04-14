class DeviceBase
{
public:
	virtual void reset() = 0;
	virtual void setup() = 0;
	virtual int command_handler(char const * const command, char * reply) = 0;
	virtual void tick() = 0;
};
