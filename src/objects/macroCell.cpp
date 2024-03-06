//
// Created by Денис Громачихин on 19.02.2024.
//

#include "hunterCell.h"
#include "macroCell.h"

void MacroCell::drawTexture(sf::RenderWindow &window) {
    texture.changeCenter(getPosition());
    texture.update();
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}
