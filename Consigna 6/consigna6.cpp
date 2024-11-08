#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;

// Clase para el Crosshair (mira)
class Crosshair {
private:
    RectangleShape lineaHorizontal;
    RectangleShape lineaVertical;

public:
    Crosshair() {
        lineaHorizontal.setSize(Vector2f(20.0f, 2.0f));
        lineaHorizontal.setFillColor(Color::Red);
        lineaHorizontal.setOrigin(10.0f, 1.0f);

        lineaVertical.setSize(Vector2f(2.0f, 20.0f));
        lineaVertical.setFillColor(Color::Red);
        lineaVertical.setOrigin(1.0f, 10.0f);
    }

    void update(Vector2f posicionMouse) {
        lineaHorizontal.setPosition(posicionMouse);
        lineaVertical.setPosition(posicionMouse);
    }

    void draw(RenderWindow& window) {
        window.draw(lineaHorizontal);
        window.draw(lineaVertical);
    }
};

// Clase para el enemigo
class Enemy {
private:
    Sprite sprite;
    bool isActive;

public:
    Enemy(Texture& texture, Vector2f position) {
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);
        sprite.setPosition(position);
        isActive = true;
    }

    bool checkClick(Vector2f posicionMouse) {
        if (isActive && sprite.getGlobalBounds().contains(posicionMouse)) {
            isActive = false;  // Desactiva el enemigo
            return true;
        }
        return false;
    }

    bool getIsActive() const {
        return isActive;
    }

    void reset(Vector2f position) {
        sprite.setPosition(position);
        isActive = true;
    }

    void draw(RenderWindow& window) {
        if (isActive) {
            window.draw(sprite);
        }
    }
};

// Genera una posición aleatoria dentro de la ventana
Vector2f generarPosicionAleatoria(int windowWidth, int windowHeight, int enemyWidth, int enemyHeight) {
    int x = rand() % (windowWidth - enemyWidth);
    int y = rand() % (windowHeight - enemyHeight);
    return Vector2f(static_cast<float>(x), static_cast<float>(y));
}

int main() {
    RenderWindow window(VideoMode(800, 600), "Juego Crosshair");

    Texture texturaEnemigo;
    if (!texturaEnemigo.loadFromFile("et.png")) {
        std::cerr << "Error: No se pudo cargar la textura et.png" << std::endl;
        return -1;
    }

    Crosshair crosshair;

    int enemigosDerrotados = 0;
    const int enemigosObjetivo = 5;

    srand(static_cast<unsigned>(time(0)));

    // Crear el primer enemigo en una posición aleatoria
    Enemy enemigo(texturaEnemigo, generarPosicionAleatoria(800, 600, texturaEnemigo.getSize().x, texturaEnemigo.getSize().y));

    // Bucle principal del juego
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Detecta clic izquierdo
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f posicionMouse(event.mouseButton.x, event.mouseButton.y);

                // Verifica si el enemigo fue clickeado
                if (enemigo.checkClick(posicionMouse)) {
                    enemigosDerrotados++;

                    // Si no hemos alcanzado el objetivo, reactiva al enemigo en una nueva posición aleatoria
                    if (enemigosDerrotados < enemigosObjetivo) {
                        enemigo.reset(generarPosicionAleatoria(800, 600, texturaEnemigo.getSize().x, texturaEnemigo.getSize().y));
                    }
                }
            }
        }

        // Verificar la condición de victoria
        if (enemigosDerrotados >= enemigosObjetivo) {
            std::cout << "¡Derrotaste a " << enemigosObjetivo << " enemigos! ¡Ganaste!" << std::endl;
            window.close();
        }

        // Actualiza la posición de la mira
        crosshair.update(Vector2f(Mouse::getPosition(window)));

        // Dibuja todo en la ventana
        window.clear(Color::Black);
        crosshair.draw(window);
        enemigo.draw(window);

        window.display();
    }

    return 0;
}

