//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BODYCELL_H
#define ECOSYSTEM_BODYCELL_H


#include "cell.h"
#include "../utils/cells.h"
#include "../textures/cellTexture.h"

class BodyCell : public Cell {
public:
    BodyCell(texture::AnimationParameters animation, float radius, int size, float speed,
             sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color), lifeTime(sf::seconds(-(rand() % 20 + 15))) { }

    int type() const override { return CellType::BODY; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    void cellDivision(sf::Time &deltaTime, std::vector<BodyCell *> &bodyCells);

    void update(Field &field, sf::Time deltaTime) override;

private:
    sf::Time lifeTime;
};


#endif //ECOSYSTEM_BODYCELL_H
