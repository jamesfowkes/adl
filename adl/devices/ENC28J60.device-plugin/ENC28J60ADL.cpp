#include <EtherCard.h>

#include "adl.h"

#include "ENC28J60ADL.h"

ENC28J60ADL::ENC28J60ADL()
{
}

void ENC28J60ADL::tick() {}

void ENC28J60ADL::reset()
{

}

void ENC28J60ADL::setup()
{
    this->reset();
}

int ENC28J60ADL::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    return reply_length;
}
