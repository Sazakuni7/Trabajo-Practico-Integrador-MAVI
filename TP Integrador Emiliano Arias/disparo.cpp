#include "disparo.h"

Disparo::Disparo(const sf::Texture& texture, int totalFrames, float frameDuration)
    : totalFrames(totalFrames), frameDuration(frameDuration), isActive(false) {
    sprite.setTexture(texture);
    currentFrame = sf::IntRect(0, 0, texture.getSize().x / totalFrames, texture.getSize().y);
    sprite.setTextureRect(currentFrame);
    sprite.setScale(0.6f, 0.6f);
}

void Disparo::start(const sf::Vector2f& position) {
    isActive = true;
    //Ajusta la posición inicial del disparo del enemigo
    sprite.setPosition(position.x - sprite.getGlobalBounds().width / 2.f,
    position.y - sprite.getGlobalBounds().height / 2.f);
    animationClock.restart();
}

void Disparo::update() {
    if (!isActive) return;
    float elapsed = animationClock.getElapsedTime().asSeconds(); //Se obtiene el tiempo en segundos del reloj de animación
    int frameIndex = static_cast<int>(elapsed / frameDuration); //El indice del frame es: Cuánto tiempo pasó durante la animación dividido por la duración total del frame actual
    if (frameIndex >= totalFrames) { //Si el frame actual es mayor o igual que la totalidad de frames del sheet, finalizar la animación
        isActive = false;
        return;
    }
    //Luego actualizar el frame actual, teniendo en cuenta el ancho de este nuevo frame, para que se agrande hacia la izquierda si es necesario
    currentFrame.left = frameIndex * currentFrame.width;
    sprite.setTextureRect(currentFrame);
}

void Disparo::render(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

bool Disparo::isFinished() const {
    return !isActive;
}