#include <SFML/Graphics.hpp>
#include <iostream>

#include "textures/cellTextures.h"

int main() {
    setbuf(stdout, nullptr);

    sf::RenderWindow window(sf::VideoMode({1600, 900}), "SFML Island", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    texture::Cell cell({400, 300}, 100);
    texture::Neutrophil neutrophil({1200, 300}, 100);
    texture::Macrophage macrophage({400, 600,}, 100);
    texture::Antibody antibody({1200, 600}, 50);
    texture::Pathogen virus({800, 450}, 100, 720);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        virus.update();
        cell.update();
        neutrophil.update();
        macrophage.update();
        antibody.update();


        window.clear();
        window.draw(virus);
        window.draw(cell);
        window.draw(neutrophil);
        window.draw(macrophage);
        window.draw(antibody);
        window.display();
        sf::Time time = clock.restart();
    }

    return 0;
}
