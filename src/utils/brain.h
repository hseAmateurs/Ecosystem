//
// Created by Shon on 11.03.2024.
//

#ifndef ECOSYSTEM_BRAIN_H
#define ECOSYSTEM_BRAIN_H

#include <SFML/Graphics.hpp>
#include "settings.h"


namespace brain {
    struct Animation {
        double targetAngle;
        double currentAngle;
        double speedScale;
        double speed;
    };

    sf::Vector2f getXY(int index, int amount, double distance = settings::BCELL_DISTANCE);

    sf::Vector2f getXY(double angle, double distance = settings::BCELL_DISTANCE);

    void updateAngle(Animation &anim, const sf::Clock &timer);

    const double angleEps = 0.0025;
}

#endif //ECOSYSTEM_BRAIN_H
