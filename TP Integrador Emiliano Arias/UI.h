#ifndef UI_H
#define UI_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class UI {
private:
    sf::Font font;
    sf::Text textoPuntaje;
    sf::Text textoVidas;
    sf::Text textoEnemigos;
    sf::Text gameOverText;
    sf::Text puntajeFinalText;
    sf::Text firma;
    sf::RectangleShape franjaNegra;
    int vidas;
    int puntaje;
    int enemigosDerrotados;
    int contInocent;

public:
    UI();
    bool gameOver;
    void actualizarTextos();
    void dibujar(sf::RenderWindow& ventana);

    void nuevoPuntaje(int cantidad);
    void incrementarEnemigosDerrotados(int cantidad);
    void perderVida();
    void setGameOver(bool state);
    void actualizarPuntajeFinal();

    int getVidas() const;
    const sf::Text& getGameOverText() const;
};

#endif // UI_H