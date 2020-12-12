#include "ReaderPriority.hpp"

std::mutex ReaderPriority::s_AcsessData;
std::mutex ReaderPriority::s_AcsessWriter;
int ReaderPriority::s_Data = 0;

int ReaderPriority::s_CountReaders = 0;
bool ReaderPriority::s_IsRunning = true;

void ReaderPriority::DoExample(void) {
    std::vector<std::thread> readers(2);
    int numberOfReader = 1;
    for (auto& reader : readers) reader = std::thread(Read, std::to_string(numberOfReader++));
    
    std::vector<std::thread> writers(2);
    int numberOfWriter = 1;
    for (auto& writer : writers) writer = std::thread(Write, std::to_string(numberOfWriter++));
    
    s_CountReaders = 0;
    s_IsRunning = true;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    s_IsRunning = false;
    
    for (auto& reader: readers) reader.join();
    for (auto& writer: writers) writer.join();
}

void ReaderPriority::Read(const std::string& name) {
    while (s_IsRunning) {
        s_AcsessData.lock();
        if (s_CountReaders == 0)
            s_AcsessWriter.lock();
        s_CountReaders++;
        s_AcsessData.unlock();
        
        s_AcsessData.lock();
        std::cout << "Read " << s_Data << " by reader " << name << std::endl;
        s_AcsessData.unlock();
        
        s_AcsessData.lock();
        s_CountReaders--;
        if (s_CountReaders == 0)
            s_AcsessWriter.unlock();
        s_AcsessData.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}


void ReaderPriority::Write(const std::string& name) {
    while (s_IsRunning) {
        s_AcsessWriter.lock();
        s_Data++;
        std::cout << "Write " << s_Data << " by writer " << name << std::endl;
        s_AcsessWriter.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}
