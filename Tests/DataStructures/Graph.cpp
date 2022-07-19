/*
BSD 3-Clause License

Copyright (c) 2021 Jack Miles Hunt
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


/*
 * Test basic edge class.
 */
TEST(GraphTestSuite, OutwardEdgeTest) {
    Graphs::OutwardEdge<int, int> edge(0, 1);
    EXPECT_EQ(edge.getVertex(), 0);
    EXPECT_EQ(edge.getWeight(), 1);
}

/*
 * Test empty graph creation.
 */
template<typename T>
void EmptyGraphTestImpl() {
    T G;
    EXPECT_EQ(G.getVertexCardinality(), 0);
    EXPECT_TRUE(G.getVertices().empty());
    EXPECT_TRUE(G.getAdjacencyList(0).empty());
}

TEST(GraphTestSuite, EmptyGraphTest) {
    EmptyGraphTestImpl<Graphs::Graph<int>>();
    EmptyGraphTestImpl<Graphs::Graph<float>>();
    EmptyGraphTestImpl<Graphs::Graph<double>>();
}

TEST(GraphTestSuite, EmptyDirectedGraphTest) {
    EmptyGraphTestImpl<Graphs::Graph<int>>();
    EmptyGraphTestImpl<Graphs::Graph<float>>();
    EmptyGraphTestImpl<Graphs::Graph<double>>();
}

/*
 * Test adding vertices.
 */
template<typename T>
void GraphAddVerticesTestImpl() {
    T G;

    constexpr int V[3] = { 0, 1, 2 };
    for (const auto v : V) {
        G.addVertex(v);
    }

    EXPECT_EQ(G.getVertexCardinality(), 3);

    for (const auto v : V) {
        EXPECT_TRUE(G.vertexExists(v));
    }

    const auto G_V = G.getVertices();
    for (const auto v : V) {
        EXPECT_NE(std::find(G_V.begin(), G_V.end(), v), G_V.end());
    }
}

TEST(GraphTestSuite, GraphAddVerticesTest) {
    GraphAddVerticesTestImpl<Graphs::Graph<int>>();
    GraphAddVerticesTestImpl<Graphs::Graph<float>>();
    GraphAddVerticesTestImpl<Graphs::Graph<double>>();
}

TEST(GraphTestSuite, DirectedGraphAddVerticesTest) {
    GraphAddVerticesTestImpl<Graphs::DirectedGraph<int>>();
    GraphAddVerticesTestImpl<Graphs::DirectedGraph<float>>();
    GraphAddVerticesTestImpl<Graphs::DirectedGraph<double>>();
}

/*
 * Test removing vertices.
 */
template<typename T>
void GraphRemoveVerticesTestImpl() {
    T G;

    constexpr int V[3] = { 0, 1, 2 };
    for (const auto v : V) {
        G.addVertex(v);
    }

    G.removeVertex(0);
    G.removeVertex(2);

    const auto G_V = G.getVertices();
    EXPECT_EQ(G_V.size(), 1);
    EXPECT_EQ(G_V.at(0), 1);
}

TEST(GraphTestSuite, GraphRemoveVerticesTest) {
    GraphRemoveVerticesTestImpl<Graphs::Graph<int>>();
    GraphRemoveVerticesTestImpl<Graphs::Graph<float>>();
    GraphRemoveVerticesTestImpl<Graphs::Graph<double>>();
}

TEST(GraphTestSuite, DirectedGraphRemoveVerticesTest) {
    GraphRemoveVerticesTestImpl<Graphs::DirectedGraph<int>>();
    GraphRemoveVerticesTestImpl<Graphs::DirectedGraph<float>>();
    GraphRemoveVerticesTestImpl<Graphs::DirectedGraph<double>>();
}

/*
 * Test adding edges.
 */
TEST(GraphTestSuite, GraphAddEdgesTest) {
    Graphs::Graph<int> G;

    // Setup the graph.
    G.addEdge(0, 1, 0.5);

    G.addEdge(2, 0, 0.1);
    G.addEdge(2, 1, -0.1);

    // Check each vertices connections.
    const auto& adj_0 = G.getAdjacencyList(0);
    EXPECT_EQ(adj_0.size(), 2);
    EXPECT_EQ(adj_0.at(0).getVertex(), 1);
    EXPECT_EQ(adj_0.at(0).getWeight(), 0.5);
    EXPECT_EQ(adj_0.at(1).getVertex(), 2);
    EXPECT_EQ(adj_0.at(1).getWeight(), 0.1);

    const auto& adj_1 = G.getAdjacencyList(1);
    EXPECT_EQ(adj_1.size(), 2);
    EXPECT_EQ(adj_1.at(0).getVertex(), 0);
    EXPECT_EQ(adj_1.at(0).getWeight(), 0.5);
    EXPECT_EQ(adj_1.at(1).getVertex(), 2);
    EXPECT_EQ(adj_1.at(1).getWeight(), -0.1);

    const auto& adj_2 = G.getAdjacencyList(2);
    EXPECT_EQ(adj_2.size(), 2);
    EXPECT_EQ(adj_2.at(0).getVertex(), 0);
    EXPECT_EQ(adj_2.at(0).getWeight(), 0.1);
    EXPECT_EQ(adj_2.at(1).getVertex(), 1);
    EXPECT_EQ(adj_2.at(1).getWeight(), -0.1);
}

TEST(GraphTestSuite, DirectedGraphAddEdgesTest) {
    Graphs::DirectedGraph<int> G;

    // Setup the graph.
    G.addEdge(0, 1, 0.5);
    G.addEdge(1, 0, -0.5);

    G.addEdge(2, 0, 0.1);
    G.addEdge(2, 1, -0.1);

    // Check each vertices connections.
    const auto& adj_0 = G.getAdjacencyList(0);
    EXPECT_EQ(adj_0.size(), 1);
    EXPECT_EQ(adj_0.at(0).getVertex(), 1);
    EXPECT_EQ(adj_0.at(0).getWeight(), 0.5);

    const auto& adj_1 = G.getAdjacencyList(1);
    EXPECT_EQ(adj_1.size(), 1);
    EXPECT_EQ(adj_1.at(0).getVertex(), 0);
    EXPECT_EQ(adj_1.at(0).getWeight(), -0.5);

    const auto& adj_2 = G.getAdjacencyList(2);
    EXPECT_EQ(adj_2.size(), 2);
    EXPECT_EQ(adj_2.at(0).getVertex(), 0);
    EXPECT_EQ(adj_2.at(0).getWeight(), 0.1);
    EXPECT_EQ(adj_2.at(1).getVertex(), 1);
    EXPECT_EQ(adj_2.at(1).getWeight(), -0.1);
}

/*
 * Test removing edges.
 */
TEST(GraphTestSuite, GraphRemoveEdgesTest) {
    Graphs::Graph<int> G;

    // Setup the graph.
    G.addEdge(0, 1, 0.5);

    G.addEdge(2, 0, 0.1);
    G.addEdge(2, 1, -0.1);

    // Remove an edge.
    G.removeEdge(2, 0);

    // Check each vertices connections.
    const auto& adj_0 = G.getAdjacencyList(0);
    EXPECT_EQ(adj_0.size(), 1);
    EXPECT_EQ(adj_0.at(0).getVertex(), 1);
    EXPECT_EQ(adj_0.at(0).getWeight(), 0.5);

    const auto& adj_1 = G.getAdjacencyList(1);
    EXPECT_EQ(adj_1.size(), 2);
    EXPECT_EQ(adj_1.at(0).getVertex(), 0);
    EXPECT_EQ(adj_1.at(0).getWeight(), 0.5);
    EXPECT_EQ(adj_1.at(1).getVertex(), 2);
    EXPECT_EQ(adj_1.at(1).getWeight(), -0.1);

    const auto& adj_2 = G.getAdjacencyList(2);
    EXPECT_EQ(adj_2.size(), 1);
    EXPECT_EQ(adj_2.at(0).getVertex(), 1);
    EXPECT_EQ(adj_2.at(0).getWeight(), -0.1);
}

TEST(GraphTestSuite, DirectedGraphRemoveEdgesTest) {
    Graphs::DirectedGraph<int> G;

    // Setup the graph.
    G.addEdge(0, 1, 0.5);
    G.addEdge(1, 0, -0.5);

    G.addEdge(2, 0, 0.1);
    G.addEdge(2, 1, -0.1);

    // Remove an edge.
    G.removeEdge(2, 0);

    // Check each vertices connections.
    const auto& adj_0 = G.getAdjacencyList(0);
    EXPECT_EQ(adj_0.size(), 1);
    EXPECT_EQ(adj_0.at(0).getVertex(), 1);
    EXPECT_EQ(adj_0.at(0).getWeight(), 0.5);

    const auto& adj_1 = G.getAdjacencyList(1);
    EXPECT_EQ(adj_1.size(), 1);
    EXPECT_EQ(adj_1.at(0).getVertex(), 0);
    EXPECT_EQ(adj_1.at(0).getWeight(), -0.5);

    const auto& adj_2 = G.getAdjacencyList(2);
    EXPECT_EQ(adj_2.size(), 1);
    EXPECT_EQ(adj_2.at(0).getVertex(), 1);
    EXPECT_EQ(adj_2.at(0).getWeight(), -0.1);
}
