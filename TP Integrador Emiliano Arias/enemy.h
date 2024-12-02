#ifndef ENEMY_H
#define ENEMY_H

#include "personaje.h"
#include "disparo.h"
#include <functional>

class Enemy : public Personaje {
private:
    Disparo disparo;
    sf::Vector2f cannonOffset; //Para conocer la posicion del cañon del enemy
    sf::IntRect shotFrame;        //Para manejar la animación del disparo
    sf::Clock animationClock;     //Controla la duración de cada frame
    int totalFrames;              
    float frameDuration;          
    bool shootingState = false;   

public:
    Enemy(float x, float y, const sf::Texture& texture, const sf::Texture& shotTexture);
    std::function<void()> onEnemyShotCallback;
    bool isShooting() const { return shootingState; }
    void update() override;                           
    void render(sf::RenderWindow& window) override;
    void startShooting();                             
    void stopShooting();                              
};

#endif