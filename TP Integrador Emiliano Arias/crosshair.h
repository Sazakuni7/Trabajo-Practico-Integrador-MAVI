#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <SFML/Graphics.hpp>

class Crosshair {
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Crosshair(const std::string& textureFile);
    void update(const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
};

#endif