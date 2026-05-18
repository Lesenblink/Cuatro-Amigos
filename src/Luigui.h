#pragma once

#include "Jugador.h"
#include "Mesa.h"
#include <optional>
#include <algorithm> 
#include <random>  
class Carta;
class Luigui {
private:
	vector<vector<Carta>> cartas;
	random_device semilla;
	mt19937 aleatorio{ semilla() };  //intancia de un generador pseudoaleatorio

public:
	void recibirBaraja(vector<vector<Carta>> cartasdeMesa);
	void mesclarBaraja();
	vector<vector<Carta>> darCartasBarajeadas();

};