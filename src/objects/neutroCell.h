//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H


#include "cell.h"
#include "../textures/neutrophil.h"

class NeutroCell : public Cell {
public:
    NeutroCell(float radius, int size, float speed, float posX, float posY)
            : Cell(radius, size,
                   speed,
                   posX,
                   posY),
              texture(){ }

    void drawTexture(sf::RenderWindow& window);

private:
    texture::Neutrophil texture;
};


#endif //ECOSYSTEM_NEUTROCELL_H
