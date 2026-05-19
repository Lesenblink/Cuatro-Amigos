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
	Vector2f mousePos;
	bool click;  //Variable para separar las cosas. 
	bool turno;
	int cadenaComodin;
	void validarFonts();  //Separar la logica 
	void cargar();
	void comerCarta();
	void juego();
	void eventos();
	void comerCartaBuche();
	void dejarCartas();
	void jugarCartasReserva();
	void jugarCartasFinal();
	void limpiar4Buhce();
	void dibujar();
public:
	
	GamePlay();
	void ejecutarJuego();
	

};