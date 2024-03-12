//
// Created by Shon on 06.03.2024.
//

#ifndef ECOSYSTEM_SETTINGS_H
#define ECOSYSTEM_SETTINGS_H

namespace settings {
    // Разрешение экрана
    const unsigned int SCREEN_WIDTH = 1600;
    const unsigned int SCREEN_HEIGHT = 900;

    // Невидимые границы (указано расстояние от видимых)
    const float BORDER_OFFSET = 100.f;

    // Радиус левого нижнего круга, в котором выпускаются антитела
    const float BRAIN_RADIUS = 490.f;

    // Минимальная дистанция для триггера на цель
    const float HUNT_TRIGGER = 150.f;

    // Процент удаления статичных клетки от центра "мозгового" круга
    const double PLASMA_DISTANCE = 0.4;
    const double BCELL_DISTANCE = 0.9;

    // Процент удаления макрофага от центра "мозгового" круга
    const double MACRO_DISTANCE = 1.1;
}

#endif //ECOSYSTEM_SETTINGS_H
