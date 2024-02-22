#include "consumer.h"
#include "entities.h"
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

std::vector<std::thread> Consumer::start()
{
    std::vector<std::thread> consumers(num_of_consumers);
    for (int i = 0; i < num_of_consumers; i++) {
        consumers[i] = std::thread(consume, std::ref(*this), i, DEFAULT_FFED_COUNT);
    }
    return consumers;
}

void Consumer::writeOnRegister(int id) {
    reg->registerConsumer(id);
}

void Consumer::consume(Consumer &instance, int id, int ct)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ct));
        Portie data = instance.message_bus->receive();
        if (data.isSignal) {
            std::cout << "Animalul " << id << " si-a oprit executia " << std::endl;
            instance.reg->imDone();
            return;
        }
        std::cout << "Animal " << id << " a mâncat o portie" << std::endl;
        instance.writeOnRegister(id);
    }
}