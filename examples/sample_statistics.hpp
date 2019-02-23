#ifndef CPPUTILS_SAMPLE_STATISTICS_EXAMPLE
#define CPPUTILS_SAMPLE_STATISTICS_EXAMPLE

#include "../Statistics/SampleStatistics.hpp"

#include <iostream>

namespace CPPUtils::Examples {
	inline void sample_statistics_example() {
		using CPPUtils::Statistics::RunningSampleStatistics;
		using CPPUtils::Statistics::WindowedSampleStatistics;
		using CPPUtils::Statistics::getSampleStatistics;

		RunningSampleStatistics<float> running;
		WindowedSampleStatistics<float> windowed(5);

		const std::vector<float> samples = {1, 2, 3, 4, 5, 6, 7, 8, 9};

		unsigned short idx = 0;
		for (const auto s : samples) {
			running.provideSample(s);
			windowed.provideSample(s);

			std::cout << "Sample #: " << idx << std::endl;
			
			const auto res = running.getEstimate();
			std::cout << "RunningSampleStatistics: \n \t Mean: " << res.first
				      << " Variance: " << res.second << std::endl;

			const auto res2 = windowed.getEstimate();
			std::cout << "WindowedSampleStatistics: \n \t Mean: " << res2.first
				      << " Variance: " << res2.second << std::endl << std::endl;

			idx++;
		}

		const auto res = getSampleStatistics(samples);
		std::cout << "getSampleStatistics: \n \t Mean: " << res.first 
			      << " Variance: " << res.second << std::endl;
	}
}

#endif