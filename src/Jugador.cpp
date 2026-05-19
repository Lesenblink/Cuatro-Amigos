#include "Carta.h"
#include "Jugador.h"
using namespace sf;
using namespace std;

//Funciones Private
void Jugador::definirPosicionMano() {
    for (int i = 0; i < mano.size(); i++) {
        mano[i].setPosition(Vector2f(700.f - i * 50.f, 700.f)); //Posicion de las cartas de la mano principal
    }
}
void Jugador::definirPosicionManoReserva() {
	for (int i = 0; i < manoReserva.size(); i++) {
		manoReserva[i].setPosition(Vector2f(700.f - i * 50.f, 520.f)); // Posiciona las cartas de la mano reserva
	}
}
void Jugador::definirPosicionManoFinal() {
	for (int i = 0; i < manoFinal.size(); i++) {
		manoFinal[i].setPosition(Vector2f(1000.f - i * 50.f, 700.f)); // Posiciona las cartas de la mano final
	}
}
// public

Jugador::Jugador(Carta  carta1, Carta carta2, Carta carta3, Carta  carta4, Carta  carta5, Carta  carta6, Carta  carta7, Carta  carta8, Carta  carta9, int num) : numeroJugador(num) {
	mano.push_back(carta1);
	mano.push_back(carta2);
	mano.push_back(carta3);
	manoReserva.push_back(carta4);
	manoReserva.push_back(carta5);
	manoReserva.push_back(carta6);
	manoFinal.push_back(carta7);
	manoFinal.push_back(carta8);
	manoFinal.push_back(carta9);
	definirPosicionMano();
	definirPosicionManoReserva();
	definirPosicionManoFinal();
	for (auto& carta : manoFinal) { //Aquí volteamos las cartas de la mano final
		carta.aparecerAlreves();
	}
}
void Jugador::operator+(Carta carta) {  //Función sobrecargada para comer 
	mano.push_back(carta); // Agrega la carta a la última  de la mano
	mano.back().setPosition(Vector2f(700.f - (mano.size() - 1) * 50.f, 700.f)); // Aquí acomoda la posicion de la nueva carta a la mano
}
Carta& Jugador::getCarta(int  posicion) {
	return mano[posicion];
}
Carta& Jugador::getCartaReserva(int  posicion) {
	return manoReserva[posicion];
}
Carta  Jugador::QuitarCarta(int x) {
	Carta carta = mano[x]; // Guarda la carta que se va a quitar
	mano.erase(mano.begin() + x); // Elimina la carta de la mano
	definirPosicionMano(); // Reajusta las posiciones de las cartas restantes
	return carta; // Devuelve la carta quitada
}
Carta  Jugador::QuitarCartaReserva(int x) {
	Carta carta = manoReserva[x]; // Guarda la carta que se va a quitar
	manoReserva.erase(manoReserva.begin() + x); // Elimina la carta de la mano reserva
	definirPosicionManoReserva(); // Reajusta las posiciones de las cartas restantes en la mano reserva
	return carta; // Devuelve la carta quitada
}
int Jugador::numeroCartas() {
	return mano.size();
}
int Jugador::numeroCartasReserva() {
	return manoReserva.size();
}
Carta& Jugador::getCartaManoFinal(int  posicion) {
	return manoFinal[posicion];
}
Carta Jugador::darCartaDeReserva(int x) {
	Carta carta = manoReserva[x]; // Guarda la carta que se va a dar
	manoReserva.erase(manoReserva.begin() + x); // Elimina la carta de la mano reserva
	definirPosicionManoReserva(); // Reajusta las posiciones de las cartas restantes en la mano reserva
	return carta; // Devuelve la carta dada
}
void Jugador::voltearCarta(int x) {
	if (x >= 0 && x < mano.size()) {   //Validamos si el indice es correcto
		mano[x].voltear();
	}
	else {
		throw out_of_range("Índice fuera de rango");//Detenemos el programa si el indice es incorrecto y lanzamos un mensaje de error 
	}
}
int Jugador::tamanoManoFinal() {
	return manoFinal.size(); //Regresa el tamaño de la mano final
}

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


