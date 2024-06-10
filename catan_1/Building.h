//guyguy845@gmail.com
#ifndef BUILDING_H
#define BUILDING_H

class Building {
public:
    enum Type { SETTLEMENT, CITY };

    Building(Type type);

    Type getType() const;

private:
    Type type;
};

#endif // BUILDING_H
