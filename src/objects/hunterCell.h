#ifndef ECOSYSTEM_HUNTERCELL_H
#define ECOSYSTEM_HUNTERCELL_H


#include "cell.h"
#include "../textures/animations.h"
#include <iostream>

class HunterCell : public Cell {
public:
    HunterCell(texture::AnimationParameters animation, float radius, int size, float speed, sf::Vector2f center,
               sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { }

    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                       std::vector<neutro> &neutros, sf::Time deltaTime);

    virtual char getName() const = 0;

    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateBody(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                    std::vector<neutro> &neutros, sf::Time deltaTime);
};

template<typename pathogen, typename body, typename macro, typename neutro>
void HunterCell::updateBody(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                            std::vector<neutro> &neutros, sf::Time deltaTime) {
    // лучше не спрашивайте, зачем это здесь, иначе просто не работает
    // можете попробовать убрать
}

template<typename pathogen, typename body, typename macro, typename neutro>
void HunterCell::updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                               std::vector<neutro> &neutros, sf::Time deltaTime) {

    const float hunt = 150.0f;
    sf::Vector2f closestBody;
    closestBody.x = 0;
    closestBody.y = 0;
    float minDistance = 30000;
    sf::Vector2f hunterPos = getPosition();
    if (this->getName() == 'p') {
        for (auto &otherCell: bodies) {
            sf::Vector2f bodyPos = otherCell.getPosition();
            float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                       (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
            if (distance < minDistance && distance < hunt) {
                minDistance = distance;
                closestBody = bodyPos;
            }
        }
    }
    else if (this->getName() == 'm' || this->getName() == 'n') {
        for (auto &otherCell: pathogens) {
            sf::Vector2f bodyPos = otherCell.getPosition();
            float distance = std::sqrt((bodyPos.x - hunterPos.x) * (bodyPos.x - hunterPos.x) +
                                       (bodyPos.y - hunterPos.y) * (bodyPos.y - hunterPos.y));
            if (distance < minDistance && distance < hunt) {
                minDistance = distance;
                closestBody = bodyPos;
            }
        }
    }
    if (minDistance == 30000) {
        if (timer.getElapsedTime() > randomMoveInterval) {
            setRandomVelocity();
            auto randomSeconds = static_cast<float>(std::rand() % 5 + 1); // Случайное число от 1 до 5
            randomMoveInterval = sf::seconds(randomSeconds);
            timer.restart();
        }
    }
    else {
        velocity = closestBody - getPosition();
        velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
    }
    reflectionControl();
    updateCollision(neutros);
    updateCollision(pathogens);
    updateCollision(macroes);
    updateCollision(bodies);
    move(velocity * deltaTime.asSeconds());
}

#endif //ECOSYSTEM_HUNTERCELL_H
