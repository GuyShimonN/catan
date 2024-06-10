//
// Created by guy on 6/4/24.
//

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

    };

}
#endif //CPP_EX3_24_MAIN_GAME_H
