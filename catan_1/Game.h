//
// Created by guy on 6/4/24.
//
//guyguy845@gmail.com
#ifndef CPP_EX3_24_MAIN_GAME_H
#define CPP_EX3_24_MAIN_GAME_H
#include "Player.hpp"
#include "Board.h"
#include "Resource.hpp"
#include "vertex.h"
#include <vector>
#include <opencv2/opencv.hpp>
namespace ariel {
    class Game {
        enum Type { KNIGHT, VICTORY_POINT, ROAD_BUILDING, MONOPOLY, YEAR_OF_PLENTY };

    public:
        Game( Board& board,Player& player1, Player& player2,Player& player3);
        void play();
        bool GameOver();
        void diceRoll();
        void printWinner();
        bool chack_valid_city(int ver_id);
        void load_image();
        Player* get_player(std::string id);
        std::vector<Player*>& getPlayers();
        void buildSettlement(Player& player);
        std::vector<int>dev_cards;
        bool useDevelopmentCard(Player &player);

    private:
        Board& board;
        Player& player1;
        Player& player2;
        Player& player3;
        void buildSettlement_for_the_first(Player &player,int vertex_id);
        std::vector<Player*> players;
        void add_resource(std::string player_id, Resource::Type resource, enum vertex::city city_type);
        void play_turn(Player& player);
        void bild_road(Player& player);
        int round ;
        void add_resource_for_the_first(Player &player, vertex &vertex);
        void add_development_card(Player &player);
         Player& player_with_most_knights;
         void chack_largest_army(Player &player);
         int max_knights;
         bool knight;
       void chack_7();


    };

}
#endif //CPP_EX3_24_MAIN_GAME_H
