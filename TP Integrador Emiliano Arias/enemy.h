#ifndef ENEMY_H
#define ENEMY_H

#include "personaje.h"
#include "disparo.h"
#include <functional>

class Enemy : public Personaje {
private:
    Disparo disparo;
    sf::Vector2f cannonOffset; //Para conocer la posicion del ca�on del enemy
    sf::IntRect shotFrame;        //Para manejar la animaci�n del disparo
    sf::Clock animationClock;     //Controla la duraci�n de cada frame
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