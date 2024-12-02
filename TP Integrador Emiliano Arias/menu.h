#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

enum class MenuState { //Se crea un arreglo para manejar los estados del menu principal
    MainMenu,
    Instructions
};

class Menu {
private:
    sf::Texture menuBgTexture;
    sf::Sprite menuBgSprite;
    sf::Texture tutoBgTexture;
    sf::Sprite tutoBgSprite;
    sf::Font font;
    sf::Text titulo;
    sf::Text botonJugar;
    sf::Text botonSalir;
    sf::Text instrucciones;

    MenuState currentState; // Estado actual del menú

public:
    Menu();
    void manejarEvento(const sf::Event& evento, sf::RenderWindow& ventana, bool& iniciarJuego);
    void dibujar(sf::RenderWindow& ventana);
};

#endif // MENU_H