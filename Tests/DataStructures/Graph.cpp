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

#define BOOST_TEST_MODULE GraphTests
#include <algorithm>
#include <utility>

#include <boost/test/included/unit_test.hpp>

#include <CPPUtils/DataStructures/Graph.hpp>

using namespace CPPUtils::DataStructures;

BOOST_AUTO_TEST_SUITE(GraphTestSuite)

/*
 * Test basic edge class.
 */
BOOST_AUTO_TEST_CASE(OutwardEdgeTest) {
    Graphs::OutwardEdge<int, int> edge(0, 1);
    BOOST_CHECK(edge.getVertex() == 0);
    BOOST_CHECK(edge.getWeight() == 1);
}

/*
 * Test empty graph creation.
 */
template<typename T>
void EmptyGraphTestImpl() {
    T G;
    BOOST_CHECK(G.getVertexCardinality() == 0);
    BOOST_CHECK(G.getVertices().empty());
    BOOST_CHECK(G.getAdjacencyList(0).empty());
}

BOOST_AUTO_TEST_CASE(EmptyGraphTest) {
    EmptyGraphTestImpl<Graphs::Graph<int>>();
    EmptyGraphTestImpl<Graphs::Graph<float>>();
    EmptyGraphTestImpl<Graphs::Graph<double>>();
}

BOOST_AUTO_TEST_CASE(EmptyDirectedGraphTest) {
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

    BOOST_CHECK(G.getVertexCardinality() == 3);

    for (const auto v : V) {
        BOOST_CHECK(G.vertexExists(v));
    }

    const auto G_V = G.getVertices();
    for (const auto v : V) {
        BOOST_CHECK(std::find(G_V.begin(), G_V.end(), v) != G_V.end());
    }
}

BOOST_AUTO_TEST_CASE(GraphAddVerticesTest) {
    GraphAddVerticesTestImpl<Graphs::Graph<int>>();
    GraphAddVerticesTestImpl<Graphs::Graph<float>>();
    GraphAddVerticesTestImpl<Graphs::Graph<double>>();
}

BOOST_AUTO_TEST_CASE(DirectedGraphAddVerticesTest) {
    GraphAddVerticesTestImpl<Graphs::DirectedGraph<int>>();
    GraphAddVerticesTestImpl<Graphs::DirectedGraph<float>>();
    GraphAddVerticesTestImpl<Graphs::DirectedGraph<double>>();
}

BOOST_AUTO_TEST_SUITE_END()