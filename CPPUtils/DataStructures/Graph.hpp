#ifndef CPP_UTILS_DATA_STRUCTURES_GRAPH
#define CPP_UTILS_DATA_STRUCTURES_GRAPH

#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

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
            assert(weight >= 0);
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
    class Graph final {
    private:
        // Controls how edges are added - bidirectional or not.
        const bool directed;

        // An adjacency list (value) for each vertex (key).
        std::unordered_map<T, AdjacencyList<T, U>> edges;

        void removeAdjacency(const T& a, AdjacencyList<T, U>& s) {
            auto shouldRemove = [&a](const OutwardEdge<T, U>& c) {
                return a == c.getVertex();
            };

            // Remove b from a's adjacency set.
            s.erase(std::remove_if(s.begin(), s.end(), shouldRemove));
        }

    public:
        Graph(bool directed = false) :
            directed(directed) {
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
            // Remove the edge from a to b.
            removeAdjacency(a, edges.at(b));

            // If undirected, also remove the edge from b to a.
            if (!directed) {
                removeAdjacency(b, edges.at(a));
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

}

#endif