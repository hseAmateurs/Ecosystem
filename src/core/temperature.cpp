#include "temperature.h"


void Temperature::updateAndDraw(int numberOfPathogens, sf::RenderWindow &window, sf::Font font) {
    temp = 36.6f + numberOfPathogens*0.05f;
    tempText.setFillColor(sf::Color(numberOfPathogens*7.5f, 255.f - numberOfPathogens*7.5f, 0));
    std::ostringstream ss;
    ss << temp;
    tempText.setString(ss.str() + endTempText);
    tempText.setFont(font);
    window.draw(tempText);
}
