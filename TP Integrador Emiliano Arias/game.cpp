#include "game.h"
#include "config.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

std::vector<sf::Vector2f> spawnPoints = {
    {528.f, 300.f},  // Ventana 1 (techo)
    {529.f, 852.f},  // Ventana 2 (primer piso medio)
    {216.f, 852.f}, // Ventana 3 (primer piso izquierda)
    {220.f, 1345.f}, // Ventana 4 (planta baja izquierda)
    {838.f, 852.f}, // Ventana 5 (primer piso derecha)
    {528.f, 1500.f}, // Puerta
    {830.f, 1345.f}  // Ventana 6 (planta baja derecha)
};

Game::Game(sf::RenderWindow& ventana)
    : window(ventana), crosshair("assets/crosshair.png"), vidas(3),
    spawnOccupied(spawnPoints.size(), false), windowClosed(spawnPoints.size(), true) {//Por defecto: spawn no ocupado, ventana cerrada
    std::cout << "Spawn points inicializados: " << spawnPoints.size() << " puntos.\n";
    // Cargar texturas
    if (!bgTexture.loadFromFile("assets/house2.png") ||
        !windowTexture.loadFromFile("assets/window.png") ||
        !doorTexture.loadFromFile("assets/door.png") ||
        !innocentTexture.loadFromFile("assets/innocent.png") ||
        !hitTexture.loadFromFile("assets/hit.png")) {
        std::cerr << "Error: No se pudo cargar una textura.\n";
    }
    bgSprite.setTexture(bgTexture);
    float scaleX = ANCHO_VENTANA / bgTexture.getSize().x;
    float scaleY = ALTO_JUEGO / bgTexture.getSize().y;
    bgSprite.setScale(scaleX, scaleY);
    float verticalOffset = -05.f; // Desplazamiento hacia arriba
    // Ajustar puntos de spawn para el área jugable
    for (auto& spawnPoint : spawnPoints) {
        spawnPoint.y *= scaleY;
        spawnPoint.y += verticalOffset;
    }
    // Cargar texturas de enemigos
    for (int i = 0; i < 3; ++i) {
        std::string filename = "assets/enemy" + std::to_string(i + 1) + ".png"; //string para asignar numero de enemigo: 1, 2 o 3 (i+1)
        if (!enemyTextures[i].loadFromFile(filename)) {
            std::cerr << "Error: No se pudo cargar " << filename << "\n";
        }
    }
    //Asignar texturas de ventana, puerta y disparo del jugador a sus sprites
    windowSprite.setTexture(windowTexture);
    windowSprite.setScale(0.79f, 0.79f);
    windowSprite.setOrigin(windowTexture.getSize().x / 2.f, windowTexture.getSize().y / 2.f);
    doorSprite.setTexture(doorTexture);
    doorSprite.setOrigin(doorTexture.getSize().x / 2.f, doorTexture.getSize().y / 2.f);
    hitSprite.setTexture(hitTexture);
    hitSprite.setOrigin(hitTexture.getSize().x / 2.f, hitTexture.getSize().y / 2.f);
    hitSprite.setScale(0.8f, 0.8f);

    srand(static_cast<unsigned>(time(nullptr))); // Semilla para apariciones aleatorias
}

void Game::run(){
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    ui.actualizarTextos();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        //Si es Game Over, solo lee la tecla espacio
        if (ui.gameOver) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                window.close();
            }
            return;
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Obtén la posición del mouse en coordenadas del mundo
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (auto& personaje : personajes) {
                // Verifica colisión con un personaje
                if (personaje->checkCollision(mousePos)) {
                    personaje->die(); //Destruye al personaje
                    //Si era enemigo...
                    if (Enemy* enemy = dynamic_cast<Enemy*>(personaje.get())) {
                        ui.nuevoPuntaje(1);
                        ui.incrementarEnemigosDerrotados(1);
                        //Configura la animación de hit
                        hitPosition = mousePos;
                        hitSprite.setPosition(hitPosition);
                        showHit = true;
                        hitClock.restart(); // Reinicia el temporizador del hit
                    }
                    else { // Si era un inocente, reduce una vida y un punto
                        ui.nuevoPuntaje(-1);
                        ui.perderVida();
                        if (ui.getVidas() <= 0) {
                            ui.setGameOver(true);
                            ui.actualizarPuntajeFinal();
                        }
                    }
                }
            }
        }
    }
    crosshair.update(window);
}

void Game::update() { //SE ENCUENTRAN LOGICAS COMO: SPAWN DE ENEMIGOS, RETRASO DE SPAWN DESPUES DE LA MUERTE, ANIMACIÓN DE DISPARO.
    // Si es Game Over, detener toda lógica de actualización
    if (ui.gameOver) {
        return;
    }
    // Spawnea un nuevo personaje cada 1 segundos
    if (spawnClock.getElapsedTime().asSeconds() > 1.f && !spawnAfterDeath) {
        spawnPersonaje();
        spawnClock.restart();
    }
    //Si se está mostrando la animación de disparo y ha pasado mas de un cuarto de segundo, dejar de mostrar la animación
    if (showHit && hitClock.getElapsedTime().asSeconds() > 0.15f) {
        showHit = false;
    }
    // Actualiza todos los personajes
    for (auto it = personajes.begin(); it != personajes.end();) {
        (*it)->update();
        //Si la entidad ya no está viva y pasaron mas de 2 segundos, liberar punto de spawn y mostrar la ventana cerrada
        if (!(*it)->isAlive() || (*it)->getLifeTimer().getElapsedTime().asSeconds() > 2.f) {
            for (size_t i = 0; i < spawnPoints.size(); ++i) {
                if ((*it)->getPosition() == spawnPoints[i]) {
                    spawnOccupied[i] = false;
                    windowClosed[i] = true;
                    break;
                }
            }
            // Activa el retraso para el próximo spawn
            spawnAfterDeath = true;
            postDeathSpawnClock.restart();
            Enemy* enemy = dynamic_cast<Enemy*>(it->get());
            // Si es un enemigo y no ha disparado aún en menos de 2 segundos, inicia el disparo
            if (enemy && !enemy->isShooting() && enemy->getLifeTimer().getElapsedTime().asSeconds() <= 2.f) {
                enemy->startShooting();
                ++it; // Salta la eliminación para dejar que termine el disparo
                continue;
            }
            // Elimina el personaje una vez terminado el disparo o superado el tiempo
            it = personajes.erase(it);
        }
        else {
            ++it;
        }
    }
    // Realiza un spawn después del retraso
    if (spawnAfterDeath && postDeathSpawnClock.getElapsedTime().asSeconds() > 0.15f) {//Si la bandera es true y el reloj de spawn post muerte marcó mas de un cuarto de segundo,
        spawnPersonaje();                                                             //spawnear entidad aleatoria
        spawnAfterDeath = false;
      //  spawnClock.restart(); /*Sincroniza el temporizador principal, si se desea, descomente esta linea para lograr que luego de un enemigo eliminado, spawnee solamente una entidad, y no dos a la vez*/
    }
}

void Game::spawnPersonaje() {
    /*if (spawnPoints.empty()) {
        std::cerr << "Error: No hay puntos de spawn disponibles. spawnPoints está vacío.\n";
        return;
    }*/
    int randomIndex;
    int attempts = 0;
    //Asignar un indice aleatorio para el arreglo de spawn (entre la cantidad de puntos de spawn maximos, que serían 7)
    do {
        randomIndex = rand() % spawnPoints.size();
        attempts++;
        // Evitar un bucle infinito
        if (attempts > 100) {
            std::cerr << "Error: No hay puntos de spawn disponibles.\n";
            return;
        }
    } while (spawnOccupied[randomIndex]);
    spawnOccupied[randomIndex] = true;
    windowClosed[randomIndex] = false; //Si el spawn está ocupado, abrir ventana (ocultar ventana cerrada)
    //Crear vector para los puntos de spawn
    sf::Vector2f spawnPosition = spawnPoints[randomIndex];
    int randomChoice = rand() % 2; //Decide si será un enemigo o un inocente
    if (randomChoice == 0) {
        /*Investigué que el uso de "auto" logra que se deduzca automáticamente el tipo de variable para inocent basado en la expresión asignada, en este caso std::make_unique
        Es útil para ahorrar código y aunque cambie el tipo de valor que devuelte "make_unique", se adapta para que coincida con un tipo válido (aquí fue std::unique_ptr)
        "std::make_unique" crea un objeto y devuelve un puntero que lo administra, es creado exclusivamente en esta operación y se auto-destruye cuando "std::unique_ptr" sale de alcance*/
        auto inocent = std::make_unique<Inocent>(spawnPosition.x, spawnPosition.y, innocentTexture);
        inocent->setOrigin(inocent->getWidth() / 2.f, inocent->getHeight() / 2.f);
        personajes.emplace_back(std::move(inocent)); /*"std::move(inocent)" convierte inocent en un valor de referencia para indicar que su contenido puede ser movido en vez de copiarse
        despues con "emplace_back" se lo añade al contenedor personajes, así evitamos copiar un objeto, por si contiene demasiados datos, como en el caso siguiente que son 3 tipos de
        texturas de enemigos y además, una textura de disparo.*/
    }
    else {
        int enemyType = rand() % 3;
        auto enemy = std::make_unique<Enemy>(spawnPosition.x, spawnPosition.y, enemyTextures[enemyType], shotTexture);
        enemy->setOrigin(enemy->getWidth() / 2.f, enemy->getHeight() / 2.f);
        enemy->onEnemyShotCallback = [this]() { /*Si en game.update se cumplió la logica del enemigo que disparó, desde enemy.startShooting se enviará aquí una bandera para habilitar
                                                la perdida de vida*/
            std::cout << "¡Has perdido una vida!" << std::endl;
            ui.perderVida();
            };
        personajes.emplace_back(std::move(enemy));
    }
}

void Game::render() { //PRIMERO PERSONAJES, LUEGO VENTANAS Y PUERTA, LA CASA, EL DISPARO DE JUGADOR, LA INTERFAZ DE USUARIO Y POR ULTIMO LA MIRA
    window.clear();
    // Dibuja los personajes
    for (auto& personaje : personajes) {
        auto pos = personaje->getPosition();
        if (pos.y > ALTO_JUEGO) {
            pos.y = ALTO_JUEGO; //Asegurar que los personajes no se dibujen fuera del área jugable
        }
        personaje->setPosition(pos);
        personaje->render(window);
    }
    // Dibuja las ventanas cerradas y la puerta
    for (size_t i = 0; i < spawnPoints.size(); ++i) {
        if (windowClosed[i]) { // Si la ventana/puerta está cerrada
            if (i == 5) { // Puerta
                doorSprite.setPosition(spawnPoints[i]);
                window.draw(doorSprite);
            }
            else {
                // Es una ventana
                windowSprite.setPosition(spawnPoints[i]);
                window.draw(windowSprite);
            }
        }
    }
    window.draw(bgSprite);
    if (showHit) {
        window.draw(hitSprite);
    }
    ui.dibujar(window);
    crosshair.render(window);
    window.display();
}
