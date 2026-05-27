#include "Carta.h"
#include "Jugador.h"
using namespace sf;
using namespace std;

//Funciones Private
<<<<<<< HEAD
void Jugador::definirPosicionMano() {
    for (int i = 0; i < mano.size(); i++) {
        mano[i].setPosition(Vector2f(700.f - i * 50.f, 700.f)); //Posicion de las cartas de la mano principal
    }
}
void Jugador::definirPosicionManoReserva() {
	for (int i = 0; i < manoReserva.size(); i++) {
		manoReserva[i].setPosition(Vector2f(700.f - i * 50.f, 520.f)); // Posiciona las cartas de la mano reserva
	for (int i = 0; i < mano.size(); i++) {
		mano[i].setPosition(Vector2f(900.f - i * 70.f, 650.f)); //Posicion de las cartas de la mano principal
=======

void Jugador::asignarPosicion(string tipoMano) {

	Vector2f posicion;

	if (tipoMano == "mano") {

		posicion = Vector2f(1320.f, 770.f);

		for (int i = 0; i < mano.size(); i++) {
			mano[i].setPosition(posicion - Vector2f(i * 70.f, 0));
		}
>>>>>>> 70f5719d16e1a00a49b78eeaf07915e22b276042
	}
	else if (tipoMano == "reserva") {

		posicion = Vector2f(1640.f, 770.f);

		for (int i = 0; i < manoReserva.size(); i++) {
			manoReserva[i].setPosition(posicion - Vector2f(i * 100.f, 0));
		}
	}
<<<<<<< HEAD
}
void Jugador::definirPosicionManoFinal() {
	for (int i = 0; i < manoFinal.size(); i++) {
		manoFinal[i].setPosition(Vector2f(1000.f - i * 50.f, 700.f)); // Posiciona las cartas de la mano final
		manoFinal[i].setPosition(Vector2f(1240.f - i * 50.f, 690.f)); // Posiciona las cartas de la mano final
=======
	else if (tipoMano == "final") {

		posicion = Vector2f(1640.f, 840.f);

		for (int i = 0; i < manoFinal.size(); i++) {
			manoFinal[i].setPosition(posicion - Vector2f(i * 100.f, 0));
		}
>>>>>>> 70f5719d16e1a00a49b78eeaf07915e22b276042
	}

	cout << "todos los jugadores posicionados" << endl;
}

void Jugador::separarCarta(Vector2f mousePos) { //Separar las cartas de la mano principal al pasar el mouse por encima
	for (int i = 0; i < mano.size(); i++) {
		if (mano[i].getGlobalBounds().contains(mousePos)) {
			mano[i].setPosition(Vector2f(1320.f - i * 70.f, 670.f));
		}
		else {
			mano[i].setPosition(Vector2f(1320.f - i * 70.f, 770.f));
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
void Jugador::operator+(Carta carta) {  //Función sobrecargada para comer 
	mano.push_back(carta); // Agrega la carta a la última  de la mano
<<<<<<< HEAD
	mano.back().setPosition(Vector2f(700.f - (mano.size() - 1) * 50.f, 700.f)); // Aquí acomoda la posicion de la nueva carta a la mano
	mano.back().setPosition(Vector2f(900.f - (mano.size() - 1) * 70.f, 700.f)); // Aquí acomoda la posicion de la nueva carta a la mano
=======
	mano.back().setPosition(Vector2f(1320.f - (mano.size() - 1) * 70.f, 770.f)); // Aquí acomoda la posicion de la nueva carta a la mano
	cout << "Carta agregada a la mano del jugador" << endl;
>>>>>>> 70f5719d16e1a00a49b78eeaf07915e22b276042
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

<<<<<<< HEAD
Carta& Jugador::gettamanoManoFinal(int  posicion) {
	return manoFinal[posicion];
}
Carta Jugador::darCartaFinal(int x) {
	if (x >= 0 && x < manoFinal.size()) {  //Validamos si el indice es correcto
		Carta carta = manoFinal[x];  //Creamos una copia
		manoFinal.erase(manoFinal.begin() + x); // Elimina la carta de la mano final
		cout << "Sacaste la carta de la mano final" << x << endl;
		return carta; //Regresamos la copia
	}
	else {
		throw out_of_range("Índice fuera de rango");//Detenemos el programa si el indice es incorrecto y lanzamos un mensaje de error 
	}
}
=======


>>>>>>> 70f5719d16e1a00a49b78eeaf07915e22b276042

bool Jugador::getCartaHitBox(int x) {
	if (x >= 0 && x < mano.size()) {  //Validamos si el indice es correcto
		return mano[x].getHItBox();
	}
	else {
		cout << "Error fuera del rango de hitBox " << endl;
	}
}
<<<<<<< HEAD
=======

>>>>>>> 70f5719d16e1a00a49b78eeaf07915e22b276042
