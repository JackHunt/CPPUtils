#include <iostream>
#include <CPPUtils/ContainerTools/TupleTools.hpp>

using CPPUtils::ContainerTools::Tuple::tupleFor;

int main() {
    auto tuple = std::make_tuple(1, 2.0, -3, -2.5);

    const auto a = -5.0;
    tupleFor(tuple, [&a](size_t idx, auto &elem) { elem *= 2 + a; });
    tupleFor(tuple, [](size_t idx, const auto &elem) {std::cout << idx << " " << elem << std::endl; });

    std::getchar();
    return 0;
}