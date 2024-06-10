//guyguy845@gmail.com
#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H

class DevelopmentCard {
public:
    enum Type { KNIGHT, VICTORY_POINT, ROAD_BUILDING, MONOPOLY, YEAR_OF_PLENTY };

    DevelopmentCard();

    Type getType() const;
    DevelopmentCard Drow();
private:
    Type type;
};

#endif // DEVELOPMENTCARD_H
