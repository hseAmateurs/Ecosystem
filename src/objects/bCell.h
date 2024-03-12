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
        MOVING,
        AWAIT
    };

    BCell(texture::AnimationParameters animation, float radius, int size, float speed,
          sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color), m_status(FREE) { }

    BCell(const BCell &right) : Cell(right), m_status(FREE) { code.setString(std::string()); }

    int type() const override { return CellType::BCELL; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    Status getStatus() const { return m_status; }

    void setStatus(Status status) { m_status = status; };

    void scrollPrepare(int index, int amount, Status nextStatus);

    void update(Field &field, sf::Time deltaTime) override;

    ~BCell() override;

private:
    Status m_nextStatus;
    Status m_status;
    brain::Animation anim;
    int m_index; // Индекс в field.bCells
};


#endif //ECOSYSTEM_NEUTROCELL_H
