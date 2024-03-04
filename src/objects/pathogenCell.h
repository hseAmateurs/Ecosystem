#ifndef ECOSYSTEM_PATHOGENCELL_H
#define ECOSYSTEM_PATHOGENCELL_H


#include "cell.h"
#include "../textures/cellTexture.h"

class PathogenCell : public Cell {
public:
    PathogenCell(texture::AnimationParameters animation, float radius, int size, float speed,
                 sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { }

    void drawTexture(sf::RenderWindow &window) override;
};


#endif //ECOSYSTEM_PATHOGENCELL_H
