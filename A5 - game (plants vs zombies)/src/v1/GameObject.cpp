#include "GameObject.hpp"

GameObject::GameObject(const sf::Vector2f& position, const std::string& type) {
    texture.loadFromFile(type);
    sprite.setTexture(texture);
    float xPos = position.x - (sprite.getTextureRect().width / 2);
    float yPos = position.y - (sprite.getTextureRect().height / 2);
    sprite.setPosition(xPos, yPos);
}

void GameObject::Render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f GameObject::GetPosition() {
    return sprite.getPosition();
}
