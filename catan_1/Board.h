//#ifndef BOARD_H
//#define BOARD_H
//
//#include <vector>
//#include "Tile.h"
//#include "vertex.h"
//#include "edge.h"
//
//namespace ariel {
//    class Board {
//    public:
//        Board();
//        void generateBoard();
//        const std::vector<Tile>& getTiles() const;
//        void printBoard() const;  // New method to print the board
//
//    private:
//        std::vector<Tile> tiles;
//        std::vector<vertex> vertices;
//        std::vector<edge> edges;
//        void initializeTiles();
//        void assignNumbers();
//        void initializeVertices();
//        void initializeEdges();
//        void initialize_tile_to_vertex();
//        void initialize_vertex_to_vertex();
//    };
//}
//
//#endif // BOARD_H


#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"
#include "vertex.h"
#include "edge.h"

namespace ariel {
    class Board {
    public:
        Board();
        void generateBoard();
        const std::vector<Tile>& getTiles() const;
        void printBoard() const;  // New method to print the board

    private:
        std::vector<Tile> tiles;
        std::vector<vertex> vertices;
        std::vector<edge> edges;
        void initializeTiles();
        void assignNumbers();
        void initializeVertices();
        void initializeEdges();
        void initialize_tile_to_vertex();
        void initialize_vertex_to_vertex();
    };
}

#endif // BOARD_H
