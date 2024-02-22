#include "register.h"

void Register::registerProducer(int id, int count) {
  std::unique_lock<std::mutex> lock(mutex);
  producerRegister.emplace_back(ProducerResult{id, count, std::time(0)});
  lock.unlock();
}

void Register::registerConsumer(int id) {
  std::unique_lock<std::mutex> lock(mutex);
  consumerRegister.emplace_back(ConsumerResult{id, std::time(0)});
  lock.unlock();
}

std::vector<Register::ConsumerResult> Register::getAllConsumer() {
  std::unique_lock<std::mutex> lock(mutex);
  return consumerRegister;
}

std::vector<Register::ProducerResult> Register::getAllProducer() {
  std::unique_lock<std::mutex> lock(mutex);
  return producerRegister;
}

bool Register::done() {
  std::unique_lock<std::mutex> lock(mutex);
  return consumers == 0;
}