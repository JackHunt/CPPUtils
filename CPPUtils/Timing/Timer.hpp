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

#ifndef CPP_UTILS_TIMER
#define CPP_UTILS_TIMER

#include <chrono>
#include <stdexcept>
#include <vector>
#include <utility>

namespace CPPUtils::Timing {
    class Timer {
    public:
        using Clock = std::chrono::steady_clock;
        using Timestamp = std::chrono::time_point<Clock>;
        
    protected:
        Timestamp latestTic;
        Timestamp latestToc;
        std::vector<std::pair<Timestamp, Timestamp>> ticTocs;

    public:
        Timer() {
            //
        }

        virtual ~Timer() {
            //
        }

        virtual void tic() {
            latestTic = Clock::now();
        }

        virtual void toc() {
            latestToc = Clock::now();
            if (latestToc <= latestTic) {
                throw std::runtime_error("Clock appears to be non-monotonic.");
            }
            ticTocs.emplace_back(latestTic, latestToc);
        }

        void reset() {
            latestTic = Timestamp();
            latestToc = Timestamp();
            ticTocs.clear();
        }

        Timestamp getLatestTic() const {
            return latestTic;
        }

        Timestamp getLatestToc() const {
            return latestToc;
        }

        const decltype(ticTocs)& getTicTocs() const {
            return ticTocs;
        }

        const std::vector<Timestamp> getElapsedTimes(bool average = false) const {
            //
        }
    };

    template<typename T>
    inline std::vector<unsigned long long> getElapsed(const std::vector<std::pair<T, T>>& ticTocs) {
        //
    }
}

#endif