#ifndef QUEUE_H_
#define QUEUE_H_

#include <mutex>
#include <queue>
#include <semaphore>
#include <thread>

#include "entities.h"

class Queue
{
public:
    Queue() : semaphore(0){};

    Queue(const Queue& other);
    void send(Portie portie);

    bool empty();

    Portie receive();
private:
    std::queue<Portie> dataQueue;

    mutable std::mutex queueMutex;
    std::counting_semaphore<2> semaphore{0}; // contorizare
};

#endif