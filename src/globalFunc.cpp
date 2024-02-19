#include "cell.h"
#include "globalFunc.h"
#include "patogenCell.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


void createPatogenCells(std::vector<PatogenCell>& cellVector,int count,int windowWidth,int windowHeight,float radius,int size,float speed,sf::Color color,sf::RenderWindow& window){
    srand(time(0)); // возможно придётся перенести в какое-нибудь место в main
    for(int i=0;i<count;++i){
        float posX=rand()%(windowWidth-2*static_cast<int>(radius));
        float posY=rand()%(windowHeight-2*static_cast<int>(radius)); // this will be a problem later on. i don't care.
        PatogenCell cell(radius, size, speed, color, posX, posY);
        cellVector.push_back(cell);
    }
    for(int i=0;i<count;++i){
        cellVector.at(i).draw(window);
    }
}




void createBodyCells(std::vector<BodyCell>& cellVector,int count,int windowWidth,int windowHeight,float radius,int size,float speed,sf::Color color,sf::RenderWindow& window){
    srand(time(0)); // возможно придётся перенести в какое-нибудь место в main
    for(int i=0;i<count;++i){
        float posX=rand()%(windowWidth-2*static_cast<int>(radius));
        float posY=rand()%(windowHeight-2*static_cast<int>(radius)); // this will be a problem later on. i don't care.
        BodyCell cell(radius, size, speed, color, posX, posY);
        cellVector.push_back(cell);
    }
    for(int i=0;i<count;++i){
        cellVector.at(i).draw(window);
    }
}


void createMacroCells(std::vector<MacroCell>& cellVector,int count,int windowWidth,int windowHeight,float radius,int size,float speed,sf::Color color,sf::RenderWindow& window){
    srand(time(0)); // возможно придётся перенести в какое-нибудь место в main
    for(int i=0;i<count;++i){
        float posX=rand()%(windowWidth-2*static_cast<int>(radius));
        float posY=rand()%(windowHeight-2*static_cast<int>(radius)); // this will be a problem later on. i don't care.
        MacroCell cell(radius, size, speed, color, posX, posY);
        cellVector.push_back(cell);
    }
    for(int i=0;i<count;++i){
        cellVector.at(i).draw(window);
    }
}


void createNeutroCells(std::vector<NeutroCell>& cellVector,int count,int windowWidth,int windowHeight,float radius,int size,float speed,sf::Color color,sf::RenderWindow& window){
    srand(time(0)); // возможно придётся перенести в какое-нибудь место в main
    for(int i=0;i<count;++i){
        float posX=rand()%(windowWidth-2*static_cast<int>(radius));
        float posY=rand()%(windowHeight-2*static_cast<int>(radius)); // this will be a problem later on. i don't care.
        NeutroCell cell(radius, size, speed, color, posX, posY);
        cellVector.push_back(cell);
    }
    for(int i=0;i<count;++i){
        cellVector.at(i).draw(window);
    }
}






void csvInput(const std::string& fileName,
              std::vector<float>& radiusArr,
              std::vector<int>& sizeArr,
              std::vector<float>& speedArr,
              std::vector<int>& countArr)
{
    std::ifstream file(fileName);
    std::string line;

    //getline(file, line);
    //std::cout<<line<<"pupupu\n";








    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        std::cout<<line<<"lox"<<std::endl;

        while (std::getline(ss, token, ';'))
            tokens.push_back(token);

        if (tokens.size() != 4) {
            std::cerr << "csv pizda" << std::endl;
            continue;
        }



        radiusArr.push_back(std::stof(tokens[0]));
        sizeArr.push_back(std::stoi(tokens[1]));
        speedArr.push_back(std::stof(tokens[2]));
        //posXArr.push_back(std::stof(tokens[3]));
        //posYArr.push_back(std::stof(tokens[4]));
        countArr.push_back(std::stoi(tokens[3]));
    }




    file.close();
}