//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H


#include "hunterCell.h"
#include "../textures/cellTexture.h"

class NeutroCell : public HunterCell {
public:
    NeutroCell(texture::AnimationParameters animation, float radius, int size, float speed,
               sf::Vector2f center, sf::Color color)
            : HunterCell(animation, radius, size,
                   speed,
                   center, color) { }

    void drawTexture(sf::RenderWindow &window) override;
};


#endif //ECOSYSTEM_NEUTROCELL_H
