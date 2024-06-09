#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include "edge.h"
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
        if (removeResource(Resource::BRICK, 1) && removeResource(Resource::WOOD, 1) &&
            removeResource(Resource::WOOL, 1) && removeResource(Resource::GRAIN, 1)) {
            buildings.push_back(Building(Building::SETTLEMENT));
            addVictoryPoints(1);
            std::cout << "Settlement built. Total victory points: " << victoryPoints << std::endl;
        } else {
            std::cout << "Not enough resources to build a settlement." << std::endl;
        }
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
    void Player::buyDevelopmentCard() {
        if (removeResource(Resource::ORE, 1) && removeResource(Resource::WOOL, 1) &&
            removeResource(Resource::GRAIN, 1)) {
            // Simplified to always give a Victory Point card for now
            developmentCards.push_back(DevelopmentCard(DevelopmentCard::VICTORY_POINT));
            addVictoryPoints(1);
            std::cout << "Development card bought. Total victory points: " << victoryPoints << std::endl;
        } else {
            std::cout << "Not enough resources to buy a development card." << std::endl;
        }
    }

    void Player::trade(Player &other, Resource::Type give, int giveQty, Resource::Type receive, int receiveQty) {
        if (removeResource(give, giveQty) && other.removeResource(receive, receiveQty)) {
            addResource(receive, receiveQty);
            other.addResource(give, giveQty);
            std::cout << "Trade completed." << std::endl;
        } else {
            std::cout << "Trade failed due to insufficient resources." << std::endl;
            // Reverse the resource removal if trade fails
            addResource(give, giveQty);
            other.addResource(receive, receiveQty);
        }
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

}