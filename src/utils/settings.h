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

    const int RAND_SPAWN_NEUTRO_ITER = 800;

    const int RAND_SPAWN_MACRO_ITER = 1000;

    //const sf::Vector2f SPAWN_POS = sf::Vector2f(1620.f, -20.f);
    const std::vector<sf::Vector2f> SPAWN_POS = {sf::Vector2f(1620.f, -20.f), sf::Vector2f(-20.f, -20.f),
                                                 sf::Vector2f(-20.f, 920.f)};

    // В среднем количество итераций для рандомного спавна патогена
    const int RAND_SPAWN_PATHOGEN_ITER = 500;

    // В среднем количество рандомных спавнов патогенов для увеличение сложности на 1
    const int RAND_PATHOGEN_MUTATION = 10;

    const char INIT_CODE = '!';

    const sf::Time SEARCH_CODE_DELAY = sf::seconds(0.2f);

    const sf::Time PLASMA_ANTI_DELAY = sf::seconds(1.f);

    const int ANTI_COUNT = 15;

    const sf::Time ANTI_LIFETIME = sf::seconds(15);

    namespace color {
        const sf::Color PATHOGEN = sf::Color(180, 30, 220);
        const sf::Color BODY = sf::Color(245, 20, 0);
        const sf::Color MACRO = sf::Color(225, 200, 0);
        const sf::Color NEUTRO = sf::Color(20, 150, 20);
        const sf::Color BCELL = sf::Color(50, 200, 215);
        const sf::Color PLASMA = sf::Color(225, 10, 10);
        const sf::Color ANTI = sf::Color(219, 112, 147);

        const sf::Color BACKGROUND = sf::Color(210, 225, 220);
        const sf::Color BRAIN_BACKGROUND = sf::Color(0, 0, 0, 10);
    }

    const float NORMAL_TEMP = 36.6f;
    const float CRITICAL_TEMP = 42.f;
}

#endif //ECOSYSTEM_SETTINGS_H
