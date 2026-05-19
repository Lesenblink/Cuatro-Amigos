#pragma once
#include "Carta.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
class Luigui;
using namespace sf;

class Mesa: public RectangleShape {
private:
    vector<vector<Carta>> cartasTotales; // Un contenedor organizado por vectores (simula una base de datos)
    vector<Carta> bucheDeCartas; // Un contenedor para las cartas que ya se han usado
    RectangleShape borde;                // El marco de madera de la mesa
	void crearMazo(const sf::Font& font, const Font& font2); //Función para crear el mazo de cartas
    void estatica();
public:
	Mesa(const sf::Font& font, const Font& font2);
	vector<vector<Carta>> darCartasTotales();
	RectangleShape& getBorde();
	vector<vector<Carta>> darTodasLasCartas();
	void recibirCartasBarajeadas(Luigui& mario);
	void llenarBuche(Carta carta);  //Mecanica de 4 amigos como el UNO, recibe las cartas del jugador y los mete en el buche
	Carta& getBuche();  //Obtemenos la carta del buche 
	int tamanoDelBuche();  //Tamaño del buche
	Carta darCartaDelBuche();  //Función para comer la carta del buche
	void  limpiarBuche();
	Carta darCarta();
	Carta& getCarta();
	int tamanoCartasTotales();
	int valorDeCartaBuche(int a);
	Carta& getCartaBuche(int i);
};