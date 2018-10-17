#include <Arduino.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "parameter.h"
#include "device.h"
#include "adl-callbacks.h"
#include "adl-defs.h"
#include "adl.h"
#include "protocol.h"

// ADL receives into this buffer
static char s_adl_recv_buffer[ADL_BUFFER_SIZE];
static uint32_t s_recv_idx = 0;

// ADL builds reply strings into this buffer
static char s_adl_tx_buffer[ADL_BUFFER_SIZE];

// ADL passes this buffer to application to fill with command replies 
static char s_adl_reply_buffer[ADL_BUFFER_SIZE];

static bool s_command_pending = false;

static ProtocolHandler s_protocol_handler; 

static unsigned long s_timer = 0;

static inline bool end_of_command(char c)
{
    return c == '\n';
}

static int adl_board_device_command(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'R')
    {
        int i = 0;

        for (i = 1; i <= ADL_DEVICE_COUNT; i++)
        {
            adl_get_device(i).reset();
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

static int adl_board_param_command(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'R')
    {
        int i = 0;

        for (i = 1; i <= ADL_PARAM_COUNT; i++)
        {
            adl_get_param(i).reset();
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

static int adl_process_device_command(DEVICE_ADDRESS address, char const * const command, char * reply)
{
    int reply_length = 0;

    if (address == ADL_BOARD_ADDRESS)
    {
        return adl_board_device_command(command, reply);
    }
    else if (address > ADL_DEVICE_COUNT)
    {
        strcpy(reply, "?");
        return strlen(reply);
    }
    else
    {
        reply_length = adl_get_device_cmd_handler(address)(command, reply);
    }

    return reply_length;
}

static int adl_process_param_command(PARAM_ADDRESS address, char const * const command, char * reply)
{
    int reply_length = 0;

    if (address == ADL_BOARD_ADDRESS)
    {
        return adl_board_param_command(command, reply);
    }
    else if (address > ADL_PARAM_COUNT)
    {
        strcpy(reply, "?");
        return strlen(reply);
    }
    else
    {
        reply_length = adl_get_param_cmd_handler(address)(command, reply);
    }

    return reply_length;
}

int adl_chars_to_address(char const * const buffer)
{
    return ((buffer[0] - '0') * 10) + (buffer[1] - '0');
}

bool adl_validate_char_address(char const * const buffer)
{
    if (!buffer) { return false; }

    return (isdigit(buffer[0]) && isdigit(buffer[1]));
}

ADDRESS_TYPE adl_get_address_type_from_string(char const * const s)
{
    ADDRESS_TYPE t = ADDRESS_TYPE_NONE;

    if ((strlen(s) >= 6) && (strncmp(s, "device", 6) == 0))
    {
        t = ADDRESS_TYPE_DEVICE;
    }
    else if ((strlen(s) >= 5) && (strncmp(s, "param", 5) == 0))
    {
        t = ADDRESS_TYPE_PARAM;
    }
    else if ((strlen(s) >= 6) && (strncmp(s, "module", 6) == 0))
    {
        t = ADDRESS_TYPE_MODULE;
    }
    
    return t;
}

ADDRESS_TYPE adl_get_address_type_from_char(char c)
{
    ADDRESS_TYPE t = ADDRESS_TYPE_NONE;

    switch(c)
    {
    case 'D':
        t = ADDRESS_TYPE_DEVICE;
        break;
    case 'P':
        t = ADDRESS_TYPE_PARAM;
        break;
    default:
        break;
    }

    return t;
}

char adl_get_char_from_address_type(ADDRESS_TYPE t)
{
    char c = '?';

    switch(t)
    {
    case ADDRESS_TYPE_DEVICE:
        c = 'D';
        break;
    case ADDRESS_TYPE_PARAM:
        c = 'P';
        break;
    default:
        break;
    }

    return c;
}

void adl_handle_any_pending_commands()
{
    int reply_length = 0;

    if (s_command_pending)
    {
        memset(s_adl_tx_buffer, '\0', sizeof(s_adl_tx_buffer));
        memset(s_adl_reply_buffer, '\0', sizeof(s_adl_reply_buffer));

        switch(s_protocol_handler.process(s_adl_recv_buffer))
        {
        case ADDRESS_TYPE_DEVICE:
            reply_length = adl_process_device_command(
                s_protocol_handler.last_address,
                s_protocol_handler.command,
                s_adl_reply_buffer);
            break;
        case ADDRESS_TYPE_PARAM:
            reply_length = adl_process_param_command(
                s_protocol_handler.last_address,
                s_protocol_handler.command,
                s_adl_reply_buffer);
        default:
            break;
        }

        if(reply_length)
        {
            s_protocol_handler.write_reply(s_adl_tx_buffer, s_adl_reply_buffer, reply_length);
        }
        else
        {
            strcpy(s_adl_tx_buffer, "ADDR?");
        }

        adl_board_send(s_adl_tx_buffer);

        s_command_pending = false;
        s_recv_idx = 0;
    }
}

void adl_service_timer()
{
    unsigned long time_now = millis();

    int i;

    if ((time_now - s_timer) > ADL_TICK_MS)
    {
        s_timer = time_now;
        if (ADL_DEVICE_COUNT)
        {
            for (i = 1; i <= ADL_DEVICE_COUNT; i++)
            {
                adl_get_device(i).tick();
            }
        }
        if (ADL_PARAM_COUNT)
        {
            for (i = 1; i <= ADL_PARAM_COUNT; i++)
            {
                adl_get_param(i).tick();
            }
        }
    }
}

void adl_delay_start(uint8_t seconds)
{
    while(seconds)
    {
        adl_on_delay_start_tick(seconds);
        seconds--;
        delay(1000);
    }
}

void adl_add_char(char c)
{
    s_command_pending = end_of_command(c);
    if (!s_command_pending)
    {
        s_adl_recv_buffer[s_recv_idx++] = c;
        s_adl_recv_buffer[s_recv_idx] = '\0';
    }
}

bool is_digit_string(char const * s)
{
    if (s == NULL) { return false; }
    if (strlen(s) == 0) { return false; }

    while(*s)
    {
        if (!isdigit(*s)) { return false; }
        s++;
    }
    return true;
}
