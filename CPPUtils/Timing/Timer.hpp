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