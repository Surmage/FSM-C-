#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

const sf::Vector2f coords[6] = { sf::Vector2f(10, 50), sf::Vector2f(300, 50), 
    sf::Vector2f(600, 50), sf::Vector2f(10, 400), sf::Vector2f(300, 400), sf::Vector2f(600, 400) };

namespace LocationC {
    inline sf::Vector2f getCoords(int& i, int id) {
        switch (id){
        case(0): 
            return coords[i];        
            break;
        case(1): 
            return sf::Vector2f(coords[i].x + 100, coords[i].y);
            break;
        case(2): 
            return sf::Vector2f(coords[i].x, coords[i].y + 100);
            break;
        case(3): 
            return sf::Vector2f(coords[i].x + 100, coords[i].y + 100);
            break;

        }
        return coords[i];
    }
    
}

enum struct Location : int 
{
    Mines = 0,
    Home = 1,
    Work = 2,
    Restaurant = 3,
    Bar = 4,
    Field = 5
};