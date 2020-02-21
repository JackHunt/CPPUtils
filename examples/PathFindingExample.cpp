/*
BSD 3-Clause License

Copyright (c) 2020 Jack Miles Hunt
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

#include <iostream>
#include <CPPUtils/Algorithms/Hashing.hpp>

using CPPUtils::Algorithms::cantorHash;

enum class CellState : unsigned short {
    START,
    OPEN,
    WALL,
    INVALID
};

struct Cell final {
    unsigned int x;
    unsigned int y;
    CellState state;
    unsigned int id;

    Cell() :
        x(0),
        y(0),
        state(CellState::INVALID),
        id(0) {
        //
    }

    Cell(unsigned int x,
        unsigned int y,
        CellState state,
        unsigned int id) :
        x(x),
        y(y),
        state(state),
        id(id) {
        //
    }
};

namespace std {
    /*
     * As Cell is used as a key in various map types within
     * Graph, a specialisation of std::hash is required.
     *
     * As we have a simple 2D space in which the nodes of the graph
     * live, a pairing function (in this case the Cantor Hash) over
     * their 2D coordinates is sufficient.
     */
    template<>
    struct hash<Cell> {
        size_t operator()(const Cell& cell) const {
            return cantorHash(cell.x, cell.y);
        }
    };
}

#include <CPPUtils/Algorithms/PathFinding.hpp>

using CPPUtils::DataStructures::Graphs::Graph;
using CPPUtils::Algorithms::AStarSearch;
using CPPUtils::Algorithms::dijkstra;

static constexpr unsigned short H = 5;
static constexpr unsigned short W = 6;
static constexpr char M[H][W] = {{'X', 'O', 'X', 'X', 'X', 'X'},
                                 {'X', 'O', 'X', 'O', 'O', 'X'},
                                 {'X', 'O', 'X', 'O', 'X', 'X'},
                                 {'X', 'O', 'O', 'O', 'S', 'X'},
                                 {'X', 'X', 'X', 'X', 'X', 'X'}};

inline bool operator==(const Cell& lhs, const Cell& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator<(const Cell& lhs, const Cell& rhs) {
    return lhs.id < rhs.id;
}

inline std::ostream& operator<<(std::ostream& lhs, const Cell& rhs) {
    lhs << "Row: " << rhs.y << " Col: " << rhs.x;
    return lhs;
}

Graph<Cell> buildGraph() {
    // For parsing a given symbol into it's associated cell state.
    auto symbolState = [](unsigned int x, unsigned int y) -> CellState {
        switch (M[y][x]) {
        case 'S':
            return CellState::START;
        case 'O':
            return CellState::OPEN;
        case 'X':
            return CellState::WALL;
        default:
            throw std::runtime_error("ERROR: Unknown symbol!");
        }
    };

    Graph<Cell> G;

    // For each symbol/cell in the maze.
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            // For each neighbour of the current cell.
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    // If the same vertex, skip.
                    if (i == j) {
                        continue;
                    }

                    // Neighbour coordinates.
                    const int neighY = y + i;
                    const int neighX = x + j;

                    // Check bounds.
                    if (neighY < 0 || neighY >= H || neighX < 0 || neighX >= W) {
                        continue;
                    }

                    // Make current cell.
                    const unsigned int idx = y * W + x;
                    const Cell cell(x, y, symbolState(x, y), idx);

                    // Make neighbour cell.
                    const unsigned int neighIdx = neighY * W + neighX;
                    const Cell neighCell(neighX, neighY, symbolState(neighX, neighY), neighIdx);

                    // Uniform cost for nodes of differing states.
                    auto cost = std::numeric_limits<double>::max();

                    // Same state, or start and open state - zero cost.
                    if (cell.state == neighCell.state ||
                        (cell.state == CellState::OPEN && neighCell.state == CellState::START) ||
                        (cell.state == CellState::START && neighCell.state == CellState::OPEN)) {
                        cost = 0.0;
                    }

                    // Add edge.
                    G.addEdge(cell, neighCell, cost);
                }
            }
        }
    }

    return G;
}

int main() {
    // Print the map.
    std::cout << "Map:" << std::endl;
    for (unsigned short i = 0; i < H; i++) {
        for (unsigned short j = 0; j < W; j++) {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Build a graph.
    const auto G = buildGraph();

    // Find the starting cell.
    const auto vertices = G.getVertices();
    const auto S = std::find_if(vertices.begin(), 
                                vertices.end(),
                                [](const Cell& c) -> bool {
        return c.state == CellState::START;
    });

    // Check that a starting cell exists.
    if (S == vertices.end()) {
        std::cout << "No starting cell present!" << std::endl;
        return 0;
    }

    /*
     * A* Algorithm.
     */
    auto goalTest = [](const Cell& c) -> bool {
        // Check if an open cell.
        if (c.state != CellState::OPEN) {
            return false;
        }

        // Check horizontal boundaries.
        if (c.x == 0 || c.x == W - 1) {
            return true;
        }

        // Check vertical boundaries.
        if (c.y == 0 || c.y == H - 1) {
            return true;
        }

        return false;
    };

    auto heuristic = [](const Cell& a, const Cell& b) -> double {
        return std::sqrt(std::pow(b.x - a.x, 2.0) + std::pow(b.y - a.y, 2.0));
    };

    std::cout << "A* path from starting cell:" << std::endl;
    const auto aStarPath = AStarSearch<Cell>(G, *S, goalTest, heuristic);
    for (const auto& v : aStarPath) {
        std::cout << v << std::endl;
    }
    std::cout << std::endl;

    /*
     * Disjkstra's Algorithm.
     */
    // Find a target cell.
    const auto E = std::find_if(vertices.begin(), vertices.end(),
        [](const Cell& c) -> bool {
        return c.x == 1 && c.y == 0;
    });

    // Check the maze contains a wall cell.
    if (E == vertices.end()) {
        std::cout << "No wall cell present in map!" << std::endl;
        return 0;
    }

    std::cout << "Dijkstra's Algorithm path from starting cell:" << std::endl;
    const auto dijkstraPath = dijkstra<Cell>(G, *S, *E);
    for (const auto& v : dijkstraPath) {
        std::cout << v << std::endl;
    }

    std::getchar();
    return 0;
}