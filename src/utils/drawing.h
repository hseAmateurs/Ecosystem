//
// Created by Shon on 21.02.2024.
//

#ifndef ECOSYSTEM_DRAWING_H
#define ECOSYSTEM_DRAWING_H

#include <vector>
#include <SFML/Graphics.hpp>

using std::vector;

template<class T>
void drawing(const vector<T> &cells, sf::RenderWindow &window);

#endif //ECOSYSTEM_DRAWING_H
