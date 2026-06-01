#pragma once
#include "Carta.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Jugador {
private:
protected:
	vector <Carta>  mano;         //Vector para la mano del jugador del inicio
	vector<Carta> manoReserva;    //Venctor para la mano de reserva 
	vector<Carta> manoFinal;
	 virtual void asignarPosicion(string tipoMano = "mano");
	
	void inicializarMazo(Carta& carta, Carta& carta2, Carta& carta3, string tipoMano = "mano");//Vector para la mano que se uitliza al final con las cartas volteadas
public:
	Jugador( vector<Carta>& cartas);
	virtual void operator+(Carta carta);  //Función sobrecargada para comer 
	Carta& getCarta(int  posicion, string tipoMano = "mano");   //Obtenemos una carta especifica
	Carta  QuitarCarta(int x, string tipoMano = "mano");
	int numeroCartas(string tipoMano = "mano");

	//Función para obtener una carta de la mano final
	Carta darCartaDeReserva(int x);
	void voltearCarta(int x);
	 //Función para saber cuantas cartas tiene la mano final 

	void separarCarta(Vector2f mousePos);
	bool getCartaHitBox(int x);
};