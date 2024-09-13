#include "TileMap.hpp"

TileMap::TileMap(const sf::Vector2f& position, float gridWidth, float gridHeight, int numRows, int numCols)
    : numOfRows(numRows), numOfCols(numCols), position(position) {
    tileHight = gridHeight;
    tileWidth = gridWidth;
    cellWidth = gridWidth / numCols;
    cellHeight = gridHeight / numRows;
    CreateTileMapLines(gridWidth, gridHeight);
}

void TileMap::CreateTileMapLines(float gridWidth, float gridHeight) {
    for (int i = 0; i <= numOfRows; i++) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(position.x, position.y + i * cellHeight);
        line[1].position = sf::Vector2f(position.x + gridWidth, position.y + i * cellHeight);
        tileMapLines.push_back(line);
    }

    for (int i = 0; i <= numOfCols; i++) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(position.x + i * cellWidth, position.y);
        line[1].position = sf::Vector2f(position.x + i * cellWidth, position.y + gridHeight);
        tileMapLines.push_back(line);
    }
}

void TileMap::DrawTileMap(sf::RenderWindow& window) {
    for (GameObject* const gameObject : gameObjects) {
        gameObject->Render(window);
    }
    for (const auto& line : tileMapLines) {
        window.draw(line);
    }
}

bool TileMap::IsPositionInTile(sf::Vector2f objectPosition) {
    return objectPosition.x >= position.x &&
           objectPosition.x <= position.x + tileWidth &&
           objectPosition.y >= position.y &&
           objectPosition.y <= position.y + tileHight;
}

void TileMap::AddGameObject(sf::Vector2f objectPosition, std::string type) {
    if (!IsPositionInTile(objectPosition)) {
        return;
    }
    sf::Vector2f localPosition = objectPosition - position;
    int row = std::ceil(localPosition.x / cellWidth);
    int col = std::ceil(localPosition.y / cellHeight);
    auto newPos = sf::Vector2f((row * cellWidth) - (cellWidth / 2), (col * cellHeight) - (cellHeight / 2)) + position;
    gameObjects.push_back(new GameObject(newPos, type));
}