#ifndef ECOSYSTEM_TEMPERATURE_H
#define ECOSYSTEM_TEMPERATURE_H


#include <SFML/Graphics.hpp>

#include "../utils/settings.h"
#include "field.h"

class Temperature : public sf::Text {
public:

    explicit Temperature(const Field *field);

    bool isCritical() const { return temp > settings::CRITICAL_TEMP; }

    void update();

private:
    const Field *m_field;
    float temp;
};

#endif //ECOSYSTEM_TEMPERATURE_H
