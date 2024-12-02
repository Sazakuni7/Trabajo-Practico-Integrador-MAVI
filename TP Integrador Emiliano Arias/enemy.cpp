#include "enemy.h"

Enemy::Enemy(float x, float y, const sf::Texture& texture, const sf::Texture& shotTexture)
    : Personaje(texture, x, y), shootingState(false), disparo(shotTexture, 3, 0.1f), cannonOffset(-70.f, -40.f) {
    sprite.setScale(0.8f, 0.8f);
    //Configura el rect�ngulo inicial de la animaci�n
    shotFrame = sf::IntRect(0, 0, 256, 256); 
    sprite.setTextureRect(shotFrame);
}

void Enemy::update() {
    float elapsed = lifeTimer.getElapsedTime().asSeconds();
    if (shootingState) {
        disparo.update();
        //Detiene el disparo cuando la animaci�n completa ha terminado
        if (disparo.isFinished()) {
            shootingState = false;
        }
    }
    //Si el tiempo de vida est� cerca de terminar, empieza la animaci�n de disparo
    if (!shootingState && elapsed > 1.75f && elapsed <= 2.f) {
        startShooting();
    }
}

void Enemy::render(sf::RenderWindow& window) {
    Personaje::render(window);
    disparo.render(window);
}

void Enemy::startShooting() {
    if (!isAlive()) return; // Si el enemigo ya est� muerto, no dispara
    shootingState = true;
    disparo.start(sprite.getPosition() + cannonOffset); //Inicia la animaci�n del disparo donde est� el ca�on del sprite de enemy
    animationClock.restart();
    //Notifica al juego que el enemigo ha disparado
    if (onEnemyShotCallback) {
        onEnemyShotCallback();
    }
}

void Enemy::stopShooting() {
    shootingState = false;
}