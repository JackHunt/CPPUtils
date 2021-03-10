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

#ifndef CPP_UTILS_DATA_STRUCTURES_GRAPH
#define CPP_UTILS_DATA_STRUCTURES_GRAPH

#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <utility>
#include <vector>

namespace CPPUtils::DataStructures::Graphs {

    template<typename T, typename U = double>
    class OutwardEdge final {
    private:
        T vertex;
        U weight;

    public:
        OutwardEdge(const T& vertex, U weight) :
            vertex(vertex),
            weight(weight) {
            //
        }

        const T& getVertex() const {
            return vertex;
        }

        U getWeight() const {
            return weight;
        }
    };

    template<typename T, typename U = double>
    using AdjacencyList = std::vector<OutwardEdge<T, U>>;

    template<typename T, typename U = double>
    class Graph {
    protected:
        // Controls how edges are added - bidirectional or not.
        bool directed;

        // An adjacency list (value) for each vertex (key).
        std::unordered_map<T, AdjacencyList<T, U>> edges;

        void removeAdjacency(const T& a, AdjacencyList<T, U>& s) {
            if (s.empty()) {
                return;
            }

            // Remove b from a's adjacency set.
            s.erase(std::remove_if(s.begin(), s.end(),
                [&a](const OutwardEdge<T, U>& c) {
                    return a == c.getVertex();
                }));
        }

    public:
        Graph() :
            directed(false) {
            //
        }

        bool vertexExists(const T& a) const {
            return edges.find(a) != edges.end();
        }

        void addVertex(const T& a) {
            if (!vertexExists(a)) {
                edges[a] = AdjacencyList<T, U>();
            }
        }

        void removeVertex(const T& a) {
            // If it doesn't exist, early out.
            if (!vertexExists(a)) {
                return;
            }

            // Remove the vertex from all other vertices adjacency lists.
            for (auto& s : edges) {
                removeAdjacency(a, s.second);
            }

            // Remove the vertex from the map.
            edges.erase(a);
        }

        void addEdge(const T& a, const T& b, U weight) {
            // Add a if it doesn't exist.
            if (!vertexExists(a)) {
                addVertex(a);
            }

            // Ditto for b.
            if (!vertexExists(b)) {
                addVertex(b);
            }

            // Add edge from a to b.
            edges.at(a).emplace_back(b, weight);

            // If undirected add an edge back from b to a.
            if (!directed) {
                edges.at(b).emplace_back(a, weight);
            }
        }

        void removeEdge(const T& a, const T& b) {
            // Early out if either doesn't exist.
            if (!vertexExists(a) || !vertexExists(b)) {
                return;
            }

            // Remove the edge from a to b.
            removeAdjacency(b, edges.at(a));

            // If undirected, also remove the edge from b to a.
            if (!directed) {
                removeAdjacency(a, edges.at(b));
            }
        }

        size_t getVertexCardinality() const {
            return edges.size();
        }

        const AdjacencyList<T, U>& getAdjacencyList(const T& a) const {
            // If the vertex doesn't exist, return an empty adjacency list.
            if (!vertexExists(a)) {
                static const AdjacencyList<T, U> empty;
                return empty;
            }

            return edges.at(a);
        }

        const std::vector<T> getVertices() const {
            // Pull out the map keys.
            std::vector<T> vertices;
            std::transform(edges.begin(), edges.end(), std::back_inserter(vertices),
                           [](const std::pair<T, AdjacencyList<T, U>>& a) -> T {
                               return a.first;
                           });
            return vertices;
        }
    };

    template<typename T, typename U = double>
    class DirectedGraph : public Graph<T, U> {
    public:
        DirectedGraph() {
            directed = true;
        }
    };
}

#endif