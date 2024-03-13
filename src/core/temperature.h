#ifndef ECOSYSTEM_TEMPERATURE_H
#define ECOSYSTEM_TEMPERATURE_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "../utils/settings.h"


class Temperature {
public:

    Temperature(): temp(36.6) {
        tempText.setCharacterSize(settings::SCREEN_HEIGHT*0.07f);
        tempText.setPosition(settings::SCREEN_WIDTH*0.02f, settings::SCREEN_HEIGHT*0.89f);
        tempText.setFillColor(sf::Color::Green);

        endTempText = " °C";
        endTempText.erase(1);
    };

    void updateAndDraw(int numberOfPathogens, sf::RenderWindow &window, sf::Font font);

    bool isCriticalTemp() const { return temp >= 40.f; }

private:

    sf::Text tempText;
    sf::String endTempText;
    float temp;

};

#endif //ECOSYSTEM_TEMPERATURE_H
