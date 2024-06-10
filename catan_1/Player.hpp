//guyguy845@gmail.com
#ifndef PLAYER_H
#define PLAYER_H
#include <unordered_set>
#include <vector>
#include "Resource.hpp"
#include "DevelopmentCard.h"
#include "Building.h"
#include "Road.h"
#include <string>
#include "Board.h"
#include "vertex.h"

namespace ariel {
    class edge; // Forward declaration
    class vertex; // Forward declaration
    class Board; // Forward declaration
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
        bool valid_resource(Resource::Type type,int quantity);
        bool buildRoad();
        void print_cards();

        bool buyDevelopmentCard();

        void trade(Player &other, Resource::Type give, int giveQty, Resource::Type receive, int receiveQty);
        std::vector<ariel::edge*>& get_edges();
        void add_edge(ariel::edge* edge);
        std::vector<ariel::vertex*>& get_vertexes();
        void add_vertex(ariel::vertex *vertex);
        int longestRoad();
        void addDevelopmentCard(DevelopmentCard card);
        bool printPossibleSettlements(Board& b);
    private:
        std::string name;
        int victoryPoints;
        std::vector<int> resources;
        std::vector<DevelopmentCard> developmentCards;
        std::vector<Building> buildings;
        std::vector<Road> roads;
        std::vector<ariel::edge*> edges;
        std::vector<ariel::vertex*> vertexes;
        int DFS(edge* current, std::unordered_set<edge*>& visited);
        bool isConnectedToRoad(vertex& v);
        bool noAdjacentBuildings(vertex& v);
    };
}
#endif // PLAYER_H
