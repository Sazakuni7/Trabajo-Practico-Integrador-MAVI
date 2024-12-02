#ifndef CONFIG_H
#define CONFIG_H
/*Header que contiene constantes globales usados unicamente en game.cpp y ui.cpp.Cree esto para lograr que la franja negra del a UI no tape los elementos de la pantalla
y que en su lugar el área de juego se comprima hacia arriba en el eje Y (sin redimensionar la ventana)*/
constexpr float ALTO_UI = 100.0f;    //Altura reservada para la UI
constexpr float ALTO_JUEGO = 800.0f - ALTO_UI; //Altura del área jugable
constexpr float ANCHO_VENTANA = 1024.0f; //Ancho de la ventana

#endif // CONFIG_H