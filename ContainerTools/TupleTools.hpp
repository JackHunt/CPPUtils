#ifndef CPP_UTILS_TUPLE_TOOLS
#define CPP_UTILS_TUPLE_TOOLS

#include <tuple>
#include <functional>
#include <cstddef>

namespace CPPUtils::ContainerTools::Tuple {
    template<typename T, typename F, std::size_t ...S>
    constexpr void tupleFor(T &tuple, const F &func, std::index_sequence<S...>) {
        (func(std::integral_constant<size_t, S>{}, std::get<S>(tuple)),...);
    }

    template<typename ...T, typename F>
    constexpr void tupleFor(std::tuple<T...> &tuple, const F &func) {
        tupleFor(tuple, std::forward<const F>(func), std::make_index_sequence<sizeof...(T)>{});
    }
}

#endif