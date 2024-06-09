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
namespace ariel {
    class Game {
    public:
        Game( Board& board,Player& player1, Player& player2,Player& player3);
        void play();
        bool GameOver();
        int diceRoll();
        void printWinner();
        bool chack_valid_city(int ver_id);
        void load_image();
        Player* get_player(std::string id);
        std::vector<Player*>& getPlayers();

    private:
        Board& board;
        Player& player1;
        Player& player2;
        Player& player3;
        void buildSettlement_for_the_first(Player &player,int vertex_id);
        std::vector<Player*> players;
        void add_resource(std::string player_id, Resource::Type resource, vertex::city city_type);


    };

}
#endif //CPP_EX3_24_MAIN_GAME_H
