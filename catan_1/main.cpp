#include <iostream>
#include "catan.hpp"
#include "Tile.h"
#include "vertex.h"
#include "Board.h"
#include "edge.h"
using namespace std;
using namespace ariel;
int main() {
    Board board;
    board.printBoard();  // Print the board
    cout << board.getTiles()[0].getType() << endl;
    cout << board.getTiles()[2].getType() << endl;
    cout << board.getTiles()[3].getType() << endl;
    cout << board.getTiles()[7].getType() << endl;
    cout << board.getTiles()[12].getType() << endl;
    cout << board.getTiles()[16].getType() << endl;
//    Catan game;
//    game.initialize();
//    game.playRound();
//
//    Board board;
//    board.printBoard();  // Print the board

Player player("Alice");
Player player2("Bob");
Player player3("Charlie");



    return 0;
}
