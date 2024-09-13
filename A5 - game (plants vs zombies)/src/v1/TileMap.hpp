#ifndef TILE_MAP_HPP_INCLUDE
#define TILE_MAP_HPP_INCLUDE

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "GameObject.hpp"

class TileMap {
public:
    TileMap(const sf::Vector2f& position, float gridWidth, float gridHeight, int numRows, int numCols);
    void DrawTileMap(sf::RenderWindow& window);
    void AddGameObject(sf::Vector2f objectPosition, std::string type);

private:
    void CreateTileMapLines(float gridWidth, float gridHeight);
    bool IsPositionInTile(sf::Vector2f objectPosition);
    float tileWidth;
    float tileHight;
    float cellWidth;
    float cellHeight;
    int numOfRows;
    int numOfCols;
    sf::Vector2f position;
    std::vector<sf::VertexArray> tileMapLines;
    std::vector<GameObject*> gameObjects;
};

#endif