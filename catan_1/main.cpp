#include <iostream>
#include "catan.hpp"
#include "Tile.h"
#include "vertex.h"
#include "Board.h"
#include "edge.h"
#include "Game.h"
using namespace std;
using namespace ariel;
int main() {
    Board board;
    board.printBoard();  // Print the board
Player player("Alice");
Player player2("Bob");
Player player3("Charlie");
Game game( board,player, player2, player3);



    return 0;
}
