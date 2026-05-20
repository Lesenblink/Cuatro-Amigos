#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <vector>
class Mesa;
class Luigui;
class Carta;
class Jugador;
class Bot;
using namespace sf;
class GamePlay {
private:
	RenderWindow window;
	std::vector <Bot*> IA;
	Mesa* mesa;
	Luigui* luigui;
	Jugador* jugador1;
	Font font, font2;
	Vector2f mousePos;
	Music musica;
	bool estaLevantada; //Variable para separar las cosas.
	bool click;  //Variable para separar las cosas. 
	int turno; //Variable para el sistema de turnos
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

	void JugarManoIA(Bot* ia);
	void comerBuhceIA(Bot* ia);
	void IAcomerCarta(Bot* ia);
	void jugarMAnoIAReserva(Bot* ia);
	void jugarManoIAFinal(Bot* ia);

	void IAJugar(Bot* ia);
public:

	GamePlay();
	void ejecutarJuego();


};