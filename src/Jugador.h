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
<<<<<<< HEAD
	int tamanoManoFinal(); //Función para saber cuantas cartas tiene la mano final
	Carta& gettamanoManoFinal(int  posicion);  //Función para obtener una carta de la mano final
	Carta darCartaFinal(int x);     //Damos la carta de la mano final
<<<<<<< HEAD

=======
	void separarCarta(Vector2f mousePos);
	bool getCartaHitBox(int x); //Función para obtener el valor de la hitbox
>>>>>>> 0cb4faacb84d8c46680c17aef0860b37bf9a8e78
=======
	 //Función para saber cuantas cartas tiene la mano final 

	void separarCarta(Vector2f mousePos);
	bool getCartaHitBox(int x);
>>>>>>> 70f5719d16e1a00a49b78eeaf07915e22b276042
};