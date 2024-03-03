#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>

class Cell : public sf::CircleShape {
public:
    explicit Cell(float radius, int size, float speed, sf::Vector2f center, sf::Color color);

    // Переименовал эту функцию (было setPosition), т.к. она наследуется от CircleShape
    void setPos(float x, float y);

    void setTargetPosition(float windowWidth, float windowHeight);

    template<typename pathogen, typename body, typename macro, typename neutro>
    void update(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                std::vector<neutro> &neutros, sf::Time deltaTime);

    // установка случайного вектора движения
    void setRandomVelocity();

    void reflectionControl();

    // Означает, что эта функция должна быть обязательно переопределена в производных классах
    virtual void drawTexture(sf::RenderWindow &window) = 0;

    void setCode(const char &new_code) { code.setString(new_code); };

    char getCode() const { return code.getString()[0]; };

    void setFont(const sf::Font &font) { code.setFont(font); };

protected:
    sf::Text code;

private:
    template<class T>
    void updateCollision(std::vector<T> &cells);

    float speed;
    sf::Vector2f velocity;
    sf::Vector2f targetPosition;
    sf::Time interval;
    sf::Clock timer;
    sf::Time randomMoveInterval;
    sf::Color color;
    int size;
};

template<class T>
void Cell::updateCollision(std::vector<T> &cells) {
    for (auto &otherCell: cells) {
        if (&otherCell == this) continue;
        sf::Vector2f otherPosition = otherCell.getPosition();
        sf::Vector2f direction = otherPosition - getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (getGlobalBounds().intersects(otherCell.getGlobalBounds())) {
            velocity = (getPosition() - otherCell.getPosition());
            velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
            otherCell.velocity = otherCell.getPosition() - getPosition();
            otherCell.velocity = otherCell.velocity / std::sqrt(
                    otherCell.velocity.x * otherCell.velocity.x + otherCell.velocity.y * otherCell.velocity.y) *
                                 otherCell.speed;
        }
    }
}

template<typename pathogen, typename body, typename macro, typename neutro>
void Cell::update(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
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
    updateCollision(bodies);
    updateCollision(macroes);

    move(velocity * deltaTime.asSeconds());
}

#endif //ECOSYSTEM_CELL_H
