#ifndef CPPUTILS_COUNTING_ITERATOR_EXAMPLE
#define CPPUTILS_COUNTING_ITERATOR_EXAMPLE

#include "../Iterators/CountingIterator.hpp"
#include <iostream>

namespace CPPUtils::Examples {
	inline void counting_iterator_example() {
		using CPPUtils::Iterators::CountingIterator;

		const int min = 1;
		const int max = 10;

		// Say what we are doing.
		std::cout << "Counting from " << min << " to " << max << std::endl;

		// Ground truth.
		std::cout << "An indexed loop yields the following: " << std::endl;
		std::cout << "[";
		for (int i = min; i < max; i++) {
			std::cout << i << ",";
		}
		std::cout << "]" << std::endl;

		// Test CountingIterator.
		CountingIterator<int> begin(min);
		CountingIterator<int> end(max);
		std::cout << "A CountingIterator yields the following: " << std::endl;
		std::cout << "[";
		for (auto iter = begin; iter != end; iter++) {
			std::cout << iter << ",";
		}
		std::cout << "]" << std::endl;
	}
}

#endif