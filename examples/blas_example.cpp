/*
BSD 3-Clause License

Copyright (c) 2023 Jack Miles Hunt
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
#include <CPPUtils/LinearAlgebra/BLAS.hpp>

using namespace CPPUtils::LinearAlgebra::BLAS;

void gemmExample() {
  std::array<float, 9> A = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::array<float, 9> B = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<float, 9> C;

  // C = A * B
  GEMMCallConfig cfg(3, 3, 3);
  gemm(A.data(), B.data(), C.data(), cfg);

  for (auto e : C) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

void axpyExample() {
  std::array<float, 4> Y = {1, 1, 1, 1};
  std::array<float, 4> X = {1, 2, 3, 4};
  const float alpha = 2.0;

  AXPYCallConfig cfg(4, alpha);
  axpy(Y.data(), X.data(), cfg);

  for (auto e : Y) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

void scalExample() {
  std::array<float, 4> Y = {1, 1, 1, 1};
  const float alpha = 2.0;

  SCALCallConfig cfg(4, alpha);
  scal(Y.data(), cfg);

  for (auto e : Y) {
    std::cout << e << " ";
  }
  std::cout << std::endl; 
}

int main() {
  //gemmExample();
  //axpyExample();
  scalExample();
  return 0;
}