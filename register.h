#ifndef REG_H_
#define REG_H_

#include <mutex>
#include <vector>

class Register
{
public:
    
    struct ProducerResult{
        int id;
        int count;
        std::time_t time;
    };

    struct ConsumerResult{
        int id;
        std::time_t time;
    };

    Register(int consumers) : consumers(consumers){};

    void registerProducer(int id, int count);

    void registerConsumer(int id);

    std::vector<ConsumerResult> getAllConsumer();

    std::vector<ProducerResult> getAllProducer();

    bool done();
    void imDone() {consumers--;}
    
private:
    std::vector<ProducerResult> producerRegister{};
    std::vector<ConsumerResult> consumerRegister{};
    mutable std::mutex mutex;
    int consumers;
};

#endif