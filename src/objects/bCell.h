//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BCELL_H
#define ECOSYSTEM_BCELL_H


#include "cell.h"
#include "../utils/cells.h"
#include "../textures/cellTexture.h"

#include "../utils/brain.h"

class BCell : public Cell {
public:
    enum Status {
        FREE,
        BUSY,
        SCROLL,
        MOVING
    };

    BCell(texture::AnimationParameters animation, float radius, int size, float speed,
          sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color), m_status(FREE) { }

    BCell(const BCell &right) : Cell(right), m_status(FREE) { code.setString(""); }

    int type() const override { return CellType::BCELL; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    Status getStatus() const { return m_status; }

    void setStatus(Status status) { m_status = status; };

    void update(Field &field, sf::Time deltaTime) override;

    ~BCell() override;

private:
    int getID(const Field &field) const;

    void scrollPrepare(const Field &field);

    Status m_status;
    brain::Animation anim;
};


#endif //ECOSYSTEM_NEUTROCELL_H
