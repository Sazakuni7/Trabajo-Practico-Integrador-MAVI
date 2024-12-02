#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje {
protected:
    sf::Sprite sprite;
   // const sf::Texture& texture; // Referencia constante a la textura
    bool alive;
    sf::Clock lifeTimer; // Tiempo de vida en pantalla

public: //Quedó un poco desordenado aquí anteriormente, así que voy a comentar denotando los métodos ordenados
    //Constructor y destructor
    Personaje(const sf::Texture& texture, float x, float y);
    virtual ~Personaje() = default;
    // Métodos principales
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window);
    //Propiedades de los sprites
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    void setOrigin(float x, float y);
    void setScale(float scaleX, float scaleY);
    sf::FloatRect getBounds() const;
    // Vida y estado
    void die();
    bool isAlive() const;
    // Colisiones
    virtual bool checkCollision(const sf::Vector2f& point);
    // Tiempo de vida
    sf::Clock& getLifeTimer();
    float getWidth() const;
    float getHeight() const;
};

#endif