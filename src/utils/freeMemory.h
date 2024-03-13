//
// Created by Shon on 10.03.2024.
//
#include "cells.h"
#include "utils.h"

namespace utils {
    template<class T>
    void deleteCellType(std::vector<T *> cells) {
        for (T *&cell: cells)
            delete cell;
    }

    void freeField(Field &field) {
        deleteCellType(field.bCells);
        deleteCellType(field.pathogens);
        deleteCellType(field.bodies);
        deleteCellType(field.macroes);
        deleteCellType(field.neutroes);
        deleteCellType(field.plasmas);
        deleteCellType(field.antis);
    }
}
