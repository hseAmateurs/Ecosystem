//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_MACROCELL_H
#define ECOSYSTEM_MACROCELL_H


#include "cell.h"
#include "../utils/cells.h"
#include "../textures/cellTexture.h"

class MacroCell : public Cell {
public:
    MacroCell(texture::AnimationParameters animation, float radius, int size, float speed,
              sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { }

    int type() const override { return CellType::MACRO; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    void update(Field &field, sf::Time deltaTime) override;

    void scrollBCells(Field &field);

private:

};

#endif //ECOSYSTEM_MACROCELL_H
