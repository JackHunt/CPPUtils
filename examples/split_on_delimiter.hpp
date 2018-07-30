#ifndef CPPUTILS_DELIM_SPLIT_EXAMPLE
#define CPPUTILS_DELIM_SPLIT_EXAMPLE

#include "../StringManipulation/Tokenizing.hpp"

#include <iostream>
#include <string>

namespace CPPUtils::Examples {
	inline void split_on_delimiter_example() {
		using CPPUtils::StringManipulation::splitOnDelimiter;

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
	}
}

#endif