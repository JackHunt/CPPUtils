#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <functional>
#include <queue>
#include <map>
#include <unordered_set>
#include <CPPUtils/DataStructures/Graph.hpp>

namespace CPPUtils::Algorithms {

    template<typename T>
    using RankedVertex = std::pair<double, T>;

    template<typename T>
    struct VertexCostPriority final {
        bool operator()(const RankedVertex<T>& a,
            const RankedVertex<T>& b) const {
            return a.first < b.first;
        }
    };

    template<typename T>
    using VertexPriorityQueue = std::priority_queue<RankedVertex<T>,
                                                    std::vector<RankedVertex<T>>,
                                                    VertexCostPriority<T>>;

    template<typename T>
    inline std::vector<T> getPath(std::map<T, T> path, const T& src, const T& sink) {
        // Start at the sink vertex.
        std::vector<T> reversedPath = { sink };

        // While there are traversals to check.
        while (!path.empty()) {
            // Get the last appended (to the output path) vertex.
            const T& v = reversedPath.back();

            // If the last vertex added does not exist as a key, then we can 
            // traverse no further.
            if (path.find(v) == path.end()) {
                return {};
            }

            // Store the node u traversed to from v.
            const T& u = path.at(v);
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

    template<typename T>
    inline std::vector<T> AStarSearch(const Graph<T>& G, const T& startingVertex,
                                      std::function<bool(T)> goalTest,
                                      std::function<double(T, T)> heuristic) {
        // Sanity check the starting vertex.
        if (!G.vertexExists(startingVertex)) {
            return {};
        }

        // Vertices to visit.
        VertexPriorityQueue<T> Q;

        // Vertices along the path from start to goal.
        std::map<T, T> path;

        // Cumulative costs - key set also determines visited vertices.
        std::unordered_map<T, double> cumulativeCosts;
        for (const auto v : G.getVertices()) {
            cumulativeCosts[v] = std::numeric_limits<double>::max();
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

    template<typename T>
    inline std::vector<T> dijkstra(const Graph<T>& G, const T& src, const T& sink) {
        // Goal state test; if a given vertex is the sink vertex.
        auto goal = [sink](const T& a) -> bool {
            return a == sink;
        };

        // A constant heuristic of 0.
        auto h = [](const T&, const T&) -> double {
            return 0;
        };

        // Run A* with the above goal test and nought heuristic.
        return AStarSearch<T>(G, src, goal, h);
    }
}

#endif