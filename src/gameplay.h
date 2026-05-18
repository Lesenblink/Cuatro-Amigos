#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Mesa;
class Luigui;
class Carta;
class Jugador;

using namespace sf;
class GamePlay {
private:
	RenderWindow window;
	Mesa* mesa;
	Luigui* luigui;
	Jugador* jugador1;
	Font font, font2;
	
	bool turno;
	int cadenaComodin;
	void validarFonts();
	void cargar();

	void juego();
public:
	
	GamePlay();
	void ejecutarJuego();
	

};