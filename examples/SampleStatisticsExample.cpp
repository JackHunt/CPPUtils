/*
BSD 3-Clause License

Copyright (c) 2020 Jack Miles Hunt
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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