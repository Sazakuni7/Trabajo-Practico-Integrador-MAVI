#ifndef DISPARO_H
#define DISPARO_H

#include <SFML/Graphics.hpp>

class Disparo {
private:
    sf::Sprite sprite;             
    sf::IntRect currentFrame;      //Rectángulo que define el frame actual
    sf::Clock animationClock;      //Reloj para manejar la animación
    int totalFrames;               //Número total de frames en el sprite sheet
    float frameDuration;           //Duración de cada frame (en segundos)
    bool isActive;                 //Indica si el disparo está activo

public:
    Disparo(const sf::Texture& texture, int totalFrames, float frameDuration);
    void start(const sf::Vector2f& position); 
    void update();                            
    void render(sf::RenderWindow& window);    
    bool isFinished() const;                  
};

#endif