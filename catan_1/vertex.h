//#ifndef CPP_EX3_24_MAIN_VERTEX_H
//#define CPP_EX3_24_MAIN_VERTEX_H
//
//#include "Tile.h"
//#include <vector>
//namespace ariel {
//    using namespace std;
//    class vertex {
//    public:
//        vertex(int id,int sub_id);  //constructor
//        ~vertex();
//        bool operator==(const vertex &rhs) const;
//        vector<Tile> get_tiles();
//        void set_tiles(Tile tiles);
//        int get_id(){return id;};
//        int get_sub_id(){return sub_id;};
//        int get_player(){return player;};
//        void add_vertex(vertex v);
//        void add_edge(edge e);
//
//    private:
//        int id;
//        int sub_id;
//        vector<Tile> tiles;
//        std::vector<vertex> vertices;
//        std::vector<edge> edges;
//        int player;
//    };
//
//}
//// ...
//
//#endif // VERTEX_H


#ifndef CPP_EX3_24_MAIN_VERTEX_H
#define CPP_EX3_24_MAIN_VERTEX_H

#include <vector>
#include "Tile.h"
#include "edge.h"

namespace ariel {
    class Tile; // Forward declaration of Tile class
    class edge; // Forward declaration of edge class
    class vertex {
    public:
        vertex(int id, int sub_id);  // Constructor
        bool operator==(const vertex &rhs) const;
        std::vector<ariel::Tile> get_tiles() { return tiles; }
        void set_tiles(const std::vector<ariel::Tile>& tiles) { this->tiles = tiles; }
        int get_id() { return id; }
        int get_sub_id() { return sub_id; }
        int get_city() { return city; }
        void add_vertex(vertex v);
        void add_edge(edge e);
        std::vector<vertex>get_verrices(){return vertices;}
        void set_city(ariel::Tile::city cu );
        std::string get_player_id(){return player_id;}
        std::string set_player_id(std::string id);
    private:
        int id;
        int sub_id;
        std::vector<ariel::Tile> tiles;
        std::vector<vertex> vertices;
        std::vector<edge> edges;
        Tile::city city;
        std::string player_id;
    };
}

#endif // CPP_EX3_24_MAIN_VERTEX_H


//#ifndef VERTEX_H
//#define VERTEX_H
//
//#include "Tile.h"
//#include <vector>
//
//namespace ariel {
//    class edge; // Forward declaration
//
//    class vertex {
//    public:
//        vertex(int id, int sub_id);  //constructor
//        ~vertex() = default;
//        bool operator==(const vertex &rhs) const;
//        std::vector<ariel::Tile> get_tiles() { return tiles; }
//        void set_tiles(const std::vector<ariel::Tile>& tiles) { this->tiles = tiles; }
//        int get_id() { return id; }
//        int get_sub_id() { return sub_id; }
//        int get_player() { return player; }
//        void add_vertex(vertex v);
//        void add_edge(edge e);
//
//    private:
//        int id;
//        int sub_id;
//        std::vector<ariel::Tile> tiles;
//        std::vector<vertex> vertices;
//        std::vector<edge> edges;
//        int player;
//    };
//
//} // namespace ariel
//
//#endif // VERTEX_H
