//guyguy845@gmail.com
#include "DevelopmentCard.h"
#include <cstdlib>
DevelopmentCard::DevelopmentCard() {
    this->type = static_cast<Type>(rand() % 5);
}

DevelopmentCard::Type DevelopmentCard::getType() const {
    return type;
}

