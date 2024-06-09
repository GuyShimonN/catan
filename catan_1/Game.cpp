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

        players.push_back(&player1);
        players.push_back(&player2);
        players.push_back(&player3);

        load_image();
        buildSettlement_for_the_first(player1,8);
        buildSettlement_for_the_first(player2,12);
        buildSettlement_for_the_first(player3,4);
        buildSettlement_for_the_first(player3,18);
        buildSettlement_for_the_first(player2,30);
        buildSettlement_for_the_first(player1,40);
        play();
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
            if (p->get_city()!=vertex::city::NONE)return false;
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
                        if (v->get_city() != vertex::city::NONE) {
                            cout << "Player " << v->get_player_id() << " gets a resource" << endl;
                            add_resource(v->get_player_id(), board.getTiles()[i].getResource(),v->get_city_type());
                        }
                    }
                }
            }
        }
        printWinner();
    }
void Game::add_resource(std::string player_id, Resource::Type resource,::ariel::city city){
    if (city==vertex::city::SETTLEMENT){
        if (resource==Resource::WOOD){
            Game::get_player(player_id)->addResource(Resource::WOOD,1);
        }
        if (resource==Resource::BRICK){
            Game::get_player(player_id)->addResource(Resource::BRICK,1);
        }
        if (resource==Resource::WOOL){
            Game::get_player(player_id)->addResource(Resource::WOOL,1);
        }
        if (resource==Resource::GRAIN){
            Game::get_player(player_id)->addResource(Resource::GRAIN,1);
        }
        if (resource==Resource::ORE){
            Game::get_player(player_id)->addResource(Resource::ORE,1);
        }
    }
    if (city==vertex::city::CITY){
        if (resource==Resource::WOOD){
            Game::get_player(player_id)->addResource(Resource::WOOD,2);
        }
        if (resource==Resource::BRICK){
            Game::get_player(player_id)->addResource(Resource::BRICK,2);
        }
        if (resource==Resource::WOOL){
            Game::get_player(player_id)->addResource(Resource::WOOL,2);
        }
        if (resource==Resource::GRAIN){
            Game::get_player(player_id)->addResource(Resource::GRAIN,2);
        }
        if (resource==Resource::ORE){
            Game::get_player(player_id)->addResource(Resource::ORE,2);
        }
    }
}
    bool Game::GameOver() {
        for (auto &player : Game::getPlayers()) {
            if (player->getVictoryPoints() >= 10) {
                return true;
            }
        }
        return false;
    }

    void Game::printWinner() {
        int max = 0;
        string winner;
        for (auto &player : Game::getPlayers()) {
            if (player->getVictoryPoints() > max) {
                max = player->getVictoryPoints();
                winner = player->get_name();
            }
        }
        cout << "The winner is: " << winner << endl;
    }
    Player* Game::get_player(std::string id) {
        for (Player* player : players) {
            if (player->get_name() == id) {
                return player;
            }
        }
        return nullptr;
    }

    std::vector<Player*>& Game::getPlayers() {

        return players;
    }


}