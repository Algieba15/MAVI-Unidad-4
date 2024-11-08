#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

int main() {
    RenderWindow App(VideoMode(800, 600), "Crosshair"); //Creamos la pantalla

    Texture texture;
    if (!texture.loadFromFile("crosshair.png")) { //Cargamos la textura
        std::cerr << "Error: No se pudo cargar la textura." << std::endl;
        return -1; //Indicación al Visual de qué hacer si no puede cargar la textura
    }

    Sprite sprite; // Cargamos el material del sprite. Definimos tamaño y posición de la textura del sprite del círculo azul
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(App.getSize().x / 2, App.getSize().y / 2);

    while (App.isOpen()) { //Bucle que indica cómo funciona la pantalla
        Event event;
        while (App.pollEvent(event)) {
            if (event.type == Event::Closed)
                App.close();
        }

        App.clear(); //Limpiamos la pantalla

        App.draw(sprite); //Dibujamos el sprite

        App.display(); //Mostramos la pantalla lo dibujado en el backbuffer
    }

    return 0;
}

