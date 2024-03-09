//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_BCELL_H
#define ECOSYSTEM_BCELL_H


#include "cell.h"
#include "../textures/cellTexture.h"

class BCell : public Cell {
public:
    BCell(texture::AnimationParameters animation, float radius, int size, float speed,
          sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { setOrigin(getRadius() / 2, getRadius() / 2); }

    int type() const override { return CellType::BCELL; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;

    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateBody(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                    std::vector<neutro> &neutros, sf::Time deltaTime) { };

    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                       std::vector<neutro> &neutros, sf::Time deltaTime) { };
};


#endif //ECOSYSTEM_NEUTROCELL_H
