#ifndef ECOSYSTEM_PATHOGENCELL_H
#define ECOSYSTEM_PATHOGENCELL_H


#include "hunterCell.h"
#include "../textures/cellTexture.h"

class PathogenCell : public HunterCell {
public:
    PathogenCell(texture::AnimationParameters animation, float radius, int size, float speed,
                 sf::Vector2f center, sf::Color color)
            : HunterCell(animation, radius, size,
                   speed,
                   center, color) { }

    void drawTexture(sf::RenderWindow &window) override;
    char getName() override;
};


#endif //ECOSYSTEM_PATHOGENCELL_H
