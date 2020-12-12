#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class WriterPriority {
public:
    WriterPriority() = delete;
    
    static void DoExample(void);
private:
    static void Write(const std::string& name);
    static void Read(const std::string& name);
private:
    static std::mutex s_AcsessData;
    static std::mutex s_AcsessReader;
    static int s_Data;
    
    static int s_CountWriters;
    static bool s_IsRunning;
};
