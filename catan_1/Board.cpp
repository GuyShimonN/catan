
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
            tiles.push_back(Tile(tileTypes[i], i + 1));
        }
        initializeVertices();
    }

    void Board::assignNumbers() {
        std::vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
        auto it = numbers.begin();

        for (auto &tile: tiles) {
            if (tile.getType() != Tile::DESERT) {
                tile.setNumber(*it);
                ++it;
            }
        }
    }

    const std::vector<Tile> &Board::getTiles() const {
        return tiles;
    }
    void Board::printBoard() const {
        std::cout << "**************** CATAN BOARD ****************" << std::endl;

        for (int row = 0; row < 7; ++row) {
            for (int col = 0; col < 7; ++col) {
                int index = row * 7 + col;
                if (index < 19) {
                    const Tile& tile = tiles[index];
                    std::string resource;
                    switch (tile.getType()) {
                        case Tile::FOREST:
                            resource = "wood";
                            break;
                        case Tile::HILL:
                            resource = "brick";
                            break;
                        case Tile::PASTURE:
                            resource = "wool";
                            break;
                        case Tile::FIELD:
                            resource = "wheat";
                            break;
                        case Tile::MOUNTAIN:
                            resource = "iron";
                            break;
                        case Tile::DESERT:
                            resource = "desert";
                            break;
                    }
                    if (tile.getType() == Tile::DESERT) {
                        std::cout << std::setw(6) << resource;
                    } else {
                        std::cout << std::setw(6) << resource << " " << tile.getNumber();
                    }
                } else {
                    std::cout << std::setw(6) << "sea";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "**********************************************" << std::endl;
    }

    void Board::initializeVertices() {
        // Clear the existing vertices
        vertices.clear();

        // Create a vertex for each possible intersection of tiles
        int id = 1;
        for (int i = 0; i < 54; ++i) {
            vertices.push_back(vertex(i, id));
        }
        initializeEdges();
    }

    void Board::initializeEdges() {
        // Clear the existing edges
        edges.clear();

        // Create an edge for each possible edge between tiles
        int id = 1;
        for (int i = 0; i < 72; ++i) {
            edges.push_back(edge(i, id));
        }
    }

    void Board::initialize_tile_to_vertex() {
        tiles[0].addvertex(vertices[0]);
        tiles[0].addvertex(vertices[1]);
        tiles[0].addvertex(vertices[2]);
        tiles[0].addvertex(vertices[9]);
        tiles[0].addvertex(vertices[8]);
        tiles[0].addvertex(vertices[7]);

        tiles[1].addvertex(vertices[2]);
        tiles[1].addvertex(vertices[3]);
        tiles[1].addvertex(vertices[4]);
        tiles[1].addvertex(vertices[11]);
        tiles[1].addvertex(vertices[10]);
        tiles[1].addvertex(vertices[9]);

        tiles[2].addvertex(vertices[4]);
        tiles[2].addvertex(vertices[5]);
        tiles[2].addvertex(vertices[6]);
        tiles[2].addvertex(vertices[13]);
        tiles[2].addvertex(vertices[12]);
        tiles[2].addvertex(vertices[11]);

        tiles[3].addvertex(vertices[7]);
        tiles[3].addvertex(vertices[8]);
        tiles[3].addvertex(vertices[15]);
        tiles[3].addvertex(vertices[17]);
        tiles[3].addvertex(vertices[18]);
        tiles[3].addvertex(vertices[19]);

        tiles[4].addvertex(vertices[8]);
        tiles[4].addvertex(vertices[9]);
        tiles[4].addvertex(vertices[10]);
        tiles[4].addvertex(vertices[19]);
        tiles[4].addvertex(vertices[20]);
        tiles[4].addvertex(vertices[21]);

        tiles[5].addvertex(vertices[10]);
        tiles[5].addvertex(vertices[11]);
        tiles[5].addvertex(vertices[12]);
        tiles[5].addvertex(vertices[21]);
        tiles[5].addvertex(vertices[22]);
        tiles[5].addvertex(vertices[23]);

        tiles[6].addvertex(vertices[12]);
        tiles[6].addvertex(vertices[13]);
        tiles[6].addvertex(vertices[14]);
        tiles[6].addvertex(vertices[23]);
        tiles[6].addvertex(vertices[24]);
        tiles[6].addvertex(vertices[25]);

        tiles[7].addvertex(vertices[16]);
        tiles[7].addvertex(vertices[17]);
        tiles[7].addvertex(vertices[18]);
        tiles[7].addvertex(vertices[35]);
        tiles[7].addvertex(vertices[36]);
        tiles[7].addvertex(vertices[37]);


        tiles[8].addvertex(vertices[18]);
        tiles[8].addvertex(vertices[19]);
        tiles[8].addvertex(vertices[20]);
        tiles[8].addvertex(vertices[33]);
        tiles[8].addvertex(vertices[34]);
        tiles[8].addvertex(vertices[35]);

        tiles[9].addvertex(vertices[20]);
        tiles[9].addvertex(vertices[21]);
        tiles[9].addvertex(vertices[22]);
        tiles[9].addvertex(vertices[31]);
        tiles[9].addvertex(vertices[32]);
        tiles[9].addvertex(vertices[33]);

        tiles[10].addvertex(vertices[22]);
        tiles[10].addvertex(vertices[23]);
        tiles[10].addvertex(vertices[24]);
        tiles[10].addvertex(vertices[29]);
        tiles[10].addvertex(vertices[30]);
        tiles[10].addvertex(vertices[31]);

        tiles[11].addvertex(vertices[24]);
        tiles[11].addvertex(vertices[25]);
        tiles[11].addvertex(vertices[26]);
        tiles[11].addvertex(vertices[27]);
        tiles[11].addvertex(vertices[28]);
        tiles[11].addvertex(vertices[29]);

        tiles[12].addvertex(vertices[36]);
        tiles[12].addvertex(vertices[35]);
        tiles[12].addvertex(vertices[34]);
        tiles[12].addvertex(vertices[38]);
        tiles[12].addvertex(vertices[39]);
        tiles[12].addvertex(vertices[40]);

        tiles[13].addvertex(vertices[34]);
        tiles[13].addvertex(vertices[33]);
        tiles[13].addvertex(vertices[32]);
        tiles[13].addvertex(vertices[41]);
        tiles[13].addvertex(vertices[42]);
        tiles[13].addvertex(vertices[40]);

        tiles[14].addvertex(vertices[32]);
        tiles[14].addvertex(vertices[31]);
        tiles[14].addvertex(vertices[30]);
        tiles[14].addvertex(vertices[43]);
        tiles[14].addvertex(vertices[44]);
        tiles[14].addvertex(vertices[42]);

        tiles[15].addvertex(vertices[30]);
        tiles[15].addvertex(vertices[29]);
        tiles[15].addvertex(vertices[28]);
        tiles[15].addvertex(vertices[45]);
        tiles[15].addvertex(vertices[46]);
        tiles[15].addvertex(vertices[44]);

        tiles[16].addvertex(vertices[39]);
        tiles[16].addvertex(vertices[40]);
        tiles[16].addvertex(vertices[41]);
        tiles[16].addvertex(vertices[51]);
        tiles[16].addvertex(vertices[52]);
        tiles[16].addvertex(vertices[53]);

        tiles[17].addvertex(vertices[41]);
        tiles[17].addvertex(vertices[42]);
        tiles[17].addvertex(vertices[43]);
        tiles[17].addvertex(vertices[49]);
        tiles[17].addvertex(vertices[50]);
        tiles[17].addvertex(vertices[51]);

        tiles[18].addvertex(vertices[43]);
        tiles[18].addvertex(vertices[44]);
        tiles[18].addvertex(vertices[45]);
        tiles[18].addvertex(vertices[47]);
        tiles[18].addvertex(vertices[48]);
        tiles[18].addvertex(vertices[49]);

    }

    void Board::initialize_vertex_to_vertex() {
        vertices[0].add_vertex(vertices[1]);
        vertices[0].add_vertex(vertices[7]);

        vertices[1].add_vertex(vertices[0]);
        vertices[1].add_vertex(vertices[2]);

        vertices[2].add_vertex(vertices[1]);
        vertices[2].add_vertex(vertices[3]);
        vertices[2].add_vertex(vertices[9]);

        vertices[3].add_vertex(vertices[2]);
        vertices[3].add_vertex(vertices[4]);

        vertices[4].add_vertex(vertices[3]);
        vertices[4].add_vertex(vertices[5]);
        vertices[4].add_vertex(vertices[11]);

        vertices[5].add_vertex(vertices[4]);
        vertices[5].add_vertex(vertices[6]);

        vertices[6].add_vertex(vertices[5]);
        vertices[6].add_vertex(vertices[13]);

        vertices[7].add_vertex(vertices[0]);
        vertices[7].add_vertex(vertices[8]);
        vertices[7].add_vertex(vertices[15]);

        vertices[8].add_vertex(vertices[7]);
        vertices[8].add_vertex(vertices[9]);
        vertices[8].add_vertex(vertices[19]);

        vertices[9].add_vertex(vertices[2]);
        vertices[9].add_vertex(vertices[8]);
        vertices[9].add_vertex(vertices[10]);

        vertices[10].add_vertex(vertices[9]);
        vertices[10].add_vertex(vertices[11]);
        vertices[10].add_vertex(vertices[21]);

        vertices[11].add_vertex(vertices[4]);
        vertices[11].add_vertex(vertices[10]);
        vertices[11].add_vertex(vertices[12]);

        vertices[12].add_vertex(vertices[11]);
        vertices[12].add_vertex(vertices[13]);
        vertices[12].add_vertex(vertices[23]);

        vertices[13].add_vertex(vertices[6]);
        vertices[13].add_vertex(vertices[12]);
        vertices[13].add_vertex(vertices[14]);

        vertices[14].add_vertex(vertices[13]);
        vertices[14].add_vertex(vertices[25]);

        vertices[15].add_vertex(vertices[7]);
        vertices[15].add_vertex(vertices[17]);

        vertices[16].add_vertex(vertices[17]);
        vertices[16].add_vertex(vertices[37]);

        vertices[17].add_vertex(vertices[15]);
        vertices[17].add_vertex(vertices[16]);
        vertices[17].add_vertex(vertices[18]);

        vertices[18].add_vertex(vertices[17]);
        vertices[18].add_vertex(vertices[19]);
        vertices[18].add_vertex(vertices[35]);

        vertices[19].add_vertex(vertices[8]);
        vertices[19].add_vertex(vertices[18]);
        vertices[19].add_vertex(vertices[20]);

        vertices[20].add_vertex(vertices[19]);
        vertices[20].add_vertex(vertices[21]);
        vertices[20].add_vertex(vertices[33]);

        vertices[21].add_vertex(vertices[10]);
        vertices[21].add_vertex(vertices[20]);
        vertices[21].add_vertex(vertices[22]);

        vertices[22].add_vertex(vertices[21]);
        vertices[22].add_vertex(vertices[23]);
        vertices[22].add_vertex(vertices[31]);

        vertices[23].add_vertex(vertices[12]);
        vertices[23].add_vertex(vertices[22]);
        vertices[23].add_vertex(vertices[24]);

        vertices[24].add_vertex(vertices[23]);
        vertices[24].add_vertex(vertices[25]);
        vertices[24].add_vertex(vertices[29]);

        vertices[25].add_vertex(vertices[14]);
        vertices[25].add_vertex(vertices[24]);
        vertices[25].add_vertex(vertices[26]);

        vertices[26].add_vertex(vertices[25]);
        vertices[26].add_vertex(vertices[27]);

        vertices[27].add_vertex(vertices[26]);
        vertices[27].add_vertex(vertices[28]);

        vertices[28].add_vertex(vertices[27]);
        vertices[28].add_vertex(vertices[29]);
        vertices[28].add_vertex(vertices[46]);

        vertices[29].add_vertex(vertices[24]);
        vertices[29].add_vertex(vertices[28]);
        vertices[29].add_vertex(vertices[30]);

        vertices[30].add_vertex(vertices[29]);
        vertices[30].add_vertex(vertices[31]);
        vertices[30].add_vertex(vertices[44]);

        vertices[31].add_vertex(vertices[22]);
        vertices[31].add_vertex(vertices[30]);
        vertices[31].add_vertex(vertices[32]);

        vertices[32].add_vertex(vertices[31]);
        vertices[32].add_vertex(vertices[33]);
        vertices[32].add_vertex(vertices[42]);

        vertices[33].add_vertex(vertices[20]);
        vertices[33].add_vertex(vertices[32]);
        vertices[33].add_vertex(vertices[34]);

        vertices[34].add_vertex(vertices[33]);
        vertices[34].add_vertex(vertices[35]);
        vertices[34].add_vertex(vertices[40]);

        vertices[35].add_vertex(vertices[18]);
        vertices[35].add_vertex(vertices[34]);
        vertices[35].add_vertex(vertices[36]);

        vertices[36].add_vertex(vertices[35]);
        vertices[36].add_vertex(vertices[37]);
        vertices[36].add_vertex(vertices[38]);

        vertices[37].add_vertex(vertices[16]);
        vertices[37].add_vertex(vertices[36]);

        vertices[38].add_vertex(vertices[39]);
        vertices[38].add_vertex(vertices[36]);

        vertices[39].add_vertex(vertices[38]);
        vertices[39].add_vertex(vertices[40]);
        vertices[39].add_vertex(vertices[53]);

        vertices[40].add_vertex(vertices[34]);
        vertices[40].add_vertex(vertices[39]);
        vertices[40].add_vertex(vertices[41]);

        vertices[41].add_vertex(vertices[40]);
        vertices[41].add_vertex(vertices[42]);
        vertices[41].add_vertex(vertices[51]);

        vertices[42].add_vertex(vertices[32]);
        vertices[42].add_vertex(vertices[41]);
        vertices[42].add_vertex(vertices[43]);

        vertices[43].add_vertex(vertices[42]);
        vertices[43].add_vertex(vertices[44]);
        vertices[43].add_vertex(vertices[49]);

        vertices[44].add_vertex(vertices[30]);
        vertices[44].add_vertex(vertices[43]);
        vertices[44].add_vertex(vertices[45]);

        vertices[45].add_vertex(vertices[44]);
        vertices[45].add_vertex(vertices[46]);
        vertices[45].add_vertex(vertices[47]);

        vertices[46].add_vertex(vertices[28]);
        vertices[46].add_vertex(vertices[45]);

        vertices[47].add_vertex(vertices[45]);
        vertices[47].add_vertex(vertices[48]);

        vertices[48].add_vertex(vertices[47]);
        vertices[48].add_vertex(vertices[49]);

        vertices[49].add_vertex(vertices[43]);
        vertices[49].add_vertex(vertices[48]);
        vertices[49].add_vertex(vertices[50]);

        vertices[50].add_vertex(vertices[49]);
        vertices[50].add_vertex(vertices[51]);

        vertices[51].add_vertex(vertices[41]);
        vertices[51].add_vertex(vertices[50]);
        vertices[51].add_vertex(vertices[52]);

        vertices[52].add_vertex(vertices[51]);
        vertices[52].add_vertex(vertices[53]);

        vertices[53].add_vertex(vertices[39]);
        vertices[53].add_vertex(vertices[52]);

    }
}