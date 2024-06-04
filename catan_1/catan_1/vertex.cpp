////
//// Created by guy on 5/31/24.
////
//
//#include "vertex.h"
//namespace ariel {
//
//    vertex::vertex(int id, int sub_id) : id(id), sub_id(sub_id) {
//        this->player = NULL;
//        this->tiles = NULL;
//    }
//
//    void vertex::add_vertex(ariel::vertex v) {
//        this->vertices.push_back(v);
//    }
//
//    void vertex::add_edge(ariel::edge e) {
//        this->edges.push_back(e);
//    }
//}

#include "vertex.h"

namespace ariel {

    vertex::vertex(int id, int sub_id) : id(id), sub_id(sub_id), player(0) {
        // Initialize tiles as an empty vector
    }

    void vertex::add_vertex(ariel::vertex v) {
        this->vertices.push_back(v);
    }

    void vertex::add_edge(ariel::edge e) {
        this->edges.push_back(e);
    }

} // namespace ariel
