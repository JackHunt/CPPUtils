#include "counting_iterator.hpp"
#include "zip_iterator.hpp"
#include "split_on_delimiter.hpp"
#include "tuple_tools.hpp"

#include <iostream>

using namespace CPPUtils::Examples;

int main(int argc, char *argv[]) {
	// Counting iterator example.
	//counting_iterator_example();

	// Delimiter split example.
	//split_on_delimiter_example();

	// Zip Iterator example.
	zip_iterator_example();

	// Tuple tools example.
	//tuple_tools_example();

	std::getchar();

	return 0;
}