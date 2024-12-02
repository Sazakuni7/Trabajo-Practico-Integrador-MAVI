#include "personaje.h"

Personaje::Personaje(const sf::Texture& texture, float x, float y)
    :alive(true) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setPosition(x, y);
}

void Personaje::render(sf::RenderWindow& window) {
    if (alive) {
        window.draw(sprite);
    }
}

sf::Vector2f Personaje::getPosition() const {
    return sprite.getPosition();
}

void Personaje::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Personaje::setOrigin(float x, float y) {
    sprite.setOrigin(x, y);
}
void Personaje::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

sf::FloatRect Personaje::getBounds() const {
    return sprite.getGlobalBounds();
}

void Personaje::die() {
    alive = false;
}

bool Personaje::isAlive() const {
    return alive;
}

bool Personaje::checkCollision(const sf::Vector2f& point) {
    if (!alive) return false;
    sf::FloatRect collisionBounds = sprite.getGlobalBounds(); //Obtener los bounds del sprite
    collisionBounds.height *= 0.8f; //Redimensionar los bounds de colision, se puede ajustar si el disparo con respecto al objetivo se ve un poco fuera de lugar o falta un margen mas grande
    collisionBounds.width *= 0.8f;
    return collisionBounds.contains(point); //Comprueba la colisión
}

sf::Clock& Personaje::getLifeTimer() {
    return lifeTimer;
}

float Personaje::getWidth() const {
    return sprite.getGlobalBounds().width;
}

float Personaje::getHeight() const {
    return sprite.getGlobalBounds().height;
}