#ifndef GAME_OBJECT_HPP_INCLUDE
#define GAME_OBJECT_HPP_INCLUDE

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

namespace GameObjectType {
const std::string FLOWER = "asset/Sunflower.png";

}

class GameObject {
public:
    GameObject(const sf::Vector2f& position, const std::string& type);
    void Render(sf::RenderWindow& window);
    sf::Vector2f GetPosition();

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif
