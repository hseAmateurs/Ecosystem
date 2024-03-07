//
// Created by Денис Громачихин on 19.02.2024.
//

#include "pathogenCell.h"

void PathogenCell::drawTexture(sf::RenderWindow &window, sf::Time elapsed) {
    texture.changeCenter(getPosition());
    texture.update(elapsed);
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}
