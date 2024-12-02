#include "menu.h"
#include <iostream>

Menu::Menu() : currentState(MenuState::MainMenu) { //El constructor primero se crea con el primer estado, el de menu principal, no con el de instrucciones
    if (!menuBgTexture.loadFromFile("assets/menubg.png")) {
        std::cerr << "Error al cargar la imagen." << std::endl;
    }
    menuBgSprite.setTexture(menuBgTexture);

    if (!tutoBgTexture.loadFromFile("assets/tutobg.png")) {
        std::cerr << "Error al cargar la imagen." << std::endl;
    }
    tutoBgSprite.setTexture(tutoBgTexture);

    if (!font.loadFromFile("assets/fuente.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }

    titulo.setFont(font);
    titulo.setString("Pirate Gunman");
    titulo.setCharacterSize(48);
    titulo.setFillColor(sf::Color::Yellow);
    titulo.setPosition(390, 180);

    botonJugar.setFont(font);
    botonJugar.setString("Jugar");
    botonJugar.setCharacterSize(32);
    botonJugar.setFillColor(sf::Color::Green);
    botonJugar.setPosition(400, 300);

    botonSalir.setFont(font);
    botonSalir.setString("Salir");
    botonSalir.setCharacterSize(32);
    botonSalir.setFillColor(sf::Color::Red);
    botonSalir.setPosition(400, 400);

    instrucciones.setFont(font);
    instrucciones.setString(
        "Instrucciones:\n"
        "- Apunta con el ratón y dispara con el click izquierdo.\n"
        "- Mata enemigos para ganar 1 punto.\n"
        "- Disparar a inocente resta 1 punto y 1 vida.\n"
        "- Game over si te quedas sin vidas.\n\n"
        "Presiona disparar para comenzar."
    );
    instrucciones.setCharacterSize(24);
    instrucciones.setFillColor(sf::Color::White);
    instrucciones.setPosition(150, 150);
}

void Menu::manejarEvento(const sf::Event& evento, sf::RenderWindow& ventana, bool& iniciarJuego) {
    if (evento.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);
        if (currentState == MenuState::MainMenu) { //Ya sea si se ha posicionado y clickeado en boton jugar o salir, se pasa a instrucciones o se cierra respectivamente
            if (botonJugar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                currentState = MenuState::Instructions; //Cambia a instrucciones
            }
            else if (botonSalir.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                ventana.close(); // Cierra el juego
            }
        }
        else if (currentState == MenuState::Instructions) {
            iniciarJuego = true; // Empieza el juego
        }
    }
}

void Menu::dibujar(sf::RenderWindow& ventana) {
    if (currentState == MenuState::MainMenu) {
        ventana.draw(menuBgSprite);
        ventana.draw(titulo);
        ventana.draw(botonJugar);
        ventana.draw(botonSalir);
    }
    else if (currentState == MenuState::Instructions) {
        ventana.draw(tutoBgSprite);
        ventana.draw(instrucciones);
    }
}