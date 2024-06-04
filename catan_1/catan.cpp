//#include "catan.hpp"
//#include <iostream>
//
//Game::Game() : currentPlayerIndex(0) {
//    // Initialize the game with 3 players
//    players = { Player("Player 1"), Player("Player 2"), Player("Player 3") };
//}
//
//void Game::initialize() {
//    // Initialize the board and players
//    board.generateBoard();
//    std::cout << "Game initialized with 3 players." << std::endl;
//}
//
//void Game::playRound() {
//    // Example of playing one round
//    Player& currentPlayer = players[currentPlayerIndex];
//    std::cout << currentPlayer.getName() << "'s turn." << std::endl;
//
//    // Simulate rolling two dice
//    int diceRoll = (rand() % 6 + 1) + (rand() % 6 + 1);
//    std::cout << currentPlayer.getName() << " rolled a " << diceRoll << "." << std::endl;
//
//    // Distribute resources based on the dice roll
//    for (auto& tile : board.getTiles()) {
//        if (tile.getNumber() == diceRoll) {
//            Resource::Type resource = tile.getResource();
//            for (auto& player : players) {
//                // Assume some logic to check if the player has a settlement or city adjacent to the tile
//                // This is a placeholder logic and should be replaced with actual game logic
//                if (/* player has settlement or city adjacent to tile */) {
//                    player.addResource(resource);
//                }
//            }
//        }
//    }
//
//    // Proceed to the next player's turn
//    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
//}
