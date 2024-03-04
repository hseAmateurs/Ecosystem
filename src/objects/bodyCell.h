//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BODYCELL_H
#define ECOSYSTEM_BODYCELL_H


#include "cell.h"
#include "../textures/cellTexture.h"

class BodyCell : public Cell {
public:
    BodyCell(texture::AnimationParameters animation, float radius, int size, float speed,
             sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color), lifeTime(sf::seconds(-(rand()%20+15))) { }

    void drawTexture(sf::RenderWindow &window) override;
    void cellDivision(sf::Time &deltaTime, std::vector<BodyCell> &bodyCells);


    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateBody(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                std::vector<neutro> &neutros, sf::Time deltaTime);
    char getName();
    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                std::vector<neutro> &neutros, sf::Time deltaTime);
private:
    sf::Time lifeTime;


};

template<typename pathogen, typename body, typename macro, typename neutro>
void BodyCell::updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                std::vector<neutro> &neutros, sf::Time deltaTime) {

}

template<typename pathogen, typename body, typename macro, typename neutro>
void BodyCell::updateBody(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                std::vector<neutro> &neutros, sf::Time deltaTime) {
    if (timer.getElapsedTime() > randomMoveInterval) {
        setRandomVelocity();
        auto randomSeconds = static_cast<float>(std::rand() % 5 + 1); // Случайное число от 1 до 5
        randomMoveInterval = sf::seconds(randomSeconds);
        timer.restart();
    }
    reflectionControl();
    updateCollision(neutros);
    updateCollision(pathogens);
    updateCollision(macroes);
    updateCollision(bodies);


    move(velocity * deltaTime.asSeconds());
}


#endif //ECOSYSTEM_BODYCELL_H
