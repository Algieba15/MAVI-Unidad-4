#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;

// Clase para el Crosshair (mira)
class Crosshair {
private:
    RectangleShape lineaHorizontal;
    RectangleShape lineaVertical;

public:
    // Constructor que inicializa las líneas de la mira
    Crosshair() {
        // Configura línea horizontal
        lineaHorizontal.setSize(Vector2f(20.0f, 2.0f));
        lineaHorizontal.setFillColor(Color::Red);
        lineaHorizontal.setOrigin(10.0f, 1.0f);  // Centra la línea horizontal

        // Configura línea vertical
        lineaVertical.setSize(Vector2f(2.0f, 20.0f));
        lineaVertical.setFillColor(Color::Red);
        lineaVertical.setOrigin(1.0f, 10.0f);  // Centra la línea vertical
    }

    // Método para actualizar la posición de la mira según el mouse
    void update(Vector2f posicionMouse) {
        lineaHorizontal.setPosition(posicionMouse);
        lineaVertical.setPosition(posicionMouse);
    }

    // Método para dibujar la mira
    void draw(RenderWindow& window) {
        window.draw(lineaHorizontal);
        window.draw(lineaVertical);
    }
};

// Clase para el enemigo (Red Circle)
class Enemy {
private:
    Sprite sprite;
    bool isActive;  // Estado del enemigo, si está activo o no

public:
    // Constructor que carga la textura y ajusta el sprite
    Enemy(Texture& texture, Vector2f position) {
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);  // Escala para que el enemigo sea visible y de tamaño adecuado
        sprite.setPosition(position);
        isActive = true;
    }

    // Método para comprobar si el enemigo ha sido clickeado
    bool checkClick(Vector2f posicionMouse) {
        if (isActive && sprite.getGlobalBounds().contains(posicionMouse)) {
            isActive = false;  // Desactiva el enemigo si fue clickeado
            return true;       // Indica que fue clickeado
        }
        return false;
    }

    // Método para verificar si el enemigo está activo
    bool getIsActive() const {
        return isActive;
    }

    // Método para dibujar el enemigo si está activo
    void draw(RenderWindow& window) {
        if (isActive) {
            window.draw(sprite);
        }
    }
};

// Función para generar una posición aleatoria dentro de la ventana
Vector2f generarPosicionAleatoria(int windowWidth, int windowHeight, int enemyWidth, int enemyHeight) {
    int x = rand() % (windowWidth - enemyWidth);
    int y = rand() % (windowHeight - enemyHeight);
    return Vector2f(static_cast<float>(x), static_cast<float>(y));
}

int main() {
    // Inicializa la ventana
    RenderWindow window(VideoMode(800, 600), "Juego Crosshair");

    // Cargar textura para el enemigo
    Texture texturaEnemigo;
    if (!texturaEnemigo.loadFromFile("redcircle.png")) {
        std::cerr << "Error: No se pudo cargar la textura redcircle.png" << std::endl;
        return -1;
    }

    // Inicializa el crosshair
    Crosshair crosshair;

    // Vector para almacenar los enemigos
    std::vector<Enemy> enemigos;
    int enemigosDerrotados = 0;
    const int enemigosObjetivo = 5;

    // Semilla para los números aleatorios
    srand(static_cast<unsigned>(time(0)));

    // Crea el primer enemigo
    enemigos.push_back(Enemy(texturaEnemigo, generarPosicionAleatoria(800, 600, texturaEnemigo.getSize().x, texturaEnemigo.getSize().y)));

    // Bucle principal del juego
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Verifica si el usuario hace clic en el enemigo con el botón izquierdo
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f posicionMouse(event.mouseButton.x, event.mouseButton.y);

                // Verifica si algún enemigo fue clickeado
                for (auto& enemigo : enemigos) {
                    if (enemigo.checkClick(posicionMouse)) {
                        enemigosDerrotados++;
                        if (enemigosDerrotados < enemigosObjetivo) {
                            enemigos.push_back(Enemy(texturaEnemigo, generarPosicionAleatoria(800, 600, texturaEnemigo.getSize().x, texturaEnemigo.getSize().y)));
                        }
                    }
                }
            }
        }

        // Finaliza el juego si el jugador derrota5 enemigos
        if (enemigosDerrotados >= enemigosObjetivo) {
            std::cout << "¡Derrotaste " << enemigosObjetivo << " enemigos! ¡Ganaste!" << std::endl;
            window.close();
        }

        // Actualiza la posición de la mira
        crosshair.update(Vector2f(Mouse::getPosition(window)));

        // Dibuja todo en la ventana
        window.clear(Color::Black);
        crosshair.draw(window);

        for (auto& enemigo : enemigos) {
            enemigo.draw(window);
        }

        window.display();
    }

    return 0;
}


