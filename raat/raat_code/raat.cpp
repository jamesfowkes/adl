#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "raat.h"
#include "protocol.h"

// RAAT receives into this buffer
static char s_raat_recv_buffer[RAAT_BUFFER_SIZE];
static uint32_t s_recv_idx = 0;

// RAAT builds reply strings into this buffer
static char s_raat_tx_buffer[RAAT_BUFFER_SIZE];

// RAAT passes this buffer to application to fill with command replies 
static char s_raat_reply_buffer[RAAT_BUFFER_SIZE];

static bool s_command_pending = false;

static ProtocolHandler s_protocol_handler; 

static unsigned long s_timer = 0;

static inline bool end_of_command(char c)
{
    return c == '\n';
}

static int raat_board_device_command(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'R')
    {
        int i = 0;

        for (i = 1; i <= RAAT_DEVICE_COUNT; i++)
        {
            raat_get_device(i).reset();
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

static int raat_board_param_command(char const * const command, char * reply)
{
    int reply_length = 0;
    if (command[0] == 'R')
    {
        int i = 0;

        for (i = 1; i <= RAAT_PARAM_COUNT; i++)
        {
            raat_get_param(i).reset();
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

static int raat_process_device_command(DEVICE_ADDRESS address, char const * const command, char * reply)
{
    int reply_length = 0;

    if (address == RAAT_BOARD_ADDRESS)
    {
        reply_length = raat_board_device_command(command, reply);
    }
    else if (address > RAAT_DEVICE_COUNT)
    {
        strcpy(reply, "?");
        reply_length = strlen(reply);
    }
    else
    {
        reply_length = raat_get_device_cmd_handler(address)(command, reply);
    }

    return reply_length;
}

static int raat_process_param_command(PARAM_ADDRESS address, char const * const command, char * reply)
{
    int reply_length = 0;

    if (address == RAAT_BOARD_ADDRESS)
    {
        return raat_board_param_command(command, reply);
    }
    else if (address > RAAT_PARAM_COUNT)
    {
        strcpy(reply, "?");
        return strlen(reply);
    }
    else
    {
        reply_length = raat_get_param_cmd_handler(address)(command, reply);
    }

    return reply_length;
}

int raat_chars_to_address(char const * const buffer)
{
    return ((buffer[0] - '0') * 10) + (buffer[1] - '0');
}

bool raat_validate_char_address(char const * const buffer)
{
    if (!buffer) { return false; }

    return (isdigit(buffer[0]) && isdigit(buffer[1]));
}

ADDRESS_TYPE raat_get_address_type_from_string(char const * const s)
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

ADDRESS_TYPE raat_get_address_type_from_char(char c)
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

char raat_get_char_from_address_type(ADDRESS_TYPE t)
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

void raat_handle_any_pending_commands()
{
    int reply_length = 0;
    bool valid_address_type = true;

    if (s_command_pending)
    {
        memset(s_raat_tx_buffer, '\0', sizeof(s_raat_tx_buffer));
        memset(s_raat_reply_buffer, '\0', sizeof(s_raat_reply_buffer));

        switch(s_protocol_handler.process(s_raat_recv_buffer))
        {
        case ADDRESS_TYPE_DEVICE:
            reply_length = raat_process_device_command(
                s_protocol_handler.last_address,
                s_protocol_handler.command,
                s_raat_reply_buffer);
            break;
        case ADDRESS_TYPE_PARAM:
            reply_length = raat_process_param_command(
                s_protocol_handler.last_address,
                s_protocol_handler.command,
                s_raat_reply_buffer);
            break;
        case ADDRESS_TYPE_MODULE:
            break;
        case ADDRESS_TYPE_NONE:
        default:
            valid_address_type = false;
            break;
        }

        if(valid_address_type && reply_length)
        {
            s_protocol_handler.write_reply(s_raat_tx_buffer, s_raat_reply_buffer, reply_length);
        }
        else if (!valid_address_type)
        {
            strcpy(s_raat_tx_buffer, "ADDR?");
        }
        else if (reply_length == 0)
        {
            strcpy(s_raat_tx_buffer, "CMD?");
        }
        else
        {
            strcpy(s_raat_tx_buffer, "ERR");
        }

        raat_board_send(s_raat_tx_buffer);

        s_command_pending = false;
        s_recv_idx = 0;
    }
}

void raat_service_timer()
{
    unsigned long time_now = millis();

    int i;

    if ((time_now - s_timer) > RAAT_TICK_MS)
    {
        s_timer = time_now;
        if (RAAT_DEVICE_COUNT)
        {
            for (i = 1; i <= RAAT_DEVICE_COUNT; i++)
            {
                raat_get_device(i).tick();
            }
        }
    }
}

void raat_delay_start(uint8_t seconds)
{
    while(seconds)
    {
        raat_on_delay_start_tick(seconds);
        seconds--;
        delay(1000);
    }
}

void raat_add_incoming_command(char const * cmd)
{
    if (cmd)
    {
        strncpy(s_raat_recv_buffer, cmd, RAAT_BUFFER_SIZE-1);
        s_raat_recv_buffer[RAAT_BUFFER_SIZE-1] = '\0';
        s_command_pending = true;
    }
}

void raat_add_incoming_char(char c)
{
    s_command_pending = end_of_command(c);
    if (!s_command_pending)
    {
        s_raat_recv_buffer[s_recv_idx++] = c;
        s_raat_recv_buffer[s_recv_idx] = '\0';
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
