#ifndef CPP_EX3_24_MAIN_VERTEX_H
#define CPP_EX3_24_MAIN_VERTEX_H
//guyguy845@gmail.com
#include <vector>
#include "edge.h"
#include <string>
namespace ariel {
    class Tile; // Forward declaration of Tile class
    class edge; // Forward declaration of edge class
    class vertex {
    public:
        enum city { SETTLEMENT, CITY, NONE };
        vertex(int id, int sub_id);  // Constructor
        bool operator==(const vertex &rhs) const;
        std::vector<Tile*>&get_tiles() { return tiles; }
        void add_tiles(Tile* tile) { this->tiles.push_back(tile); }
        int get_id() { return id; }
        int get_sub_id() { return sub_id; }
//        int get_city() { return city; }
        void add_vertex(vertex *v);
        void add_edge(edge *e);
        std::vector<vertex*>&get_vertices(){return vertices;}
//        void set_city(int cu );  // Change city type to int
        std::string get_player_id(){return player_id;}
        std::string set_player_id(std::string id);
        std::vector<edge*>&get_edges() { return edges; }
        void print_edges();
        city get_city_type() { return city_type; }
        void set_city_type(city c) { city_type = c; }

    private:
        int id;
        int sub_id;
        std::vector<Tile*> tiles;  // Change to Tile pointers
        std::vector<vertex*> vertices;
        std::vector<edge*> edges;
//        int city;  // Change city type to int
        std::string player_id;
        enum city city_type;
    };
}

#endif // CPP_EX3_24_MAIN_VERTEX_H