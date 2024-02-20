#ifndef ECOSYSTEM_ANTIBODY_H
#define ECOSYSTEM_ANTIBODY_H


#include "cell.h"

class Antibody : public Cell {

public:
    
    explicit Antibody(sf::Vector2f center = {800, 450}, float radius = 100, int pointCount = 180, sf::Color color = sf::Color::Cyan);
};

#endif //ECOSYSTEM_ANTIBODY_H
