//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>
#include "plasmaCell.h"

void PlasmaCell::drawTexture(sf::RenderWindow &window) {
    texture.changeCenter(getPosition());
    texture.update();
    window.draw(texture);
}

PlasmaCell::PlasmaCell(texture::AnimationParameters animation, float radius, int size, float speed, sf::Vector2f center,
                       sf::Color color) : Cell(animation, radius, size, speed, center, color) {

}
