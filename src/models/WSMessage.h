#ifndef __WS_MESSAGE_H__
#define __WS_MESSAGE_H__

typedef struct ws_message
{
    double flowRate;
    double litersFilled;
    uint count;
    double targetLiters;
    unsigned long startTime;
} WSMessage;

#endif