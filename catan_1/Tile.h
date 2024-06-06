//#ifndef TILE_H
//#define TILE_H
//
//#include "Resource.hpp"
//#include "edge.h"
//#include "vertex.h"
//#include "Player.hpp"
//#include <vector>
//namespace ariel {
//
//    class Tile {
//    public:
//        enum Type { FOREST, HILL, PASTURE, FIELD, MOUNTAIN, DESERT };
//        enum city { CITY, SETTLEMENT, NONE };
//        Tile(Type type, int id);
//        int id;
//        Type getType() const;
//        int getNumber() const;
//        Resource::Type getResource() const;
//        void setNumber(int number);
//        void addvertex(vertex v);
//
//    private:
//        Type type;
//        int number;
//
//        std::vector<std::pair<Player,city>> players;
//        std::vector<vertex> vertices;
//        std::vector<edge> edges;
//    };
//
//} // namespace ariel
//
//#endif // TILE_H
#ifndef TILE_H
#define TILE_H

#include "Resource.hpp"
#include "edge.h"
#include "Player.hpp"
#include <vector>

namespace ariel {
    class vertex; // Forward declaration
    class edge; // Forward declaration
    class Tile {
    public:
        enum Type { FOREST, HILL, PASTURE, FIELD, MOUNTAIN, DESERT };
        enum city { SETTLEMENT, CITY, NONE };
        Tile(Type type, int id);
        int id;
        Type getType() const;
        int getNumber() const;
        Resource::Type getResource() const;
        void setNumber(int number);
        void addvertex(vertex* v);
        void add_edge(edge* edge);
        std::string toString() const;

    private:
        Type type;
        int number;

        std::vector<std::pair<Player*,city>> players;
        std::vector<vertex*> vertices;
        std::vector<edge*> edges;
    };

} // namespace ariel

#endif // TILE_H
