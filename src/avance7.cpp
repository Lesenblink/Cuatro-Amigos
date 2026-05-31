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
        RenderWindow window(sf::VideoMode({ 1400, 800 }), "Four Friends - Select Your Character");

        Texture sharinganTex;
        sharinganTex.loadFromFile("../assets/Sharingan.png");
        Sprite sharingan(sharinganTex);
        sharingan.setScale(Vector2f(0.1f, 0.1f));
        sharingan.setPosition(Vector2f(1320.f, 730.f));

        Texture rosterTex;
        rosterTex.loadFromFile("../assets/Roster.png");
        Sprite rosterSprite(rosterTex);
        rosterSprite.setScale(Vector2f(1400.f / rosterTex.getSize().x, 800.f / rosterTex.getSize().y));

		//Botones transparentes del roster principal
        RectangleShape btn[6];
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

        //¿Más personajes?
        btn[4] = RectangleShape(Vector2f(50.f, 50.f)); // Personaje secreto 1
        btn[4].setOrigin(Vector2f(-1330.f, -730.f));
        btn[4].setFillColor(Color::Transparent);

        btn[5] = RectangleShape(Vector2f(50.f, 50.f)); // Personaje secreto 2
        btn[5].setOrigin(Vector2f(-94.f, -600.f));
        btn[5].setFillColor(Color::Transparent);

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    for (int i = 0; i < 6; i++)
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
            window.draw(sharingan);
            for (int i = 0; i < 6; i++)
                window.draw(btn[i]);
            window.display();
        }
    }

    int getPersonajeElegido() const { return personajeElegido; }
};

class Acabajuego {
private:
    bool replayValue = 0; 
public:
    void creaPantalla() {

            RenderWindow window(VideoMode({ 800, 600 }), "Resultado");

            // fondo
            RectangleShape fondo;
            fondo.setSize(Vector2f(1000.f, 1000.f));
            fondo.setPosition(Vector2f(100.f, 100.f));
            fondo.setFillColor(Color::Black);

            while (const std::optional event = window.pollEvent())
            {

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    if (fondo.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        window.close();

                    }
                    window.clear();
                    window.draw(fondo);
                    window.display();
                }

            }
        }
};

//Motor del juego
int main() {
    Menu menu;
	Acabajuego acabajuego;
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