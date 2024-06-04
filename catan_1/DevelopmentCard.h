#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H

class DevelopmentCard {
public:
    enum Type { KNIGHT, VICTORY_POINT, ROAD_BUILDING, MONOPOLY, YEAR_OF_PLENTY };

    DevelopmentCard(Type type);

    Type getType() const;

private:
    Type type;
};

#endif // DEVELOPMENTCARD_H
