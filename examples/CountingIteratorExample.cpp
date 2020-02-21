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
#include <CPPUtils/Iterators/CountingIterator.hpp>

using CPPUtils::Iterators::Counter;

int main() {
    const int min = 1;
    const int max = 10;

    // Say what we are doing.
    std::cout << "Counting from " << min << " to " << max << std::endl;

    // Ground truth.
    std::cout << "An indexed loop yields the following: " << std::endl;
    std::cout << "[";
    for (int i = min; i < max; i++) {
        std::cout << i << ",";
    }
    std::cout << "]" << std::endl;

    // Test CountingIterator.
    Counter<int> c(min, max);
    std::cout << "A Counter yields the following: " << std::endl;
    std::cout << "[";
    for (auto iter = c.begin(); iter != c.end(); iter++) {
        std::cout << iter << ",";
    }
    std::cout << "]" << std::endl;

    std::getchar();
    return 0;
}