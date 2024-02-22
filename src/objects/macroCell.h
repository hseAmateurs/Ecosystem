//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_MACROCELL_H
#define ECOSYSTEM_MACROCELL_H


#include "cell.h"
#include "../textures/macrophage.h"

class MacroCell : public Cell {
public:
    MacroCell(float radius, int size, float speed, float posX, float posY)
            : Cell(radius, size,
                   speed,
                   posX,
                   posY),
              texture(){ }

    void drawTexture(sf::RenderWindow& window);

private:
    texture::Macrophage texture;

};


#endif //ECOSYSTEM_MACROCELL_H
