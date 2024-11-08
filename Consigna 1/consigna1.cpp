#include <SFML/Graphics.hpp>  
#include <iostream>           
using namespace sf;

int main() {
 
    RenderWindow App(VideoMode(800, 600), "Ventana Crosshair"); // Crea una ventana de 800x600 píxeles

    Texture texturaFondo; // Cargar la textura de fondo
    if (!texturaFondo.loadFromFile("chessw.png")) {  // Carga el archivo de la tectura
        std::cerr << "Error: No se pudo cargar el archivo chessw.png" << std::endl;
        return -1;  // Instrucción para que el programa se cierre si no se puede cargar la textura
    }

    while (App.isOpen()) {// Bucle principal del programa que mantiene la ventana abierta
        Event event;
        while (App.pollEvent(event)) {
            if (event.type == Event::Closed)  // Cierra la ventana si se recibe el evento de cierre
                App.close();
        }

        Sprite spriteFondo(texturaFondo);// Crea un sprite para el fondo y aplicarle la textura
        spriteFondo.setScale(// Escala la imagen para que ocupe toda la ventana de 800x600 píxeles
            800.0f / texturaFondo.getSize().x,
            600.0f / texturaFondo.getSize().y
        );

        // Crea las líneas del crosshair en el centro de la pantalla
        float crosshairLength = 20.0f;     // Longitud de cada línea 
        float crosshairThickness = 2.0f;   // Groso de las líneas 

        RectangleShape lineaHorizontal(Vector2f(crosshairLength, crosshairThickness));// Línea horizontal del crosshair
        lineaHorizontal.setFillColor(Color::Red);  // Asigna color rojo al crosshair
        lineaHorizontal.setOrigin(crosshairLength / 2, crosshairThickness / 2);  // Centra la línea
        lineaHorizontal.setPosition(App.getSize().x / 2, App.getSize().y / 2);   // Coloca en el centro

        RectangleShape lineaVertical(Vector2f(crosshairThickness, crosshairLength));// Línea vertical del crosshair
        lineaVertical.setFillColor(Color::Red);  // Asigna color rojo al crosshair
        lineaVertical.setOrigin(crosshairThickness / 2, crosshairLength / 2);   // Centra la línea
        lineaVertical.setPosition(App.getSize().x / 2, App.getSize().y / 2);    // Coloca en el centro

        App.clear();  // Limpia la ventana

        App.draw(spriteFondo);  // Dibuja el fondo usando la textura de chessw.png

        App.draw(lineaHorizontal); // Dibuja las líneas del crosshair en el centro de la ventana
        App.draw(lineaVertical);

        App.display();  // Muestra en pantalla
    }

    return 0;
}

