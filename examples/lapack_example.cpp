/*
BSD 3-Clause License

Copyright (c) 2022 Jack Miles Hunt
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

#include <array>
#include <iostream>
#include <vector>

#include <CPPUtils/LinearAlgebra/LAPACK.hpp>

using namespace CPPUtils::LinearAlgebra::LAPACK;

void check_lu_status(const GETRFExecutionStatus& status) {
    std::cout << std::endl;
    std::cout << "SUCCESS: " << status.success() << std::endl;

    if (status.illegal_value()) {
        std::cout << "Illegal value at index: " << status.illegal_value_index() << std::endl;
    }

    if (status.singular_value()) {
        const auto i = status.singular_value_diagonal_index();
        std::cout << "Singular value at index [" << i << ", " << i << "]" << std::endl;
    }
}

void getrf_example() {
    std::vector<float> A(16, 1.0);

    GETRFCallConfig cfg(4, 4);
    const auto status = getrf<float>(A, cfg);

    for (unsigned short i = 0; i < 16; i++) {
        std::cout << A[i] << " ";
        if ((i + 1) % 4 == 0) {
            std::cout << std::endl;
        }
    }

    check_lu_status(status);
}

void gesv_example() {
    std::array<float, 9> A = {1, 1, 1, 3, 1, -3, 1, -2 -5};
    std::array<float, 3> B = {1, 5, 10};

    GESVCallConfig cfg(3);
    const auto status = gesv<float>(A, B, cfg);

    std::cout << "L and U Factors:" << std::endl;
    for (unsigned short i = 0; i < 9; i++) {
        std::cout << A[i] << " ";
        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
    }

    std::cout << "Solution:" << std::endl;
    for (unsigned short i = 0; i < 3; i++) {
        std::cout << B[i] << " ";
    }
    std::cout << std::endl;

    check_lu_status(status);
}

int main() {
    //getrf_example();
    gesv_example();
    return 0;
}