#ifndef ECOSYSTEM_PATHOGENCELL_H
#define ECOSYSTEM_PATHOGENCELL_H


#include "cell.h"
#include "../textures/pathogen.h"

class PathogenCell : public Cell {
public:
    PathogenCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : Cell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;

private:
    texture::Pathogen texture;
};


#endif //ECOSYSTEM_PATHOGENCELL_H
