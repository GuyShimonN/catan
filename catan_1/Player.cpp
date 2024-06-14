//guyguy845@gmail.com
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include "edge.h"
#include "Board.h"


namespace ariel {

    Player::Player(std::string playerName) : name(playerName), victoryPoints(0) {
        developmentCards = std::vector<int>(5, 0);

        // Resize the vector to accommodate all resource types
        resources.resize(static_cast<size_t>(60),
                         0);  // Assuming TOTAL_RESOURCES is a valid enum value or constant that reflects the total number of resources.

        // Initialize resource counts to zero
        resources[Resource::WOOD] = 0;
        resources[Resource::BRICK] = 0;
        resources[Resource::WOOL] = 0;
        resources[Resource::GRAIN] = 0;
        resources[Resource::ORE] = 0;
    }

    std::string Player::get_name() const {
        return name;
    }

    int Player::getVictoryPoints() const {
        return victoryPoints;
    }

    void Player::addVictoryPoints(int points) {
        victoryPoints += points;
    }

    void Player::addResource(Resource::Type type, int quantity) {
        resources[type] += quantity;
    }

    bool Player::valid_resource(Resource::Type type, int quantity) {
        if (resources[type] < quantity) {
            return false;
        }
        return true;
    }

    bool Player::removeResource(Resource::Type type, int quantity) {
        if (resources[type] < quantity) {
            return false;
        }
        resources[type] -= quantity;
        return true;
    }

    void Player::buildSettlement() {
        if (!(valid_resource(Resource::BRICK, 1) && valid_resource(Resource::WOOD, 1) &&
              valid_resource(Resource::WOOL, 1) && valid_resource(Resource::GRAIN, 1))) {
            std::cout << "Not enough resources to build a settlement." << std::endl;
            return;
        }

//        buildings.push_back(Building(Building::SETTLEMENT));
        addVictoryPoints(1);
        std::cout << "Settlement built. Total victory points: " << victoryPoints << std::endl;

    }



    void Player::buildCity(Board &b) {
        std::set<int> intSet;
        std::cout << "the option for building a city is: " << std::endl;
        for (vertex *v: vertexes) {
            if (v->get_city_type() == vertex::city::SETTLEMENT) {
                std::cout << "Vertex " << v->get_id() << std::endl;
                intSet.insert(v->get_id());
            }
        }
        if (intSet.size() > 0 && valid_resource(Resource::ORE, 3) && valid_resource(Resource::GRAIN, 2)) {
            std::cout << "Enter the vertex id to build a city: ";
            while (true) {
                int vertex_id;
                std::cin >> vertex_id;
                if (intSet.find(vertex_id) != intSet.end()) {
                    removeResource(Resource::ORE, 3);
                    removeResource(Resource::GRAIN, 2);
                    b.getVertices()[vertex_id].set_city_type(vertex::city::CITY);
                    addVictoryPoints(1);
                    std::cout << "City built. Total victory points: " << victoryPoints << std::endl;
                    break;
                }
            }
        } else {
            std::cout << "Not enough resources to build a city." << std::endl;
        }

    }

    bool Player::buildRoad() {
        if (valid_resource(Resource::BRICK, 1) && valid_resource(Resource::WOOD, 1)) {
            removeResource(Resource::BRICK, 1);
            removeResource(Resource::WOOD, 1);
//                roads.push_back(Road());
            std::cout << "Road built." << std::endl;
            return true;
        } else {
            std::cout << "Not enough resources to build a road." << std::endl;
            return false;
        }
    }

    bool Player::buyDevelopmentCard(std::vector<int>& dev_cards) {
        if (valid_resource(Resource::ORE, 1) && valid_resource(Resource::WOOL, 1) &&
            valid_resource(Resource::GRAIN, 1)) {
            addResource(Resource::ORE, -1);
            addResource(Resource::WOOL, -1);
            addResource(Resource::GRAIN, -1);

            // Check if there are any cards left in the deck
            if (dev_cards.empty()) {
                std::cout << "No more development cards left in the deck." << std::endl;
                return false;
            }

            // Draw a card from the deck
            int randomIndex = rand() %dev_cards.size();
            int drawnCard =dev_cards[randomIndex];

            // Remove the drawn card from the deck
          dev_cards.erase(dev_cards.begin() + randomIndex);

            // Add the drawn card to the player's hand
//            developmentCards[drawnCard]++;

            // If the drawn card is a victory point card, increase the player's victory points
            if (drawnCard == 0) {
                developmentCards[KNIGHT]++;
                std::cout << "Development card KNIGHT bought." << std::endl;
            } else if (drawnCard == 1) {
                developmentCards[VICTORY_POINT]++;
                addVictoryPoints(1);
                std::cout << "Development card bought VICTORY POINT. Total victory points: " << victoryPoints << std::endl;
            } else if (drawnCard == 2) {
                developmentCards[ROAD_BUILDING]++;
                std::cout << "Development card ROAD_BUILDING bought." << std::endl;
            } else if (drawnCard == 3) {
                developmentCards[MONOPOLY]++;
                std::cout << "Development card MONOPOLY bought." << std::endl;
            } else {
                developmentCards[YEAR_OF_PLENTY]++;
                std::cout << "Development card YEAR_OF_PLENTY bought." << std::endl;
            }
            std::cout << "Development card bought. Total victory points: " << victoryPoints << std::endl;

            return true;
        }
        else {
            std::cout << "Not enough resources to buy a development card." << std::endl;
            return false;
        }
    }
    void Player::trade(Player &other, Resource::Type give, int giveQty, Resource::Type receive, int receiveQty) {
        if (!(valid_resource(give, giveQty) && other.valid_resource(receive, receiveQty))) {
            std::cout << "Trade failed due to insufficient resources." << std::endl;
            return;
        }
        removeResource(give, giveQty);
        other.addResource(give, giveQty);
        other.removeResource(receive, receiveQty);
        addResource(receive, receiveQty);
        std::cout << "Trade completed." << std::endl;
        print_cards();
        other.print_cards();

    }

    int Player::longestRoad() {
        int longest = 0;
        for (edge *e: edges) {
            std::unordered_set<edge *> visited;
            longest = std::max(longest, DFS(e, visited));
        }
        return longest;
    }

    int Player::DFS(edge *current, std::unordered_set<edge *> &visited) {
        visited.insert(current);
        int longest = 0;
        for (edge *neighbor: current->get_neighbors()) {
            if (neighbor->get_player_id() == this->get_name() && visited.find(neighbor) == visited.end()) {
                longest = std::max(longest, DFS(neighbor, visited));
            }
        }
        visited.erase(current);
        return 1 + longest;
    }

    std::vector<edge *> &Player::get_edges() {
        return edges;
    }

    void Player::add_edge(edge *edge) {
        edges.push_back(edge);
    }

    std::vector<vertex *> &Player::get_vertexes() {
        return vertexes;
    }

    void Player::add_vertex(vertex *vertex) {
        vertexes.push_back(vertex);
    }

    void Player::print_cards() {
        std::cout << "Player " << name << " has the following resources:" << std::endl;
        std::cout << "Wood: " << resources[Resource::WOOD] << std::endl;
        std::cout << "Brick: " << resources[Resource::BRICK] << std::endl;
        std::cout << "Wool: " << resources[Resource::WOOL] << std::endl;
        std::cout << "Grain: " << resources[Resource::GRAIN] << std::endl;
        std::cout << "Ore: " << resources[Resource::ORE] << std::endl;
    }


    bool Player::printPossibleSettlements(Board &board) {
        int sum = 0;
        std::cout << "Player " << name << " can build a settlement at the following vertices:" << std::endl;
        for (vertex v: board.getVertices()) {
            if (v.get_city_type() == vertex::NONE && isConnectedToRoad(v) && noAdjacentBuildings(v)) {
                std::cout << "Vertex " << sum << ": " << v.get_id() << std::endl;
                sum++;
            }
        }
        if (sum == 0) {
            std::cout << "No possible settlements." << std::endl;
            return false;
        }
        return true;
    }

    bool Player::isConnectedToRoad(vertex &v) {
        for (edge *e: v.get_edges()) {
            if (e->get_player_id() == this->get_name()) {
                std::cout << "connected to road" << std::endl;
                return true;
            }
            std::cout << "not connected to road edge: " << e->get_id() << std::endl;
        }
        return false;
    }

    bool Player::noAdjacentBuildings(vertex &v) {
        for (vertex *neighbor: v.get_vertices()) {
            if (neighbor->get_city_type() != vertex::city::NONE) {
                std::cout << "adjacent building" << std::endl;
                return false;
            }
        }
        return true;
    }



    bool Player::valid_settlement(Board &b, std::set<int> &intSet) {
        bool flagg = false;
        for (edge *e: edges) {
            for (edge *neighbor: e->get_neighbors()) {
                if (neighbor->get_player_id() == this->get_name()) {
                    if (neighbor->get_vertexes()[0]->get_id() != e->get_vertexes()[0]->get_id() &&
                        neighbor->get_vertexes()[0]->get_id() != e->get_vertexes()[1]->get_id()) {
                        bool flag = true;
                        for (vertex *v: neighbor->get_vertexes()[0]->get_vertices()) {
                            if (v->get_city_type() != vertex::city::NONE) {
                                flag = false;
                            }
                            if (flag && neighbor->get_vertexes()[0]->get_player_id() != this->get_name() &&
                                chack_valid_city(neighbor->get_vertexes()[0]->get_id(), b)) {
//                            std::cout << "vertex  1 id: " << neighbor->get_vertexes()[0]->get_id()<< std::endl;
                                flagg = true;
                                intSet.insert(neighbor->get_vertexes()[0]->get_id());
                            }
                        }
                    }
                    if (neighbor->get_vertexes()[1]->get_id() != e->get_vertexes()[0]->get_id() &&
                        neighbor->get_vertexes()[1]->get_id() != e->get_vertexes()[1]->get_id()) {
//                    std::cout << "vertex id: " << neighbor->get_vertexes()[1]->get_id() << std::endl;
                        bool flag = true;
                        for (vertex *v: neighbor->get_vertexes()[1]->get_vertices()) {
                            if (v->get_city_type() != vertex::city::NONE) {
                                flag = false;
//                            std::cout << "vertex id is in use: " << v->get_id() << std::endl;

                            }
                            if (flag && neighbor->get_vertexes()[1]->get_player_id() != this->get_name() &&
                                chack_valid_city(neighbor->get_vertexes()[1]->get_id(), b)) {
//                            std::cout << "vertex 2 id: " << neighbor->get_vertexes()[1]->get_id() << std::endl;
                                flagg = true;
                                intSet.insert(neighbor->get_vertexes()[1]->get_id());
                            }
                        }

                    }
                    if (e->get_vertexes()[0]->get_id() != neighbor->get_vertexes()[0]->get_id() &&
                        e->get_vertexes()[0]->get_id() != neighbor->get_vertexes()[1]->get_id()) {
//                    std::cout << "vertex id: " << e->get_vertexes()[0]->get_id() << std::endl;
                        bool flag = true;
                        for (vertex *v: e->get_vertexes()[0]->get_vertices()) {
                            if (v->get_city_type() != vertex::city::NONE) {
                                flag = false;
//                                std::cout << "vertex 3 id is in use: " << v->get_id() << std::endl;

                            }
                            if (flag && e->get_vertexes()[0]->get_player_id() != this->get_name() &&
                                chack_valid_city(e->get_vertexes()[0]->get_id(), b)) {
//                            std::cout << "vertex id: " << e->get_vertexes()[0]->get_id() << std::endl;
                                flagg = true;
                                intSet.insert(e->get_vertexes()[0]->get_id());
                            }
                        }
                    }
                    if (e->get_vertexes()[1]->get_id() != neighbor->get_vertexes()[0]->get_id() &&
                        e->get_vertexes()[1]->get_id() != neighbor->get_vertexes()[1]->get_id()) {
//                    std::cout << "vertex id: " << e->get_vertexes()[1]->get_id() << std::endl;

                        bool flag = true;
                        for (vertex *v: e->get_vertexes()[1]->get_vertices()) {
                            if (v->get_city_type() != vertex::city::NONE) {
                                flag = false;
//                            std::cout << "vertex id is in use: " << v->get_id() << std::endl;

                            }
                            if (flag && e->get_vertexes()[1]->get_player_id() != this->get_name() &&
                                chack_valid_city(e->get_vertexes()[1]->get_id(), b)) {

//                                std::cout << "vertex  4 id: " << e->get_vertexes()[1]->get_id() << std::endl;
                                flagg = true;
                                intSet.insert(e->get_vertexes()[1]->get_id());

                            }
                        }
                    }

                }
            }
        }
        return flagg;
    }

    bool Player::chack_valid_city(int ver_id, Board &board) {
        vertex v = board.getVertices()[ver_id];
        for (vertex *p: v.get_vertices()) {
            if (p->get_city_type() != vertex::city::NONE)return false;
        }
        return true;

    }
    void Player:: printinfo(){
        std::cout << "Player " << name << " has the following resources:" << std::endl;
        std::cout << "Wood: " << resources[Resource::WOOD] << std::endl;
        std::cout << "Brick: " << resources[Resource::BRICK] << std::endl;
        std::cout << "Wool: " << resources[Resource::WOOL] << std::endl;
        std::cout << "Grain: " << resources[Resource::GRAIN] << std::endl;
        std::cout << "Ore: " << resources[Resource::ORE] << std::endl;
        std::cout << "Player " << name << " has the following victory points:" << std::endl;
        std::cout << "Victory Points: " << victoryPoints << std::endl;
        std::cout << "Player " << name << " has the following development cards:" << std::endl;
        printDevelopmentCards();
        std::cout << "Player " << name << " has the following buildings:" << std::endl;
        for(vertex *v: vertexes){
            if(v->get_city_type() == vertex::city::SETTLEMENT){
                std::cout << "Settlement: " << v->get_id() << std::endl;
            }
            if(v->get_city_type() == vertex::city::CITY){
                std::cout << "City: " << v->get_id() << std::endl;
            }
        }
        std::cout << "Player " << name << " has the following roads:" << std::endl;
        for(edge *e: edges){
            std::cout << "Road: " << e->get_id() << std::endl;
        }
    }
    void Player::printDevelopmentCards() {
        std::cout << "Player " << name << " has the following development cards:" << std::endl;
        for (size_t i = 0; i < developmentCards.size(); i++) {
            if (i==0) {
                std::cout << "1. Development Card: Knight number "<<developmentCards[0] << std::endl;
            } else if (i==1) {
                std::cout << "2. Development Card: VICTORY POINT number: "<<developmentCards[1] << std::endl;
            } else if (i==2) {
                std::cout << "3. Development Card: Road Building number: "<<developmentCards[2] << std::endl;
            } else if (i==3) {
                std::cout << "4. Development Card: Monopoly number:"<<developmentCards[3] << std::endl;
            } else if (i==4) {
                std::cout << "5. Development Card: Year of Plenty number: "<<developmentCards[4] << std::endl;
            }
        }
    }
    int Player::get_num_resources() const{
        int sum = 0;
        for (size_t i = 0; i < resources.size(); i++) {
            sum += resources[i];
        }
        return sum;
    }


}
