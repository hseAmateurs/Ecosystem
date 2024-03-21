//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BCELL_H
#define ECOSYSTEM_BCELL_H


#include "cell.h"
#include "../utils/cells.h"

#include "../utils/brain.h"

class BCell : public Cell {
public:
    enum Status {
        FREE,
        BUSY,
        MOVING,
        AWAIT
    };

    explicit BCell(const Assets::CellParam &cellParam)
            : Cell(cellParam, texture::bCell, color::BCELL), m_status(FREE) { }

    virtual void runScript(Field &field, const sf::Time &deltaTime) override;

    void scrollPrepare(int index, int amount);

    Status getStatus() const { return m_status; }

    static std::vector<Status> statuses;

private:
    Status m_status;
    brain::Animation anim;
    int m_index; // Индекс в field.bCells
};


#endif //ECOSYSTEM_NEUTROCELL_H
