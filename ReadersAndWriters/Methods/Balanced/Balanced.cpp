#include "Balanced.hpp"

std::mutex Balanced::s_AcsessData;
std::condition_variable Balanced::s_ReaderCondition;
std::condition_variable Balanced::s_WriterCondition;

int Balanced::s_Data = 0;

int Balanced::s_CountReaders = 0;
int Balanced::s_CountWriters = 0;
bool Balanced::s_IsRunning = true;

void Balanced::DoExample(void) {
    std::vector<std::thread> readers(2);
    int numberOfReader = 1;
    for (auto& reader : readers) reader = std::thread(Read, std::to_string(numberOfReader++));
    
    std::vector<std::thread> writers(2);
    int numberOfWriter = 1;
    for (auto& writer : writers) writer = std::thread(Write, std::to_string(numberOfWriter++));
    
    s_CountReaders = 0;
    s_CountReaders = 0;
    s_IsRunning = true;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    s_IsRunning = false;
    
    for (auto& reader: readers) reader.join();
    for (auto& writer: writers) writer.join();
}

void Balanced::Read(const std::string& name) {
    while (s_IsRunning) {
        
        std::unique_lock<std::mutex> lock(s_AcsessData, std::defer_lock);
        
        lock.lock();
        if (s_CountWriters > 0)
            s_ReaderCondition.wait(lock, [](){ return s_CountWriters == 0; });
        s_CountReaders++;
        lock.unlock();
        
        lock.lock();
        std::cout << "Read " << s_Data << " by reader " << name << std::endl;
        lock.unlock();
        
        lock.lock();
        s_CountReaders--;
        s_WriterCondition.notify_all();
        s_ReaderCondition.notify_all();
        lock.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}


void Balanced::Write(const std::string& name) {
    while (s_IsRunning) {
        
        std::unique_lock<std::mutex> lock(s_AcsessData, std::defer_lock);
        
        lock.lock();
        s_CountWriters++;
        if (s_CountReaders > 0)
            s_WriterCondition.wait(lock, [](){ return s_CountReaders == 0; });
        lock.unlock();
        
        lock.lock();
        s_Data++;
        std::cout << "Write " << s_Data << " by writer " << name << std::endl;
        lock.unlock();
        
        lock.lock();
        s_CountWriters--;
        s_WriterCondition.notify_all();
        s_ReaderCondition.notify_all();
        lock.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}
