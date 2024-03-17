#include "temperature.h"
#include "assets.h"


Temperature::Temperature(const Field *field) :
        m_field(field), temp(settings::NORMAL_TEMP) {
    setFont(Assets::instance().font);
    setCharacterSize(settings::SCREEN_HEIGHT * 0.07f);
    setPosition(settings::SCREEN_WIDTH * 0.02f, settings::SCREEN_HEIGHT * 0.89f);
    setFillColor(sf::Color::Green);
}

void Temperature::update() {
    temp = settings::CRITICAL_TEMP - settings::NORMAL_TEMP *
                                     ((float)m_field->bodies.size() / (float)m_field->pathogens.size());
    int greenAspect = 255 - ((temp - settings::NORMAL_TEMP) / (settings::CRITICAL_TEMP - settings::NORMAL_TEMP)) * 255;
    int redAspect = (temp - settings::NORMAL_TEMP) / (settings::CRITICAL_TEMP - settings::NORMAL_TEMP) * 255;
    setFillColor(sf::Color(redAspect, greenAspect, 0));

    setString(std::to_string(temp) + " °C");
}
