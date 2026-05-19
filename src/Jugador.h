#pragma once
#include "Carta.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Jugador {
private:
	vector <Carta>  mano;         //Vector para la mano del jugador del inicio
	vector<Carta> manoReserva;    //Venctor para la mano de reserva 
	vector<Carta> manoFinal;      //Vector para la mano que se uitliza al final con las cartas volteadas
	int numeroJugador;
	void definirPosicionMano();  //Separamos el constructor (Los for) en funciones miembro privadas.
	void definirPosicionManoReserva();
	void definirPosicionManoFinal();

public:
	Jugador(Carta  carta1, Carta carta2, Carta carta3, Carta  carta4, Carta  carta5, Carta  carta6, Carta  carta7, Carta  carta8, Carta  carta9, int num = 1);
	void operator+(Carta carta);  //Función sobrecargada para comer 
	Carta& getCarta(int  posicion);   //Obtenemos una carta especifica
	Carta& getCartaReserva(int  posicion);
	Carta  QuitarCarta(int x);
	Carta  QuitarCartaReserva(int x);
	int numeroCartas();
	int numeroCartasReserva();
	Carta& getCartaManoFinal(int  posicion); //Función para obtener una carta de la mano final
	Carta darCartaDeReserva(int x);
	void voltearCarta(int x);
	int tamanoManoFinal(); //Función para saber cuantas cartas tiene la mano final
	Carta& gettamanoManoFinal(int  posicion);  //Función para obtener una carta de la mano final
	Carta darCartaFinal(int x);     //Damos la carta de la mano final

};