#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow App(sf::VideoMode(800, 600), "Fondo de Pantalla");

    sf::Texture texturaFondo;

    if (!texturaFondo.loadFromFile("fondo.jpg")) {
        std::cerr << "Error al cargar la imagen fondo.jpg" << std::endl;
        return -1;
    }
    sf::Sprite spriteFondo;
    spriteFondo.setTexture(texturaFondo);

    spriteFondo.setScale(
        800.0f / texturaFondo.getSize().x,
        600.0f / texturaFondo.getSize().y
    );

    App.clear();
    App.draw(spriteFondo);
    App.display();

    sf::sleep(sf::seconds(10));

    return 0;
}





