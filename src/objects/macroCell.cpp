//
// Created by Денис Громачихин on 19.02.2024.
//

#include "hunterCell.h"
#include "macroCell.h"

void MacroCell::drawTexture(sf::RenderWindow &window) {
    sf::Vector2f radiusOffset(getRadius(), getRadius());
    texture.changeCenter(getPosition() + radiusOffset);
    texture.update();
    window.draw(texture);

    code.setPosition(getPosition() + radiusOffset);
    window.draw(code);
}

char MacroCell::getName(){
    return 'm';
}