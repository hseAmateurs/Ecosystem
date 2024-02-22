//
// Created by Денис Громачихин on 19.02.2024.
//

#include "macroCell.h"

void MacroCell::drawTexture(sf::RenderWindow& window)
{
    sf::Vector2f vect(getRadius(), getRadius());
    texture.changeCenter(getPosition() + vect);
    texture.update();
    window.draw(texture);
}
