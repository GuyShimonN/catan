#include <iostream>
#include <cassert>
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
    assert(player1.removeResource(Resource::Type::BRICK, 2));
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
}

void testGame() {
    Board board;
    Player player1("Player1");
    Player player2("Player2");
    Player player3("Player3");

    Game game(board, player1, player2, player3);

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
//    testGame();
    testBoard();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
