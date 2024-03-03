//
// Created by Денис Громачихин on 19.02.2024.
//

#include "pathogenCell.h"

void PathogenCell::drawTexture(sf::RenderWindow &window) {
    sf::Vector2f radiusOffset(getRadius(), getRadius());
    texture.changeCenter(getPosition() + radiusOffset);
    texture.update();
    window.draw(texture);

    code.setPosition(getPosition() + radiusOffset);
    window.draw(code);
}
