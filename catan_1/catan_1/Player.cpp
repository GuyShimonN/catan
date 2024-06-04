#include "Player.hpp"
#include <algorithm>
#include <iostream>
namespace ariel {
    Player::Player(std::string) : name(name), victoryPoints(0) {
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

    void Player::buildRoad() {
        if (removeResource(Resource::BRICK, 1) && removeResource(Resource::WOOD, 1)) {
            roads.push_back(Road());
            std::cout << "Road built." << std::endl;
        } else {
            std::cout << "Not enough resources to build a road." << std::endl;
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
}