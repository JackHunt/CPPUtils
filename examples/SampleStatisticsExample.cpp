#include <iostream>
#include <vector>
#include <CPPUtils/Statistics/SampleStatistics.hpp>

using CPPUtils::Statistics::getSampleStatistics;
using CPPUtils::Statistics::RunningSampleStatistics;
using CPPUtils::Statistics::WindowedSampleStatistics;

int main() {
    RunningSampleStatistics<float> running;
    WindowedSampleStatistics<float> windowed(5);

    const std::vector<float> samples = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    unsigned short idx = 0;
    for (const auto s : samples) {
        running.provideSample(s);
        windowed.provideSample(s);

        std::cout << "Sample #: " << idx << std::endl;
            
        const auto res = std::get<std::pair<float, float>>(running.getEstimate());
        std::cout << "RunningSampleStatistics: \n \t Mean: " << res.first
                  << " Variance: " << res.second << std::endl;

        const auto res2 = std::get<std::pair<float, float>>(windowed.getEstimate());
        std::cout << "WindowedSampleStatistics: \n \t Mean: " << res2.first
                  << " Variance: " << res2.second << std::endl << std::endl;

        idx++;
    }

    const auto res = getSampleStatistics(samples);
    std::cout << "getSampleStatistics: \n \t Mean: " << res.first 
              << " Variance: " << res.second << std::endl;

    std::getchar();
    return 0;
}