#ifndef RESOURCE_H
#define RESOURCE_H

class Resource {
public:
    enum Type { WOOD, BRICK, WOOL, GRAIN, ORE, NONE };

    Resource(Type type, int quantity = 0);

    Type getType() const;
    int getQuantity() const;
    void addQuantity(int quantity);
    void removeQuantity(int quantity);

private:
    Type type;
    int quantity;
};

#endif // RESOURCE_H
