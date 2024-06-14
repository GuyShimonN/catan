//guyguy845@gmail.com
#include "vertex.h"
#include <iostream>
namespace ariel {

    vertex::vertex(int id, int sub_id) : id(id), sub_id(sub_id),city_type(NONE){
        // Initialize tiles as an empty vector
    }

    void vertex::add_vertex(vertex *v) {
        this->vertices.push_back(v);
    }

    void vertex::add_edge(edge *e) {
        edges.push_back(e);
    }

    std::string vertex::set_player_id(std::string id){
        this->player_id=id;
        return id;
    }
    void vertex::print_edges(){
        int size = edges.size();
        for (int i = 0; i < size; i++) {
            std::cout << edges[i]->get_id() << std::endl;
        }
    }


} // namespace ariel