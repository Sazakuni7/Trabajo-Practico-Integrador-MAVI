#include <SFML/Graphics.hpp>
#include "game.h"
#include "menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 800), "Pirate Gunman by Emiliano Ariel Arias - MAVI TP Integrador");
    Menu menu;
    Game game(window);
    UI ui;
    ui.actualizarTextos(); //Llamada temprana para poder mostrar textos y valores iniciales, si no solo se mostrarían en la primera actualización de puntaje, vidas o kills.
    bool iniciarJuego = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!iniciarJuego) {
                menu.manejarEvento(event, window, iniciarJuego);
            }
        }
        window.clear();
        if (!iniciarJuego) {
            window.setMouseCursorVisible(true); // Mostrar cursor en el menú
            menu.dibujar(window);
        }
        else {
            window.setMouseCursorVisible(false);
            game.run();
            break;//Salir del menú si la bandera de iniciar juego es verdadera
        }
        window.display();
    }
    return 0;
}