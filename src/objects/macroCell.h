//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_MACROCELL_H
#define ECOSYSTEM_MACROCELL_H


#include "../textures/cellTexture.h"
#include "hunterCell.h"

class MacroCell : public HunterCell {
public:
    MacroCell(texture::AnimationParameters animation, float radius, int size, float speed,
              sf::Vector2f center, sf::Color color)
            : HunterCell(animation, radius, size,
                   speed,
                   center, color) { }

    int type() const override { return CellType::MACRO; }

    void drawTexture(sf::RenderWindow &window) override;
};


#endif //ECOSYSTEM_MACROCELL_H
