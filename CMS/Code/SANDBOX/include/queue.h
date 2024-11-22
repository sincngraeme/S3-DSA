#pragma once

#include "RS232Comm.h"
#include "message.h"

class Queue
{
    private:

    public:
        Queue();
        int queueFlag;
        void* addQueueNode(pcomhdr header, void* payload);
        void* popQueueNode();

};