#include "Game.hpp"

Game::Game() {
    tileMap = new TileMap(sf::Vector2f(30, 90), 720, 475, 5, 9);
}

void Game::Start() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "plants vs zombies");
    sf::Clock clock;
    const sf::Time targetFrameTime = sf::seconds(1.0f / 30.0f);

    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("asset/Background-crop.png");
        sf::Sprite backgroundSprite(backgroundTexture);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f clickPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    tileMap->AddGameObject(clickPosition, GameObjectType::FLOWER);
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        tileMap->DrawTileMap(window);

        window.display();

        if (elapsedTime < targetFrameTime) {
            sf::sleep(targetFrameTime - elapsedTime);
        }
    }
}