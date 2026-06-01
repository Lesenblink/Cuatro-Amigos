#include "Jugador.h"
#include "Carta.h"
#include <SFML/Graphics.hpp>
#include "Bot.h"


// Aquí implementas la función que daba error
void Bot::asignarPosicion(std::string tipoMano) {
	if (numeroBot == 2) {
		if (tipoMano == "mano") {
			for (int i = 0; i < numeroCartas(); i++) {
				getCarta(i).setPosition(Vector2f(460.f + i * 40.f, 210.f));
				getCarta(i).setRotation(sf::degrees(180.f));
			}
		}
		else if (tipoMano == "reserva") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(160.f + i * 60.f, 260.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(180.f));
			}
		}
		else if (tipoMano == "final") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(160.f + i * 60.f, 210.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(180.f));
			}
		}
	}
	else if (numeroBot == 3) {

		if (tipoMano == "mano") {
			for (int i = 0; i < numeroCartas(); i++) {
				getCarta(i).setPosition(Vector2f(210.f, 405.f + i * 40.f));
				getCarta(i).setRotation(sf::degrees(90.f));
			}
		}
		else if (tipoMano == "reserva") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(260.f, 705.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(90.f));
			}
		}
		else if (tipoMano == "final") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(210.f, 705.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(90.f));
			}
		}

	}
	else if (numeroBot == 4) {
		if (tipoMano == "mano") {
			for (int i = 0; i < numeroCartas(); i++) {
				getCarta(i).setPosition(Vector2f(1590.f, 460.f + i * 40.f));
				getCarta(i).setRotation(sf::degrees(-90.f));
			}
		}
		else if (tipoMano == "reserva") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(1520.f, 160.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(-90.f));
			}
		}
		else if (tipoMano == "final") {
			for (int i = 0; i < numeroCartas(tipoMano); i++) {
				getCarta(i, tipoMano).setPosition(Vector2f(1590.f, 160.f + i * 90.f));
				getCarta(i, tipoMano).setRotation(sf::degrees(-90.f));
			}
		}
	}

	cout << "Posiciones asignadas para Bot " << numeroBot << " en la mano " << tipoMano << endl;
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
<<<<<<< HEAD
	carta.voltear(true); // Voltea la carta para que quede oculta
=======
	carta.voltear(true);
>>>>>>> c36b49c0a80e64443566d79a5ddc87cb6acdb8da
	mano.push_back(carta);
	if (numeroBot == 2) {
		mano.back().setPosition(Vector2f(460.f + (mano.size() - 1) * 30.f, 210.f));
		mano.back().setRotation(sf::degrees(180.f));
	}
	else if (numeroBot == 3) {
		mano.back().setPosition(Vector2f(210.f, 405.f + (mano.size() - 1) * 30.f));
		mano.back().setRotation(sf::degrees(90.f));
	}
	else if (numeroBot == 4) {
		mano.back().setPosition(Vector2f(1590.f, 460.f + (mano.size() - 1) * 30.f));
		mano.back().setRotation(sf::degrees(-90.f));
	}

	cout << "Carta agregada a Bot " << numeroBot << ". Posición: (" << mano.back().getPos().x << ", " << mano.back().getPos().y << ")" << endl;
}
