#ifndef DISPARO_H
#define DISPARO_H

#include <SFML/Graphics.hpp>

class Disparo {
private:
    sf::Sprite sprite;             
    sf::IntRect currentFrame;      //Rect�ngulo que define el frame actual
    sf::Clock animationClock;      //Reloj para manejar la animaci�n
    int totalFrames;               //N�mero total de frames en el sprite sheet
    float frameDuration;           //Duraci�n de cada frame (en segundos)
    bool isActive;                 //Indica si el disparo est� activo

public:
    Disparo(const sf::Texture& texture, int totalFrames, float frameDuration);
    void start(const sf::Vector2f& position); 
    void update();                            
    void render(sf::RenderWindow& window);    
    bool isFinished() const;                  
};

#endif