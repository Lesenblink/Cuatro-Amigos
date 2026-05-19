#pragma once
#include "Jugador.h"
#include "Carta.h"
#include <SFML/Graphics.hpp>
class Jugador;
class Carta;

class Bot: public Jugador {
private:
	int numeroBot;
public:
	Bot(Carta  carta1, Carta carta2, Carta carta3, Carta  carta4, Carta  carta5, Carta  carta6, Carta  carta7, Carta  carta8, Carta  carta9, int num = 2);

};