//
// Created by guy on 6/4/24.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Game.h"
#include <algorithm>
using namespace std;
namespace ariel {
    int Game::diceRoll() {
        return (rand() % 6 + 1) + (rand() % 6 + 1);
    }

    Game::Game( Board& board,Player& player1, Player& player2, Player& player3) :board(board),player1(player1),
                                                                              player2(player2), player3(player3) {

        load_image();
        buildSettlement_for_the_first(player1,8);
        buildSettlement_for_the_first(player2,12);
        buildSettlement_for_the_first(player3,4);
        buildSettlement_for_the_first(player3,18);
        buildSettlement_for_the_first(player2,30);
        buildSettlement_for_the_first(player1,40);
    }

    void Game::buildSettlement_for_the_first(Player &player, int vertex_id) {
            if (!chack_valid_city(vertex_id)){
                cout<<"invalid option for settlement"<<endl;
                return;
            }
            vertex& v=board.getVertices()[vertex_id];
            v.set_city(Tile::city::SETTLEMENT);
            v.set_player_id(player.get_name());
            cout<<"test chack that the player is the owner of the vertex: "<<v.get_player_id()<<endl;
            cout<<board.getVertices()[vertex_id].get_player_id()<<endl;
            cout<<"player "<<player.get_name()<<" build a settlement in vertex "<<vertex_id<<endl;
            player.addVictoryPoints(1);
            cout<<"player "<<player.get_name()<<" get 1 victory point"<<endl;
            cout<<"player "<<player.get_name()<<" which edge do you want to put? the option are:"<<endl;
            cout<<board.getVertices()[vertex_id].get_edges().size()<<endl;
           v.print_edges();
            cout<<"enter the edge id"<<endl;
        while (true) {
            int edge_id;
            cin >> edge_id;
            auto it = find_if(v.get_edges().begin(), v.get_edges().end(), [edge_id](edge* e) { return e->get_id() == edge_id; });
            if (it != v.get_edges().end()) {
                edge *e = *it;
                e->set_player_id(player.get_name());
                cout << "player " << player.get_name() << " build a road in edge " << edge_id << endl;

                cout<<"test chack that the player is the owner of the edge: "<<e->get_player_id()<<endl;
                cout<<board.getEdges()[edge_id].get_player_id()<<endl;
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
    void Game::load_image(){
        cv::Mat image = cv::imread("image.jpeg");
        cv::imshow("image", image);
        cv::waitKey(0);
    }
    void Game::play() {
        while (!GameOver()) {
            int dice = diceRoll();
            cout << "Dice roll: " << dice << endl;
            for (int i = 0; i < 19; i++) {
                if (board.getTiles()[i].getNumber() == dice) {
                    cout << "Tile " << i << " produced resources" << endl;
                    for (vertex *v : board.getTiles()[i].getVertices()) {
                        if (v->get_city() != Tile::city::NONE) {
                            cout << "Player " << v->get_player_id() << " gets a resource" << endl;
                        }
                    }
                }
            }
        }
        printWinner();
    }


}