#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "queue.h"
#include "register.h"
#include <memory>
#include <string>
#include <vector>
class Producer
{
public:
    Producer(
        int producers,
        int consumers,
        std::shared_ptr<Queue> &message_bus,
        std::shared_ptr<Register> &reg)
        : message_bus(message_bus),
          num_of_consumers(consumers),
          num_of_producers(producers),
          reg(reg){};

    std::vector<std::thread> start();
    static void produce(int id,
                        Producer &instance,
                        int it);

private:
    void send(int count);
    void generateFileNames();
    void writeOnRegister(int id, int count);

    int getCount();


    std::shared_ptr<Queue> message_bus;
    std::shared_ptr<Register> reg;

    int num_of_producers{};
    int num_of_consumers{};
    int files_per_thread{};

    std::vector<std::string> filenames;

    int DEFAULT_TIME = 700;
    int DEFAULT_PORTII_COUNT = 5;
};

#endif