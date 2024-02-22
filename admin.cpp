#include "admin.h"
#include "register.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>

std::thread Admin::start()
{
    std::thread admin_thread = std::thread(sumUp, std::ref(*this), DEFAULT_TIME);
    return admin_thread;
}

void Admin::sumUp(Admin &ref, int time)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        std::cout << "Admin got in work" << std::endl;
        if(ref.reg->done()){
            ref.end();
            return;
        }
        std::vector<Register::ProducerResult> producerResults = ref.reg->getAllProducer();
        std::vector<Register::ConsumerResult> consumerResults = ref.reg->getAllConsumer();
        ref.writeToFile(producerResults, consumerResults);
    }
}

void Admin::writeToFile(std::vector<Register::ProducerResult> producerResults,
                        std::vector<Register::ConsumerResult> consumerResults)
{
    std::ofstream outfile;
    outfile.open("out.txt", std::ios_base::app); // append instead of overwrite

    int produced = 0;
    int consumed = 0;
    
    for(auto& result : producerResults){
        outfile<<result.id<<" -> "<<result.count<<" -> "<<result.time<<" -> OFERIT\n";
        produced+=result.count;
    }

    for(auto& result : consumerResults){
        outfile<<result.id<<" -> 1 -> "<<result.time<<" -> CONSUMAT\n";
        consumed+=1;
    }

    outfile<<"VERIFICAT -> " << produced << " " << consumed <<"\n";
    outfile<<"<------------------------------------------------------>\n\n";
    outfile.close();
    std::cout<<"Admin wrote to file";
}

void Admin::end()
{
    std::ofstream outfile;
    outfile.open("out.txt", std::ios_base::app); // append instead of overwrite
    outfile<<"OK\n";
    outfile.close();
}