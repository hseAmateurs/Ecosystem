//
// Created by Shon on 11.03.2024.
//

#include "brain.h"
#include <cmath>

using namespace settings;

namespace brain {
    void updateAngle(Animation &anim, const sf::Clock &timer) {
        double deltaAngle = anim.targetAngle - anim.currentAngle;
        double scale = sin(M_PI * timer.getElapsedTime().asSeconds() / (anim.speedScale / (anim.speed / 10)));
        anim.currentAngle += deltaAngle * scale;
    }

    sf::Vector2f getXY(const double angle, const double distance) {
        float posX = std::cos(angle) * (distance * BRAIN_RADIUS);
        float posY = std::sin(angle) * (distance * BRAIN_RADIUS);
        return {SCREEN_WIDTH - posX, SCREEN_HEIGHT - posY};
    }

    sf::Vector2f getXY(const int index, const int amount, const double distance) {
        const double angleOffset = M_PI / 8;
        double angle = (M_PI / 2 + angleOffset) / (amount + 1) * (amount - index) - angleOffset / 2;
        return getXY(angle, distance);
    }
}
