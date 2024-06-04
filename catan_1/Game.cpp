//
// Created by guy on 6/4/24.
//
#include <iostream>
#include "Game.h"
using namespace std;
namespace ariel {
    int Game::diceRoll() {
        return (rand() % 6 + 1) + (rand() % 6 + 1);
    }

    Game::Game(Board board, Player player1, Player player2, Player player3) : board(board), player1(player1),
                                                                              player2(player2), player3(player3) {

    }

    void Game::buildSettlement_for_the_first(Player &player, int vertex_id) {
            if (!chack_valid_city(vertex_id)){
                cout<<"invalid option"<<endl;
                return;
            }
            vertex v=board.getTiles()[vertex_id];
            v.set_city(Tile::city::SETTLEMENT);
            v.set_player_id(player.get_name());

    }
    bool Game::chack_valid_city(int ver_id){
        vertex v =this->board.getTiles()[ver_id];
        for (vertex p : v.get_verrices()){
            if (p.get_city()!=Tile::city::NONE)return false;
        }
        return true;

    }

}