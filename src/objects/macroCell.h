//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_MACROCELL_H
#define ECOSYSTEM_MACROCELL_H


#include "cell.h"
#include "../utils/cells.h"
#include "../textures/cellTexture.h"

#include "../utils/brain.h"

class MacroCell : public Cell {
public:
    enum Status {
        HUNTING,
        DELIVERY,
        CHECKING,
        MOVING
    };

    MacroCell(texture::AnimationParameters animation, float radius, int size, float speed,
              sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color), m_status(HUNTING), bCellIndex(0) { }

    int type() const override { return CellType::MACRO; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    void update(Field &field, sf::Time deltaTime) override;

    Status getStatus() const { return m_status; }

    void setStatus(Status status) { m_status = status; };

private:
    void runPlasma(Field &field);

    void scrollBCells(Field &field);

    void hunting(Field &field, sf::Time deltaTime);

    void moveNextPrepare(Field &field);

    bool isBCellReady(const Field &field) const;

    Status m_status;
    int bCellIndex;

    brain::Animation anim;
};

#endif //ECOSYSTEM_MACROCELL_H
