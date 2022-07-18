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

#ifndef CPP_UTILS_ALGORITHMS_GRADIENT_OPTIMIZERS
#define CPP_UTILS_ALGORITHMS_GRADIENT_OPTIMIZERS

#include <vector>

namespace CPPUtils::Algorithms {

  template<typename T>
  class GradientOptimizerBase {
  protected:
    const T convergence_threshold;
    const unsigned int max_iterations;
    unsigned int current_iteration;

    std::vector<T> loss_history;

    virtual T step() = 0;

  public:
    GradientOptimizerBase(T convergence_threshold,
                          unsigned int max_iterations) :
      convergence_threshold(convergence_threshold),
      max_iterations(max_iterations),
      current_iteration(0) {
      // Reserve for losses.
      loss_history.reserve(max_iterations);
    }

    virtual ~GradientOptimizerBase() = 0;

    virtual bool hasConverged() const {
      return !loss_history.empty() && loss_history.back() <= convergence_threshold;
    }

    virtual T getConvergenceThreshold() const {
      return convergence_threshold;
    }

    virtual unsigned int getMaxIterations() const {
      return max_iterations;
    }

    virtual const std::vector<T>& getLossHistory() const {
      return loss_history;
    }

    virtual void reset() {
      loss_history.clear();
      current_iteration = 0;
    }
  };

}

#endif