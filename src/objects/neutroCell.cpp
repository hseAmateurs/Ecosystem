//
// Created by Денис Громачихин on 19.02.2024.
//

#include "hunterCell.h"
#include "neutroCell.h"

void NeutroCell::drawTexture(sf::RenderWindow &window) {
    texture.changeCenter(getPosition());
    texture.update();
    window.draw(texture);
}
