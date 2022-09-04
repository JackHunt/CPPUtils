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

#include <algorithm>
#include <utility>

#include <gtest/gtest.h>

#include <CPPUtils/DataStructures/Graph.hpp>

using namespace CPPUtils::DataStructures;

template <typename T>
class GraphTestSuite : public ::testing::Test {
 public:
    using GraphType = T;

 protected:
    void SetUp() override {
        //
    }
};

using GraphTypes = ::testing::Types<
    Graphs::Graph<int>,
    Graphs::Graph<float>,
    Graphs::Graph<double>,
    Graphs::DirectedGraph<int>,
    Graphs::DirectedGraph<float>,
    Graphs::DirectedGraph<double>>;

TYPED_TEST_SUITE(GraphTestSuite, GraphTypes);

TYPED_TEST(GraphTestSuite, OutwardEdgeTest) {
    typename TypeParam::EdgeType edge(0, 1);
    ASSERT_EQ(edge.getVertex(), 0);
    ASSERT_EQ(edge.getWeight(), 1);
}

TYPED_TEST(GraphTestSuite, EmptyGraphTest) {
    TypeParam G;
    ASSERT_EQ(G.getVertexCardinality(), 0);
    ASSERT_TRUE(G.getVertices().empty());
    ASSERT_TRUE(G.getAdjacencyList(0).empty());
}

TYPED_TEST(GraphTestSuite, GraphAddVerticesTest) {
    TypeParam G;

    constexpr int V[3] = { 0, 1, 2 };
    for (const auto v : V) {
        G.addVertex(v);
    }

    ASSERT_EQ(G.getVertexCardinality(), 3);

    for (const auto v : V) {
        ASSERT_TRUE(G.vertexExists(v));
    }

    const auto G_V = G.getVertices();
    for (const auto v : V) {
        ASSERT_NE(std::find(G_V.begin(), G_V.end(), v), G_V.end());
    }
}

TYPED_TEST(GraphTestSuite, GraphRemoveVerticesTest) {
    TypeParam G;

    constexpr int V[3] = { 0, 1, 2 };
    for (const auto v : V) {
        G.addVertex(v);
    }

    G.removeVertex(0);
    G.removeVertex(2);

    const auto G_V = G.getVertices();
    ASSERT_EQ(G_V.size(), 1);
    ASSERT_EQ(G_V.at(0), 1);
}

TYPED_TEST(GraphTestSuite, GraphAddEdgesTest) {
    TypeParam G;

    if (G.isDirected()) {
        // Setup the graph.
        G.addEdge(0, 1, 0.5);
        G.addEdge(1, 0, -0.5);

        G.addEdge(2, 0, 0.1);
        G.addEdge(2, 1, -0.1);

        // Check each vertices connections.
        const auto& adj_0 = G.getAdjacencyList(0);
        ASSERT_EQ(adj_0.size(), 1);
        ASSERT_EQ(adj_0.at(0).getVertex(), 1);
        ASSERT_EQ(adj_0.at(0).getWeight(), 0.5);

        const auto& adj_1 = G.getAdjacencyList(1);
        ASSERT_EQ(adj_1.size(), 1);
        ASSERT_EQ(adj_1.at(0).getVertex(), 0);
        ASSERT_EQ(adj_1.at(0).getWeight(), -0.5);

        const auto& adj_2 = G.getAdjacencyList(2);
        ASSERT_EQ(adj_2.size(), 2);
        ASSERT_EQ(adj_2.at(0).getVertex(), 0);
        ASSERT_EQ(adj_2.at(0).getWeight(), 0.1);
        ASSERT_EQ(adj_2.at(1).getVertex(), 1);
        ASSERT_EQ(adj_2.at(1).getWeight(), -0.1);
    } else {
        // Setup the graph.
        G.addEdge(0, 1, 0.5);

        G.addEdge(2, 0, 0.1);
        G.addEdge(2, 1, -0.1);

        // Check each vertices connections.
        const auto& adj_0 = G.getAdjacencyList(0);
        ASSERT_EQ(adj_0.size(), 2);
        ASSERT_EQ(adj_0.at(0).getVertex(), 1);
        ASSERT_EQ(adj_0.at(0).getWeight(), 0.5);
        ASSERT_EQ(adj_0.at(1).getVertex(), 2);
        ASSERT_EQ(adj_0.at(1).getWeight(), 0.1);

        const auto& adj_1 = G.getAdjacencyList(1);
        ASSERT_EQ(adj_1.size(), 2);
        ASSERT_EQ(adj_1.at(0).getVertex(), 0);
        ASSERT_EQ(adj_1.at(0).getWeight(), 0.5);
        ASSERT_EQ(adj_1.at(1).getVertex(), 2);
        ASSERT_EQ(adj_1.at(1).getWeight(), -0.1);

        const auto& adj_2 = G.getAdjacencyList(2);
        ASSERT_EQ(adj_2.size(), 2);
        ASSERT_EQ(adj_2.at(0).getVertex(), 0);
        ASSERT_EQ(adj_2.at(0).getWeight(), 0.1);
        ASSERT_EQ(adj_2.at(1).getVertex(), 1);
        ASSERT_EQ(adj_2.at(1).getWeight(), -0.1);
    }
}

TYPED_TEST(GraphTestSuite, GraphRemoveEdgesTest) {
    TypeParam G;

    if (G.isDirected()) {
        // Setup the graph.
        G.addEdge(0, 1, 0.5);
        G.addEdge(1, 0, -0.5);

        G.addEdge(2, 0, 0.1);
        G.addEdge(2, 1, -0.1);

        // Remove an edge.
        G.removeEdge(2, 0);

        // Check each vertices connections.
        const auto& adj_0 = G.getAdjacencyList(0);
        ASSERT_EQ(adj_0.size(), 1);
        ASSERT_EQ(adj_0.at(0).getVertex(), 1);
        ASSERT_EQ(adj_0.at(0).getWeight(), 0.5);

        const auto& adj_1 = G.getAdjacencyList(1);
        ASSERT_EQ(adj_1.size(), 1);
        ASSERT_EQ(adj_1.at(0).getVertex(), 0);
        ASSERT_EQ(adj_1.at(0).getWeight(), -0.5);

        const auto& adj_2 = G.getAdjacencyList(2);
        ASSERT_EQ(adj_2.size(), 1);
        ASSERT_EQ(adj_2.at(0).getVertex(), 1);
        ASSERT_EQ(adj_2.at(0).getWeight(), -0.1);
    } else {
        // Setup the graph.
        G.addEdge(0, 1, 0.5);

        G.addEdge(2, 0, 0.1);
        G.addEdge(2, 1, -0.1);

        // Remove an edge.
        G.removeEdge(2, 0);

        // Check each vertices connections.
        const auto& adj_0 = G.getAdjacencyList(0);
        ASSERT_EQ(adj_0.size(), 1);
        ASSERT_EQ(adj_0.at(0).getVertex(), 1);
        ASSERT_EQ(adj_0.at(0).getWeight(), 0.5);

        const auto& adj_1 = G.getAdjacencyList(1);
        ASSERT_EQ(adj_1.size(), 2);
        ASSERT_EQ(adj_1.at(0).getVertex(), 0);
        ASSERT_EQ(adj_1.at(0).getWeight(), 0.5);
        ASSERT_EQ(adj_1.at(1).getVertex(), 2);
        ASSERT_EQ(adj_1.at(1).getWeight(), -0.1);

        const auto& adj_2 = G.getAdjacencyList(2);
        ASSERT_EQ(adj_2.size(), 1);
        ASSERT_EQ(adj_2.at(0).getVertex(), 1);
        ASSERT_EQ(adj_2.at(0).getWeight(), -0.1);
    }
}
