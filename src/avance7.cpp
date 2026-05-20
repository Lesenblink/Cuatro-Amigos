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
<<<<<< < HEAD

<<<<<<< HEAD
class Menu {
private:
    bool iniciarJuego;
public:
    void iniciarMenu() {
        int menux = -600.f;
        int menuy = -150.f;

        sf::RenderWindow window(sf::VideoMode({ 1400, 800 }), "SFML works!");

        sf::RectangleShape Opcion1(sf::Vector2f(400.f, 200.f));
        Opcion1.setOrigin(sf::Vector2f(menux, menuy));
        Opcion1.setFillColor(sf::Color::Green);
        sf::RectangleShape Opcion2(sf::Vector2f(400.f, 200.f));
        Opcion2.setOrigin(sf::Vector2f(menux, menuy - 300.f));
        Opcion2.setFillColor(sf::Color::Blue);

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
                }
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    if (Opcion2.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        window.close();
                        iniciarJuego = 0;
                    }
                }
            }

            window.clear();
            window.draw(Opcion1);
            window.draw(Opcion2);
            window.display();
        }
    }

    bool getIniciarJuego() const {
        return iniciarJuego;
    }

	void setIniciarJuego(bool iniciar) {
		iniciarJuego = iniciar;
	}

};

=======
    class Menu {
    private:
        bool iniciarJuego = 0;
    public:
        void iniciarMenu() {
            int menux = -600.f;
            int menuy = -150.f;

            sf::RenderWindow window(sf::VideoMode({ 1400, 800 }), "SFML works!");

            sf::RectangleShape Opcion1(sf::Vector2f(400.f, 200.f));
            Opcion1.setOrigin(sf::Vector2f(menux, menuy));
            Opcion1.setFillColor(sf::Color::Green);
            sf::RectangleShape Opcion2(sf::Vector2f(400.f, 200.f));
            Opcion2.setOrigin(sf::Vector2f(menux, menuy - 300.f));
            Opcion2.setFillColor(sf::Color::Blue);

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
                    }
                    if (event->is<sf::Event::MouseButtonPressed>())
                    {
                        if (Opcion2.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                        {
                            window.close();
                            iniciarJuego = 1;
                        }
                    }
                }

                window.clear();
                window.draw(Opcion1);
                window.draw(Opcion2);
                window.display();
            }
        }

        bool getIniciarJuego() const {
            return iniciarJuego;
        }

};
>>>>>>> 43da6d6f2c86c3c414286d2effad6f5fc907024f

//motor del juego
int main() {
    // Intentamos cargar la fuente de letra de Windows
<<<<<<< HEAD
    GamePlay juego;
    Menu menu;
	menu.setIniciarJuego(0);
=======
	GamePlay juego;
	Menu menu;
>>>>>>> 43da6d6f2c86c3c414286d2effad6f5fc907024f
    menu.iniciarMenu();
    if (menu.getIniciarJuego() == 1) {
        juego.ejecutarJuego();
    };
<<<<<<< HEAD
=======
  
	GamePlay juego;
	juego.ejecutarJuego();

>>>>>>> 43da6d6f2c86c3c414286d2effad6f5fc907024f
    return 0;
}

/*
COSAS OBSERVADAS:
-Faltan el sistema de turnos
-Tambien falta la IA
-Falta el menu
-Tarda en arrancar (creo que se puede optimizar mejor)
-Falta la última meécanica, lanzar cartas encadenadas


*/