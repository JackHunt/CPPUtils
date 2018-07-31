#ifndef CPPUTILS_ZIP_ITERATOR_EXAMPLE
#define CPPUTILS_ZIP_ITERATOR_EXAMPLE

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iterator>
#include "../Iterators/ZipIterator.hpp"

namespace CPPUtils::Examples {
	inline void zip_iterator_example() {
		//using CPPUtils::Iterators::ZipIterator;
        using CPPUtils::Iterators::ZipperFactory;

		// Type aliases, just for readability.
		using IntList = std::vector<int>;
		using BoolList = std::vector<bool>;
		using FloatMap = std::map<std::string, float>;

		// Make some data.
        IntList a = { 0, 1, 2, 3, 4, 5};
		FloatMap b;
		b["z"] = 3.0;
		b["x"] = 1.0;
		b["y"] = 2.0;
		BoolList c = {true, false, true, true};

        auto zip = ZipperFactory<IntList, FloatMap, BoolList>()(a, b, c);

		// Iterate.
        for (auto iter = zip.begin(); iter != zip.end(); iter++) {
            std::cout << *std::get<0>(*iter) << ", ";
            std::cout << "[" << std::get<1>(*iter)->first << ", " << std::get<1>(*iter)->second << "], ";
            std::cout << *std::get<2>(*iter) << std::endl;
		}
	}
}

#endif