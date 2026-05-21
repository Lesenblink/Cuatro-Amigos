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
	// Mano principal: al revés (ocultas)
	for (int i = 0; i < numeroCartas(); i++)
		getCarta(i).aparecerAlreves();

	// Mano reserva: al revés (ocultas)
	for (int i = 0; i < numeroCartasReserva(); i++)
		getCartaReserva(i).aparecerAlreves();

	// Mano final: visibles
	for (int i = 0; i < tamanoManoFinal(); i++)
		getCartaManoFinal(i).voltear();
}

// Bot 2 - arriba de la mesa, cartas rotadas 180° (boca abajo)
// Mano principal se expande hacia la derecha desde X=360
void Bot::posicionJugador2() {
	for (int i = 0; i < numeroCartas(); i++) {
		getCarta(i).setPosition(Vector2f(360.f + i * 90.f, 60.f));
		getCarta(i).setRotation(sf::degrees(180.f));
	}
}

// Mano reserva se expande hacia la derecha desde X=60, misma Y que la principal
void Bot::posicionJugador2Reserva() {
	for (int i = 0; i < numeroCartasReserva(); i++) {
		getCartaReserva(i).setPosition(Vector2f(60.f + i * 90.f, 60.f));
		getCartaReserva(i).setRotation(sf::degrees(180.f));
	}
}

// Mano final debajo de la reserva en Y=110
void Bot::posicionJugador2Final() {
	for (int i = 0; i < tamanoManoFinal(); i++) {
		getCartaManoFinal(i).setPosition(Vector2f(60.f + i * 90.f, 110.f));
		getCartaManoFinal(i).setRotation(sf::degrees(180.f));
	}
}

// Bot 3 - lado izquierdo, cartas rotadas 90°
// Mano principal se expande hacia abajo desde Y=460
void Bot::posicionJugador3() {
	for (int i = 0; i < numeroCartas(); i++) {
		getCarta(i).setPosition(Vector2f(60.f, 460.f + i * 90.f));
		getCarta(i).setRotation(sf::degrees(90.f));
	}
}

// Mano reserva debajo de la principal desde Y=760
void Bot::posicionJugador3Reserva() {
	for (int i = 0; i < numeroCartasReserva(); i++) {
		getCartaReserva(i).setPosition(Vector2f(60.f, 760.f + i * 90.f));
		getCartaReserva(i).setRotation(sf::degrees(90.f));
	}
}

// Mano final a la derecha de la reserva en X=130
void Bot::posicionJugador3Final() {
	for (int i = 0; i < tamanoManoFinal(); i++) {
		getCartaManoFinal(i).setPosition(Vector2f(130.f, 760.f + i * 90.f));
		getCartaManoFinal(i).setRotation(sf::degrees(90.f));
	}
}

// Bot 4 - lado derecho, cartas rotadas -90°
// Mano principal se expande hacia abajo desde Y=350
void Bot::posicionJugador4() {
	for (int i = 0; i < numeroCartas(); i++) {
		getCarta(i).setPosition(Vector2f(1540.f, 350.f + i * 90.f));
		getCarta(i).setRotation(sf::degrees(-90.f));
	}
}

// Mano reserva arriba de la principal desde Y=60
void Bot::posicionJugador4Reserva() {
	for (int i = 0; i < numeroCartasReserva(); i++) {
		getCartaReserva(i).setPosition(Vector2f(1540.f, 60.f + i * 90.f));
		getCartaReserva(i).setRotation(sf::degrees(-90.f));
	}
}

// Mano final a la izquierda de la reserva en X=1470
void Bot::posicionJugador4Final() {
	for (int i = 0; i < tamanoManoFinal(); i++) {
		getCartaManoFinal(i).setPosition(Vector2f(1470.f, 60.f + i * 90.f));
		getCartaManoFinal(i).setRotation(sf::degrees(-90.f));
	}
}

// Agrega una carta a la mano del bot y la posiciona según el lado que ocupa en la mesa
// La rotación y posición se adaptan automáticamente al número del bot
void Bot::operator+(Carta carta) {
	mano.push_back(carta);
	if (numeroBot == 2) {
		mano.back().setPosition(Vector2f(360.f + (mano.size() - 1) * 90.f, 60.f));
		mano.back().setRotation(sf::degrees(180.f));
	}
	else if (numeroBot == 3) {
		mano.back().setPosition(Vector2f(60.f, 460.f + (mano.size() - 1) * 90.f));
		mano.back().setRotation(sf::degrees(90.f));
	}
	else if (numeroBot == 4) {
		mano.back().setPosition(Vector2f(1540.f, 350.f + (mano.size() - 1) * 90.f));
		mano.back().setRotation(sf::degrees(-90.f));
	}
}
