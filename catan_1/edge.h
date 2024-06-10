    ////
    //// Created by guy on 5/31/24.
    ////
    //
    //#ifndef CPP_EX3_24_MAIN_EDGE_H
    //#define CPP_EX3_24_MAIN_EDGE_H
    //
    //#include "Player.hpp"
    //namespace ariel {
    //    class edge {
    //    public:
    //        edge(int id, int sub_id); //constructor
    //        ~edge();
    //
    //        bool operator==(const edge &rhs) const;
    //
    //        int get_id() { return id; };
    //
    //        int get_sub_id() { return sub_id; };
    //
    //        Player get_player() { return player; };
    //
    //    private:
    //        int id;
    //        int sub_id;
    //        Player player;
    //    };
    //
    //}
    //#endif //CPP_EX3_24_MAIN_EDGE_H


    #ifndef EDGE_H
    #define EDGE_H

    #include <vector>
    #include "vertex.h"
    #include <string>
    namespace ariel {
        class edge {
        public:
            edge(int id, int sub_id);
            bool operator==(const edge &rhs) const;
            int get_id() const { return id; }
            int get_sub_id() const { return sub_id; }
            void add_neighbor(edge* e);
            std::vector<edge*>& get_neighbors()  { return neighbors; }
            void set_player_id(std::string id);
            std::string get_player_id() const { return player_id; }

        private:
            int id;
            int sub_id;
            std::vector<edge*>neighbors;
            std::string player_id;
        };

    } // namespace ariel

    #endif // EDGE_H
