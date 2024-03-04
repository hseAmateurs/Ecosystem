//
// Created by Денис Громачихин on 19.02.2024.
//

#include "hunterCell.h"
#include "neutroCell.h"

void NeutroCell::drawTexture(sf::RenderWindow &window) {
    sf::Vector2f radiusOffset(getRadius(), getRadius());
    texture.changeCenter(getPosition() + radiusOffset);
    texture.update();
    window.draw(texture);
}
