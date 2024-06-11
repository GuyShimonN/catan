    ////
    //// Created by guy on 5/31/24.
    ////
//guyguy845@gmail.com
    #ifndef EDGE_H
    #define EDGE_H

    #include <vector>
    #include "vertex.h"
    #include <string>
    namespace ariel {
    class vertex; // Forward declaration
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
            void add_vertex(vertex* v);
            std::vector<vertex*>& get_vertexes() { return vertexes; }

        private:
            int id;
            int sub_id;
            std::vector<edge*>neighbors;
            std::string player_id;
            std::vector<vertex*> vertexes;
        };

    } // namespace ariel

    #endif // EDGE_H
