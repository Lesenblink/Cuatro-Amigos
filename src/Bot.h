#pragma once
#include "Jugador.h"
#include "Carta.h"
#include <SFML/Graphics.hpp>
class Jugador;
class Carta;

class Bot: public Jugador {
private:
	int numeroBot;
	void posicionJugador2(); //Función para posicionar las cartas del bot
	void posicionJugador2Reserva(); //Función para posicionar las cartas de reserva del bot
	void posicionJugador2Final(); //Función para posicionar las cartas de la mano final del bot
	void posicionJugador3(); //Función para posicionar las cartas del bot
	void posicionJugador3Reserva(); //Función para posicionar las cartas de reserva del bot
	void posicionJugador3Final(); //Función para posicionar las cartas de la mano final del bot
	void posicionJugador4(); //Función para posicionar las cartas del bot
	void posicionJugador4Reserva(); //Función para posicionar las cartas de reserva del bot
	void posicionJugador4Final(); //Función para posicionar las cartas de la mano final del bot
public:
	Bot(Carta  carta1, Carta carta2, Carta carta3, Carta  carta4, Carta  carta5, Carta  carta6, Carta  carta7, Carta  carta8, Carta  carta9, int num);
	int verBuche(Carta cartaDelBuhce); // Verifica si el bot puede jugar sobre el buche
	int verMano( Carta cartita); // Verifica las cartas en la mano del bot
	int getNumeroJugador() { return numeroBot; } // Retorna el número del bot (2, 3 o 4)
	void operator+(Carta carta); // Agrega una carta a la mano del bot y la posiciona

};