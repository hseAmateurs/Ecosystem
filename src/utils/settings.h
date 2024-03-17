//
// Created by Shon on 06.03.2024.
//

#ifndef ECOSYSTEM_SETTINGS_H
#define ECOSYSTEM_SETTINGS_H

#include <SFML/Graphics.hpp>

namespace settings {
    // Разрешение экрана
    const unsigned int SCREEN_WIDTH = 1600;
    const unsigned int SCREEN_HEIGHT = 900;

    // Невидимые границы (указано расстояние от видимых)
    const float BORDER_OFFSET = 100.f;

    // Радиус левого нижнего круга, в котором выпускаются антитела
    const float BRAIN_RADIUS = 490.f;

    // Минимальная дистанция для триггера на цель для патогена
    const float PATH_HUNT_TRIGGER = 350.f;

    // Минимальная дистанция для триггера на цель для иммунных клеток
    const float IMMUNE_HUNT_TRIGGER = 150.f;

    // Процент удаления статичных клетки от центра "мозгового" круга
    const double PLASMA_DISTANCE = 0.4;
    const double BCELL_DISTANCE = 0.9;

    // Процент удаления макрофага от центра "мозгового" круга
    const double MACRO_DISTANCE = 1.1;

    // Дельта, на которую увеличивается радиус при съедении патогена
    const float NEUTRO_RADIUS_DELTA = 2.f;

    namespace color {
        const sf::Color PATHOGEN = sf::Color(139, 0, 255);
        const sf::Color BODY = sf::Color::Red;
        const sf::Color MACRO = sf::Color::Yellow;
        const sf::Color NEUTRO = sf::Color::Green;
        const sf::Color BCELL = sf::Color::Cyan;
        const sf::Color PLASMA = sf::Color::Magenta;
        const sf::Color ANTI = sf::Color(219, 112, 147);;
    }

    const float NORMAL_TEMP = 36.6f;
    const float CRITICAL_TEMP = 42.f;
}

#endif //ECOSYSTEM_SETTINGS_H
