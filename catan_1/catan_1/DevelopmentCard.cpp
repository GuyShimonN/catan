#include "DevelopmentCard.h"

DevelopmentCard::DevelopmentCard(Type type) : type(type) {}

DevelopmentCard::Type DevelopmentCard::getType() const {
    return type;
}
