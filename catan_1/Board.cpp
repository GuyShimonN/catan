
//Board::Board() {
//    generateBoard();
//}
//
//void Board::generateBoard() {
//    initializeTiles();
//    assignNumbers();
//}
//
//void Board::initializeTiles() {
//    tiles = {
//            Tile(Tile::FOREST, 0), Tile(Tile::FOREST, 0), Tile(Tile::FOREST, 0), Tile(Tile::FOREST, 0),
//            Tile(Tile::HILL, 0), Tile(Tile::HILL, 0), Tile(Tile::HILL, 0),
//            Tile(Tile::PASTURE, 0), Tile(Tile::PASTURE, 0), Tile(Tile::PASTURE, 0), Tile(Tile::PASTURE, 0),
//            Tile(Tile::FIELD, 0), Tile(Tile::FIELD, 0), Tile(Tile::FIELD, 0), Tile(Tile::FIELD, 0),
//            Tile(Tile::MOUNTAIN, 0), Tile(Tile::MOUNTAIN, 0), Tile(Tile::MOUNTAIN, 0),
//            Tile(Tile::DESERT, 0)
//    };
//
//    std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine(static_cast<unsigned>(time(0))));
//}
//
//void Board::assignNumbers() {
//    std::vector<int> numbers = { 2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12 };
//    auto it = numbers.begin();
//
//    for (auto& tile : tiles) {
//        if (tile.getType() != Tile::DESERT) {
//            tile.setNumber(*it);
//            ++it;
//        }
//    }
//}
//
//const std::vector<Tile>& Board::getTiles() const {
//    return tiles;
//}
//
//void Board::printBoard() const {
//    for (const auto& tile : tiles) {
//        std::cout << "Tile Type: ";
//        switch (tile.getType()) {
//            case Tile::FOREST: std::cout << "Forest"; break;
//            case Tile::HILL: std::cout << "Hill"; break;
//            case Tile::PASTURE: std::cout << "Pasture"; break;
//            case Tile::FIELD: std::cout << "Field"; break;
//            case Tile::MOUNTAIN: std::cout << "Mountain"; break;
//            case Tile::DESERT: std::cout << "Desert"; break;
//        }
//        std::cout << ", Number: " << tile.getNumber() << std::endl;
//    }
//}

#include <iomanip>
#include "Board.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
namespace ariel {

    Board::Board() {
        generateBoard();
    }

    void Board::generateBoard() {
        initializeTiles();
        assignNumbers();
        initialize_tile_to_vertex();
        initialize_vertex_to_vertex();
        initialize_edge_to_edge();
    }

    void Board::initializeTiles() {
        // Create a vector with the exact number of each Tile::Type
        std::vector<Tile::Type> tileTypes = {
                Tile::FOREST, Tile::FOREST, Tile::FOREST, Tile::FOREST,
                Tile::HILL, Tile::HILL, Tile::HILL,
                Tile::PASTURE, Tile::PASTURE, Tile::PASTURE, Tile::PASTURE,
                Tile::FIELD, Tile::FIELD, Tile::FIELD, Tile::FIELD,
                Tile::MOUNTAIN, Tile::MOUNTAIN, Tile::MOUNTAIN,
                Tile::DESERT
        };

        // Shuffle the tileTypes vector
        std::shuffle(tileTypes.begin(), tileTypes.end(),
                     std::default_random_engine(static_cast<unsigned>(std::time(0))));

        // Clear the existing tiles
        tiles.clear();

        // Create a Tile for each type in tileTypes and add it to the tiles vector
        int p =tileTypes.size();
        for (int i = 0; i <p; ++i) {
            Tile tile =Tile(tileTypes[i], i + 1);
            tiles.push_back(&tile);
        }
        initializeVertices();
    }

    void Board::assignNumbers() {
        std::vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
        auto it = numbers.begin();

        for (auto &tile: tiles) {
            if (tile->getType() != Tile::DESERT) {
                tile->setNumber(*it);
                ++it;
            }
        }
    }

    const std::vector<Tile*> &Board::getTiles() const {
        return tiles;
    }


    void Board::printBoard() const {
        std::cout << "**************** CATAN BOARD ****************" << std::endl;
        std::cout << "sae        "<< tiles[2]->toString()<<"  "<< tiles[1]->toString()<<"  "<< tiles[0]->toString()<<"      sea"<<std::endl;
        std::cout << "sae   "<< tiles[6]->toString()<<"  "<< tiles[5]->toString()<<"  "<< tiles[4]->toString()<<"  "<< tiles[3]->toString()<<"  sea"<<std::endl;
        std::cout << "sae   "<< tiles[11]->toString()<<"  "<< tiles[10]->toString()<<"  "<< tiles[9]->toString()<<"  "<< tiles[8]->toString()<<"  "<< tiles[7]->toString()<<"  sea"<<std::endl;
        std::cout << "sae   "<< tiles[15]->toString()<<"  "<< tiles[14]->toString()<<"  "<< tiles[13]->toString()<<"  "<< tiles[12]->toString()<<"  sea"<<std::endl;
        std::cout << "sae        "<< tiles[18]->toString()<<"  "<< tiles[17]->toString()<<"  "<< tiles[16]->toString()<<"      sea"<<std::endl;


        // Print the tiles


        // Print the footer
        std::cout << "**********************************************" << std::endl;
    }
    void Board::initializeVertices() {
        // Clear the existing vertices
        vertices.clear();

        // Create a vertex for each possible intersection of tiles
        int id = 1;
        for (int i = 0; i < 54; ++i) {
            vertex v = vertex(i, id);
            vertices.push_back(&v);

        }
        initializeEdges();
    }

    void Board::initializeEdges() {
        // Clear the existing edges
        edges.clear();

        // Create an edge for each possible edge between tiles
        int id = 1;
        for (int i = 0; i < 72; ++i) {
            edge e = edge(i, id);
            edges.push_back(&e);
        }
    }

    void Board::initialize_tile_to_vertex() {
        tiles[0]->addvertex(vertices[0]);
        tiles[0]->addvertex(vertices[1]);
        tiles[0]->addvertex(vertices[2]);
        tiles[0]->addvertex(vertices[9]);
        tiles[0]->addvertex(vertices[8]);
        tiles[0]->addvertex(vertices[7]);

        tiles[0]->add_edge(edges[0]);
        tiles[0]->add_edge(edges[1]);
        tiles[0]->add_edge(edges[2]);
        tiles[0]->add_edge(edges[3]);
        tiles[0]->add_edge(edges[4]);
        tiles[0]->add_edge(edges[5]);

        tiles[1]->addvertex(vertices[2]);
        tiles[1]->addvertex(vertices[3]);
        tiles[1]->addvertex(vertices[4]);
        tiles[1]->addvertex(vertices[11]);
        tiles[1]->addvertex(vertices[10]);
        tiles[1]->addvertex(vertices[9]);

        tiles[1]->add_edge(edges[6]);
        tiles[1]->add_edge(edges[7]);
        tiles[1]->add_edge(edges[8]);
        tiles[1]->add_edge(edges[9]);
        tiles[1]->add_edge(edges[10]);
        tiles[1]->add_edge(edges[2]);

        tiles[2]->addvertex(vertices[4]);
        tiles[2]->addvertex(vertices[5]);
        tiles[2]->addvertex(vertices[6]);
        tiles[2]->addvertex(vertices[13]);
        tiles[2]->addvertex(vertices[12]);
        tiles[2]->addvertex(vertices[11]);

        tiles[2]->add_edge(edges[11]);
        tiles[2]->add_edge(edges[12]);
        tiles[2]->add_edge(edges[13]);
        tiles[2]->add_edge(edges[14]);
        tiles[2]->add_edge(edges[15]);
        tiles[2]->add_edge(edges[8]);

        tiles[3]->addvertex(vertices[7]);
        tiles[3]->addvertex(vertices[8]);
        tiles[3]->addvertex(vertices[15]);
        tiles[3]->addvertex(vertices[17]);
        tiles[3]->addvertex(vertices[18]);
        tiles[3]->addvertex(vertices[19]);

        tiles[3]->add_edge(edges[16]);
        tiles[3]->add_edge(edges[4]);
        tiles[3]->add_edge(edges[17]);
        tiles[3]->add_edge(edges[18]);
        tiles[3]->add_edge(edges[19]);
        tiles[3]->add_edge(edges[20]);

        tiles[4]->addvertex(vertices[8]);
        tiles[4]->addvertex(vertices[9]);
        tiles[4]->addvertex(vertices[10]);
        tiles[4]->addvertex(vertices[19]);
        tiles[4]->addvertex(vertices[20]);
        tiles[4]->addvertex(vertices[21]);

        tiles[4]->add_edge(edges[3]);
        tiles[4]->add_edge(edges[10]);
        tiles[4]->add_edge(edges[21]);
        tiles[4]->add_edge(edges[22]);
        tiles[4]->add_edge(edges[23]);
        tiles[4]->add_edge(edges[17]);

        tiles[5]->addvertex(vertices[10]);
        tiles[5]->addvertex(vertices[11]);
        tiles[5]->addvertex(vertices[12]);
        tiles[5]->addvertex(vertices[21]);
        tiles[5]->addvertex(vertices[22]);
        tiles[5]->addvertex(vertices[23]);

        tiles[5]->add_edge(edges[9]);
        tiles[5]->add_edge(edges[15]);
        tiles[5]->add_edge(edges[24]);
        tiles[5]->add_edge(edges[25]);
        tiles[5]->add_edge(edges[26]);
        tiles[5]->add_edge(edges[21]);

        tiles[6]->addvertex(vertices[12]);
        tiles[6]->addvertex(vertices[13]);
        tiles[6]->addvertex(vertices[14]);
        tiles[6]->addvertex(vertices[23]);
        tiles[6]->addvertex(vertices[24]);
        tiles[6]->addvertex(vertices[25]);

        tiles[6]->add_edge(edges[14]);
        tiles[6]->add_edge(edges[27]);
        tiles[6]->add_edge(edges[28]);
        tiles[6]->add_edge(edges[29]);
        tiles[6]->add_edge(edges[30]);
        tiles[6]->add_edge(edges[24]);

        tiles[7]->addvertex(vertices[16]);
        tiles[7]->addvertex(vertices[17]);
        tiles[7]->addvertex(vertices[18]);
        tiles[7]->addvertex(vertices[35]);
        tiles[7]->addvertex(vertices[36]);
        tiles[7]->addvertex(vertices[37]);

        tiles[7]->add_edge(edges[31]);
        tiles[7]->add_edge(edges[19]);
        tiles[7]->add_edge(edges[32]);
        tiles[7]->add_edge(edges[33]);
        tiles[7]->add_edge(edges[34]);
        tiles[7]->add_edge(edges[35]);


        tiles[8]->addvertex(vertices[18]);
        tiles[8]->addvertex(vertices[19]);
        tiles[8]->addvertex(vertices[20]);
        tiles[8]->addvertex(vertices[33]);
        tiles[8]->addvertex(vertices[34]);
        tiles[8]->addvertex(vertices[35]);

        tiles[8]->add_edge(edges[18]);
        tiles[8]->add_edge(edges[23]);
        tiles[8]->add_edge(edges[36]);
        tiles[8]->add_edge(edges[37]);
        tiles[8]->add_edge(edges[38]);
        tiles[8]->add_edge(edges[32]);

        tiles[9]->addvertex(vertices[20]);
        tiles[9]->addvertex(vertices[21]);
        tiles[9]->addvertex(vertices[22]);
        tiles[9]->addvertex(vertices[31]);
        tiles[9]->addvertex(vertices[32]);
        tiles[9]->addvertex(vertices[33]);

        tiles[9]->add_edge(edges[22]);
        tiles[9]->add_edge(edges[26]);
        tiles[9]->add_edge(edges[39]);
        tiles[9]->add_edge(edges[40]);
        tiles[9]->add_edge(edges[41]);
        tiles[9]->add_edge(edges[36]);

        tiles[10]->addvertex(vertices[22]);
        tiles[10]->addvertex(vertices[23]);
        tiles[10]->addvertex(vertices[24]);
        tiles[10]->addvertex(vertices[29]);
        tiles[10]->addvertex(vertices[30]);
        tiles[10]->addvertex(vertices[31]);

        tiles[10]->add_edge(edges[25]);
        tiles[10]->add_edge(edges[30]);
        tiles[10]->add_edge(edges[42]);
        tiles[10]->add_edge(edges[43]);
        tiles[10]->add_edge(edges[44]);
        tiles[10]->add_edge(edges[39]);

        tiles[11]->addvertex(vertices[24]);
        tiles[11]->addvertex(vertices[25]);
        tiles[11]->addvertex(vertices[26]);
        tiles[11]->addvertex(vertices[27]);
        tiles[11]->addvertex(vertices[28]);
        tiles[11]->addvertex(vertices[29]);

        tiles[11]->add_edge(edges[29]);
        tiles[11]->add_edge(edges[45]);
        tiles[11]->add_edge(edges[46]);
        tiles[11]->add_edge(edges[47]);
        tiles[11]->add_edge(edges[48]);
        tiles[11]->add_edge(edges[42]);

        tiles[12]->addvertex(vertices[36]);
        tiles[12]->addvertex(vertices[35]);
        tiles[12]->addvertex(vertices[34]);
        tiles[12]->addvertex(vertices[38]);
        tiles[12]->addvertex(vertices[39]);
        tiles[12]->addvertex(vertices[40]);

        tiles[12]->add_edge(edges[33]);
        tiles[12]->add_edge(edges[38]);
        tiles[12]->add_edge(edges[49]);
        tiles[12]->add_edge(edges[50]);
        tiles[12]->add_edge(edges[51]);
        tiles[12]->add_edge(edges[52]);

        tiles[13]->addvertex(vertices[34]);
        tiles[13]->addvertex(vertices[33]);
        tiles[13]->addvertex(vertices[32]);
        tiles[13]->addvertex(vertices[41]);
        tiles[13]->addvertex(vertices[42]);
        tiles[13]->addvertex(vertices[40]);

        tiles[13]->add_edge(edges[37]);
        tiles[13]->add_edge(edges[41]);
        tiles[13]->add_edge(edges[53]);
        tiles[13]->add_edge(edges[54]);
        tiles[13]->add_edge(edges[55]);
        tiles[13]->add_edge(edges[49]);

        tiles[14]->addvertex(vertices[32]);
        tiles[14]->addvertex(vertices[31]);
        tiles[14]->addvertex(vertices[30]);
        tiles[14]->addvertex(vertices[43]);
        tiles[14]->addvertex(vertices[44]);
        tiles[14]->addvertex(vertices[42]);

        tiles[14]->add_edge(edges[40]);
        tiles[14]->add_edge(edges[44]);
        tiles[14]->add_edge(edges[56]);
        tiles[14]->add_edge(edges[57]);
        tiles[14]->add_edge(edges[58]);
        tiles[14]->add_edge(edges[53]);


        tiles[15]->addvertex(vertices[30]);
        tiles[15]->addvertex(vertices[29]);
        tiles[15]->addvertex(vertices[28]);
        tiles[15]->addvertex(vertices[45]);
        tiles[15]->addvertex(vertices[46]);
        tiles[15]->addvertex(vertices[44]);

        tiles[15]->add_edge(edges[43]);
        tiles[15]->add_edge(edges[48]);
        tiles[15]->add_edge(edges[59]);
        tiles[15]->add_edge(edges[60]);
        tiles[15]->add_edge(edges[61]);
        tiles[15]->add_edge(edges[56]);

        tiles[16]->addvertex(vertices[39]);
        tiles[16]->addvertex(vertices[40]);
        tiles[16]->addvertex(vertices[41]);
        tiles[16]->addvertex(vertices[51]);
        tiles[16]->addvertex(vertices[52]);
        tiles[16]->addvertex(vertices[53]);

        tiles[16]->add_edge(edges[62]);
        tiles[16]->add_edge(edges[63]);
        tiles[16]->add_edge(edges[64]);
        tiles[16]->add_edge(edges[65]);
        tiles[16]->add_edge(edges[50]);
        tiles[16]->add_edge(edges[55]);

        tiles[17]->addvertex(vertices[41]);
        tiles[17]->addvertex(vertices[42]);
        tiles[17]->addvertex(vertices[43]);
        tiles[17]->addvertex(vertices[49]);
        tiles[17]->addvertex(vertices[50]);
        tiles[17]->addvertex(vertices[51]);

        tiles[17]->add_edge(edges[62]);
        tiles[17]->add_edge(edges[54]);
        tiles[17]->add_edge(edges[58]);
        tiles[17]->add_edge(edges[66]);
        tiles[17]->add_edge(edges[67]);
        tiles[17]->add_edge(edges[68]);

        tiles[18]->addvertex(vertices[43]);
        tiles[18]->addvertex(vertices[44]);
        tiles[18]->addvertex(vertices[45]);
        tiles[18]->addvertex(vertices[47]);
        tiles[18]->addvertex(vertices[48]);
        tiles[18]->addvertex(vertices[49]);

        tiles[18]->add_edge(edges[66]);
        tiles[18]->add_edge(edges[57]);
        tiles[18]->add_edge(edges[61]);
        tiles[18]->add_edge(edges[69]);
        tiles[18]->add_edge(edges[70]);
        tiles[18]->add_edge(edges[71]);


    }

    void Board::initialize_vertex_to_vertex() {
        vertices[0]->add_vertex(vertices[1]);
        vertices[0]->add_vertex(vertices[7]);

        vertices[1]->add_vertex(vertices[0]);
        vertices[1]->add_vertex(vertices[2]);

        vertices[2]->add_vertex(vertices[1]);
        vertices[2]->add_vertex(vertices[3]);
        vertices[2]->add_vertex(vertices[9]);

        vertices[3]->add_vertex(vertices[2]);
        vertices[3]->add_vertex(vertices[4]);

        vertices[4]->add_vertex(vertices[3]);
        vertices[4]->add_vertex(vertices[5]);
        vertices[4]->add_vertex(vertices[11]);

        vertices[5]->add_vertex(vertices[4]);
        vertices[5]->add_vertex(vertices[6]);

        vertices[6]->add_vertex(vertices[5]);
        vertices[6]->add_vertex(vertices[13]);

        vertices[7]->add_vertex(vertices[0]);
        vertices[7]->add_vertex(vertices[8]);
        vertices[7]->add_vertex(vertices[15]);

        vertices[8]->add_vertex(vertices[7]);
        vertices[8]->add_vertex(vertices[9]);
        vertices[8]->add_vertex(vertices[19]);

        vertices[9]->add_vertex(vertices[2]);
        vertices[9]->add_vertex(vertices[8]);
        vertices[9]->add_vertex(vertices[10]);

        vertices[10]->add_vertex(vertices[9]);
        vertices[10]->add_vertex(vertices[11]);
        vertices[10]->add_vertex(vertices[21]);

        vertices[11]->add_vertex(vertices[4]);
        vertices[11]->add_vertex(vertices[10]);
        vertices[11]->add_vertex(vertices[12]);

        vertices[12]->add_vertex(vertices[11]);
        vertices[12]->add_vertex(vertices[13]);
        vertices[12]->add_vertex(vertices[23]);

        vertices[13]->add_vertex(vertices[6]);
        vertices[13]->add_vertex(vertices[12]);
        vertices[13]->add_vertex(vertices[14]);

        vertices[14]->add_vertex(vertices[13]);
        vertices[14]->add_vertex(vertices[25]);

        vertices[15]->add_vertex(vertices[7]);
        vertices[15]->add_vertex(vertices[17]);

        vertices[16]->add_vertex(vertices[17]);
        vertices[16]->add_vertex(vertices[37]);

        vertices[17]->add_vertex(vertices[15]);
        vertices[17]->add_vertex(vertices[16]);
        vertices[17]->add_vertex(vertices[18]);

        vertices[18]->add_vertex(vertices[17]);
        vertices[18]->add_vertex(vertices[19]);
        vertices[18]->add_vertex(vertices[35]);

        vertices[19]->add_vertex(vertices[8]);
        vertices[19]->add_vertex(vertices[18]);
        vertices[19]->add_vertex(vertices[20]);

        vertices[20]->add_vertex(vertices[19]);
        vertices[20]->add_vertex(vertices[21]);
        vertices[20]->add_vertex(vertices[33]);

        vertices[21]->add_vertex(vertices[10]);
        vertices[21]->add_vertex(vertices[20]);
        vertices[21]->add_vertex(vertices[22]);

        vertices[22]->add_vertex(vertices[21]);
        vertices[22]->add_vertex(vertices[23]);
        vertices[22]->add_vertex(vertices[31]);

        vertices[23]->add_vertex(vertices[12]);
        vertices[23]->add_vertex(vertices[22]);
        vertices[23]->add_vertex(vertices[24]);

        vertices[24]->add_vertex(vertices[23]);
        vertices[24]->add_vertex(vertices[25]);
        vertices[24]->add_vertex(vertices[29]);

        vertices[25]->add_vertex(vertices[14]);
        vertices[25]->add_vertex(vertices[24]);
        vertices[25]->add_vertex(vertices[26]);

        vertices[26]->add_vertex(vertices[25]);
        vertices[26]->add_vertex(vertices[27]);

        vertices[27]->add_vertex(vertices[26]);
        vertices[27]->add_vertex(vertices[28]);

        vertices[28]->add_vertex(vertices[27]);
        vertices[28]->add_vertex(vertices[29]);
        vertices[28]->add_vertex(vertices[46]);

        vertices[29]->add_vertex(vertices[24]);
        vertices[29]->add_vertex(vertices[28]);
        vertices[29]->add_vertex(vertices[30]);

        vertices[30]->add_vertex(vertices[29]);
        vertices[30]->add_vertex(vertices[31]);
        vertices[30]->add_vertex(vertices[44]);

        vertices[31]->add_vertex(vertices[22]);
        vertices[31]->add_vertex(vertices[30]);
        vertices[31]->add_vertex(vertices[32]);

        vertices[32]->add_vertex(vertices[31]);
        vertices[32]->add_vertex(vertices[33]);
        vertices[32]->add_vertex(vertices[42]);

        vertices[33]->add_vertex(vertices[20]);
        vertices[33]->add_vertex(vertices[32]);
        vertices[33]->add_vertex(vertices[34]);

        vertices[34]->add_vertex(vertices[33]);
        vertices[34]->add_vertex(vertices[35]);
        vertices[34]->add_vertex(vertices[40]);

        vertices[35]->add_vertex(vertices[18]);
        vertices[35]->add_vertex(vertices[34]);
        vertices[35]->add_vertex(vertices[36]);

        vertices[36]->add_vertex(vertices[35]);
        vertices[36]->add_vertex(vertices[37]);
        vertices[36]->add_vertex(vertices[38]);

        vertices[37]->add_vertex(vertices[16]);
        vertices[37]->add_vertex(vertices[36]);

        vertices[38]->add_vertex(vertices[39]);
        vertices[38]->add_vertex(vertices[36]);

        vertices[39]->add_vertex(vertices[38]);
        vertices[39]->add_vertex(vertices[40]);
        vertices[39]->add_vertex(vertices[53]);

        vertices[40]->add_vertex(vertices[34]);
        vertices[40]->add_vertex(vertices[39]);
        vertices[40]->add_vertex(vertices[41]);

        vertices[41]->add_vertex(vertices[40]);
        vertices[41]->add_vertex(vertices[42]);
        vertices[41]->add_vertex(vertices[51]);

        vertices[42]->add_vertex(vertices[32]);
        vertices[42]->add_vertex(vertices[41]);
        vertices[42]->add_vertex(vertices[43]);

        vertices[43]->add_vertex(vertices[42]);
        vertices[43]->add_vertex(vertices[44]);
        vertices[43]->add_vertex(vertices[49]);

        vertices[44]->add_vertex(vertices[30]);
        vertices[44]->add_vertex(vertices[43]);
        vertices[44]->add_vertex(vertices[45]);

        vertices[45]->add_vertex(vertices[44]);
        vertices[45]->add_vertex(vertices[46]);
        vertices[45]->add_vertex(vertices[47]);

        vertices[46]->add_vertex(vertices[28]);
        vertices[46]->add_vertex(vertices[45]);

        vertices[47]->add_vertex(vertices[45]);
        vertices[47]->add_vertex(vertices[48]);

        vertices[48]->add_vertex(vertices[47]);
        vertices[48]->add_vertex(vertices[49]);

        vertices[49]->add_vertex(vertices[43]);
        vertices[49]->add_vertex(vertices[48]);
        vertices[49]->add_vertex(vertices[50]);

        vertices[50]->add_vertex(vertices[49]);
        vertices[50]->add_vertex(vertices[51]);

        vertices[51]->add_vertex(vertices[41]);
        vertices[51]->add_vertex(vertices[50]);
        vertices[51]->add_vertex(vertices[52]);

        vertices[52]->add_vertex(vertices[51]);
        vertices[52]->add_vertex(vertices[53]);

        vertices[53]->add_vertex(vertices[39]);
        vertices[53]->add_vertex(vertices[52]);

    }

    void  Board::initialize_edge_to_edge(){
        edges[0]->add_neighbor(edges[1]);
        edges[0]->add_neighbor(edges[5]);

        edges[1]->add_neighbor(edges[0]);
        edges[1]->add_neighbor(edges[2]);
        edges[1]->add_neighbor(edges[6]);

        edges[2]->add_neighbor(edges[1]);
        edges[2]->add_neighbor(edges[3]);
        edges[2]->add_neighbor(edges[6]);
        edges[2]->add_neighbor(edges[10]);

        edges[3]->add_neighbor(edges[2]);
        edges[3]->add_neighbor(edges[4]);
        edges[3]->add_neighbor(edges[10]);
        edges[3]->add_neighbor(edges[17]);

        edges[4]->add_neighbor(edges[3]);
        edges[4]->add_neighbor(edges[5]);
        edges[4]->add_neighbor(edges[17]);
        edges[4]->add_neighbor(edges[16]);

        edges[5]->add_neighbor(edges[0]);
        edges[5]->add_neighbor(edges[4]);
        edges[5]->add_neighbor(edges[16]);

        edges[6]->add_neighbor(edges[1]);
        edges[6]->add_neighbor(edges[2]);
        edges[6]->add_neighbor(edges[7]);

        edges[7]->add_neighbor(edges[6]);
        edges[7]->add_neighbor(edges[8]);
        edges[7]->add_neighbor(edges[11]);

        edges[8]->add_neighbor(edges[7]);
        edges[8]->add_neighbor(edges[9]);
        edges[8]->add_neighbor(edges[11]);
        edges[8]->add_neighbor(edges[15]);

        edges[9]->add_neighbor(edges[8]);
        edges[9]->add_neighbor(edges[10]);
        edges[9]->add_neighbor(edges[15]);
        edges[9]->add_neighbor(edges[21]);

        edges[10]->add_neighbor(edges[2]);
        edges[10]->add_neighbor(edges[3]);
        edges[10]->add_neighbor(edges[9]);
        edges[10]->add_neighbor(edges[21]);

        edges[11]->add_neighbor(edges[7]);
        edges[11]->add_neighbor(edges[12]);
        edges[11]->add_neighbor(edges[8]);

        edges[12]->add_neighbor(edges[11]);
        edges[12]->add_neighbor(edges[13]);

        edges[13]->add_neighbor(edges[12]);
        edges[13]->add_neighbor(edges[14]);
        edges[13]->add_neighbor(edges[27]);

        edges[14]->add_neighbor(edges[13]);
        edges[14]->add_neighbor(edges[27]);
        edges[14]->add_neighbor(edges[15]);
        edges[14]->add_neighbor(edges[24]);

        edges[15]->add_neighbor(edges[24]);
        edges[15]->add_neighbor(edges[9]);
        edges[15]->add_neighbor(edges[8]);
        edges[15]->add_neighbor(edges[14]);

        edges[16]->add_neighbor(edges[4]);
        edges[16]->add_neighbor(edges[5]);
        edges[16]->add_neighbor(edges[20]);

        edges[17]->add_neighbor(edges[4]);
        edges[17]->add_neighbor(edges[3]);
        edges[17]->add_neighbor(edges[18]);
        edges[17]->add_neighbor(edges[23]);

        edges[18]->add_neighbor(edges[17]);
        edges[18]->add_neighbor(edges[19]);
        edges[18]->add_neighbor(edges[23]);
        edges[18]->add_neighbor(edges[32]);

        edges[19]->add_neighbor(edges[18]);
        edges[19]->add_neighbor(edges[20]);
        edges[19]->add_neighbor(edges[31]);
        edges[19]->add_neighbor(edges[32]);

        edges[20]->add_neighbor(edges[16]);
        edges[20]->add_neighbor(edges[19]);
        edges[20]->add_neighbor(edges[31]);

        edges[21]->add_neighbor(edges[9]);
        edges[21]->add_neighbor(edges[10]);
        edges[21]->add_neighbor(edges[22]);
        edges[21]->add_neighbor(edges[26]);

        edges[22]->add_neighbor(edges[21]);
        edges[22]->add_neighbor(edges[23]);
        edges[22]->add_neighbor(edges[26]);
        edges[22]->add_neighbor(edges[36]);

        edges[23]->add_neighbor(edges[17]);
        edges[23]->add_neighbor(edges[18]);
        edges[23]->add_neighbor(edges[22]);
        edges[23]->add_neighbor(edges[36]);

        edges[24]->add_neighbor(edges[14]);
        edges[24]->add_neighbor(edges[15]);
        edges[24]->add_neighbor(edges[25]);
        edges[24]->add_neighbor(edges[30]);

        edges[25]->add_neighbor(edges[24]);
        edges[25]->add_neighbor(edges[26]);
        edges[25]->add_neighbor(edges[30]);
        edges[25]->add_neighbor(edges[39]);

        edges[26]->add_neighbor(edges[39]);
        edges[26]->add_neighbor(edges[25]);
        edges[26]->add_neighbor(edges[21]);
        edges[26]->add_neighbor(edges[22]);

        edges[27]->add_neighbor(edges[13]);
        edges[27]->add_neighbor(edges[14]);
        edges[27]->add_neighbor(edges[28]);

        edges[28]->add_neighbor(edges[27]);
        edges[28]->add_neighbor(edges[29]);
        edges[28]->add_neighbor(edges[45]);

        edges[29]->add_neighbor(edges[28]);
        edges[29]->add_neighbor(edges[30]);
        edges[29]->add_neighbor(edges[45]);

        edges[30]->add_neighbor(edges[29]);
        edges[30]->add_neighbor(edges[25]);
        edges[30]->add_neighbor(edges[24]);
        edges[30]->add_neighbor(edges[42]);

        edges[31]->add_neighbor(edges[20]);
        edges[31]->add_neighbor(edges[19]);
        edges[31]->add_neighbor(edges[35]);

        edges[32]->add_neighbor(edges[19]);
        edges[32]->add_neighbor(edges[18]);
        edges[32]->add_neighbor(edges[33]);
        edges[32]->add_neighbor(edges[38]);

        edges[33]->add_neighbor(edges[32]);
        edges[33]->add_neighbor(edges[34]);
        edges[33]->add_neighbor(edges[38]);
        edges[33]->add_neighbor(edges[52]);



        edges[34]->add_neighbor(edges[33]);
        edges[34]->add_neighbor(edges[35]);
        edges[34]->add_neighbor(edges[52]);

        edges[35]->add_neighbor(edges[34]);
        edges[35]->add_neighbor(edges[31]);

        edges[36]->add_neighbor(edges[22]);
        edges[36]->add_neighbor(edges[23]);
        edges[36]->add_neighbor(edges[37]);
        edges[36]->add_neighbor(edges[41]);

        edges[37]->add_neighbor(edges[36]);
        edges[37]->add_neighbor(edges[38]);
        edges[37]->add_neighbor(edges[41]);
        edges[37]->add_neighbor(edges[49]);

        edges[38]->add_neighbor(edges[32]);
        edges[38]->add_neighbor(edges[33]);
        edges[38]->add_neighbor(edges[37]);
        edges[38]->add_neighbor(edges[49]);

        edges[39]->add_neighbor(edges[25]);
        edges[39]->add_neighbor(edges[26]);
        edges[39]->add_neighbor(edges[40]);
        edges[39]->add_neighbor(edges[44]);

        edges[40]->add_neighbor(edges[39]);
        edges[40]->add_neighbor(edges[41]);
        edges[40]->add_neighbor(edges[44]);
        edges[40]->add_neighbor(edges[53]);

        edges[41]->add_neighbor(edges[37]);
        edges[41]->add_neighbor(edges[36]);
        edges[41]->add_neighbor(edges[40]);
        edges[41]->add_neighbor(edges[53]);

        edges[42]->add_neighbor(edges[30]);
        edges[42]->add_neighbor(edges[29]);
        edges[42]->add_neighbor(edges[43]);
        edges[42]->add_neighbor(edges[48]);

        edges[43]->add_neighbor(edges[42]);
        edges[43]->add_neighbor(edges[44]);
        edges[43]->add_neighbor(edges[48]);
        edges[43]->add_neighbor(edges[56]);

        edges[44]->add_neighbor(edges[40]);
        edges[44]->add_neighbor(edges[39]);
        edges[44]->add_neighbor(edges[43]);
        edges[44]->add_neighbor(edges[56]);

        edges[45]->add_neighbor(edges[29]);
        edges[45]->add_neighbor(edges[28]);
        edges[45]->add_neighbor(edges[46]);

        edges[46]->add_neighbor(edges[45]);
        edges[46]->add_neighbor(edges[47]);

        edges[47]->add_neighbor(edges[46]);
        edges[47]->add_neighbor(edges[48]);
        edges[47]->add_neighbor(edges[59]);

        edges[48]->add_neighbor(edges[47]);
        edges[48]->add_neighbor(edges[43]);
        edges[48]->add_neighbor(edges[42]);
        edges[48]->add_neighbor(edges[59]);

        edges[49]->add_neighbor(edges[37]);
        edges[49]->add_neighbor(edges[38]);
        edges[49]->add_neighbor(edges[50]);
        edges[49]->add_neighbor(edges[55]);

        edges[50]->add_neighbor(edges[49]);
        edges[50]->add_neighbor(edges[51]);
        edges[50]->add_neighbor(edges[55]);
        edges[50]->add_neighbor(edges[65]);

        edges[51]->add_neighbor(edges[52]);
        edges[51]->add_neighbor(edges[50]);
        edges[51]->add_neighbor(edges[65]);

        edges[52]->add_neighbor(edges[33]);
        edges[52]->add_neighbor(edges[34]);
        edges[52]->add_neighbor(edges[51]);

        edges[53]->add_neighbor(edges[41]);
        edges[53]->add_neighbor(edges[40]);
        edges[53]->add_neighbor(edges[54]);
        edges[53]->add_neighbor(edges[58]);

        edges[54]->add_neighbor(edges[53]);
        edges[54]->add_neighbor(edges[55]);
        edges[54]->add_neighbor(edges[58]);
        edges[54]->add_neighbor(edges[62]);

        edges[55]->add_neighbor(edges[50]);
        edges[55]->add_neighbor(edges[49]);
        edges[55]->add_neighbor(edges[54]);
        edges[55]->add_neighbor(edges[62]);

        edges[56]->add_neighbor(edges[44]);
        edges[56]->add_neighbor(edges[43]);
        edges[56]->add_neighbor(edges[57]);
        edges[56]->add_neighbor(edges[61]);

        edges[57]->add_neighbor(edges[56]);
        edges[57]->add_neighbor(edges[58]);
        edges[57]->add_neighbor(edges[61]);
        edges[57]->add_neighbor(edges[66]);

        edges[58]->add_neighbor(edges[54]);
        edges[58]->add_neighbor(edges[53]);
        edges[58]->add_neighbor(edges[57]);
        edges[58]->add_neighbor(edges[66]);

        edges[59]->add_neighbor(edges[48]);
        edges[59]->add_neighbor(edges[47]);
        edges[59]->add_neighbor(edges[60]);

        edges[60]->add_neighbor(edges[59]);
        edges[60]->add_neighbor(edges[61]);
        edges[60]->add_neighbor(edges[69]);

        edges[61]->add_neighbor(edges[60]);
        edges[61]->add_neighbor(edges[56]);
        edges[61]->add_neighbor(edges[57]);
        edges[61]->add_neighbor(edges[69]);

        edges[62]->add_neighbor(edges[55]);
        edges[62]->add_neighbor(edges[54]);
        edges[62]->add_neighbor(edges[63]);
        edges[62]->add_neighbor(edges[68]);

        edges[63]->add_neighbor(edges[62]);
        edges[63]->add_neighbor(edges[64]);
        edges[63]->add_neighbor(edges[68]);

        edges[64]->add_neighbor(edges[63]);
        edges[64]->add_neighbor(edges[65]);

        edges[65]->add_neighbor(edges[64]);
        edges[65]->add_neighbor(edges[50]);
        edges[65]->add_neighbor(edges[51]);

        edges[66]->add_neighbor(edges[57]);
        edges[66]->add_neighbor(edges[58]);
        edges[66]->add_neighbor(edges[67]);
        edges[66]->add_neighbor(edges[71]);

        edges[67]->add_neighbor(edges[66]);
        edges[67]->add_neighbor(edges[68]);
        edges[67]->add_neighbor(edges[71]);

        edges[68]->add_neighbor(edges[67]);
        edges[68]->add_neighbor(edges[63]);
        edges[68]->add_neighbor(edges[62]);

        edges[69]->add_neighbor(edges[60]);
        edges[69]->add_neighbor(edges[61]);
        edges[69]->add_neighbor(edges[70]);

        edges[70]->add_neighbor(edges[69]);
        edges[70]->add_neighbor(edges[71]);

        edges[71]->add_neighbor(edges[70]);
        edges[71]->add_neighbor(edges[66]);
        edges[71]->add_neighbor(edges[67]);


    }

    void Board::initialize_vertex_to_edge(){
        vertices[0]->add_edge(edges[0]);
        vertices[0]->add_edge(edges[5]);

        vertices[1]->add_edge(edges[0]);
        vertices[1]->add_edge(edges[1]);

        vertices[2]->add_edge(edges[1]);
        vertices[2]->add_edge(edges[2]);
        vertices[2]->add_edge(edges[6]);

        vertices[3]->add_edge(edges[6]);
        vertices[3]->add_edge(edges[7]);

        vertices[4]->add_edge(edges[7]);
        vertices[4]->add_edge(edges[8]);
        vertices[4]->add_edge(edges[11]);

        vertices[5]->add_edge(edges[11]);
        vertices[5]->add_edge(edges[12]);

        vertices[6]->add_edge(edges[12]);
        vertices[6]->add_edge(edges[13]);

        vertices[7]->add_edge(edges[5]);
        vertices[7]->add_edge(edges[4]);
        vertices[7]->add_edge(edges[16]);

        vertices[8]->add_edge(edges[4]);
        vertices[8]->add_edge(edges[3]);
        vertices[8]->add_edge(edges[17]);

        vertices[9]->add_edge(edges[2]);
        vertices[9]->add_edge(edges[3]);
        vertices[9]->add_edge(edges[10]);

        vertices[10]->add_edge(edges[9]);
        vertices[10]->add_edge(edges[10]);
        vertices[10]->add_edge(edges[21]);

        vertices[11]->add_edge(edges[9]);
        vertices[11]->add_edge(edges[8]);
        vertices[11]->add_edge(edges[15]);

        vertices[12]->add_edge(edges[14]);
        vertices[12]->add_edge(edges[15]);
        vertices[12]->add_edge(edges[24]);

        vertices[13]->add_edge(edges[14]);
        vertices[13]->add_edge(edges[13]);
        vertices[13]->add_edge(edges[27]);

        vertices[14]->add_edge(edges[27]);
        vertices[14]->add_edge(edges[28]);

        vertices[15]->add_edge(edges[20]);
        vertices[15]->add_edge(edges[16]);

        vertices[16]->add_edge(edges[31]);
        vertices[16]->add_edge(edges[35]);

        vertices[17]->add_edge(edges[20]);
        vertices[17]->add_edge(edges[19]);
        vertices[17]->add_edge(edges[31]);

        vertices[18]->add_edge(edges[18]);
        vertices[18]->add_edge(edges[19]);
        vertices[18]->add_edge(edges[32]);

        vertices[19]->add_edge(edges[17]);
        vertices[19]->add_edge(edges[18]);
        vertices[19]->add_edge(edges[23]);

        vertices[20]->add_edge(edges[22]);
        vertices[20]->add_edge(edges[23]);
        vertices[20]->add_edge(edges[36]);

        vertices[21]->add_edge(edges[21]);
        vertices[21]->add_edge(edges[22]);
        vertices[21]->add_edge(edges[26]);

        vertices[22]->add_edge(edges[25]);
        vertices[22]->add_edge(edges[26]);
        vertices[22]->add_edge(edges[39]);

        vertices[23]->add_edge(edges[30]);
        vertices[23]->add_edge(edges[24]);
        vertices[23]->add_edge(edges[25]);

        vertices[24]->add_edge(edges[29]);
        vertices[24]->add_edge(edges[30]);
        vertices[24]->add_edge(edges[42]);

        vertices[25]->add_edge(edges[29]);
        vertices[25]->add_edge(edges[28]);
        vertices[25]->add_edge(edges[45]);

        vertices[26]->add_edge(edges[46]);
        vertices[26]->add_edge(edges[45]);

        vertices[27]->add_edge(edges[46]);
        vertices[27]->add_edge(edges[47]);

        vertices[28]->add_edge(edges[47]);
        vertices[28]->add_edge(edges[48]);
        vertices[28]->add_edge(edges[59]);

        vertices[29]->add_edge(edges[42]);
        vertices[29]->add_edge(edges[48]);
        vertices[29]->add_edge(edges[43]);

        vertices[30]->add_edge(edges[43]);
        vertices[30]->add_edge(edges[44]);
        vertices[30]->add_edge(edges[56]);

        vertices[31]->add_edge(edges[39]);
        vertices[31]->add_edge(edges[44]);
        vertices[31]->add_edge(edges[40]);

        vertices[32]->add_edge(edges[40]);
        vertices[32]->add_edge(edges[41]);
        vertices[32]->add_edge(edges[53]);

        vertices[33]->add_edge(edges[36]);
        vertices[33]->add_edge(edges[41]);
        vertices[33]->add_edge(edges[37]);

        vertices[34]->add_edge(edges[38]);
        vertices[34]->add_edge(edges[49]);
        vertices[34]->add_edge(edges[37]);

        vertices[35]->add_edge(edges[38]);
        vertices[35]->add_edge(edges[32]);
        vertices[35]->add_edge(edges[33]);

        vertices[36]->add_edge(edges[52]);
        vertices[36]->add_edge(edges[34]);
        vertices[36]->add_edge(edges[33]);

        vertices[37]->add_edge(edges[35]);
        vertices[37]->add_edge(edges[34]);

        vertices[38]->add_edge(edges[52]);
        vertices[38]->add_edge(edges[51]);

        vertices[39]->add_edge(edges[50]);
        vertices[39]->add_edge(edges[51]);
        vertices[39]->add_edge(edges[65]);

        vertices[40]->add_edge(edges[49]);
        vertices[40]->add_edge(edges[50]);
        vertices[40]->add_edge(edges[55]);

        vertices[41]->add_edge(edges[55]);
        vertices[41]->add_edge(edges[54]);
        vertices[41]->add_edge(edges[62]);

        vertices[42]->add_edge(edges[53]);
        vertices[42]->add_edge(edges[54]);
        vertices[42]->add_edge(edges[58]);

        vertices[43]->add_edge(edges[58]);
        vertices[43]->add_edge(edges[57]);
        vertices[43]->add_edge(edges[66]);

        vertices[44]->add_edge(edges[56]);
        vertices[44]->add_edge(edges[57]);
        vertices[44]->add_edge(edges[61]);

        vertices[45]->add_edge(edges[60]);
        vertices[45]->add_edge(edges[61]);
        vertices[45]->add_edge(edges[69]);

        vertices[46]->add_edge(edges[59]);
        vertices[46]->add_edge(edges[60]);

        vertices[47]->add_edge(edges[69]);
        vertices[47]->add_edge(edges[70]);

        vertices[48]->add_edge(edges[70]);
        vertices[48]->add_edge(edges[71]);

        vertices[49]->add_edge(edges[66]);
        vertices[49]->add_edge(edges[67]);
        vertices[49]->add_edge(edges[71]);

        vertices[50]->add_edge(edges[67]);
        vertices[50]->add_edge(edges[68]);

        vertices[51]->add_edge(edges[63]);
        vertices[51]->add_edge(edges[62]);
        vertices[51]->add_edge(edges[68]);

        vertices[52]->add_edge(edges[63]);
        vertices[52]->add_edge(edges[64]);

        vertices[53]->add_edge(edges[64]);
        vertices[53]->add_edge(edges[65]);





    }

}