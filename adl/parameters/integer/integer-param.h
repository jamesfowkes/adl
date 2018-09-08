#ifndef _INTEGER_PARAM_H_
#define _INTEGER_PARAM_H_

class IntegerParam : public ParameterBase
{
public:
	IntegerParam(int32_t reset_value, int32_t min_limit=INT32_MIN, int32_t max_limit=INT32_MAX, bool clip_on_out_of_range=true);
	void setup();
	void reset();
	int command_handler(char const * const command, char * reply);
	
	bool set(int32_t setting);
	int32_t get();

private:
	int32_t m_reset_value;
	LimitedRangeInt m_value;
};

#endif