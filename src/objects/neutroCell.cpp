//
// Created by Денис Громачихин on 19.02.2024.
//

#include "neutroCell.h"

void NeutroCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);
}
