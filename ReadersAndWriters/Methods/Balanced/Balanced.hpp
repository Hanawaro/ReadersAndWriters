#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

class Balanced {
public:
    Balanced() = delete;
    
    static void DoExample(void);
private:
    static void Write(const std::string& name);
    static void Read(const std::string& name);
private:
    static std::mutex s_AcsessData;
    static std::condition_variable s_ReaderCondition;
    static std::condition_variable s_WriterCondition;
    
    static int s_Data;
    
    static int s_CountReaders;
    static int s_CountWriters;
    static bool s_IsRunning;
};
