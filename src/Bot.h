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
	int  verBuche(Carta cartaDelBuhce);
	int verMano( Carta cartita);

};