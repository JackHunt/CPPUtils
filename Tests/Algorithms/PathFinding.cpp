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


#include <map>
#include <vector>

#include <gtest/gtest.h>
#include <gtest/gtest-matchers.h>

#include <CPPUtils/Algorithms/PathFinding.hpp>

using namespace CPPUtils::Algorithms;
using namespace CPPUtils::DataStructures::Graphs;


class PathFindingTestSuite : public ::testing::Test {
 protected:
    std::map<int, int> traversals, traversals_no_path;
    DirectedGraph<int> G;

    void SetUp() override {
        traversals = {
            {4, 3},
            {3, 2},
            {2, 1}
        };

        traversals_no_path = {
            {4, 3},
            {3, 3},
            {2, 1}
        };

        constexpr double w = 0.1;
        G.addEdge(1, 2, w);
        G.addEdge(2, 3, w);
        G.addEdge(3, 4, w);
        G.addEdge(4, 5, w);
        G.addEdge(2, 4, w);
    }
};

TEST_F(PathFindingTestSuite, VertexCostPriorityTest) {
    RankedVertex<int> a(0.1, 1);
    RankedVertex<int> b(0.2, 1);

    ASSERT_TRUE(VertexCostPriority<int>()(a, b));
    ASSERT_FALSE(VertexCostPriority<int>()(b, a));
}

TEST_F(PathFindingTestSuite, GetPathTest) {
    const auto path = getPath(traversals, 1, 4);
    const std::vector<int> true_path = { 1, 2, 3, 4 };
    ASSERT_EQ(path.size(), true_path.size());
    //ASSERT_THAT(path, testing::ElementsAre(true_path));
}

TEST_F(PathFindingTestSuite, GetPathTestEmpty) {
    const auto path = getPath(traversals_no_path, 1, 4);
    ASSERT_TRUE(path.empty());
}

TEST_F(PathFindingTestSuite, GetPathInvalidSourceTest) {
    const auto path = getPath(traversals, 5, 4);
    ASSERT_TRUE(path.empty());
}

TEST_F(PathFindingTestSuite, GetPathInvalidSinkTest) {
    const auto path = getPath(traversals, 1, 5);
    ASSERT_TRUE(path.empty());
}

TEST_F(PathFindingTestSuite, AStarSearchTest) {
    auto heuristic = [](int a, int b) -> double {
        return a % b == 0 ? 0.0 : 1.0;
    };

    auto goal = [](int v) {
        return v == 5;
    };

    const auto path = AStarSearch<int, double, double>(G, 1, goal, heuristic);
    const std::vector<int> true_path = { 1, 2, 4, 5 };
    ASSERT_EQ(path.size(), true_path.size());
    //ASSERT_THAT(path, ContainerEq(true_path));
}

TEST_F(PathFindingTestSuite, AStarSearchNeverReachGoalTest) {
    auto heuristic = [](int a, int b) -> double {
        return 0;
    };

    auto goal = [](int v) {
        return false;
    };

    const auto path = AStarSearch<int, double, double>(G, 1, goal, heuristic);
    ASSERT_TRUE(path.empty());
}

TEST_F(PathFindingTestSuite, AStarSearchInvalidStartTest) {
    auto heuristic = [](int a, int b) -> double {
        return a % b == 0 ? 0.0 : 1.0;
    };

    auto goal = [](int v) {
        return v == 5;
    };

    const auto path = AStarSearch<int, double, double>(G, 6, goal, heuristic);
    ASSERT_TRUE(path.empty());
}

TEST_F(PathFindingTestSuite, DijkstraTest) {
    // Remove the 2, 4 edge.
    G.removeEdge(2, 4);

    G.addEdge(1, 4, 1.5); // Shorter, but higher cost.

    const auto path = dijkstra<int, double>(G, 1, 5);

    const std::vector<int> true_path = { 1, 2, 3, 4, 5 };
    ASSERT_EQ(path.size(), true_path.size());

    //ASSERT_THAT(path, ElementsAre(true_path));
}

TEST_F(PathFindingTestSuite, DijkstraInvalidStartTest) {
    const auto path = dijkstra<int, double>(G, 6, 5);
    ASSERT_TRUE(path.empty());
}

TEST_F(PathFindingTestSuite, DijkstraInvalidEndTest) {
    const auto path = dijkstra<int, double>(G, 1, 6);
    ASSERT_TRUE(path.empty());
}
