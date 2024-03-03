#ifndef ECOSYSTEM_PATHOGENCELL_H
#define ECOSYSTEM_PATHOGENCELL_H



#include "../textures/pathogen.h"
#include "hunterCell.h"
#include "cell.h"

class PathogenCell : public HunterCell {
public:
    PathogenCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : HunterCell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;
    char getName();
private:
    texture::Pathogen texture;
};


#endif //ECOSYSTEM_PATHOGENCELL_H
