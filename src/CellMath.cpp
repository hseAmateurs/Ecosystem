#include <cmath>
#include "CellMath.h"


sf::Vector2f getRadiusVector(float angle, float radius) {
    return sf::Vector2f(radius * cos(angle), radius * sin(angle));
}
