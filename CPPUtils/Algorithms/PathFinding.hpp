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

#ifndef CPP_UTILS_ALGORITHMS_PATH_FINDING
#define CPP_UTILS_ALGORITHMS_PATH_FINDING

#include <functional>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector>

#include <CPPUtils/DataStructures/Graph.hpp>

namespace CPPUtils::Algorithms {

    template<typename T, typename U = double>
    using Graph = CPPUtils::DataStructures::Graphs::Graph<T, U>;

    template<typename T, typename U = double>
    using RankedVertex = std::pair<U, T>;

    template<typename T, typename U = double>
    struct VertexCostPriority final {
        bool operator()(const RankedVertex<T, U>& a, const RankedVertex<T, U>& b) const {
            return a.first < b.first;
        }
    };

    template<typename T, typename U = double>
    using VertexPriorityQueue = std::priority_queue<RankedVertex<T, U>,
                                                    std::vector<RankedVertex<T, U>>,
                                                    VertexCostPriority<T, U>>;

    template<typename T>
    inline std::vector<T> getPath(std::map<T, T> path, const T& src, const T& sink) {
        // Start at the sink vertex.
        std::vector<T> reversedPath = { sink };

        // While there are traversals to check.
        while (!path.empty()) {
            // Get the last appended (to the output path) vertex.
            const auto& v = reversedPath.back();

            // If the last vertex added does not exist as a key, then we can 
            // traverse no further.
            if (path.find(v) == path.end()) {
                return {};
            }

            // Store the node u traversed to from v.
            const auto& u = path.at(v);
            reversedPath.push_back(u);

            // If u is the source node, we have reconstructed the path.
            if (u == src) {
                break;
            }

            // Remove for next iteration.
            path.erase(v);
        }

        // What we actually have is the path in reverse, so we just need to reverse it.
        std::reverse(reversedPath.begin(), reversedPath.end());
        return reversedPath;
    }

    template<typename T, typename U, typename V = double>
    inline std::vector<T> AStarSearch(const Graph<T, U>& G, const T& startingVertex,
                                      std::function<bool(T)> goalTest,
                                      std::function<typename V(T, T)> heuristic) {
        // Sanity check the starting vertex.
        if (!G.vertexExists(startingVertex)) {
            return {};
        }

        // Vertices to visit.
        VertexPriorityQueue<T, V> Q;

        // Vertices along the path from start to goal.
        std::map<T, T> path;

        // Cumulative costs - key set also determines visited vertices.
        std::unordered_map<T, V> cumulativeCosts;
        for (const auto& v : G.getVertices()) {
            cumulativeCosts[v] = (std::numeric_limits<V>::max)();
        }

        // Start by adding the starting vertex, with cost 0.
        Q.emplace(0.0, startingVertex);
        cumulativeCosts[startingVertex] = 0.0;

        // While we still have vertices to visit.
        while (!Q.empty()) {
            // Get the current lowest cost vertex.
            const auto v = Q.top().second;
            Q.pop();

            // Test if this vertex satisfies the goal state.
            if (goalTest(v)) {
                return getPath(path, startingVertex, v);
            }

            // Evaluate the move cost for each neighbour.
            for (const auto& n : G.getAdjacencyList(v)) {
                // Compute the cost of moving to neighbour u of v.
                const auto& u = n.getVertex();
                const auto cost = cumulativeCosts.at(v) + n.getWeight();

                // If this neighbour cost is lower.
                if (cost < cumulativeCosts.at(u)) {
                    // Push the vertex with the sum of these two costs.
                    Q.emplace(cost, u);

                    // Update cost.
                    cumulativeCosts[u] = cost + heuristic(v, u);

                    // Add the vertex traversal - think of a breadcrumb path.
                    path[u] = v;
                }
            }
        }
        return {};
    }

    template<typename T, typename U = double>
    inline std::vector<T> dijkstra(const Graph<T, U>& G, const T& src, const T& sink) {
        // Goal state test; if a given vertex is the sink vertex.
        auto g = [sink](const T& a) -> bool {
            return a == sink;
        };

        // A constant heuristic of 0.
        auto h = [](const T&, const T&) -> double {
            return 0;
        };

        // Run A* with the above goal test and nought heuristic.
        return AStarSearch<T, U>(G, src, g, h);
    }
}

#endif