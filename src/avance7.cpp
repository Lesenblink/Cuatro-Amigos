#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Mesa.h"
#include "Luigui.h"
#include "Carta.h"
#include "Jugador.h"
#include "gameplay.h"
using namespace sf;
using namespace std;


class Menu {
private:
    bool iniciarJuego = 0;
public:
    void iniciarMenu() {
        int menux = -600.f;
        int menuy = -150.f;

        sf::RenderWindow window(sf::VideoMode({ 1400, 800 }), "Four Friends");

        //Imagen de fondo
        sf::Texture menuTex;
        menuTex.loadFromFile("../assets/Menu.png");
        sf::Sprite menuSprite(menuTex);
        sf::Vector2u texSize = menuTex.getSize();
        menuSprite.setScale(sf::Vector2f(1400.f / texSize.x, 800.f / texSize.y));

        //Botones interactivos del menú
        sf::RectangleShape Opcion1(sf::Vector2f(450.f, 105.f));
        Opcion1.setOrigin(sf::Vector2f(-830.f, -440.f));
        Opcion1.setFillColor(sf::Color::Transparent);
        sf::RectangleShape Opcion2(sf::Vector2f(450.f, 105.f));
        Opcion2.setOrigin(sf::Vector2f(-830.f, -600.f));
        Opcion2.setFillColor(sf::Color::Transparent);

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    if (Opcion1.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        window.close();
                        iniciarJuego = 1;
                    }
                    if (Opcion2.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        window.close();
                        iniciarJuego = 0;
                    }
                }
            }

            window.clear();
            window.draw(menuSprite);
            window.draw(Opcion1);
            window.draw(Opcion2);
            window.display();
        }
    }

    bool getIniciarJuego() const {
        return iniciarJuego;
    }
};

//Motor del juego
int main() {
    GamePlay juego;
    Menu menu;
    menu.iniciarMenu();
    if (menu.getIniciarJuego() == 1) {
        juego.ejecutarJuego();
    }

    return 0;
}

/*
COSAS OBSERVADAS:
-Tarda en arrancar (creo que se puede optimizar mejor)
-Falta la última meécanica, lanzar cartas encadenadas


*/