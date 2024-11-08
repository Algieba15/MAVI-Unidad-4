#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main() {
    // Crea la  ventana
    RenderWindow window(VideoMode(1000, 800), "Alternar cuadrado amarillo y círculo rojo");

    // Carga las texturas
    Texture texturaCuadrado, texturaCirculo;
    if (!texturaCuadrado.loadFromFile("cuad_yellow.png") || !texturaCirculo.loadFromFile("redcircle.png")) {
        std::cerr << "Error: No se pudieron cargar las texturas cuad_yellow.png y/o rcircleg.png" << std::endl;
        return -1;
    }

    // Crea sprite y lo configura como cuadrado 
    Sprite forma;
    forma.setTexture(texturaCuadrado);

    // Tamaño de referencia para ambos sprites
    Vector2u tamanioCuadrado = texturaCuadrado.getSize();
    Vector2u tamanioCirculo = texturaCirculo.getSize();

    // Escalar el círculo para que coincida con el tamaño del cuadrado
    float escalaX = static_cast<float>(tamanioCuadrado.x) / tamanioCirculo.x;
    float escalaY = static_cast<float>(tamanioCuadrado.y) / tamanioCirculo.y;

    // Posición inicial de la figura
    forma.setPosition(200, 100);

    // Variables de control
    bool esCuadrado = true;   // Variable para controlar la forma actual
    float velocidad = 5.0f;   // Velocidad de movimiento

    // Bucle principal
    while (window.isOpen()) {
        // Procesa eventos
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            // Cambia la forma cuando se presiona space
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                if (esCuadrado) {
                    forma.setTexture(texturaCirculo);
                    forma.setScale(escalaX, escalaY); // Ajusta escala para el círculo
                }
                else {
                    forma.setTexture(texturaCuadrado);
                    forma.setScale(1.0f, 1.0f); // Restaura escala para el cuadrado
                }
                esCuadrado = !esCuadrado;
            }
        }

        // Movimiento con teclas de dirección
        Vector2f posicion = forma.getPosition();
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            posicion.x -= velocidad;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            posicion.x += velocidad;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            posicion.y -= velocidad;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            posicion.y += velocidad;
        }

        // Restringe el movimiento dentro de la pantalla
        if (posicion.x < 0) posicion.x = 0;
        if (posicion.y < 0) posicion.y = 0;
        if (posicion.x + tamanioCuadrado.x > window.getSize().x)
            posicion.x = window.getSize().x - tamanioCuadrado.x;
        if (posicion.y + tamanioCuadrado.y > window.getSize().y)
            posicion.y = window.getSize().y - tamanioCuadrado.y;

        forma.setPosition(posicion);

        // Dibuja la pantalla
        window.clear(Color::White);  // Limpiar pantalla
        window.draw(forma);          // Dibujar la figura actual
        window.display();            // Mostrar en pantalla
    }

    return 0;
}

