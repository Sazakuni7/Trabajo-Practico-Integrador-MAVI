#include "UI.h"
#include "config.h"
#include <iostream>

UI::UI() : puntaje(0), vidas(3), enemigosDerrotados(0), contInocent(0), gameOver(false) {
   if (!font.loadFromFile("assets/fuente.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }

   franjaNegra.setSize(sf::Vector2f(ANCHO_VENTANA, ALTO_UI));
    franjaNegra.setFillColor(sf::Color::Black);
    franjaNegra.setPosition(0, ALTO_JUEGO);

    textoPuntaje.setFont(font);
    textoPuntaje.setCharacterSize(20);
    textoPuntaje.setFillColor(sf::Color::White);
    textoPuntaje.setPosition(10, 710);

    textoVidas.setFont(font);
    textoVidas.setCharacterSize(20);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(10, 740);

    textoEnemigos.setFont(font);
    textoEnemigos.setCharacterSize(20);
    textoEnemigos.setFillColor(sf::Color::White);
    textoEnemigos.setPosition(10, 770);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(25);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER\nPresiona espacio para cerrar");
    gameOverText.setPosition(300, 720);

    puntajeFinalText.setFont(font);
    puntajeFinalText.setCharacterSize(25);
    puntajeFinalText.setFillColor(sf::Color::White);    

    firma.setFont(font);
    firma.setCharacterSize(20);
    firma.setFillColor(sf::Color::White);
    firma.setString("Emiliano Arias - MAVI");
    firma.setPosition(855, 775);
}
void UI::actualizarTextos() {
    textoVidas.setString("Vidas: " + std::to_string(vidas));
    textoPuntaje.setString("Puntaje: " + std::to_string(puntaje));
    textoEnemigos.setString("Enemigos derrotados: " + std::to_string(enemigosDerrotados));
}

void UI::nuevoPuntaje(int num) { //Si el puntaje recibido es 1, sumar; si es -1 contar internamente inocentes abatidos y sumar puntaje (en este caso restará porque positivo + negativo es negativo)
    if (num == 1) {
        puntaje += num;
    }
    else {
        contInocent++;
        puntaje += num;
    }
}
void UI::incrementarEnemigosDerrotados(int incremento) {
    enemigosDerrotados += std::max(0, incremento);
}
void UI::perderVida() {
    if (vidas > 0) {
        vidas--;
    }
    if(vidas <=0){
        setGameOver(true);
    }
}
void UI::setGameOver(bool state) {
    gameOver = state;
}

void UI::actualizarPuntajeFinal() {
    int puntajeFinal = enemigosDerrotados - (contInocent * 2); //Cálculo del puntaje final (Restarle a enemigosDerrotados la cantidad multiplicada de Inocentes disparados por 2)
    puntajeFinalText.setString("Puntaje final: " + std::to_string(puntajeFinal));
    //Ajusta la posición a la derecha del texto de Game Over
    sf::FloatRect bounds = gameOverText.getGlobalBounds();
    puntajeFinalText.setPosition(bounds.left + bounds.width + 20, bounds.top); //A la derecha con un margen de 20
}

 void UI::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(franjaNegra);
    ventana.draw(textoPuntaje);
    ventana.draw(textoVidas);
    ventana.draw(textoEnemigos);
    ventana.draw(firma);
    if (gameOver) {
        ventana.draw(gameOverText);
        ventana.draw(puntajeFinalText);
    }
}

 //Métodos de acceso/getters
 int UI::getVidas() const {
     return vidas;
 }

 const sf::Text& UI::getGameOverText() const {
     return gameOverText;
 }

