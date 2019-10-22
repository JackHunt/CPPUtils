#include <iostream>
#include <string>

#include <CPPUtils/StringManipulation/Tokenizing.hpp>

using CPPUtils::StringManipulation::splitOnDelimiter;

int main() {
    const std::string str("This,is,a,string,I like the number 23");

    // Say what we are doing.
    std::cout << "The following string split on the delimiter \',\':" << std::endl;
    std::cout << "\"" << str << "\"" << std::endl;
    std::cout << "Is the following:" << std::endl;

    // Split and print.
    const auto out = splitOnDelimiter(str, ',');
    for (const auto &token : out) {
        std::cout << token << std::endl;
    }

    std::getchar();
    return 0;
}