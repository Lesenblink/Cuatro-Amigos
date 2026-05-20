#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
<<<<<<< HEAD
=======
#include <SFML/Audio.hpp>
>>>>>>> 0cb4faacb84d8c46680c17aef0860b37bf9a8e78
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
<<<<<<< HEAD
	
	bool turno;
	int cadenaComodin;
	void validarFonts();
	void cargar();

	void juego();
public:
	
	GamePlay();
	void ejecutarJuego();
	
=======
	Vector2f mousePos;
	Music musica;
	bool estaLevantada; //Variable para separar las cosas.
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
	void hitboxMano();
public:

	GamePlay();
	void ejecutarJuego();

>>>>>>> 0cb4faacb84d8c46680c17aef0860b37bf9a8e78

};