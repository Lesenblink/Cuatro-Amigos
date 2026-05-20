#include "gameplay.h"
#include "Mesa.h"
#include "Jugador.h"
#include "Carta.h"
#include "Luigui.h"
#include "Bot.h"
using namespace sf;
//Funciones privadas
void GamePlay::validarFonts() {
    font.openFromFile("../assets/arial.ttf");
    font2.openFromFile("../assets/arial.ttf");

}
void GamePlay::cargar() {    
    window.create(VideoMode(Vector2u(1400, 900)), "4 amigos");
    mesa = new Mesa(font, font2);
    luigui = new Luigui();

    luigui->recibirBaraja(mesa->darTodasLasCartas());
    luigui->mesclarBaraja();
    mesa->recibirCartasBarajeadas(*luigui);

    Carta c1 = mesa->darCarta(); c1.voltear();//poner todas volteadas al inicio
    Carta c2 = mesa->darCarta(); c2.voltear();
    Carta c3 = mesa->darCarta(); c3.voltear();
    Carta c4 = mesa->darCarta(); c4.voltear();
    Carta c5 = mesa->darCarta(); c5.voltear();
    Carta c6 = mesa->darCarta(); c6.voltear();
    Carta c7 = mesa->darCarta(); c7.voltear();
    Carta c8 = mesa->darCarta(); c8.voltear();
    Carta c9 = mesa->darCarta(); c9.voltear();

    Carta c10 = mesa->darCarta(); c10.voltear();//poner todas volteadas al inicio
    Carta c11 = mesa->darCarta(); c11.voltear();
    Carta c12 = mesa->darCarta(); c12.voltear();
    Carta c13 = mesa->darCarta(); c13.voltear();
    Carta c14 = mesa->darCarta(); c14.voltear();
    Carta c15 = mesa->darCarta(); c15.voltear();
    Carta c16 = mesa->darCarta(); c16.voltear();
    Carta c17 = mesa->darCarta(); c17.voltear();
    Carta c18 = mesa->darCarta(); c18.voltear();
    Carta c19 = mesa->darCarta(); c19.voltear();
    Carta c20 = mesa->darCarta(); c20.voltear();//poner todas volteadas al inicio
    Carta c21 = mesa->darCarta(); c21.voltear();
    Carta c22 = mesa->darCarta(); c22.voltear();
    Carta c23 = mesa->darCarta(); c23.voltear();
    Carta c24 = mesa->darCarta(); c24.voltear();
    Carta c25 = mesa->darCarta(); c25.voltear();
    Carta c26 = mesa->darCarta(); c26.voltear();
    Carta c27 = mesa->darCarta(); c27.voltear();
    Carta c28 = mesa->darCarta(); c28.voltear();
    Carta c29 = mesa->darCarta(); c29.voltear();
    Carta c30 = mesa->darCarta(); c30.voltear();

    Carta c31 = mesa->darCarta(); c31.voltear();//poner todas volteadas al inicio
    Carta c32 = mesa->darCarta(); c32.voltear();
    Carta c33 = mesa->darCarta(); c33.voltear();
    Carta c34 = mesa->darCarta(); c34.voltear();
    Carta c35 = mesa->darCarta(); c35.voltear();
    Carta c36 = mesa->darCarta(); c36.voltear();

	IA.push_back(new Bot(c10, c11, c12, c13, c14, c15, c16, c17, c18,2));
    IA.push_back(new Bot(c19, c20, c21, c22, c23, c24, c25, c26, c27, 3));
    IA.push_back(new Bot(c28, c29, c30, c31, c32, c33, c34, c35, c36, 4));
    jugador1 = new Jugador(c1, c2, c3, c4, c5, c6, c7, c8, c9);
    Carta inicial = mesa->darCarta();//inicializar variable para voltear la primera carta de el buche (las que se sueltan)
    inicial.voltear();
    mesa->llenarBuche(inicial);

    //musica de fondo
    if (musica.openFromFile("../assets/musica.mp3")) {
        musica.setLooping(true);  // Se repite en loop
        musica.setVolume(50.f);   // Volumen del 0 al 100
        musica.play();
    }
}

GamePlay::GamePlay() {
    click = false;
    validarFonts();
	turno = 1;
    cargar();
}

/*----------------------------------------Lógica del Jugador  -----------------------------------------------------------*/
void GamePlay::hitboxMano() {

    Vector2f temporalMouse =
        window.mapPixelToCoords(Mouse::getPosition(window));

    estaLevantada = false;

    for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) {

        jugador1->getCarta(i).setPosition(Vector2f(700.f - i * 50.f, 700.f));



        if (!estaLevantada && jugador1->getCarta(i).getGlobalBounds().contains(temporalMouse))
        {
            jugador1->getCarta(i).setPosition(Vector2f(700.f - i * 50.f, 650.f));
            jugador1->getCarta(i).setHitBox(true);
            estaLevantada = true;
            jugador1->getCarta(i).setHitBox(true);
        }
        else {

            jugador1->getCarta(i).setPosition(Vector2f(700.f - i * 50.f, 700.f));
            jugador1->getCarta(i).setHitBox(false);
        }
    }
}

void GamePlay::eventos() {   // Aquí manejamos la función de los eventos
    while (const auto event = window.pollEvent()) {
        if (event->is<Event::Closed>())
            window.close();
        if (auto mouseEvent = event->getIf<Event::MouseButtonPressed>()) {  // Si el usuario presiona el botón izquierdo del mouse
            if (mouseEvent->button == Mouse::Button::Left) {

                mousePos = window.mapPixelToCoords(mouseEvent->position);
                click = true;

            }
        }
    }
}
void GamePlay::comerCarta() {

    // ¿El clic fue dentro de la carta (posicion o posiciones)?
    if (mesa->tamanoCartasTotales() > 0 && mesa->getCarta().getGlobalBounds().contains(mousePos) && jugador1->numeroCartas() < 3 ) {  //Aquí es donde sucede la mágia para comer cartas
       
            Carta nueva = mesa->darCarta();
            nueva.voltear();
            (*jugador1) + nueva;
            click = false;
           
		 // Cambia el turno al siguiente jugador (en este caso, solo hay un jugador, pero se puede expandir para más jugadores)
    }
}
void GamePlay::comerCartaBuche() {
    if (mesa->tamanoDelBuche() > 0 && mesa->getBuche().getGlobalBounds().contains(mousePos)) { //En si no se porque no agarra todas las cartas del buche de una. 
        cout << mesa->tamanoDelBuche() << endl;
        while (mesa->tamanoDelBuche() > 0) {  //Un while mientras haya cartas en el buche entonces agarrar  para agarrar las cartas
            cout << "Sacando carta\n";
            Carta delBuche = mesa->darCartaDelBuche();
            delBuche.voltear();
            (*jugador1) + delBuche;
        }
        click = false;
        turno = 2;
    }
}
void GamePlay::dejarCartas() {

    for (int x = 0; x < jugador1->numeroCartas(); x++) {   //Aquí con este for ayuda a dejar las cartas.
        if (jugador1->getCarta(x).getGlobalBounds().contains(mousePos) && jugador1->getCartaHitBox(x) && turno == 1) {   //Si el jugador hizo click entonces...

            //Mecanica para el número 10
            if ((mesa->tamanoDelBuche() == 0 || jugador1->getCarta(x).getValor() >= mesa->getBuche().getValor() || jugador1->getCarta(x).getValor() == 10 || jugador1->getCarta(x).getValor() == 2)) {
                if (jugador1->getCarta(x).getValor() == 10) { //Si la carta es un 10, se limpia el buche
                    mesa->llenarBuche(jugador1->QuitarCarta(x));
                    mesa->limpiarBuche();  // La mecanica es eliminar todo el buhce que hay con un 10 puesto
                    click = false;
                    turno = 2;
                }
                else if (jugador1->getCarta(x).getValor() == 2)
                {
                    mesa->llenarBuche(jugador1->QuitarCarta(x));
                    click = false;
					turno = 1;  //Esto hace que el poder del 2, le da otra posibilidad de tirar otra carta
                }
                else {
                    mesa->llenarBuche(jugador1->QuitarCarta(x)); // Mueve la carta al buche
                    click = false;
                    turno = 2;
                }

            }
        }


    }
}
void GamePlay::jugarCartasReserva() {
    if (jugador1->numeroCartas() == 0 && jugador1->numeroCartasReserva() > 0 && mesa->tamanoCartasTotales() == 0 && turno == 1) {  //Aquí le decimos al gamplay que si np hay cartas en la mano principal entonces pasar a la otra regla del gameplay
        for (int y = 0; y < jugador1->numeroCartasReserva(); y++) { //For para las cartas de la mano reserva
            if (jugador1->getCartaReserva(y).getGlobalBounds().contains(mousePos)) {  //Si el jugador hizo click entonces...

                (*jugador1) + jugador1->QuitarCartaReserva(y);  //Le pasamos esas carta a la mano principal
                click = false;
                break;
            }

        }
    }//
}
void GamePlay::jugarCartasFinal() {
    if (jugador1->numeroCartas() == 0 && jugador1->numeroCartasReserva() == 0 && turno == 1) {
        for (int z = 0; z < jugador1->tamanoManoFinal(); z++) {
            if (jugador1->getCartaManoFinal(z).getGlobalBounds().contains(mousePos)) {

                Carta cartaFinal = jugador1->darCartaFinal(z);  //Creamos una copia para mas tarde voltear esa carta
                cartaFinal.voltear();                   //Volteamos esa carta
                (*jugador1) + cartaFinal;  //Le pasamos esa carta a la mano principal
                click = false;
                break;
            }
        }
    }
}
void GamePlay::limpiar4Buhce() {
    if (mesa->tamanoDelBuche() >= 4) {   //Mecanica para eliminar el buche cuando hay 4 cartas con el mismo valor
        int a = mesa->tamanoDelBuche() - 1;  //variable temporal del mismo tamaño del vector 
        int valorCarta1 = mesa->valorDeCartaBuche(a);  //Variables temporales 
        int valorCarta2 = mesa->valorDeCartaBuche(a - 1);
        int valorCarta3 = mesa->valorDeCartaBuche(a - 2);
        int valorCarta4 = mesa->valorDeCartaBuche(a - 3);
        if (valorCarta1 == valorCarta2 && valorCarta2 == valorCarta3 && valorCarta3 == valorCarta4)  //Si las 4 son iguales entonces limpiar buhce 
            mesa->limpiarBuche();
    }
}
void GamePlay::dibujar() {
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
    if (mesa->tamanoCartasTotales() > 0) {
        window.draw(mesa->getCarta());
    }
    window.display();
}

//********************************************************************  Función donde se llaman las anterios mecanicnas para el jugador ********************************************************************
void GamePlay::juego() {
    hitboxMano();
    if (!click)
        return; // Si no se hizo clic, no hacemos nada
    comerCarta();
    // ¿El clic fue dentro de la carta (posicion o posiciones)?
    comerCartaBuche();
    dejarCartas();
    jugarCartasReserva();
    jugarCartasFinal();
    limpiar4Buhce();
    mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    jugador1->separarCarta(mousePos);
    click = false;
}


/*---------------------------------------------------------------------------- Lógica para la IA ------------------------------------------------------------------------------*/
//La idea es tener una función para todas las IA, solo se necesita el parametro del objeto IA. Aquí no se necesita el mouse. Solo validar posiciones con if y hacer la acción 

void JugarManoIA(Bot* ia)//Lanza la carta si el buhce se lo permite
{}     
void GamePlay::IAcomerCarta(Bot* ia) {}  //Come las cartas si se acabo su turno y tiene menos de 3 cartas.
void GamePlay::comerBuhceIA(Bot* ia) {} // Si no pudo lanzar carta entonces comer del buche
void GamePlay::jugarMAnoIAReserva(Bot* ia) {} //SI ya no hay cartas en la mano principal y en la mano comunitaria de la mesa, entonces pasar esas cartas reservas a su mano principal
void GamePlay::jugarManoIAFinal(Bot* ia) {} //SI ya no hay cartas en la mano principal y en la mano comunitaria de la mesa y ya no tiene mano reserva, entonces pasar las cartas de la mano final a su mano principal para seguir jugando


void GamePlay::IAJugar(Bot* ia) {  //Función para llamar las las anteriores funciones y hacer el flujo de la IA
	
}
void GamePlay::ejecutarJuego() {
    void validarFonts();
    void cargar();
    while (window.isOpen()) {
        eventos();
        dibujar();
        juego();
    }
	delete mesa;  //Eliminamos los objetos creados con new para liberar memoria
    delete jugador1;
    delete luigui;
    for (int i = 0; i < IA.size(); i++)
    {
        delete IA[i];
    }
    IA.clear();


}



