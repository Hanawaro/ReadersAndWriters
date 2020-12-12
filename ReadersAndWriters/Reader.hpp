#pragma once

#include <iostream>
#include <functional>

template<typename Type>
void readData(Type& data, const std::string& title, const std::string& incorrect, std::function<bool(Type)> check) {
    bool isIncorrect = true;
    do {
        std::cout << title;
        std::cin >> data;
        if (check(data))
            isIncorrect = false;
        else
            std::cout << incorrect << std::endl;
    } while(isIncorrect);
}
