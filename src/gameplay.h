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
	Clock relojIA;
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
	void hitboxMano(); // Detecta el mouse sobre las cartas y las levanta al pasar encima


	void JugarManoIA(Bot* ia); // La IA tira la mejor carta válida al buche
	void comerBuhceIA(Bot* ia); // La IA toma todas las cartas del buche si no puede jugar
	void IAcomerCarta(Bot* ia); // La IA toma cartas del mazo para reponer su mano
	void jugarMAnoIAReserva(Bot* ia); // La IA pasa cartas de reserva a mano principal cuando se acaban
	void jugarManoIAFinal(Bot* ia); // La IA pasa cartas de mano final a mano principal cuando no hay más

	void IAJugar(Bot* ia); // Función principal que controla el flujo del turno de la IA

	bool puedeJugarCarta(Bot* ia, int indice); // Verifica si una carta específica de la IA es válida para tirar
	int mejorCartaIA(Bot* ia); // Encuentra el índice de la mejor carta a jugar (guarda comodines)

	bool verificarGanador(); // Verifica si algún jugador se quedó sin cartas y termina el juego

public:

	GamePlay();
	void ejecutarJuego();


};