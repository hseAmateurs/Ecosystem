//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_MACROCELL_H
#define ECOSYSTEM_MACROCELL_H


#include "cell.h"
#include "../textures/macrophage.h"
#include "hunterCell.h"


class MacroCell : public HunterCell {
public:
    MacroCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : HunterCell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;
    char getName();
private:
    texture::Macrophage texture;
};


#endif //ECOSYSTEM_MACROCELL_H
