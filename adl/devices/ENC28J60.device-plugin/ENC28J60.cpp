#include "adl.h"

#include "ENC28J60.h"

ENC28J60::ENC28J60()
{
}

void ENC28J60::tick() {}

void ENC28J60::reset()
{

}

void ENC28J60::setup()
{
    this->reset();
}

int ENC28J60::command_handler(char const * const command, char * reply)
{
    int reply_length = 0;
    return reply_length;
}
