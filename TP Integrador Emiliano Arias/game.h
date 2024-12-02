#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "enemy.h"
#include "inocent.h"
#include "UI.h"
#include "crosshair.h"


class Game {
private:
    //Ventana del juego, interfaz de usuario y mira del jugador
    sf::RenderWindow& window;
    UI ui;
    Crosshair crosshair;

    //Casa, ventana y puerta
    sf::Texture bgTexture; // Textura para la casa
    sf::Sprite bgSprite;
    sf::Texture windowTexture; //Textura para la ventana
    sf::Sprite windowSprite;
    sf::Texture doorTexture; //Textura para la puerta
    sf::Sprite doorSprite;

    //Personajes
    sf::Texture enemyTextures[3]; // Para enemigos enemy1, enemy2, enemy3
    sf::Texture innocentTexture; // Para el inocente
    sf::Texture shotTexture; // Textura para la animación del disparo
    std::vector<std::unique_ptr<Personaje>> personajes; // Almacena enemigos e inocentes

    // Animaciones y efectos
    sf::Texture hitTexture;
    sf::Sprite hitSprite;
    sf::Clock hitClock;
    sf::Vector2f hitPosition;
    bool showHit = false;

    // Lógica de spawn
    std::vector<bool> spawnOccupied; //Almacena spawns ocupados
    std::vector<bool> windowClosed;  //Indica si una ventana cerrada está visible
    sf::Clock spawnClock; //Temporizador para apariciones
    sf::Clock postDeathSpawnClock; //Indica si un spawn está pendiente
    bool spawnAfterDeath = false;

    // Vida del jugador
    int vidas;

    // Métodos privados
    void handleEvents();
    void update();
    void spawnPersonaje();
    void render();
public:
    Game(sf::RenderWindow& ventana);
    void run();
};

#endif