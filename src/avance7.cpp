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

class Roster {
private:
    int personajeElegido = -1;
public:
    void mostrarRoster() {
        sf::RenderWindow window(sf::VideoMode({ 1400, 800 }), "Four Friends - Select Your Character");

        sf::Texture rosterTex;
        rosterTex.loadFromFile("..\\assets\\Roster.png");
        sf::Sprite rosterSprite(rosterTex);
        rosterSprite.setScale(sf::Vector2f(1400.f / rosterTex.getSize().x, 800.f / rosterTex.getSize().y));

        // Botones semitransparentes para calibrar, después los ponés Transparent
        RectangleShape btn[4];
        btn[0] = RectangleShape(Vector2f(250.f, 300.f)); // Leon
        btn[0].setOrigin(Vector2f(-590.f, -80.f));
        btn[0].setFillColor(Color::Transparent);

        btn[1] = RectangleShape(Vector2f(250.f, 300.f)); // Peashooter
        btn[1].setOrigin(Vector2f(-990.f, -80.f));
        btn[1].setFillColor(Color::Transparent);

        btn[2] = RectangleShape(Vector2f(250.f, 300.f)); // Kenny
        btn[2].setOrigin(Vector2f(-590.f, -410.f));
        btn[2].setFillColor(Color::Transparent);

        btn[3] = RectangleShape(Vector2f(250.f, 300.f)); // Sans
        btn[3].setOrigin(Vector2f(-990.f, -410.f));
        btn[3].setFillColor(Color::Transparent);

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (btn[i].getGlobalBounds().contains(sf::Vector2f(mousePos)))
                        {
                            personajeElegido = i;
                            window.close();
                        }
                    }
                }
            }

            window.clear();
            window.draw(rosterSprite);
            for (int i = 0; i < 4; i++)
                window.draw(btn[i]);
            window.display();
        }
    }

    int getPersonajeElegido() const { return personajeElegido; }
};

//Motor del juego
int main() {
    Menu menu;
    menu.iniciarMenu();
    if (menu.getIniciarJuego() == 1) {
        Roster roster;
        roster.mostrarRoster();
        int personaje = roster.getPersonajeElegido();

        GamePlay juego(personaje);
        juego.ejecutarJuego();
    }

    return 0;
}

/*
Lógica, totalmente termianda
Falta algunos detalles visuales nada más.
*/