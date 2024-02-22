#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "queue.h"
#include "register.h"
#include <memory>
class Consumer
{

public:
    Consumer(int consumers, std::shared_ptr<Queue> &message_bus, std::shared_ptr<Register> &reg)
        : num_of_consumers(consumers),
          message_bus(message_bus),
          reg(reg){};
    std::vector<std::thread> start();
    static void consume(Consumer &, int id, int ct);

private:
    int num_of_consumers;
    std::shared_ptr<Queue> message_bus;
    std::shared_ptr<Register> reg;
    void writeOnRegister(int id);

    int DEFAULT_FFED_COUNT = 500;
};

#endif