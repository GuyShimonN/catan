//guyguy845@gmail.com
#include "Tile.h"

namespace ariel {
    Tile::Tile(Type type, int id)
            :  id(id) ,type(type){}

    Tile::Type Tile::getType() const {
        return type;
    }

    int Tile::getNumber() const {
        return number;
    }

    Resource::Type Tile::getResource() const {
        switch (type) {
            case FOREST:
                return Resource::WOOD;
            case HILL:
                return Resource::BRICK;
            case PASTURE:
                return Resource::WOOL;
            case FIELD:
                return Resource::GRAIN;
            case MOUNTAIN:
                return Resource::ORE;
            default:
                return Resource::NONE;
        }
    }

    void Tile::setNumber(int number) {
        this->number = number;
    }

    void Tile::addvertex(vertex *v) {
        this->vertices.push_back(v);
    }

    std::string Tile::toString() const {
        std::string s;
        switch (type) {
            case FOREST:
                s = "FOREST";
                break;
            case HILL:
                s = "HILL";
                break;
            case PASTURE:
                s = "PASTURE";
                break;
            case FIELD:
                s = "FIELD";
                break;
            case MOUNTAIN:
                s = "MOUNTAIN";
                break;
            default:
                s = "DESERT";
                break;
        }
        if (s=="DESERT")
            return s;
        s = s + " " + std::to_string(this->number);
        return s;
    }

    void Tile::add_edge(edge *edge) {
        this->edges.push_back(edge);
    }
    std::vector<vertex*>& Tile::getVertices()  {
        return const_cast<std::vector<vertex*>&>(vertices); // Define this method to return the vertices
    }
}