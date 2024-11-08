#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main() {
    // Configuraci�n inicial de la ventana
    RenderWindow window(VideoMode(800, 600), "Ventana Redimensionable con L�mites");

    // Define l�mites de tama�o
    const unsigned int minWidth = 100;
    const unsigned int minHeight = 100;
    const unsigned int maxWidth = 1000;
    const unsigned int maxHeight = 1000;

    // Bucle principal
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Cierra la ventana si se recibe el evento de cierre
            if (event.type == Event::Closed)
                window.close();

            // Maneja el evento de redimensionamiento
            if (event.type == Event::Resized) {
                // Obtiene el nuevo ancho y alto de la ventana
                unsigned int newWidth = event.size.width;
                unsigned int newHeight = event.size.height;

                // Ajusta el tama�o dentro de los l�mites
                if (newWidth < minWidth) newWidth = minWidth;
                if (newWidth > maxWidth) newWidth = maxWidth;
                if (newHeight < minHeight) newHeight = minHeight;
                if (newHeight > maxHeight) newHeight = maxHeight;

                // Aplica el tama�o ajustado
                window.setSize(Vector2u(newWidth, newHeight));
            }
        }

        window.clear(Color::Black);  // Limpia la ventana con color negro
        window.display();            // Muestra el contenido de la ventana
    }

    return 0;
}
