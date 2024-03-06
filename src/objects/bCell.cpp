//
// Created by Денис Громачихин on 19.02.2024.
//

#include "bCell.h"

void BCell::drawTexture(sf::RenderWindow &window) {
    texture.changeCenter(getPosition());
    texture.update();
    window.draw(texture);
}
