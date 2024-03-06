//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_NEUTROCELL_H
#define ECOSYSTEM_NEUTROCELL_H


#include "../textures/cellTexture.h"
#include "cell.h"

class NeutroCell : public Cell {
public:
    NeutroCell(texture::AnimationParameters animation, float radius, int size, float speed,
               sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { }

    void drawTexture(sf::RenderWindow &window) override;
    char getName() const override { return 'n'; };

    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                       std::vector<neutro> &neutros, sf::Time deltaTime);
};

template<typename pathogen, typename body, typename macro, typename neutro>
void NeutroCell::updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
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


#endif //ECOSYSTEM_NEUTROCELL_H
