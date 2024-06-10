//
// Created by guy on 5/31/24.
//
//guyguy845@gmail.com
#include "edge.h"
namespace ariel {

    edge::edge(int id, int sub_id) {
        this->id = id;
        this->sub_id = sub_id;
        this->player_id = "";
    }

    bool edge::operator==(const edge &rhs) const {
        return id == rhs.id &&
               sub_id == rhs.sub_id;
    }

    void edge::add_neighbor(edge* e) {
        this->neighbors.push_back(e);
    }

    void edge::set_player_id(std::string id) {
        this->player_id = id;
    }

}// namespace ariel