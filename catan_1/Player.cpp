//guyguy845@gmail.com
#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include "edge.h"
#include "Board.h"
namespace ariel {

    Player::Player(std::string playerName) : name(playerName), victoryPoints(0) {
        // Resize the vector to accommodate all resource types
        resources.resize(static_cast<size_t>(60), 0);  // Assuming TOTAL_RESOURCES is a valid enum value or constant that reflects the total number of resources.

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
    bool Player::valid_resource(Resource::Type type,int quantity){
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
      if(!(valid_resource(Resource::BRICK,1) && valid_resource(Resource::WOOD,1) && valid_resource(Resource::WOOL,1) && valid_resource(Resource::GRAIN,1))){
          std::cout << "Not enough resources to build a settlement." << std::endl;
          return;
      }

            buildings.push_back(Building(Building::SETTLEMENT));
            addVictoryPoints(1);
            std::cout << "Settlement built. Total victory points: " << victoryPoints << std::endl;

    }

    void Player::buildCity() {
        if (removeResource(Resource::ORE, 3) && removeResource(Resource::GRAIN, 2)) {
            auto it = std::find_if(buildings.begin(), buildings.end(), [](const Building &b) {
                return b.getType() == Building::SETTLEMENT;
            });
            if (it != buildings.end()) {
                buildings.erase(it);
                buildings.push_back(Building(Building::CITY));
                addVictoryPoints(1); // Net gain of 1 point (lose 1 for settlement, gain 2 for city)
                std::cout << "City built. Total victory points: " << victoryPoints << std::endl;
            }
        } else {
            std::cout << "Not enough resources to build a city." << std::endl;
        }
    }

    bool Player::buildRoad() {
        if(valid_resource(Resource::BRICK,1) && valid_resource(Resource::WOOD,1)){
            removeResource(Resource::BRICK, 1);
            removeResource(Resource::WOOD, 1) ;
//                roads.push_back(Road());
                std::cout << "Road built." << std::endl;
                return true;
            } else {
                std::cout << "Not enough resources to build a road." << std::endl;
                return false;
            }
    }
    bool Player::buyDevelopmentCard() {
        if (valid_resource(Resource::ORE, 1) && valid_resource(Resource::WOOL, 1) &&
            valid_resource(Resource::GRAIN, 1)) {
            addResource(Resource::ORE, -1);
            addResource(Resource::WOOL, -1);
            addResource(Resource::GRAIN, -1);

//            developmentCards.push_back(DevelopmentCard(DevelopmentCard::VICTORY_POINT));
//            addVictoryPoints(1);
            std::cout << "Development card bought. Total victory points: " << victoryPoints << std::endl;
            return true;
        }
//        if (removeResource(Resource::ORE, 1) && removeResource(Resource::WOOL, 1) &&
//            removeResource(Resource::GRAIN, 1)) {
//            // Simplified to always give a Victory Point card for now
//            developmentCards.push_back(DevelopmentCard(DevelopmentCard::VICTORY_POINT));
//            addVictoryPoints(1);
//            std::cout << "Development card bought. Total victory points: " << victoryPoints << std::endl;
//        }
        else {
            std::cout << "Not enough resources to buy a development card." << std::endl;
            return false;
        }
    }

    void Player::trade(Player &other, Resource::Type give, int giveQty, Resource::Type receive, int receiveQty) {
        if(!(valid_resource(give,giveQty) && other.valid_resource(receive,receiveQty))){
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
//        if (removeResource(give, giveQty) && other.removeResource(receive, receiveQty)) {
//            addResource(receive, receiveQty);
//            other.addResource(give, giveQty);
//            std::cout << "Trade completed." << std::endl;
//        } else {
//            std::cout << "Trade failed due to insufficient resources." << std::endl;
//            // Reverse the resource removal if trade fails
//            addResource(give, giveQty);
//            other.addResource(receive, receiveQty);
//        }
    }
    int Player::longestRoad() {
        int longest = 0;
        for (edge* e : edges) {
            std::unordered_set<edge*> visited;
            longest = std::max(longest, DFS(e, visited));
        }
        return longest;
    }
    int Player::DFS(edge* current, std::unordered_set<edge*>& visited) {
        visited.insert(current);
        int longest = 0;
        for (edge* neighbor : current->get_neighbors()){
            if (neighbor->get_player_id() == this->get_name() && visited.find(neighbor) == visited.end()) {
                longest = std::max(longest, DFS(neighbor, visited));
            }
        }
        visited.erase(current);
        return 1 + longest;
    }
    std::vector<edge*>& Player::get_edges() {
        return edges;
    }
    void Player::add_edge(edge* edge) {
        edges.push_back(edge);
    }
    std::vector<vertex*>& Player::get_vertexes() {
        return vertexes;
    }
    void Player::add_vertex(vertex* vertex) {
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
    bool Player::printPossibleSettlements(Board& board) {
        int sum = 0;
        std::cout << "Player " << name << " can build a settlement at the following vertices:" << std::endl;
        for (vertex v : board.getVertices()) {
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

    bool Player::isConnectedToRoad(vertex& v) {
        for (edge* e : v.get_edges()) {
            if (e->get_player_id() == this->get_name()) {
                std::cout << "connected to road" << std::endl;
                return true;
            }
            std::cout << "not connected to road edge: " << e->get_id()<<std::endl;
        }
        return false;
    }

    bool Player::noAdjacentBuildings(vertex& v) {
        for (vertex* neighbor : v.get_verrices()) {
            if (neighbor->get_city_type() != vertex::city::NONE) {
                std::cout << "adjacent building" << std::endl;
                return false;
            }
        }
        return true;
    }
    void Player::addDevelopmentCard(DevelopmentCard card){
        developmentCards.push_back(card);
    }
    bool Player::valid_satlement(Board& b){
        for (edge *e : edges) {
            for (edge *neighbor : e->get_neighbors()) {
               if (neighbor->)
            }
        }
             for (vertex *v : e->get_vertices()) {
           if (v->get_city_type() != vertex::city::NONE) {
               return false;
           }
       }
   }


}