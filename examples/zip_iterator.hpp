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

        auto zipper = ZipperFactory<IntList, FloatMap, BoolList>()(a, b, c);

		// Iterate.
        for (const auto [i, f, b] : zipper) {
            std::cout << *i << ", ";
            std::cout << "[" << f->first << ", " << f->second << "], ";
            std::cout << *b << std::endl;
		}
	}
}

#endif