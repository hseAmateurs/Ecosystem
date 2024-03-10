//
// Created by Денис Громачихин on 19.02.2024.
//

#include <iostream>
#include "bCell.h"

void BCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);
}

BCell::~BCell() {
    std::cout << "Deleted\n";
}
