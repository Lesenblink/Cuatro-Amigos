#pragma once
#include "Jugador.h"
#include "Carta.h"
#include <SFML/Graphics.hpp>
class Jugador;
class Carta;
using namespace std;
using namespace sf;
class Bot: public Jugador {
private:
	int numeroBot;
	void asignarPosicion(string tipoMano = "mano") override;
public:
	Bot(vector<Carta>& cartas, int num);
	int verBuche(Carta cartaDelBuhce); // Verifica si el bot puede jugar sobre el buche
	int verMano( Carta cartita); // Verifica las cartas en la mano del bot
	int getNumeroJugador() { return numeroBot; } // Retorna el número del bot (2, 3 o 4)
	 // Agrega una carta a la mano del bot y la posiciona
	void operator+(Carta carta) override;
};