//
// Created by vivan on 20.02.2024.
//

#ifndef ECOSYSTEM_VIRUS_H
#define ECOSYSTEM_VIRUS_H


#include "cell.h"

class Virus : public Cell {
public:
    explicit Virus(sf::Vector2f center = {800, 450}, float radius = 100, int pointCount = 180, sf::Color color = sf::Color::Red);
};

#endif //ECOSYSTEM_VIRUS_H
