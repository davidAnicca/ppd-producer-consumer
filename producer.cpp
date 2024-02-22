#include "producer.h"
#include "entities.h"
#include <iostream>
#include <thread>
#include <unistd.h>

void Producer::produce(int id, Producer &instance, int it)
{
    int k = 5;
    while (k > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(it));
        int count = instance.getCount();
        instance.send(count);
        std::cout << "[T" << id << "] "
                  << "sent " << count << " portii on message bus" << std::endl;
        instance.writeOnRegister(id, count);
        k--;
    }
}

int Producer::getCount()
{
    return DEFAULT_PORTII_COUNT;
}

void Producer::writeOnRegister(int id, int count) {
    reg->registerProducer(id, count);
}

std::vector<std::thread> Producer::start()
{
    std::vector<std::thread> producers(num_of_producers);

    for (int i = 0; i < num_of_producers; i++) {
        // se dă drumul la producătorul i
        producers[i] = std::thread(produce, i, std::ref(*this), DEFAULT_TIME);
    }

    return producers;
}


void Producer::send(int count)
{
    if (message_bus->empty()) {
        for (int i = 1; i <= count; i++)
            message_bus->send(Portie{});
    }
}