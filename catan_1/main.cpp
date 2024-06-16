//guyguy845@gmail.com
#include <iostream>
//#include "catan.hpp"
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
Player player("guy");
Player player2("daniel");
Player player3("shachar");
Game game( board,player, player2, player3);
game.play();



    return 0;
}
