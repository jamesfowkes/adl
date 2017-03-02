#include <Arduino.h>

#include "device.h"
#include "adl.h"

#include "reset.h"

Reset::Reset() {}

void Reset::reset() {}

void Reset::setup() {}

int Reset::command_handler(char const * const command, char * reply)
{
	int reply_length = 0;
	if (command[0] == 'R')
	{
		int i = 0;
		int n_devices = adl_device_count();

		for (i = 0; i < n_devices; i++)
		{
			adl_get_device(i)->reset();
		}
		
		strcpy(reply, "ROK");
		reply_length = strlen(reply);
	}
	else
	{
		reply[0] = '?';
		reply_length = 1;
	}
	return reply_length;
}
