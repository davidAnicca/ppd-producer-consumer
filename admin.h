#ifndef ADMIN_H
#define ADMIN_H

#include "register.h"
#include <memory>
#include <thread>
#include <vector>
class Admin
{
public:
    Admin(std::shared_ptr<Register> &reg) : reg(reg){};
    std::thread start();
    static void sumUp(Admin &ref, int time);
    void end();

private:
    void writeToFile(std::vector<Register::ProducerResult> producerResults,
                     std::vector<Register::ConsumerResult> consumerResults);
    std::shared_ptr<Register> reg;
    int DEFAULT_TIME = 600;
};

#endif