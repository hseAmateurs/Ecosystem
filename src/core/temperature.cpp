#include <iomanip>
#include <string>
#include <sstream>

#include "temperature.h"
#include "assets.h"


Temperature::Temperature(const Field *field) :
        m_field(field), temp(settings::NORMAL_TEMP) {
    setFont(Assets::instance().font);
    setCharacterSize(settings::SCREEN_HEIGHT * 0.07f);
    setPosition(settings::SCREEN_WIDTH * 0.02f, settings::SCREEN_HEIGHT * 0.89f);
    setFillColor(sf::Color::Green);
    setOutlineThickness(2);
}

void Temperature::update() {
    temp = settings::NORMAL_TEMP + m_field->pathogens.size() * 0.12f;
    int greenAspect = 255 - ((temp - settings::NORMAL_TEMP) / (settings::CRITICAL_TEMP - settings::NORMAL_TEMP)) * 255;
    int redAspect = (temp - settings::NORMAL_TEMP) / (settings::CRITICAL_TEMP - settings::NORMAL_TEMP) * 255;
    setFillColor(sf::Color(redAspect, greenAspect, 0));

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << temp;
    std::string format = "°C";
    format.erase(0, 1);
    setString(ss.str() + format);
}
