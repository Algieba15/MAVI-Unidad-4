#include <SFML/Graphics.hpp> 
#include <vector>
#include <iostream>

using namespace sf;

int main() {

    RenderWindow window(VideoMode(800, 600), "Arrastrar círculos desde las esquinas"); // Configura la ventana

    // Carga la textura del círculo fuera del bucle principal y del bucle de eventos
    Texture texturaCirculo;
    if (!texturaCirculo.loadFromFile("redcircle.png")) {
        std::cerr << "Error: No se pudo cargar el archivo redcircle.png" << std::endl;
        return -1; // Termina si no se puede cargar el asset
    }

    // Crea y configura los sprites en las esquinas de la ventana
    std::vector<Sprite> circulos; // Vector para almacenar los círculos
    float radioCirculo = texturaCirculo.getSize().x / 2.0f;

    // Crea y posiciona los círculos en cada esquina de la ventana
    Sprite circulo1, circulo2, circulo3, circulo4;
    circulo1.setTexture(texturaCirculo);
    circulo1.setPosition(0, 0);  // Esquina superior izquierda

    circulo2.setTexture(texturaCirculo);
    circulo2.setPosition(800 - texturaCirculo.getSize().x, 0);  // Esquina superior derecha

    circulo3.setTexture(texturaCirculo);
    circulo3.setPosition(0, 600 - texturaCirculo.getSize().y);  // Esquina inferior izquierda

    circulo4.setTexture(texturaCirculo);
    circulo4.setPosition(800 - texturaCirculo.getSize().x, 600 - texturaCirculo.getSize().y);  // Esquina inferior derecha

    // Agrega los círculos al vector
    circulos.push_back(circulo1);
    circulos.push_back(circulo2);
    circulos.push_back(circulo3);
    circulos.push_back(circulo4);

    // Variables de control para el arrastre
    bool arrastrando = false;
    int circuloSeleccionado = -1;

    // Bucle principal
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)  // Cierra la ventana si se produce el evento de cierre
                window.close();

            // Detecta cuando se presiona el botón del mouse
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f posicionMouse(event.mouseButton.x, event.mouseButton.y);

                    // Comprueba si el mouse está sobre alguno de los círculos
                    for (int i = 0; i < circulos.size(); i++) {
                        FloatRect bounds = circulos[i].getGlobalBounds();
                        if (bounds.contains(posicionMouse)) {
                            arrastrando = true;         // Inicia el arrastre
                            circuloSeleccionado = i;    // Guarda el índice del círculo
                            break;
                        }
                    }
                }
            }

            // Detecta cuando se suelta el botón del mouse
            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    arrastrando = false;  // Finaliza el arrastre
                    circuloSeleccionado = -1;
                }
            }

            // Detecta el movimiento del mouse y actualiza el círculo seleccionado
            if (event.type == Event::MouseMoved) {
                if (arrastrando && circuloSeleccionado != -1) {
                    // Actualiza la posición del círculo seleccionado
                    circulos[circuloSeleccionado].setPosition(
                        event.mouseMove.x - radioCirculo,
                        event.mouseMove.y - radioCirculo
                    );
                }
            }
        }

        window.clear(Color::White);  // Limpia la pantalla con un color blanco

        // Dibuja todos los círculos en la ventana
        for (auto& circulo : circulos) {
            window.draw(circulo);
        }

        window.display();  // Muestra el contenido en pantalla
    }

    return 0;
}





