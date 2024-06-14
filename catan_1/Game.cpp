//
// Created by guy on 6/4/24.
//guyguy845@gmail.com
//

#include <unordered_set>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Game.h"
#include <algorithm>

using namespace std;
namespace ariel {
    Game::Game(Board &board, Player &player1, Player &player2, Player &player3)
            : board(board), player1(player1), player2(player2), player3(player3),
              player_with_most_knights(player1), knight(false)  {
        round = 0;
        max_knights = 0;
        players.push_back(&player1);
        players.push_back(&player2);
        players.push_back(&player3);
//        cout<< Resource::WOOD<<endl;

//        load_image();
        buildSettlement_for_the_first(player1, 8);
        buildSettlement_for_the_first(player2, 12);
        buildSettlement_for_the_first(player3, 44);

        buildSettlement_for_the_first(player3, 18);
        add_resource_for_the_first(player3, board.getVertices()[18]);

        buildSettlement_for_the_first(player2, 32);
        add_resource_for_the_first(player2, board.getVertices()[32]);

        buildSettlement_for_the_first(player1, 40);
        add_resource_for_the_first(player1, board.getVertices()[40]);
        play();
    }

    void Game::add_resource_for_the_first(Player &player, vertex &vertex) {
        for (Tile *tile: vertex.get_tiles()) {
            player.addResource(tile->getResource(), 1);
            cout << "player " << player.get_name() << " get 1 " << tile->getResource() << endl;
        }
    }

    void Game::buildSettlement_for_the_first(Player &player, int vertex_id) {
        if (!chack_valid_city(vertex_id)) {
            cout << "invalid option for settlement" << endl;
            return;
        }
        vertex &v = board.getVertices()[vertex_id];
        v.set_city_type(vertex::city::SETTLEMENT);
        cout << v.get_city_type() << endl;
        cout << board.getVertices()[vertex_id].get_city_type() << endl;
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
        for (vertex *p: v.get_vertices()) {
            if (p->get_city_type() != vertex::city::NONE)return false;
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
                cout << "player " << player_id << " get 1  wood" << endl;
            }
            if (resource == Resource::BRICK) {
                Game::get_player(player_id)->addResource(Resource::BRICK, 1);
                cout << "player " << player_id << " get 1  brick" << endl;
            }
            if (resource == Resource::WOOL) {
                Game::get_player(player_id)->addResource(Resource::WOOL, 1);
                cout << "player " << player_id << " get 1  wool" << endl;
            }
            if (resource == Resource::GRAIN) {
                Game::get_player(player_id)->addResource(Resource::GRAIN, 1);
                cout << "player " << player_id << " get 1  grain" << endl;
            }
            if (resource == Resource::ORE) {
                Game::get_player(player_id)->addResource(Resource::ORE, 1);
                cout << "player " << player_id << " get 1  ore" << endl;
            }
        }
        if (city == vertex::city::CITY) {
            if (resource == Resource::WOOD) {
                Game::get_player(player_id)->addResource(Resource::WOOD, 2);
                cout << "player " << player_id << " get 2  wood" << endl;
            }
            if (resource == Resource::BRICK) {
                Game::get_player(player_id)->addResource(Resource::BRICK, 2);
                cout << "player " << player_id << " get 2  brick" << endl;
            }
            if (resource == Resource::WOOL) {
                Game::get_player(player_id)->addResource(Resource::WOOL, 2);
                cout << "player " << player_id << " get 2  wool" << endl;
            }
            if (resource == Resource::GRAIN) {
                Game::get_player(player_id)->addResource(Resource::GRAIN, 2);
                cout << "player " << player_id << " get 2  grain" << endl;
            }
            if (resource == Resource::ORE) {
                Game::get_player(player_id)->addResource(Resource::ORE, 2);
                cout << "player " << player_id << " get 2  ore" << endl;
            }
        }
    }

    bool Game::GameOver() {
        for (auto &player: Game::getPlayers()) {
            if (player->getVictoryPoints() >= 10) {
//                printWinner();
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
        cout << "Round " << round << endl;
        int dice = (rand() % 6 + 1) + (rand() % 6 + 1);
        if (round < 3 && dice == 7) {
            diceRoll();
        }
        if (dice ==7){
            chack_7();
            return;
        }
        cout << "Dice roll: " << dice << endl;
        for (int i = 0; i < 19; i++) {
            if (board.getTiles()[i].getNumber() == dice) {
                cout << "Tile " << i << " produced resources" << endl;
                for (vertex *v: board.getTiles()[i].getVertices()) {
                    if (v->get_city_type() != vertex::city::NONE) {
                        cout << "Player " << v->get_player_id() << " gets a resource" << endl;
                        add_resource(v->get_player_id(), board.getTiles()[i].getResource(), v->get_city_type());
                    }
                }
            }
        }
    }

    void Game::play_turn(Player &player) {
        if (GameOver()) {
            return;
        }
        diceRoll();
        while (true) {
            cout << "player " << player.get_name() << " what do you want to do?" << endl;
            cout << "1. build a road" << endl;
            cout << "2. build a settlement" << endl;
            cout << "3. build a city" << endl;
            cout << "4. buy a development card" << endl;
            cout << "5. trade with other player" << endl;
            cout << "6. use development card" << endl;
            cout << "7. show the cards" << endl;
            cout << "8. print all info" << endl;
            cout << "9. end turn" << endl;
            int option;
            if (!(cin >> option)) {
                cin.clear();  // Clear the fail state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the rest of the line
                cout << "Invalid input. Please enter a number." << endl;
                continue;  // Skip the rest of the loop and start over
            }
            if (option == 1) {
                bild_road(player);
            }
            if (option == 2) {
//                player.buildSettlement();
                buildSettlement(player);
            }
            if (option == 3) {
                player.buildCity(board);
            }
            if (option == 4) {
                player.buyDevelopmentCard();
                chack_largest_army(player);
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
                player.trade(*get_player(other_player), Resource::Type(give - 1), give_qty, Resource::Type(receive - 1),
                             receive_qty);
            }
            if (option == 6) {
                useDevelopmentCard(player);
            }
            if (option == 7) {
                player.print_cards();
            }
            if (option == 8) {
                player.printinfo();
            }

            if (option == 9) {
                break;
            }
        }

    }

    void Game::bild_road(Player &player) {
        vector<int> possible_edges;
        if (!(player.valid_resource(Resource::BRICK, 1) && player.valid_resource(Resource::WOOD, 1))) {
            cout << "player " << player.get_name() << " does not have enough resources to build a road" << endl;
            return;  //check if the player have the resources
        }
        player.removeResource(Resource::BRICK, 1);
        player.removeResource(Resource::WOOD, 1);
        cout << "player " << player.get_name() << " which edge do you want to put? the option are:" << endl;
//        cout <<"you have :"<< player.get_edges().size() << " option."<<endl;
        int sun = player.get_edges().size();
        for (int i = 0; i < sun; i++) {
            for (size_t j = 0; j < player.get_edges()[i]->get_neighbors().size(); j++) {
                if (player.get_edges()[i]->get_neighbors()[j]->get_player_id() == "") {
                    possible_edges.push_back(player.get_edges()[i]->get_neighbors()[j]->get_id());
                    cout << player.get_edges()[i]->get_neighbors()[j]->get_id() << endl;
                }
            }
        }
        cout << "enter the edge id" << endl;
        while (true) {
            int edge_id;
            cin >> edge_id;
            if (std::find(possible_edges.begin(), possible_edges.end(), edge_id) != possible_edges.end()) {
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
        std::set<int> intSet;
        if (!player.valid_settlement(board, intSet)) {
            cout << "player " << player.get_name() << " does not have  place to build a settlement" << endl;
            return;//check if the player have the place to build
        }
        for (const auto &value: intSet) {
            std::cout << value << std::endl;
        }
        if (!(player.valid_resource(Resource::BRICK, 1) && player.valid_resource(Resource::WOOD, 1) &&
              player.valid_resource(Resource::WOOL, 1) && player.valid_resource(Resource::GRAIN, 1))) {
            cout << "player " << player.get_name() << " does not have enough resources to build a settlement" << endl;
            return;  //check if the player have the resources
        }
        cout << "enter the vertex id" << endl;
        while (true) {
            int vertex_id;
            cin >> vertex_id;
            if (std::find(intSet.begin(), intSet.end(), vertex_id) != intSet.end()) {
                board.getVertices()[vertex_id].set_city_type(vertex::city::SETTLEMENT);
                board.getVertices()[vertex_id].set_player_id(player.get_name());
                player.add_vertex(&board.getVertices()[vertex_id]);
                cout << "player " << player.get_name() << " build a settlement in vertex " << vertex_id << endl;
                player.addVictoryPoints(1);
                cout << "player " << player.get_name() << " get 1 victory point" << endl;
                break;
            } else {
                cout << "invalid option" << endl;
            }

        }
    }

    void Game::chack_7() {
        cout << "the dice roll 7" << endl;
        for(Player* p :players){
            if (p->get_num_resources() > 7) {
                int resource_qty = p->get_num_resources() / 2;
                while (resource_qty > 0) {
                    p->print_cards();
                    cout << "player " << p->get_name() << " you have more than 7 resources" << endl;
                    cout << "player " << p->get_name() << " which resource do you want to discard? you need to remove "
                         << resource_qty << endl;
                    cout << "1. wood" << endl;
                    cout << "2. brick" << endl;
                    cout << "3. wool" << endl;
                    cout << "4. grain" << endl;
                    cout << "5. ore" << endl;
                    int resource;
                    cin >> resource;
                    if (p->get_resource_sp(resource - 1) == 0) {
                        cout << "player " << p->get_name() << " does not have this resource" << endl;
                        continue;
                    }
                    p->removeResource(Resource::Type(resource - 1), 1);
                    cout << "player " << p->get_name() << " discard " << 1 << " " << Resource::Type(resource - 1)
                         << endl;
                    resource_qty--;

                }
            }
        }

    }

    bool Game::useDevelopmentCard(Player &player) {
        cout << "player " << player.get_name() << " which development card do you want to use?" << endl;
        player.printDevelopmentCards();
        int option;
        cin >> option;
        if (option == 1) {
            if (player.getDevelopmentCards()[0] > 0) {
                cout << "player " << player.get_name() << " use a knight card its on the buy you have a "
                     << player.getDevelopmentCards()[0] << "KNIGHT" << endl;
                return true;
            } else {
                cout << "invalid option" << endl;
                return false;
            }
        }
        if (option == 2) {
            if (player.getDevelopmentCards()[1] > 0) {
                cout << "the victory point card it was on use and the victory point update when you buy this card"
                     << endl;
            } else {
                cout << "invalid option" << endl;
                return false;
            }
        }
        if (option == 4) {
            if (player.getDevelopmentCards()[3] > 0) {
                cout << "whitch resource do you want to take from the other player?" << endl;
                cout << "1. wood" << endl;
                cout << "2. brick" << endl;
                cout << "3. wool" << endl;
                cout << "4. grain" << endl;
                cout << "5. ore" << endl;
                int resource;
                cin >> resource;

                for (Player *p: players) {
                    if (p->get_name() != player.get_name()) {
                        player.addResource(Resource::Type(resource - 1), p->get_resource_sp(resource - 1));
                        cout << "player " << player.get_name() << " get " << p->get_resource_sp(resource - 1) << " "
                             << Resource::Type(resource - 1) << endl;
                        p->removeResource(Resource::Type(resource - 1), p->get_resource_sp(resource - 1));
                        cout << "player " << p->get_name() << " lose " << p->get_resource_sp(resource - 1) << " "
                             << Resource::Type(resource - 1) << endl;
                    }
                }
                player.getDevelopmentCards()[3]--;
                return true;
            } else {
                cout << "invalid option" << endl;
                return false;
            }
        }
        if (option == 3) {
            if (player.getDevelopmentCards()[2] > 0) {
                for(int i=0;i<2;i++) {
                    player.addResource(Resource::WOOD, 1);
                    player.addResource(Resource::BRICK, 1);
                    bild_road(player);
                }
                player.getDevelopmentCards()[2]--;
                return true;
            } else {
                cout << "invalid option" << endl;
                return false;
            }
        }
        if (option == 5) {
            if (player.getDevelopmentCards()[4] > 0) {
                for (int i = 0; i < 2; i++) {
                    cout << "whitch resource do you want to take?" << endl;
                    cout << "1. wood" << endl;
                    cout << "2. brick" << endl;
                    cout << "3. wool" << endl;
                    cout << "4. grain" << endl;
                    cout << "5. ore" << endl;
                    int resource;
                    cin >> resource;
                    player.addResource(Resource::Type(resource - 1), 1);
                    cout << "player " << player.get_name() << " get 1 " << Resource::Type(resource - 1) << endl;
                }
                player.getDevelopmentCards()[4]--;
            } else {
                cout << "invalid option" << endl;
                return false;
            }
        }
        return true;
    }

    void Game::chack_largest_army(Player &player) {
        if (max_knights < 3) {
            if (player.get_knights() > max_knights) {
                max_knights = player.get_knights();
//                player_with_most_knights = player;
            }
        } else if (max_knights == 2 && player.get_knights() == 3) {
            player_with_most_knights = player;
            player_with_most_knights = player;
            player.addVictoryPoints(2);
            knight = true;
            cout << "player " << player.get_name() << " get 2 victory points" << endl;
        } else {
            if (player != player_with_most_knights && knight) {
                if (player.get_knights() > player_with_most_knights.get_knights()) {
                    player_with_most_knights.addVictoryPoints(-2);
                    std::cout << "player " << player_with_most_knights.get_name() << " lose 2 victory points"
                              << std::endl;
                    player_with_most_knights = player;
                    player_with_most_knights.addVictoryPoints(2);
                    std::cout << "player " << player_with_most_knights.get_name() << " get 2 victory points"
                              << std::endl;
                }
            }
        }
    }


}