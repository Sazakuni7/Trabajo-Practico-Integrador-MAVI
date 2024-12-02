#include "inocent.h"

Inocent::Inocent(float x, float y, const sf::Texture& texture)
    : Personaje(texture, x, y) {
    sprite.setScale(0.8f, 0.8f);
}

void Inocent::update() {
    // Lógica específica del inocente
}