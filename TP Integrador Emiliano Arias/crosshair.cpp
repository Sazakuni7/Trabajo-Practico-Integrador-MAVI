#include "crosshair.h"

Crosshair::Crosshair(const std::string& textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("No se pudo cargar la textura de mira " + textureFile);
    }
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Crosshair::update(const sf::RenderWindow& window) {
    sprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void Crosshair::render(sf::RenderWindow& window) {
    window.draw(sprite);
}