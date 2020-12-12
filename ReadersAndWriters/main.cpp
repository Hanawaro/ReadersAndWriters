#include "Methods/Balanced/Balanced.hpp"
#include "Methods/ReaderPriority/ReaderPriority.hpp"
#include "Methods/WriterPriority/WriterPriority.hpp"

#include "Methods/Method.hpp"

#include "Reader.hpp"

int main(int argc, const char * argv[]) {
    const std::string exitCommand = "exit";
    
    bool isExit = false;
    while (!isExit) {
        std::string type;
        readData<std::string>(type, "Введите метод решения: ", " Неверный метод", [&](std::string data) {
            return (Method::isBalanced(data) || Method::isReaderPriority(data) || Method::isWriterPriority(data) || exitCommand == data);
        });
        
        if (Method::isBalanced(type)) {
            Balanced::DoExample();
        } else if (Method::isWriterPriority(type)) {
            WriterPriority::DoExample();
        } else if (Method::isReaderPriority(type)) {
            ReaderPriority::DoExample();
        } else if (exitCommand == type) {
            isExit = true;
        }
    }
    
}
