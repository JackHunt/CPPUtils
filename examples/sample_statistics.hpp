#ifndef CPPUTILS_SAMPLE_STATISTICS_EXAMPLE
#define CPPUTILS_SAMPLE_STATISTICS_EXAMPLE

#include "../Statistics/SampleStatistics.hpp"

#include <iostream>

namespace CPPUtils::Examples {
	inline void sample_statistics_example() {
		using CPPUtils::Statistics::RunningSampleStatistics;
		using CPPUtils::Statistics::WindowedSampleStatistics;

		RunningSampleStatistics<float> running;
		WindowedSampleStatistics<float> windowed(5);

		const auto samples = {1, 2, 3, 4, 5, 6, 7, 8, 9};

		for (const auto s : samples) {
			//
		}
	}
}

#endif