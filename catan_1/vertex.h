#ifndef CPP_EX3_24_MAIN_VERTEX_H
#define CPP_EX3_24_MAIN_VERTEX_H

#include <vector>
#include "edge.h"
#include <string>
namespace ariel {
    class Tile; // Forward declaration of Tile class
    class edge; // Forward declaration of edge class
    class vertex {
    public:
        vertex(int id, int sub_id);  // Constructor
        bool operator==(const vertex &rhs) const;
        std::vector<Tile*> get_tiles() { return tiles; }
        void set_tiles(const std::vector<Tile*>& tiles) { this->tiles = tiles; }
        int get_id() { return id; }
        int get_sub_id() { return sub_id; }
        int get_city() { return city; }
        void add_vertex(vertex *v);
        void add_edge(edge *e);
        std::vector<vertex*>get_verrices(){return vertices;}
        void set_city(int cu );  // Change city type to int
        std::string get_player_id(){return player_id;}
        std::string set_player_id(std::string id);
        std::vector<edge*> get_edges() { return edges; }
    private:
        int id;
        int sub_id;
        std::vector<Tile*> tiles;  // Change to Tile pointers
        std::vector<vertex*> vertices;
        std::vector<edge*> edges;
        int city;  // Change city type to int
        std::string player_id;
    };
}

#endif // CPP_EX3_24_MAIN_VERTEX_H