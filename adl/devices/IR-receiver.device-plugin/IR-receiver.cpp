#include <Wire.h>
#include <IRremote.h>

#include "adl.h"

#include "IR-receiver.h"

static bool command_is_query(char const * const command)
{
    int command_length = strlen(command);
    return command[command_length-1] == '?';
}

static bool command_is_setting(char const * const command)
{
    return (command[0] == 'C') && (command[1] == 'H');
}

/*
 * Class Private Functions
 */

uint8_t IR_Receiver::handle_query_command(char const * const command, char * reply)
{
    unsigned long code;

    if (strcmp(command, "?") == 0)
    {
        if (this->get_code(code))
        {
            sprintf(reply, "%x", code);
        }
        else
        {
            sprintf(reply, "No Recv");
        }
    }
    else
    {
        reply[0] = '?';
        return 1;
    }

    return strlen(reply);
}


/*
 * Class Public Functions
 */

IR_Receiver::IR_Receiver(uint8_t pin) :
    m_irrecv(pin)
{

}

void IR_Receiver::reset()
{
    
}

void IR_Receiver::tick()
{

}

void IR_Receiver::setup()
{
    this->reset();
    m_irrecv.enableIRIn();
}

int IR_Receiver::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;

    if (command_is_query(command))
    {
        reply_length = this->handle_query_command(command, reply);
    }
    else
    {
        reply[0] = '?';
        reply_length = 1;
    }

    return reply_length;
}

bool IR_Receiver::get_code(unsigned long& code)
{
    bool received_code = m_irrecv.decode(&m_results);

    if (received_code)
    {   
        code = m_results.value;
        m_irrecv.resume();
    }
    return received_code; 
}
