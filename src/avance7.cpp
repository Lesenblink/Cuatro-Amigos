#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Mesa.h"
#include "Luigui.h"
#include "Carta.h"
#include "Jugador.h"
#include "gameplay.h"
using namespace sf;
using namespace std;



//motor del juego
int main() {
    // Intentamos cargar la fuente de letra de Windows
	GamePlay juego;
	juego.ejecutarJuego();
    return 0;
}

/*
COSAS OBSERVADAS:
-Falta la mecanica para encadenar cartas como en el UNO y soltaras si tiene el mismo valor 
-Según yo, no deberá haber crasheos
-No sé si la forma que lo hice esté bien pero funciona, pero, creo que hay mejoras formas de hacer bien las mecanicas .
-Falta implemntar la mecánica al lanzar un 2
- Faltan las IA y sistema de turnos, pero eso se puede hacer después de tener el gameplay completo.
Aparte de lo nuevo:
-Es momento de mover todo a librerias.
-Solo es bueno tener una sola instancia de Ligui porque como es semilla.
*/