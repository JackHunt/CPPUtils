/*
BSD 3-Clause License

Copyright (c) 2019 Jack Miles Hunt
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

#ifndef CPP_UTILS_SAMPLE_STATISTICS_FILE
#define CPP_UTILS_SAMPLE_STATISTICS_FILE

#include <utility>
#include <deque>
#include <numeric>

namespace CPPUtils::Statistics {
    template<typename T, bool withVariance = true>
    class RunningSampleStatistics {
    protected:
        T mean;
        T variance;
        unsigned long n;

    public:
        RunningSampleStatistics() :
            mean(0),
            variance(0),
            n(0) {
            //
        }

        virtual ~RunningSampleStatistics() {
            //
        }

        auto getEstimate() const {
            if constexpr (withVariance) {
                return std::make_pair(mean, variance);
            }
            return mean;
        }

        unsigned long getSampleCount() const {
            return n;
        }

        virtual void provideSample(T sample) {
            if (n == 0) {
                mean = sample;
                n++;
                return;
            }

            const auto mu = mean + (sample - mean) / static_cast<T>(n);
            if constexpr (withVariance) {
                variance = (sample - mean) * (sample - mu);
            }
            mean = mu;

            n++;
        }
    };

    template<typename T, bool withVariance = true>
    class WindowedSampleStatistics : public RunningSampleStatistics<T, withVariance> {
    protected:
        std::deque<T> samples;
        const unsigned int windowSize;

    public:
        WindowedSampleStatistics(unsigned int windowSize) :
            RunningSampleStatistics<T, withVariance>(),
            windowSize(windowSize) {
            //
        }

        virtual ~WindowedSampleStatistics() {
            //
        }

        virtual void provideSample(T sample) override {
            if (n >= windowSize) {
                samples.pop_front();
            }
            samples.push_back(sample);
            n = samples.size();

            mean = std::accumulate(samples.begin(), samples.end(), 0);
            mean /= static_cast<T>(n);

            if constexpr (withVariance) {
                if (n > 1) {
                    variance = std::accumulate(samples.begin(), samples.end(), 0,
                                               [this](auto acc, auto x) {
                        return std::move(acc) + std::pow(x - mean, 2);
                    });
                    variance /= static_cast<T>(n - 1);
                }
            }
        }
    };

    template<typename T, bool withVariance = true>
    inline auto getSampleStatistics(const T& data) {
        const auto n = static_cast<T::value_type>(data.size());
        const auto mu = std::accumulate(data.begin(), data.end(), 0) / n;

        if constexpr (!withVariance) {
            return mu;
        }
        
        auto sigma = std::accumulate(data.begin(), data.end(), 0,
                                     [mu](auto acc, auto sample) {
            return std::move(acc) + (sample - mu);
        });
        sigma /= (n - 1);

        return std::make_pair(mu, sigma);
    }
}

#endif