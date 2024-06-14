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
#include <set>

namespace ariel {
    class edge; // Forward declaration
    class vertex; // Forward declaration
    class Board; // Forward declaration
    class Player {
        enum Type { KNIGHT, VICTORY_POINT, ROAD_BUILDING, MONOPOLY, YEAR_OF_PLENTY };

    public:
        Player(std::string name);

        std::string get_name() const;

        int get_num_resources() const;
        int getVictoryPoints() const;

        void addVictoryPoints(int points);
        int get_resource_sp(int i){return resources[i];}

        void addResource(Resource::Type type, int quantity);

        bool removeResource(Resource::Type type, int quantity);

        void buildSettlement();

        void buildCity(Board &b);
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
        bool valid_settlement(Board &b, std::set<int> &intSet);
        void printinfo();
        void printDevelopmentCards();
        bool operator!=(const Player& other) const {
            return name != other.get_name();
        }
        int get_knights(){return developmentCards[0];}
        std::vector<int>& getDevelopmentCards(){return developmentCards;}
    private:
        std::string name;
        int victoryPoints;
        std::vector<int> resources;
        std::vector<int> developmentCards;
        std::vector<Building> buildings;
        std::vector<Road> roads;
        std::vector<ariel::edge*> edges;
        std::vector<ariel::vertex*> vertexes;
        int DFS(edge* current, std::unordered_set<edge*>& visited);
        bool isConnectedToRoad(vertex& v);
        bool noAdjacentBuildings(vertex& v);
        bool chack_valid_city(int ver_id, Board &board);
    };
}
#endif // PLAYER_H
