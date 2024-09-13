#ifndef GAME_HPP_INCLUDE
#define GAME_HPP_INCLUDE

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>

#include "GameObject.hpp"
#include "TileMap.hpp"

class Game {
public:
    Game();
    void Start();

private:
    TileMap* tileMap;
};

#endif