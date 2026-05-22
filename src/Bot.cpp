#include "Jugador.h"
#include "Carta.h"
#include <SFML/Graphics.hpp>
#include "Bot.h"


// Aquí implementas la función que daba error
void Bot::asignarPosicion(std::string tipoMano) {
	if (numeroBot == 2) {
		if (tipoMano == "mano") {
			for (int i = 0; i < numeroCartas(); i++) {
				getCarta(i).setPosition(Vector2f(360.f + i * 90.f, 60.f));
				getCarta(i).setRotation(sf::degrees(180.f));
			}
		}
		else if (tipoMano == "reserva") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(60.f + i * 90.f, 60.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(180.f));
			}
		}
		else if (tipoMano == "final") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(60.f + i * 90.f, 110.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(180.f));
			}
		}
	}
	else if (numeroBot == 3) {

		if (tipoMano == "mano") {
			for (int i = 0; i < numeroCartas(); i++) {
				getCarta(i).setPosition(Vector2f(60.f, 460.f + i * 90.f));
				getCarta(i).setRotation(sf::degrees(90.f));
			}
		}
		else if (tipoMano == "reserva") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(60.f, 760.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(90.f));
			}
		}
		else if (tipoMano == "final") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(130.f, 760.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(90.f));
			}
		}

	}
	else if (numeroBot == 4) {
		if (tipoMano == "mano") {
			for (int i = 0; i < numeroCartas(); i++) {
				getCarta(i).setPosition(Vector2f(1540.f, 350.f + i * 90.f));
				getCarta(i).setRotation(sf::degrees(-90.f));
			}
		}
		else if (tipoMano == "reserva") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(1540.f, 60.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(-90.f));
			}
		}
		else if (tipoMano == "final") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(1470.f, 60.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(-90.f));
			}
		}
	}
}
Bot::Bot(vector<Carta>& cartas, int num) : Jugador(cartas) {
	numeroBot = num; 
		asignarPosicion("mano");
		asignarPosicion("reserva");
		asignarPosicion("final");
	// Mano principal: al revés (ocultas)
	for (int i = 0; i < numeroCartas(); i++)
		getCarta(i).voltear(true);

	// Mano reserva: al revés (ocultas)
	for (int i = 0; i < numeroCartas("reserva"); i++)
		getCarta(i, "reserva").voltear();

	// Mano final: visibles
	for (int i = 0; i < numeroCartas("final"); i++)
		getCarta(i, "final").voltear(true);
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
