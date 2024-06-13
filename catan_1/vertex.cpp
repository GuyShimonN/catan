//guyguy845@gmail.com
#include "vertex.h"
#include <iostream>
namespace ariel {

    vertex::vertex(int id, int sub_id) : id(id), sub_id(sub_id),city_type(NONE){
        // Initialize tiles as an empty vector
    }

    void vertex::add_vertex(vertex *v) {
        this->vertices.push_back(v);
//        std::cout<< "Vertex with ID " << v->get_id() << " added to vertex with ID " << this->id << std::endl;
    }

    void vertex::add_edge(edge *e) {
        edges.push_back(e);
//        std::cout << "Edge with ID " << e->get_id() << " added to vertex with ID " << this->id << std::endl;
    }
//
//    void vertex::set_city(int cu){
//        this->city=cu;
//        this->city_type = static_cast<enum city>(cu);
//    }
    std::string vertex::set_player_id(std::string id){
        this->player_id=id;
        return id;
    }
    void vertex::print_edges(){
        int size = edges.size();
//        std::cout << "Edges size: " << size <<std:: endl;
        for (int i = 0; i < size; i++) {
            std::cout << edges[i]->get_id() << std::endl;
        }
    }


} // namespace ariel