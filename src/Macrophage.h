#ifndef ECOSYSTEM_MACROPHAGE_H
#define ECOSYSTEM_MACROPHAGE_H

#include "cell.h"


class Macrophage : public Cell {

public:

    explicit Macrophage(sf::Vector2f center = {800, 450}, float radius = 100, int pointCount = 180, sf::Color color = sf::Color::Yellow);
};

#endif //ECOSYSTEM_MACROPHAGE_H
