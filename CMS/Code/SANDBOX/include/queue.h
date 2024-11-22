#pragma once
class Queue
{
private:

public:

Queue();
void* addQueueNode(void* frame, long length);
void* popQueueNode();
};