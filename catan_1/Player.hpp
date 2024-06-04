#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Resource.hpp"
#include "DevelopmentCard.h"
#include "Building.h"
#include "Road.h"
#include <string>
class Player {
public:
    Player(std::string name);

    std::string get_name() const;
    int getVictoryPoints() const;
    void addVictoryPoints(int points);

    void addResource(Resource::Type type, int quantity);
    bool removeResource(Resource::Type type, int quantity);
    void buildSettlement();
    void buildCity();
    void buildRoad();
    void buyDevelopmentCard();

    void trade(Player& other, Resource::Type give, int giveQty, Resource::Type receive, int receiveQty);

private:
    std::string name;
    int victoryPoints;
    std::vector<Resource> resources;
    std::vector<DevelopmentCard> developmentCards;
    std::vector<Building> buildings;
    std::vector<Road> roads;
};

#endif // PLAYER_H
