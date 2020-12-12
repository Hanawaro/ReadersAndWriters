#pragma once

#include <iostream>

struct Method {
    Method() = delete;
    
    static inline bool isReaderPriority(const std::string& type) {
        for (int i = 0; i < s_Count; i++)
            if (tolower(type) == tolower(s_ReaderPriority[i]))
                return true;
        return false;
    }
    
    static inline bool isWriterPriority(const std::string& type) {
        for (int i = 0; i < s_Count; i++)
            if (tolower(type) == tolower(s_WriterPriority[i]))
                return true;
        return false;
    }
    
    static inline bool isBalanced(const std::string& type) {
        for (int i = 0; i < s_Count; i++)
            if (tolower(type) == tolower(s_Balanced[i]))
                return true;
        return false;
    }
private:
    static inline std::string tolower(std::string data) {
        for (auto& ch : data)
            ch = std::tolower(ch);
        return data;
    }
private:
    static const size_t s_Count = 2;
    static const std::string s_ReaderPriority[2];
    static const std::string s_WriterPriority[2];
    static const std::string s_Balanced[2];
};

