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
-Faltan el sistema de turnos
-Tambien falta la IA
-Falta el menu
-Tarda en arrancar (creo que se puede optimizar mejor)
-Falta la última meécanica, lanzar cartas encadenadas


*/