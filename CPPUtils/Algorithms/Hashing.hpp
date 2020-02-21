#ifndef CPP_UTILS_ALGORITHMS_HASHING
#define CPP_UTILS_ALGORITHMS_HASHING

namespace CPPUtils::Algorithms {

    template<typename T = int>
    inline T cantorHash(T x, T y) {
        return (x + y) * (x + y + 1) / 2 + y;
    }

}

#endif