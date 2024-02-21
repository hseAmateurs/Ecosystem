#include <SFML/Graphics.hpp>
#include <iostream>

#include "textures/cellTextures.h"
#include "cell.h"
#include "globalFunc.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

//#define SPAWNALL
#define SPAWN4TYPES

int main() {
    setbuf(stdout, nullptr);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Ecosystem", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    texture::Cell cell({400, 300}, 100);
    texture::Neutrophil neutrophil({1200, 300}, 100);
    texture::Macrophage macrophage({400, 600,}, 100);
    texture::Antibody antibody({1200, 600}, 50);
    texture::Pathogen virus({800, 450}, 100, 720);

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

    sf::CircleShape circle1(10);
    circle1.setFillColor(sf::Color::Black);
    circle1.setPosition(0, 0);

    sf::CircleShape circle2(10);
    circle2.setFillColor(sf::Color::Black);
    circle2.setPosition(900, 1600);


    sf::CircleShape circle3(10);
    circle3.setFillColor(sf::Color::Black);
    circle3.setPosition(0, 0);


    sf::CircleShape circle4(10);
    circle4.setFillColor(sf::Color::Black);
    circle4.setPosition(0, 0);

    sf::Clock clock;

    csvInput("../data.csv", radiusArr, sizeArr, speedArr, countArr);

#ifdef SPAWNALL
    createPatogenCells(patogenCells,countArr[0],1600,900,radiusArr[0],sizeArr[0],speedArr[0],sf::Color(139, 0, 255),window);
    createBodyCells(bodyCells, countArr[1], 1600, 900, radiusArr[1], sizeArr[1], speedArr[1], sf::Color::Red, window);
    createMacroCells(macroCells, countArr[2], 1600, 900, radiusArr[2], sizeArr[2], speedArr[2], sf::Color::Yellow, window);
    createNeutroCells(neutroCells, countArr[3], 1600, 900, radiusArr[3], sizeArr[3], speedArr[3], sf::Color::Green, window);
#endif


#ifdef SPAWN4TYPES
    createPatogenCells(patogenCells,25,1600,900,radiusArr[0],sizeArr[0],speedArr[0],sf::Color(139, 0, 255),window);
    createBodyCells(bodyCells, 25, 1600, 900, radiusArr[1], sizeArr[1], speedArr[1], sf::Color::Red, window);
    createMacroCells(macroCells, 25, 1600, 900, radiusArr[2], sizeArr[2], speedArr[2], sf::Color::Yellow, window);
    createNeutroCells(neutroCells, 25, 1600, 900, radiusArr[3], sizeArr[3], speedArr[3], sf::Color::Green, window);

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
        for(int i=0;i<25;++i){
            patogenCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
            macroCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
            neutroCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
            bodyCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
        }
        for(int i=0;i<25;++i){
            patogenCells.at(i).draw(window);
            macroCells.at(i).draw(window);
            neutroCells.at(i).draw(window);
            bodyCells.at(i).draw(window);
        }
        // for (int i = 0; i < countArr[0]; ++i)
        // {
        //     patogenCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
        //     patogenCells.at(i).draw(window);
        // }

        // for (int i = 0; i < countArr[2]; ++i)
        // {
        //     macroCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
        //     macroCells.at(i).draw(window);
        // }

        // for (int i = 0; i < countArr[3]; ++i)
        // {
        //     neutroCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
        //     neutroCells.at(i).draw(window);
        // }

        // for (int i = 0; i < countArr[1]; ++i)
        // {
        //     bodyCells.at(i).update(patogenCells,bodyCells,macroCells,neutroCells,deltaTime);
        //     bodyCells.at(i).draw(window);
        // }


        window.display();
    }

    return 0;
}
