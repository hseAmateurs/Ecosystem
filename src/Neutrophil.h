#ifndef ECOSYSTEM_NEUTROPHIL_H
#define ECOSYSTEM_NEUTROPHIL_H

#include "cell.h"


class Neutrophil : public Cell {

public:

    explicit Neutrophil(sf::Vector2f center = {800, 450}, float radius = 100, int pointCount = 180, sf::Color color = sf::Color::Green);
};

#endif //ECOSYSTEM_NEUTROPHIL_H
