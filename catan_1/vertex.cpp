#include "vertex.h"

namespace ariel {

    vertex::vertex(int id, int sub_id) : id(id), sub_id(sub_id), city(2) {
        // Initialize tiles as an empty vector
    }

    void vertex::add_vertex(ariel::vertex *v) {
        this->vertices.push_back(v);
    }

    void vertex::add_edge(ariel::edge *e) {
        this->edges.push_back(e);
    }
    void vertex::set_city(int cu){
        this->city=cu;
    }
    std::string vertex::set_player_id(std::string id){
        this->player_id=id;
        return id;
    }

} // namespace ariel