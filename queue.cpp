#include "queue.h"
#include "entities.h"

Portie Queue::receive()
{
    semaphore.acquire(); // astept producator
    std::unique_lock<std::mutex> lock(queueMutex);
    auto front = dataQueue.front();
    dataQueue.pop();
    return front;
}

bool Queue::empty(){
    std::unique_lock<std::mutex> lock(queueMutex);
    return dataQueue.empty();
}

void Queue::send(Portie portie)
{
    std::unique_lock<std::mutex> lock(queueMutex);
    dataQueue.emplace(portie);
    lock.unlock();
    semaphore.release(); // anunt consumator
}

Queue::Queue(const Queue &other)
{
    std::lock_guard<std::mutex> lock1(other.queueMutex);
    std::lock_guard<std::mutex> lock2(queueMutex);
    dataQueue = other.dataQueue;
}
