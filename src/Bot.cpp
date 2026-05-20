#include "Jugador.h"
#include "Carta.h"
#include <SFML/Graphics.hpp>
#include "Bot.h"


Bot::Bot(Carta  carta1, Carta carta2, Carta carta3, Carta  carta4, Carta  carta5, Carta  carta6, Carta  carta7, Carta  carta8, Carta  carta9, int num) : Jugador(carta1, carta2, carta3, carta4, carta5, carta6, carta7, carta8, carta9) {
	numeroBot = num; 
	if(numeroBot == 2) {  //Asignamos las posiciones de las cartas a cada bot 
		posicionJugador2();
		posicionJugador2Reserva();
		posicionJugador2Final();
	}
	else if(numeroBot == 3) {
		posicionJugador3();
		posicionJugador3Reserva();
		posicionJugador3Final();
	}
	else if(numeroBot == 4) {
		posicionJugador4();
		posicionJugador4Reserva();
		posicionJugador4Final();
	}
}
void Bot::posicionJugador2() {
	// Implementación para posicionar las cartas del bot 2
}
void Bot::posicionJugador2Reserva() {
	// Implementación para posicionar las cartas de reserva del bot 2
}
void Bot::posicionJugador2Final() {
	// Implementación para posicionar las cartas de la mano final del bot 2
}
void  Bot::posicionJugador3() {
	// Implementación para posicionar las cartas del bot 3
}
void Bot::posicionJugador3Reserva() {
	// Implementación para posicionar las cartas de reserva del bot 3
}
void Bot::posicionJugador3Final() {
	// Implementación para posicionar las cartas de la mano final del bot 3
}
void Bot::posicionJugador4() {
	// Implementación para posicionar las cartas del bot 4
}
void Bot::posicionJugador4Reserva() {
	// Implementación para posicionar las cartas de reserva del bot 4
}
void Bot::posicionJugador4Final() {
	// Implementación para posicionar las cartas de la mano final del bot 4
}
