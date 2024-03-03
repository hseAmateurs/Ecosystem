//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H



#include "../textures/neutrophil.h"
#include "hunterCell.h"
#include "cell.h"

class NeutroCell : public HunterCell {
public:
    NeutroCell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
            : HunterCell(radius, size,
                   speed,
                   center, color), texture(center, radius, 180, color) { }

    void drawTexture(sf::RenderWindow &window) override;
    char getName();

private:
    texture::Neutrophil texture;
};


#endif //ECOSYSTEM_NEUTROCELL_H
