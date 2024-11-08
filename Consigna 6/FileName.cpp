#include <SFML/Window.hpp>  
#include <SFML/Graphics.hpp>  

using namespace sf;


Texture texture;//Declaramos la variable la textura (la imagen) que vamos a cargar
Sprite sprite1, sprite2, sprite3, sprite4;//Creamos los cuatro sprites que van a usar la textura

int main() {

    texture.loadFromFile("redcircle.png");//Cargamos una imagen desde el archivo "redcircle.png" en la variable `texture`

    // Cargamos el material los cuatro sprites
    sprite1.setTexture(texture);// Cargamos el material del primer sprite
    sprite1.setPosition(0, 0);//Posicionamos el primer sprite en la esquina superior izquierda (0, 0)

    sprite2.setTexture(texture);  // Cargamos el material del segundo sprite
    sprite2.setPosition((800 - 128), 0);  //Posicionamos el segundo sprite en la esquina superior derecha
    //El ancho de la ventana es 800, y el sprite tiene un ancho de 128, por lo que tenemos que restar ambos para que quede en la esquina

    sprite3.setTexture(texture);  // Cargamos el material del tercer sprite
    sprite3.setPosition(0, (600 - 128));  //Posicionamos el tercer sprite en la esquina inferior izquierda
    //El alto de la ventana es 600, y el sprite tiene un alto de 128, por lo que tenemos que restar ambos números para que quede en la esquina.

    sprite4.setTexture(texture);// Cargamos el material del cuarto sprite
    sprite4.setPosition((800 - 128), (600 - 128));  //Posicionamos el cuarto sprite en la esquina inferior derecha

    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Sniper");//Creamos una ventana de 800x600 píxeles con el título "Sniper"

    bool direction = false; //Bucle principal del programa, estará activo mientras la ventana esté abierta
    while (App.isOpen())
    {
        App.clear();// Limpiamos la ventana para dibujar desde cero en cada frame

        // Dibujar cada uno de los sprites en la ventana
        App.draw(sprite1);//Dibujamos el primer sprite en la ventana
        App.draw(sprite2);//Dibujamos el segundo sprite en la ventana
        App.draw(sprite3);//Dibujamos el tercer sprite en la ventana
        App.draw(sprite4);//Dibujamos el cuarto sprite en la ventana

        App.display();//Mostramos en pantalla lo dibujado en el backbuffer
    }

    return 0;
}


