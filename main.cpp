#include "admin.h"
#include "consumer.h"
#include "producer.h"
#include "queue.h"
#include "register.h"
#include <iostream>
#include <memory>


void producerConsumer()
{

    int num_of_consumers = 5;
    int num_of_producers = 2;

    std::shared_ptr<Queue> message_bus = std::make_shared<Queue>();
    std::shared_ptr<Register> reg = std::make_shared<Register>(num_of_consumers);

    Admin admin{reg};

    Producer producer{num_of_producers, num_of_consumers, message_bus, reg};
    Consumer consumer{num_of_consumers, message_bus, reg};
    

    std::thread admin_thread = admin.start();

    std::vector<std::thread> producers = producer.start();
    
    std::vector<std::thread> consumers =consumer.start();

    ///end producers
    for (int i = 0; i < num_of_producers; i++) {
        producers[i].join();
    }

    ///send signals
    for (int i = 0; i < num_of_consumers; i++) {
        message_bus->send(Portie{true});
    }

    //end consumers
    for (int i = 0; i < num_of_consumers; i++) {
        consumers[i].join();
    }

    //end admin
    admin_thread.join();
    
}

int main(int, char **)
{
    std::cout << "Hello, from cons!\n";
    producerConsumer();
}
