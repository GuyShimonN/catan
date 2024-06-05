//
// Created by guy on 6/4/24.
//
#include <iostream>
#include "Game.h"
#include <algorithm>
using namespace std;
namespace ariel {
    int Game::diceRoll() {
        return (rand() % 6 + 1) + (rand() % 6 + 1);
    }

    Game::Game(Board board, Player player1, Player player2, Player player3) : board(board), player1(player1),
                                                                              player2(player2), player3(player3) {

        buildSettlement_for_the_first(player1,8);
    }

    void Game::buildSettlement_for_the_first(Player &player, int vertex_id) {
            if (!chack_valid_city(vertex_id)){
                cout<<"invalid option for settlement"<<endl;
                return;
            }
            vertex v=board.getVertices()[vertex_id];
            v.set_city(Tile::city::SETTLEMENT);
            v.set_player_id(player.get_name());
            cout<<"player "<<player.get_name()<<" build a settlement in vertex "<<vertex_id<<endl;
            player.addVictoryPoints(1);
            cout<<"player "<<player.get_name()<<" get 1 victory point"<<endl;
            cout<<"player "<<player.get_name()<<" which edge do you want to put? the option are:"<<endl;
            for (edge* e : v.get_edges()){
                if (e->get_player_id()=="")cout<<e->get_id()<<endl;

            }
            cout<<"enter the edge id"<<endl;
        while (true) {
            int edge_id;
            cin >> edge_id;
            auto it = find_if(v.get_edges().begin(), v.get_edges().end(), [edge_id](edge* e) { return e->get_id() == edge_id; });            if (it != v.get_edges().end()) {
                edge *e = *it;
                e->set_player_id(player.get_name());
                cout << "player " << player.get_name() << " build a road in edge " << edge_id << endl;
                break;
            } else {
                cout << "invalid option" << endl;
            }
        }
    }
    bool Game::chack_valid_city(int ver_id){
        vertex v =this->board.getVertices()[ver_id];
        for (vertex *p : v.get_verrices()){
            if (p->get_city()!=Tile::city::NONE)return false;
        }
        return true;

    }

}