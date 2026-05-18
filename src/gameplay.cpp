#include "gameplay.h"
#include "Mesa.h"
#include "Jugador.h"
#include "Carta.h"
#include "Luigui.h"
using namespace sf;
//Funciones privadas
void GamePlay::validarFonts() {
    font.openFromFile("C:\\Windows\\Fonts\\arial.ttf");
    font2.openFromFile("C:\\Windows\\Fonts\\arial.ttf");

}
void GamePlay::cargar() {
	
	window.create(VideoMode(Vector2u(1400, 900)), "4 amigos");
	mesa = new Mesa(font, font2);
	luigui = new Luigui();

    luigui->recibirBaraja(mesa->darTodasLasCartas());
    luigui->mesclarBaraja();
    mesa->recibirCartasBarajeadas(*luigui);

    jugador1 = new Jugador(mesa->darCarta(), mesa->darCarta(), mesa->darCarta(), mesa->darCarta(), mesa->darCarta(), mesa->darCarta(), mesa->darCarta(), mesa->darCarta(), mesa->darCarta());
    mesa->llenarBuche(mesa->darCarta());
}

GamePlay::GamePlay() {
    validarFonts();
    cargar();
}

void GamePlay::juego(){
    while (const auto event = window.pollEvent()) {
        if (event->is<Event::Closed>())
            window.close();

        // Si el usuario presiona el botón izquierdo del mouse
        if (auto mouseEvent = event->getIf<Event::MouseButtonPressed>()) {
            if (mouseEvent->button == Mouse::Button::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                // ¿El clic fue dentro de la carta (posicion o posiciones)?
                if (mesa->getCarta().getGlobalBounds().contains(mousePos) && jugador1->numeroCartas() < 3) {  //Aquí es donde sucede la mágia para comer cartas
                    (*jugador1)+ mesa->darCarta();

                }
                else   if (mesa->tamanoDelBuche() > 0 && mesa->getBuche().getGlobalBounds().contains(mousePos)) { //En si no se porque no agarra todas las cartas del buche de una. 
                    while (mesa->tamanoDelBuche() > 0) {  //Un while mientras haya cartas en el buche entonces agarrar  para agarrar las cartas
                        (*jugador1) + mesa->darCartaDelBuche(); // Aquí se come la carta del buche                      

                    }

                }
                else {
                    for (int x = 0; x < jugador1->numeroCartas(); x++) {   //Aquí con este for ayuda a dejar las cartas.
                        if (jugador1->getCarta(x).getGlobalBounds().contains(mousePos)) {   //Si el jugador hizo click entonces...

                            //Mecanica para el número 10
                            if ((mesa->tamanoDelBuche() == 0 || jugador1->getCarta(x).getValor() >= mesa->getBuche().getValor() || jugador1->getCarta(x).getValor() == 10 || jugador1->getCarta(x).getValor() == 2)) {
                                if (jugador1->getCarta(x).getValor() == 10) { //Si la carta es un 10, se limpia el buche
                                    mesa->llenarBuche(jugador1->QuitarCarta(x));
                                    mesa->limpiarBuche();  // La mecanica es eliminar todo el buhce que hay con un 10 puesto
                                }
                                else if (jugador1->getCarta(x).getValor() == 2)
                                {
                                    mesa->llenarBuche(jugador1->QuitarCarta(x));
                                }
                                else {
                                    mesa->llenarBuche(jugador1->QuitarCarta(x)); // Mueve la carta al buche
                                }

                            }
                        }


                    }
                    if (jugador1->numeroCartas() == 0 && jugador1->numeroCartasReserva() > 0 && mesa->tamanoCartasTotales()==0) {  //Aquí le decimos al gamplay que si np hay cartas en la mano principal entonces pasar a la otra regla del gameplay
                        for (int y = 0; y < jugador1->numeroCartasReserva(); y++) { //For para las cartas de la mano reserva
                            if (jugador1->getCartaReserva(y).getGlobalBounds().contains(mousePos)) {  //Si el jugador hizo click entonces...

                                (*jugador1) + jugador1-> QuitarCartaReserva(y);  //Le pasamos esas carta a la mano principal
                                break;
                            }

                        }
                    }//
                    if (jugador1->numeroCartas() == 0 && jugador1->numeroCartasReserva() == 0 && mesa->tamanoDelBuche() == 0) {
                        for (int z = 0; z < jugador1->tamanoManoFinal(); z++) {
                            if (jugador1->getCartaManoFinal(z).getGlobalBounds().contains(mousePos)) {

                                Carta cartaFinal = jugador1->darCartaFinal(z);  //Creamos una copia para mas tarde voltear esa carta
                                cartaFinal.voltear();                   //Volteamos esa carta
                                (*jugador1) + cartaFinal;  //Le pasamos esa carta a la mano principal
                                break;
                            }
                        }
                    }
                    if (mesa->tamanoDelBuche() >= 4) {   //Mecanica para eliminar el buche cuando hay 4 cartas con el mismo valor
                        int a = mesa->tamanoDelBuche() - 1;  //variable temporal del mismo tamaño del vector 
                        int valorCarta1 = mesa->valorDeCartaBuche(a);  //Variables temporales 
                        int valorCarta2 = mesa->valorDeCartaBuche(a - 1);
                        int valorCarta3 = mesa->valorDeCartaBuche(a - 2);
                        int valorCarta4 = mesa->valorDeCartaBuche(a - 3);
                        if (valorCarta1 == valorCarta2 && valorCarta2 == valorCarta3 && valorCarta3 == valorCarta4)  //Si las 4 son iguales entonces limpiar buhce 
                            mesa->limpiarBuche();
                    }
                }//
            }


        }


        //Limpiamos la pantalla y redibujamos todo en su nueva posición
        window.clear();
        window.draw(mesa->getBorde()); // Dibujar el marco
        window.draw(*mesa);           // Dibujar el tapete verde

        for (int i = 0; i < jugador1->numeroCartas(); i++) {  //Dibjuar las cartas y este for se adapta al tamaño de la mano del jugador
            window.draw(jugador1->getCarta(i)); // Dibujar las cartas del jugador
        }
        for (int i = 0; i < jugador1->numeroCartasReserva(); i++) {  //Dibjuar las cartas y este for se adapta al tamaño de la mano del jugador
            window.draw(jugador1->getCartaReserva(i)); // Dibujar las cartas del jugador
        }
        for (int i = 0; i < jugador1->tamanoManoFinal(); i++) {  //Dibjuar las cartas y este for se adapta al tamaño de la mano del jugador
            window.draw(jugador1->getCartaManoFinal(i)); // Dibujar las cartas del jugador
        }
        for (int i = 0; i < mesa->tamanoDelBuche(); i++) {// Dibuja la ultima carta del buche
            window.draw(mesa->getCartaBuche(i)); // Dibujar las cartas en el buche
        }


        window.draw(mesa->getCarta());
        window.display();
    }
}
void GamePlay::ejecutarJuego() {
    void validarFonts();
    void cargar();
    while (window.isOpen()) {
        juego();
    }
    delete mesa;
    delete jugador1;
	delete luigui;
	
}

