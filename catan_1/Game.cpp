//
// Created by guy on 6/4/24.
//
#include <unordered_set>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Game.h"
#include <algorithm>

using namespace std;
namespace ariel {
    Game::Game(Board &board, Player &player1, Player &player2, Player &player3) : board(board), player1(player1),
                                                                                  player2(player2), player3(player3),
                                                                                  round(0) {

        players.push_back(&player1);
        players.push_back(&player2);
        players.push_back(&player3);

//        load_image();
        buildSettlement_for_the_first(player1, 8);
        buildSettlement_for_the_first(player2, 12);
        buildSettlement_for_the_first(player3, 4);

        buildSettlement_for_the_first(player3, 18);
        add_resource_for_the_first(player3, board.getVertices()[18]);

        buildSettlement_for_the_first(player2, 30);
        add_resource_for_the_first(player2, board.getVertices()[30]);

        buildSettlement_for_the_first(player1, 40);
        add_resource_for_the_first(player1, board.getVertices()[40]);
        play();
    }
    void Game::add_resource_for_the_first(Player &player, vertex &vertex) {
        for (Tile *tile: vertex.get_tiles()) {
            player.addResource(tile->getResource(), 1);
        }
    }

    void Game::buildSettlement_for_the_first(Player &player, int vertex_id) {
        if (!chack_valid_city(vertex_id)) {
            cout << "invalid option for settlement" << endl;
            return;
        }
        vertex &v = board.getVertices()[vertex_id];
        v.set_city(Tile::city::SETTLEMENT);
        v.set_player_id(player.get_name());
        player.add_vertex(&v);
        cout << "test chack that the player is the owner of the vertex: " << v.get_player_id() << endl;
        cout << board.getVertices()[vertex_id].get_player_id() << endl;
        cout << "player " << player.get_name() << " build a settlement in vertex " << vertex_id << endl;
        player.addVictoryPoints(1);
        cout << "player " << player.get_name() << " get 1 victory point" << endl;
        cout << "player " << player.get_name() << " which edge do you want to put? the option are:" << endl;
//            cout<<board.getVertices()[vertex_id].get_edges().size()<<endl;
        v.print_edges();
        cout << "enter the edge id" << endl;
        while (true) {
            int edge_id;
            if (!(cin >> edge_id)) {
                cin.clear();  // Clear the fail state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the rest of the line
                cout << "Invalid input. Please enter a number." << endl;
                continue;  // Skip the rest of the loop and start over
            }
            auto it = find_if(v.get_edges().begin(), v.get_edges().end(),
                              [edge_id](edge *e) { return e->get_id() == edge_id; });
            if (it != v.get_edges().end()) {
                edge *e = *it;
                e->set_player_id(player.get_name());
                player.add_edge(e);
                cout << "player " << player.get_name() << " build a road in edge " << edge_id << endl;
                cout << "test chack that the player is the owner of the edge: " << e->get_player_id() << endl;
                cout << board.getEdges()[edge_id].get_player_id() << endl;
                break;
            } else {
                cout << "invalid option" << endl;
            }
        }
    }

    bool Game::chack_valid_city(int ver_id) {
        vertex v = this->board.getVertices()[ver_id];
        for (vertex *p: v.get_verrices()) {
            if (p->get_city() != vertex::city::NONE)return false;
        }
        return true;

    }

    void Game::load_image() {
        // Load the image
        cv::Mat image = cv::imread("image.jpeg");

        // Check if the image is loaded successfully
        if (image.empty()) {
            std::cerr << "Could not open or find the image" << std::endl;
            return;
        }

        // Create a window
        cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

        // Show the image in the window
        cv::imshow("Display Image", image);

        // Wait for 5 seconds
        cv::waitKey(5000);

        // Destroy the window
        cv::destroyWindow("Display Image");
    }

    void Game::play() {
        while (!GameOver()) {

            play_turn(player1);
            play_turn(player2);
            play_turn(player3);
            round++;
        }
        printWinner();
    }

    void Game::add_resource(std::string player_id, Resource::Type resource, enum vertex::city city) {
        if (city == vertex::city::SETTLEMENT) {
            if (resource == Resource::WOOD) {
                Game::get_player(player_id)->addResource(Resource::WOOD, 1);
            }
            if (resource == Resource::BRICK) {
                Game::get_player(player_id)->addResource(Resource::BRICK, 1);
            }
            if (resource == Resource::WOOL) {
                Game::get_player(player_id)->addResource(Resource::WOOL, 1);
            }
            if (resource == Resource::GRAIN) {
                Game::get_player(player_id)->addResource(Resource::GRAIN, 1);
            }
            if (resource == Resource::ORE) {
                Game::get_player(player_id)->addResource(Resource::ORE, 1);
            }
        }
        if (city == vertex::city::CITY) {
            if (resource == Resource::WOOD) {
                Game::get_player(player_id)->addResource(Resource::WOOD, 2);
            }
            if (resource == Resource::BRICK) {
                Game::get_player(player_id)->addResource(Resource::BRICK, 2);
            }
            if (resource == Resource::WOOL) {
                Game::get_player(player_id)->addResource(Resource::WOOL, 2);
            }
            if (resource == Resource::GRAIN) {
                Game::get_player(player_id)->addResource(Resource::GRAIN, 2);
            }
            if (resource == Resource::ORE) {
                Game::get_player(player_id)->addResource(Resource::ORE, 2);
            }
        }
    }

    bool Game::GameOver() {
        for (auto &player: Game::getPlayers()) {
            if (player->getVictoryPoints() >= 10) {
                return true;
            }
        }
        return false;
    }

    void Game::printWinner() {
        int max = 0;
        string winner;
        for (auto &player: Game::getPlayers()) {
            if (player->getVictoryPoints() > max) {
                max = player->getVictoryPoints();
                winner = player->get_name();
            }
        }
        cout << "The winner is: " << winner << endl;
    }

    Player *Game::get_player(std::string id) {
        for (Player *player: players) {
            if (player->get_name() == id) {
                return player;
            }
        }
        return nullptr;
    }

    std::vector<Player *> &Game::getPlayers() {

        return players;
    }

    void Game::diceRoll() {

        int dice = (rand() % 6 + 1) + (rand() % 6 + 1);
        if (round < 3 && dice == 7) {
            diceRoll();
        }

        cout << "Dice roll: " << dice << endl;
        for (int i = 0; i < 19; i++) {
            if (board.getTiles()[i].getNumber() == dice) {
                cout << "Tile " << i << " produced resources" << endl;
                for (vertex *v: board.getTiles()[i].getVertices()) {
                    if (v->get_city() != vertex::city::NONE) {
                        cout << "Player " << v->get_player_id() << " gets a resource" << endl;
                        add_resource(v->get_player_id(), board.getTiles()[i].getResource(), v->get_city_type());
                    }
                }
            }
        }
    }

    void Game::play_turn(Player &player) {
        diceRoll();
        while (true) {
            cout << "player " << player.get_name() << " what do you want to do?" << endl;
            cout << "1. build a road" << endl;
            cout << "2. build a settlement" << endl;
            cout << "3. build a city" << endl;
            cout << "4. buy a development card" << endl;
            cout << "5. trade with other player" << endl;
            cout << "6. show the cards" << endl; //add this option
            cout << "7. end turn" << endl;
            int option;
            cin >> option;
            if (option == 1) {
                bild_road(player);
            }
            if (option == 2) {
//                player.buildSettlement();
                buildSettlement(player);
            }
            if (option == 3) {
                player.buildCity();
            }
            if (option == 4) {
                player.buyDevelopmentCard();
            }
            if (option == 5) {
                cout << "player " << player.get_name() << " which player do you want to trade with?" << endl;
                for (Player *p: players) {
                    if (p->get_name() != player.get_name()) {
                        cout << p->get_name() << endl;
                    }
                }
                string other_player;
                cin >> other_player;
                cout << "player " << player.get_name() << " which resource do you want to give?" << endl;
                cout << "1. wood" << endl;
                cout << "2. brick" << endl;
                cout << "3. wool" << endl;
                cout << "4. grain" << endl;
                cout << "5. ore" << endl;
                int give;
                cin >> give;
                cout << "player " << player.get_name() << " how many resources do you want to give?" << endl;
                int give_qty;
                cin >> give_qty;
                cout << "player " << player.get_name() << " which resource do you want to receive?" << endl;
                cout << "1. wood" << endl;
                cout << "2. brick" << endl;
                cout << "3. wool" << endl;
                cout << "4. grain" << endl;
                cout << "5. ore" << endl;
                int receive;
                cin >> receive;
                cout << "player " << player.get_name() << " how many resources do you want to receive?" << endl;
                int receive_qty;
                cin >> receive_qty;
                player.trade(*get_player(other_player), Resource::Type(give), give_qty, Resource::Type(receive),
                             receive_qty);
            }
            if (option == 6) {
                player.print_cards();
            }

            if (option == 7) {
                break;
            }
        }

    }

    void Game::bild_road(Player &player) {
        if (!(player.valid_resource(Resource::BRICK, 1) && player.valid_resource(Resource::WOOD, 1))) {
            cout << "player " << player.get_name() << " does not have enough resources to build a road" << endl;
            return;  //check if the player have the resources
        }
        cout << "player " << player.get_name() << " which edge do you want to put? the option are:" << endl;
//        cout <<"you have :"<< player.get_edges().size() << " option."<<endl;
        int sun = player.get_edges().size();
        for (int i = 0; i < sun; i++) {
            for (size_t j = 0; j < player.get_edges()[i]->get_neighbors().size(); j++) {
                if (player.get_edges()[i]->get_neighbors()[j]->get_player_id() == "") {
                    cout << player.get_edges()[i]->get_neighbors()[j]->get_id() << endl;
                }
            }
        }
        cout << "enter the edge id" << endl;
        while (true) {
            int edge_id;
            cin >> edge_id;
            if (board.getEdges()[edge_id].get_player_id() == "") {
                board.getEdges()[edge_id].set_player_id(player.get_name());
                player.add_edge(&board.getEdges()[edge_id]);

                cout << "player " << player.get_name() << " build a road in edge " << edge_id << endl;
                break;
            } else {
                cout << "invalid option" << endl;
            }
        }
    }

    void Game::buildSettlement(Player &player) {
        cout << "player " << player.get_name() << " which vertex do you want to put? the option are:" << endl;
        player.printPossibleSettlements(board);
        cout << "enter the vertex id" << endl;
        while (true) {
            int vertex_id;
            cin >> vertex_id;
            if (board.getVertices()[vertex_id].get_city() == vertex::city::NONE) {
                board.getVertices()[vertex_id].set_city(vertex::city::SETTLEMENT);
                board.getVertices()[vertex_id].set_player_id(player.get_name());
                player.add_vertex(&board.getVertices()[vertex_id]);
                cout << "player " << player.get_name() << " build a settlement in vertex " << vertex_id << endl;
                player.addVictoryPoints(1);
                cout << "player " << player.get_name() << " get 1 victory point" << endl;
                cout << "player " << player.get_name() << " which edge do you want to put? the option are:" << endl;
                cout << board.getVertices()[vertex_id].get_edges().size() << endl;
                board.getVertices()[vertex_id].print_edges();
                cout << "enter the edge id" << endl;
                break;
            } else {
                cout << "invalid option" << endl;
            }

        }
    }
}