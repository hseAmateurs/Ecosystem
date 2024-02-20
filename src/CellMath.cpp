//
// Created by vivan on 18.02.2024.
//

#include <cmath>
#include "CellMath.h"


sf::Vector2f getRadiusVector(float angle, float radius) {
    return sf::Vector2f(radius * cos(angle), radius * sin(angle));
}
