//
// Created by Денис Громачихин on 19.02.2024.
//

#ifndef ECOSYSTEM_PLASMACELL_H
#define ECOSYSTEM_PLASMACELL_H


#include "cell.h"
#include "../textures/cellTexture.h"

class PlasmaCell : public Cell {
public:
    PlasmaCell(texture::AnimationParameters animation, float radius, int size, float speed,
               sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { }

    void drawTexture(sf::RenderWindow &window) override;

    char getName() const { return 'r'; };

    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateBody(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                    std::vector<neutro> &neutros, sf::Time deltaTime) { };

    template<typename pathogen, typename body, typename macro, typename neutro>
    void updateHunters(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                       std::vector<neutro> &neutros, sf::Time deltaTime) { };
};


#endif //ECOSYSTEM_NEUTROCELL_H
