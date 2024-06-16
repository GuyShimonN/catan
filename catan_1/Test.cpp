//guyguy845@gmail.com
#include <sstream>
#include <cassert>
#include <iostream>
#include "Player.hpp"
#include "Board.h"
#include "Game.h"
#include "Resource.hpp"
#include "Tile.h"
#include "vertex.h"
#include "edge.h"
#include "DevelopmentCard.h"

using namespace ariel;

void testPlayer() {
    Board board;
    Player player1("Player1");

    // Test addResource and removeResource edge cases
    player1.addResource(Resource::Type::BRICK, 5);
    assert(player1.get_resource_sp(Resource::Type::BRICK) == 5);
    assert(player1.removeResource(Resource::Type::BRICK, 3));
    assert(player1.get_resource_sp(Resource::Type::BRICK) == 2);
    assert(!player1.removeResource(Resource::Type::BRICK, 3)); // Remove more than available
    assert(!player1.removeResource(Resource::Type::BRICK, 2));
    assert(player1.get_resource_sp(Resource::Type::BRICK) == 0);

    // Test buildSettlement edge case
    player1.addResource(Resource::Type::BRICK, 1);
    player1.addResource(Resource::Type::WOOD, 1);
    player1.addResource(Resource::Type::WOOL, 1);
    player1.addResource(Resource::Type::GRAIN, 1);
    player1.buildSettlement();  // Assuming this uses the resources added
//    assert(player1.get_num_resources() == 0);

    // Test buildCity edge case
    player1.addResource(Resource::Type::ORE, 3);
    player1.addResource(Resource::Type::GRAIN, 2);
    assert(player1.valid_resource(Resource::Type::ORE, 3));
    player1.buildCity(board);

    // Test trade edge case
    Player player2("Player2");
    player2.addResource(Resource::Type::BRICK, 1);
//    assert(player1.get_resource_sp(Resource::Type::BRICK) == 0);
    player1.trade(player2, Resource::Type::ORE, 1, Resource::Type::BRICK, 1);
//    assert(player1.get_resource_sp(Resource::Type::BRICK) == 1);

    // Test buyDevelopmentCard edge case
    std::vector<int> dev_cards = {0, 1, 0, 0, 0};
    player1.addResource(Resource::Type::ORE, 1);
    player1.addResource(Resource::Type::GRAIN, 1);
    player1.addResource(Resource::Type::WOOL, 1);
    assert(player1.buyDevelopmentCard(dev_cards));
    player1.addResource(Resource::Type::BRICK, 5);
    assert(!player1.removeResource(Resource::Type::BRICK, 8));
    assert(player1.get_resource_sp(Resource::Type::BRICK) == 0);
    player1.removeResource(Resource::Type::BRICK, 3);
    assert(player1.get_resource_sp(Resource::Type::BRICK) == 0);


}

void testGame() {
    Board board;
    Player player1("Player1");
    Player player2("Player2");
    Player player3("Player3");

    Game game(board, player1, player2, player3);


    // Redirect std::cout to a stringstream
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    player1.removeResource(Resource::Type::BRICK, 1);
    player1.removeResource(Resource::Type::WOOD, 1);
    game.bild_road(player1);
    std::cout.rdbuf(prevcoutbuf);
    std::string output = buffer.str();
    assert(output == "player Player1 does not have enough resources to build a road\n");
    std::cout<<"pass test 1 on bild road\n";

    player1.addResource(Resource::Type::BRICK, 1);
    player1.addResource(Resource::Type::WOOD, 1);
    std::stringstream buffer1;
    std::streambuf* prevcoutbuf1 = std::cout.rdbuf(buffer1.rdbuf());
    game.bild_road(player1);
    std::cout.rdbuf(prevcoutbuf1);
    std::string output1 = buffer1.str();
    std::string expected_output = "player Player1 which edge do you want to put? the option are:\n"
                                  "2\n"
                                  "4\n"
                                  "10\n"
                                  "17\n"
                                  "37\n"
                                  "38\n"
                                  "50\n"
                                  "55\n"
                                  "enter the edge id\n"
                                  "player Player1 build a road in edge 2\n";
    if (output1 != expected_output) {
        std::cout << "Test 2 on build road failed.\n";
        std::cout << "Expected output:\n" << expected_output << "\n";
        std::cout << "Actual output:\n" << output1 << "\n";
    } else {
        std::cout << "Pass test 2 on build road.\n";
    }



    // Test play edge case
//    game.play();

    // Test buildSettlement edge case
//    game.buildSettlement(player1);

    // Test useDevelopmentCard edge case
    assert(!game.useDevelopmentCard(player1)); // Assuming player has no development cards
}

void testBoard() {
    Board board;
    board.generateBoard();
    assert(!board.getTiles().empty());
    assert(!board.getVertices().empty());
    assert(!board.getEdges().empty());

    board.printBoard();
}

int main() {
    testPlayer();
    testGame();
    testBoard();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
