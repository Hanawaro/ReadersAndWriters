#include "WriterPriority.hpp"

std::mutex WriterPriority::s_AcsessData;
std::mutex WriterPriority::s_AcsessReader;
int WriterPriority::s_Data = 0;

int WriterPriority::s_CountWriters = 0;
bool WriterPriority::s_IsRunning = true;

void WriterPriority::DoExample(void) {
    std::vector<std::thread> readers(2);
    int numberOfReader = 1;
    for (auto& reader : readers) reader = std::thread(Read, std::to_string(numberOfReader++));
    
    std::vector<std::thread> writers(2);
    int numberOfWriter = 1;
    for (auto& writer : writers) writer = std::thread(Write, std::to_string(numberOfWriter++));
    
    s_CountWriters = 0;
    s_IsRunning = true;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    s_IsRunning = false;
    
    for (auto& reader: readers) reader.join();
    for (auto& writer: writers) writer.join();
}

void WriterPriority::Read(const std::string& name) {
    while (s_IsRunning) {
        s_AcsessReader.lock();
        std::cout << "Read " << s_Data << " by reader " << name << std::endl;
        s_AcsessReader.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void WriterPriority::Write(const std::string& name) {
    while (s_IsRunning) {
        s_AcsessData.lock();
        if (s_CountWriters == 0)
            s_AcsessReader.lock();
        s_CountWriters++;
        s_AcsessData.unlock();
        
        s_AcsessData.lock();
        s_Data++;
        std::cout << "Write " << s_Data << " by writer " << name << std::endl;
        s_AcsessData.unlock();
        
        s_AcsessData.lock();
        s_CountWriters--;
        if (s_CountWriters == 0)
            s_AcsessReader.unlock();
        s_AcsessData.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}
