#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class ReaderPriority {
public:
    ReaderPriority() = delete;
    
    static void DoExample(void);
private:
    static void Write(const std::string& name);
    static void Read(const std::string& name);
private:
    static std::mutex s_AcsessData;
    static std::mutex s_AcsessWriter;
    static int s_Data;
    
    static int s_CountReaders;
    static bool s_IsRunning;
};
