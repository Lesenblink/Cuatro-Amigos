#include "Carta.h"
#include "Jugador.h"
using namespace sf;
using namespace std;

//Funciones Private

void Jugador::asignarPosicion(string tipoMano) {

	Vector2f posicion;

	if (tipoMano == "mano") {
		for (int i = 0; i < mano.size(); i++) {
			if (i < 8) {
				mano[i].setPosition(Vector2f(1320.f - i * 70.f, 840.f)); // Primera fila
			}
			else {
				mano[i].setPosition(Vector2f(1320.f - (i - 8) * 70.f, 770.f)); // Segunda fila
			}
		}
	}
	else if (tipoMano == "reserva") {

		posicion = Vector2f(1640.f, 770.f);

		for (int i = 0; i < manoReserva.size(); i++) {
			manoReserva[i].setPosition(posicion - Vector2f(i * 100.f, 0));
		}
	}
	else if (tipoMano == "final") {

		posicion = Vector2f(1640.f, 840.f);

		for (int i = 0; i < manoFinal.size(); i++) {
			manoFinal[i].setPosition(posicion - Vector2f(i * 100.f, 0));
		}
	}

	cout << "todos los jugadores posicionados" << endl;
}

void Jugador::separarCarta(Vector2f mousePos) {
	for (int i = 0; i < mano.size(); i++) {
		float filaY = (i < 8) ? 840.f : 770.f;
		float x = (i < 8) ? 1320.f - i * 70.f : 1320.f - (i - 8) * 70.f;

		if (mano[i].getGlobalBounds().contains(mousePos)) {
			mano[i].setPosition(Vector2f(x, filaY - 30.f));
		}
		else {
			mano[i].setPosition(Vector2f(x, filaY));
		}
	}
}

void Jugador::inicializarMazo(Carta& carta, Carta& carta2, Carta& carta3, string tipoMano) {
	if (tipoMano == "mano") {
		mano.push_back(carta);
		mano.push_back(carta2);
		mano.push_back(carta3);
	}
	else if (tipoMano == "reserva") {
		manoReserva.push_back(carta);
		manoReserva.push_back(carta2);
		manoReserva.push_back(carta3);
	}
	else if (tipoMano == "final") {
		manoFinal.push_back(carta);
		manoFinal.push_back(carta2);
		manoFinal.push_back(carta3);
		cout << "-----------------------------------------Mano final inicializada con 3 cartas" << endl;
	}
}
// public

Jugador::Jugador( vector<Carta>& cartas) {
	inicializarMazo(cartas[0], cartas[1], cartas[2]);
	inicializarMazo(cartas[3], cartas[4], cartas[5], "reserva");
	inicializarMazo(cartas[6], cartas[7], cartas[8], "final");
	asignarPosicion();
	asignarPosicion("reserva");
	asignarPosicion("final");
	for (auto& carta : mano) { //Aquí volteamos las cartas de la mano final
		carta.voltear();
	}
	for (auto& carta : manoFinal) { //Aquí volteamos las cartas de la mano final
		carta.voltear(false);
	}
	for (auto& carta : manoReserva) { //Aquí volteamos las cartas de la mano final
		carta.voltear();
	}

	cout << "se repartieron todas las cartas de jugador" << endl;
}
void Jugador::operator+(Carta carta) {
	mano.push_back(carta);
	int i = mano.size() - 1;
	float filaY = (i < 8) ? 840.f : 770.f;
	float x = (i < 8) ? 1320.f - i * 70.f : 1320.f - (i - 8) * 70.f;
	mano.back().setPosition(Vector2f(x, filaY));
}
Carta& Jugador::getCarta(int  posicion, string tipoMano) {  //Para dibujar las cartas, obtenemos una carta especifica
	if (tipoMano == "mano") {
		return mano.at(posicion); //validamos el indice con at() para evitar errores de acceso a memoria
	}
	else if (tipoMano == "reserva") {
		return manoReserva.at(posicion);
	}
	else {
		return manoFinal.at(posicion);
	}
}
Carta  Jugador::QuitarCarta(int x, string tipoMano) {
	if (tipoMano == "mano") {
		Carta carta = mano.at(x); // Guarda la carta que se va a quitar
		mano.erase(mano.begin() + x); // Elimina la carta de la mano
		asignarPosicion(tipoMano); // Reajusta las posiciones de las cartas restantes
		return carta; // Devuelve la carta quitada
	}
	else if(tipoMano=="reserva")
	{
		Carta carta = manoReserva.at(x); // Guarda la carta que se va a quitar
		manoReserva.erase(manoReserva.begin() + x); // Elimina la carta de la mano reserva
		asignarPosicion("reserva"); // Reajusta las posiciones de las cartas restantes en la mano reserva
		return carta; // Devuelve la carta quitada
	}else if(tipoMano == "final")
	{
		Carta carta = manoFinal.at(x); // Guarda la carta que se va a quitar
		manoFinal.erase(manoFinal.begin() + x); // Elimina la carta de la mano final
		asignarPosicion("final"); // Reajusta las posiciones de las cartas restantes en la mano final
		return carta; // Devuelve la carta quitada
	}
	else 
		
	cout << "Carta quitada de la mano del jugador" << endl;
}

int Jugador::numeroCartas(string tipoMano) {
	if (tipoMano == "mano") {
		return mano.size();
	}
	else if (tipoMano == "reserva") {
		return manoReserva.size();
	}
	else {
		return manoFinal.size();
	}

	cout << "Número de cartas en la mano del jugador: " << numeroCartas(tipoMano) << endl;
}

void Jugador::voltearCarta(int x) {
	if (x >= 0 && x < mano.size()) {   //Validamos si el indice es correcto
		mano[x].voltear();
	}
	else {
		cout << "Error en voltear Carta" << endl;
	}

	cout << "Carta volteada en la mano del jugador" << endl;
}




bool Jugador::getCartaHitBox(int x) {
	if (x >= 0 && x < mano.size()) {  //Validamos si el indice es correcto
		return mano[x].getHItBox();
	}
	else {
		cout << "Error fuera del rango de hitBox " << endl;
	}
}

