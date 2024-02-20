#include <SFML/Graphics.hpp>
#include "cell.h"
#include "globalFunc.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#define SPAWNALL
//#define SPAWN4TYPES

int main() {
    // Простой пример для проверки работы

    std::vector<PatogenCell> patogenCells;
    std::vector<BodyCell> bodyCells;
    std::vector<MacroCell> macroCells;
    std::vector<NeutroCell> neutroCells;

    std::vector<float> radiusArr;
    std::vector<int> sizeArr;
    std::vector<float> speedArr;
    std::vector<float> posXArr;
    std::vector<float> posYArr;
    std::vector<int> countArr;



    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Ecosystem");
    csvInput("data.csv", radiusArr, sizeArr, speedArr, countArr);

#ifdef SPAWNALL
    createPatogenCells(patogenCells,countArr[0],1600,900,radiusArr[0],sizeArr[0],speedArr[0],sf::Color(139, 0, 255),window);
    createBodyCells(bodyCells, countArr[1], 1600, 900, radiusArr[1], sizeArr[1], speedArr[1], sf::Color::Red, window);
    createMacroCells(macroCells, countArr[2], 1600, 900, radiusArr[2], sizeArr[2], speedArr[2], sf::Color::Yellow, window);
    createNeutroCells(neutroCells, countArr[3], 1600, 900, radiusArr[3], sizeArr[3], speedArr[3], sf::Color::Green, window);
#endif


#ifdef SPAWN4TYPES
    createPatogenCells(patogenCells,100,1600,900,radiusArr[0],sizeArr[0],speedArr[0],sf::Color(139, 0, 255),window);
    createBodyCells(bodyCells, 1, 1600, 900, radiusArr[1], sizeArr[1], speedArr[1], sf::Color::Red, window);
    createMacroCells(macroCells, 1, 1600, 900, radiusArr[2], sizeArr[2], speedArr[2], sf::Color::Yellow, window);
    createNeutroCells(neutroCells, 1, 1600, 900, radiusArr[3], sizeArr[3], speedArr[3], sf::Color::Green, window);

    //PatogenCell cell1(radiusArr[0],sizeArr[0],speedArr[0],sf::Color(139, 0, 255), 100, 100);
    //cell1.setTargetPosition(1600, 900);
#endif






    std::cout<<radiusArr.size()<<"\n";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = clock.restart();





        window.clear(sf::Color(255,255,255));

        for (int i = 0; i < countArr[0]; ++i)
        {
            patogenCells.at(i).update(deltaTime);
            patogenCells.at(i).draw(window);
        }

        for (int i = 0; i < countArr[2]; ++i)
        {
            macroCells.at(i).update(deltaTime);
            macroCells.at(i).draw(window);
        }

        for (int i = 0; i < countArr[3]; ++i)
        {
            neutroCells.at(i).update(deltaTime);
            neutroCells.at(i).draw(window);
        }

        for (int i = 0; i < countArr[1]; ++i)
        {
            bodyCells.at(i).update(deltaTime);
            bodyCells.at(i).draw(window);
        }


        window.display();
    }

    return 0;
}
