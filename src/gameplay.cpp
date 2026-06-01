#include "gameplay.h"
#include "Carta.h"
#include "Jugador.h"
#include "Bot.h"
#include "Mesa.h"
#include "Luigui.h"
using namespace sf;
using namespace std;
//Funciones privadas
void GamePlay::validarFonts() {
    font.openFromFile("../assets/arial.ttf");
    font2.openFromFile("../assets/arial.ttf");

}
void GamePlay::cargar() {    
    window.create(VideoMode(Vector2u(1800, 1050)), "4 amigos", sf::Style::Titlebar | sf::Style::Close); //tamaño de la ventana y quitar el resize
    mesa = new Mesa(font, font2);
    luigui = new Luigui();
    
    //sprite de luigi
    luigiTex.loadFromFile("../assets/Luigi.png");
    luigiIcono.emplace(luigiTex);
    luigiIcono->setPosition(sf::Vector2f(550.f, 320.f)); //ajustar pocisión
    luigiIcono->setScale(sf::Vector2f(0.7f, 0.7f)); //ajustar tamaño


///////////////////////////////////////////////////////////////////////////////////////
//SPRITES DE LOS PERSONAJES JUGABLES

    string archivos[6] = {
    "../assets/Leon.png",
    "../assets/Peashooter.png",
    "../assets/Kenny.png",
    "../assets/Sans.png",
    "../assets/Otaku.png",
    "../assets/Employee.png"
    };

    float tamanoBots = 0.4f;
    
    vector<int> rivales;
    for (int i = 0; i < 6; i++)
        if (i != personajeElegido) rivales.push_back(i);

    for (int i = 0; i < 6; i++) {
        iconosTex[i].loadFromFile(archivos[i]);
        iconos[i].emplace(iconosTex[i]);
    }

    iconos[personajeElegido]->setScale(Vector2f(0.6f, 0.6f));
    iconos[personajeElegido]->setPosition(Vector2f(1150.f, 570.f));

    iconos[rivales[0]]->setScale(Vector2f(tamanoBots, tamanoBots));
    iconos[rivales[0]]->setPosition(Vector2f(260.f, 250.f));
    iconos[rivales[1]]->setScale(Vector2f(tamanoBots, tamanoBots));
    iconos[rivales[1]]->setPosition(Vector2f(260, 760.f));
    iconos[rivales[2]]->setScale(Vector2f(tamanoBots, tamanoBots));
    iconos[rivales[2]]->setPosition(Vector2f(1360.f, 110.f));

///////////////////////////////////////////////////////////////////////////////////////

    luigui->recibirBaraja(mesa->darTodasLasCartas());
    luigui->mesclarBaraja();
    mesa->recibirCartasBarajeadas(*luigui);

    vector <Carta> cartasTotales;
	for (int i = 0; i < 9; i++) {
		cartasTotales.push_back(mesa->darCarta());
	}
    jugador1 = new Jugador(cartasTotales);

	cartasTotales.clear();
    for (int i = 0; i < 9; i++) {
        cartasTotales.push_back(mesa->darCarta());
    }
   
    IA.push_back(new Bot(cartasTotales, 2));

    cartasTotales.clear();
    for (int i = 0; i < 9; i++) {
        cartasTotales.push_back(mesa->darCarta());
    }
    IA.push_back(new Bot(cartasTotales, 3));

    cartasTotales.clear();
    for (int i = 0; i < 9; i++) {
        cartasTotales.push_back(mesa->darCarta());
    }
    IA.push_back(new Bot(cartasTotales, 4));
    cartasTotales.clear();
    Carta inicial = mesa->darCarta();//inicializar variable para voltear la primera carta de el buche (las que se sueltan)
    inicial.voltear();
    mesa->llenarBuche(inicial);

    //musica de fondo
    if (musica.openFromFile("../assets/musica.mp3")) {
        musica.setLooping(true);  // Se repite en loop
        musica.setVolume(50.f);   // Volumen del 0 al 100
        musica.play();
    }
   
    if (!bufferCarta.loadFromFile("../assets/cadrSound.wav")) {
        cout << "Error cargando sonido" << endl;
    }

    sonidoCarta.emplace(bufferCarta);
    sonidoCarta->setVolume(80.f);

    if (!bufferComer.loadFromFile("../assets/soudBaraja.wav")) {
        cout << "Error cargando sonido comer" << endl;
    }

    sonidoComer.emplace(bufferComer);
    sonidoComer->setVolume(100.f);

    if (!bufferPerdiste.loadFromFile("../assets/perdiste.wav")) {
        cout << "Error cargando sonido comer" << endl;
    }

    sonidoPerder.emplace(bufferPerdiste);
    sonidoPerder->setVolume(100.f);

    if (!bufferVictoria.loadFromFile("../assets/victoria.wav")) {
        cout << "Error cargando sonido comer" << endl;
    }

    sonidoVictoria.emplace(bufferVictoria);
    sonidoVictoria->setVolume(100.f);
}

GamePlay::GamePlay() : GamePlay(0) {}

// Constructor que recibe el personaje seleccionado
GamePlay::GamePlay(int personaje) {
    personajeElegido = personaje;
    click = false;
    validarFonts();
    turno = 1;
    cargar();
    numeroCartasIguales = 0;
    valorCarta = 0;
    indice1 = -1;
    indice2 = -1;
    indice3 = -1;
    indice4 = -1;
    clicDerecho = false;
}
void GamePlay::lanzarCarta(){
    if (sonidoCarta)
        sonidoCarta->play();
}
void GamePlay::agarrarCartas() {
    if (sonidoComer)
    sonidoComer->play();
}
void GamePlay::perder() {
    if (sonidoPerder)
        sonidoPerder->play();
    seacabajuego(false); // Mostrar pantalla de derrota
}

void GamePlay::victoria() {
    if (sonidoVictoria)
        sonidoVictoria->play();
    seacabajuego(true); // Mostrar pantalla de victoria

}

void GamePlay::seacabajuego(bool quienGano) {

    RenderWindow window(VideoMode({ 1000, 800 }), "Resultado");

    // fondo
    RectangleShape fondo;
    fondo.setSize(Vector2f(1000.f, 800.f));
    fondo.setPosition(Vector2f(0.f, 0.f));
    fondo.setFillColor(Color::Black);

    //texto
    sf::Font fuente;
    fuente.openFromFile("../assets/arial.ttf");

    sf::Text texto(fuente);
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::White);
    texto.setPosition({ 350.f, 400.f });

    if (quienGano == false)
    {
        texto.setString("Perdiste! Haz click para cerrar el juego.");
    }
    else {
        texto.setString("Ganaste! Haz click para cerrar el juego.");
    }

    //Aqui sucede el click para cerrar el juego
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (fondo.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                {
                    window.close();

                }
            }
        }

        window.clear();
        window.draw(fondo);
        window.draw(texto);
        window.display();
    }
}

/*----------------------------------------Lógica del Jugador  -----------------------------------------------------------*/
void GamePlay::hitboxMano() {

    Vector2f temporalMouse = window.mapPixelToCoords(Mouse::getPosition(window));
    estaLevantada = false;

    for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) {

        if (!estaLevantada && jugador1->getCarta(i).getGlobalBounds().contains(temporalMouse)) {
            jugador1->getCarta(i).setPosition(Vector2f(1320.f - i * 70.f, 810.f)); // ← carta levantada
            jugador1->getCarta(i).setHitBox(true);
			valorCarta = jugador1->getCarta(i).getValor(); // Guardamos el valor de la carta levantada para usarlo en la función de dejar cartas
            indice1 = i;
            estaLevantada = true;
            //cout << valorCarta << endl;
        }
        else {
            jugador1->getCarta(i).setPosition(Vector2f(1320.f - i * 70.f, 840.f)); // ← posición normal
            jugador1->getCarta(i).setHitBox(false);
        }
    }
}

bool GamePlay::validarMultiples() {
    if ((mesa->tamanoDelBuche() > 0 && valorCarta >= mesa->getBuche().getValor()) || valorCarta == 2 || valorCarta == 10 || mesa->tamanoDelBuche() == 0){ 
        return true; }
    else { 
        indice1 = 0;
        indice2 = 0;
        indice3 = 0;
        indice4 = 0;

        return false; }
       
}
void GamePlay::cuantasCartasIgualesTienes() {
    numeroCartasIguales = 0;
    if(validarMultiples()== true){
    for (int i = jugador1->numeroCartas() - 1; i >= 0;i--) {
		//cout << "Posicion " << i << " Valor carta: " << jugador1->getCarta(i).getValor() << endl;
      //  cout <<"Vlaor del inidice  para ver que carta es: -> " << indice1 << endl;
        if (mesa->tamanoDelBuche() != 0 && jugador1->getCarta(i).getValor() == valorCarta ) {
            numeroCartasIguales++;
            
        }else if((jugador1->getCarta(i).getValor() == valorCarta)){ numeroCartasIguales++; }
    }
    if (numeroCartasIguales > 1) {
   
       // cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>Hay posible lanzamiento Multiple<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
         }
		
    else{ 
	numeroCartasIguales = 0; // Reiniciamos el contador para la próxima vez que se levante una carta
  
    }
}
    else {
        numeroCartasIguales = 0;
        valorCarta = 0;
       
       
    }
}

void GamePlay::encontrarIndices(){
    for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) {
        if (i != indice1 && valorCarta == jugador1->getCarta(i).getValor()){
            if (indice2 == -1)
                indice2 = i;
           
            else if (indice3 == -1)
                indice3 = i;

            else if (indice4 == -1)
                indice4 = i;
        }
    }
    cout << " INdice 1 " << indice1 << endl;
    cout << " INdice 2 " << indice2 << endl;
    cout << " INdice 3 " << indice3 << endl;
    cout << " INdice 4 " << indice4 << endl;
}

void GamePlay::eventos() {   // Aquí manejamos la función de los eventos
    while (const auto event = window.pollEvent()) {
        if (event->is<Event::Closed>())
            window.close();
        if (auto mouseEvent = event->getIf<Event::MouseButtonPressed>()) {

            if (mouseEvent->button == Mouse::Button::Left) {
                mousePos = window.mapPixelToCoords(mouseEvent->position);
                click = true;
            }

            if (mouseEvent->button == Mouse::Button::Right) {
                mousePos = window.mapPixelToCoords(mouseEvent->position);
                clicDerecho = true;
                
            }
        }
    }
}

// Solo permite comer si es el turno del jugador, hay cartas en el mazo,
// el jugador hizo click sobre la carta del mazo y tiene menos de 3 cartas en mano
void GamePlay::comerCarta() {
    if (turno == 1 && mesa->tamanoCartasTotales() > 0 &&
        mesa->getCarta().getGlobalBounds().contains(mousePos) &&
        jugador1->numeroCartas() < 3) {

        Carta nueva = mesa->darCarta(); // Saca la carta del mazo
        nueva.voltear(); // La voltea para que se vea el frente
        (*jugador1) + nueva; // La agrega a la mano del jugador
        lanzarCarta();
        click = false;
    }
}

// Solo permite comer el buche si es el turno del jugador y hay cartas en el buche
// Toma todas las cartas acumuladas en el buche y las pasa a la mano del jugador
void GamePlay::comerCartaBuche() {
    if (turno == 1 && mesa->tamanoDelBuche() > 0 && mesa->getBuche().getGlobalBounds().contains(mousePos)) {
        cout << "Buche pos: " << mesa->getBuche().getPos().x << ", "<< mesa->getBuche().getPos().y << endl;
        cout << "Mouse pos: " << mousePos.x << ", " << mousePos.y << endl;
        while (mesa->tamanoDelBuche() > 0) { // Mientras haya cartas en el buche
            Carta delBuche = mesa->darCartaDelBuche(); // Saca la carta del buche
            delBuche.voltear(); // La voltea para que se vea el frente
            (*jugador1) + delBuche; // La agrega a la mano del jugador
        }
        click = false;
        agarrarCartas();
        turno = 2; // Pasa el turno al siguiente jugador
    }
}

void GamePlay::dejarMultiplesCartas() {
    int eliminar = 0;
    int seElimino = jugador1->numeroCartas();
   

    if (clicDerecho == true)quitarCadenas();
    for (int x = jugador1->numeroCartas() - 1; x >= 0; x--) {   //Aquí con este for ayuda a dejar las cartas.

        if (jugador1->getCarta(x).getGlobalBounds().contains(mousePos) && jugador1->getCartaHitBox(x) && turno == 1) {   //Si el jugador hizo click entonces...
          
            if (numeroCartasIguales > 1 && jugador1->getCarta(x).getValor() == valorCarta) { //Aquí entramos a la mecanica de multiple carta si la carta clickeada cumple con la condición multi
             
                for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) {  //Quitar cadenas pasads 
                    if (jugador1->getCarta(i).getValor() != valorCarta)
                        jugador1->getCarta(i).quitarCadena();
                }
             
                    if ((mesa->tamanoDelBuche() == 0 || jugador1->getCarta(x).getValor() >= mesa->getBuche().getValor() || jugador1->getCarta(x).getValor() == 10 || jugador1->getCarta(x).getValor() == 2)) {
                        if (valorCarta== 10) { //Aquí empieza la cadena 
                           
                          if(jugador1->getCarta(x).getEncadenada()==false){  //Si la carta que cumple con la condición y no está en cadena, entonces dar turno y encdadenar
                              
                              jugador1->getCarta(x).ponerCadena();
                              click = false;
                              turno = 1;

                          }else if(jugador1->getCarta(x).getEncadenada() == true && jugador1->getCarta(x).getValor()==valorCarta){  // Si está encadenada entonces lanzar todas las cartas encadenadas
                              vector<int> indicesAeliminar;
                              for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) {

                                  if (jugador1->getCarta(i).getEncadenada())
                                  {
                                      jugador1->getCarta(i).quitarCadena();
                                      indicesAeliminar.push_back(i);
                                  }

                              }
                              sort(indicesAeliminar.rbegin(), indicesAeliminar.rend());//Aqui funcion de la libreria algoritmo de mayor a menor
                              for (int z : indicesAeliminar)
                                  mesa->llenarBuche(jugador1->QuitarCarta(z)); 
                                 click = false;
                                 lanzarCarta();
                              turno = 2;
                              return;
                          }
                        
                           
                        }
                        else if (valorCarta== 2) {
                            if (jugador1->getCarta(x).getEncadenada() == false) {
                                jugador1->getCarta(x).ponerCadena();
                                click = false;
                                turno = 1;

                            }
                            else if (jugador1->getCarta(x).getEncadenada() == true && jugador1->getCarta(x).getValor() == 2 && valorCarta == 2) {
                                vector<int> indicesAeliminar;
                                for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) {

                                    if (jugador1->getCarta(i).getEncadenada())
                                    {
                                        jugador1->getCarta(i).quitarCadena();
                                        indicesAeliminar.push_back(i);
                                    }

                                }
                                sort(indicesAeliminar.rbegin(), indicesAeliminar.rend()); //Aqui funcion de la libreria algoritmo de mayor a menor
                                for (int z : indicesAeliminar)
                                    mesa->llenarBuche(jugador1->QuitarCarta(z));
                                click = false;
                                lanzarCarta();
                                turno = 1;
                                return;
                            }

                        } 
                        else {
                            if (jugador1->getCarta(x).getEncadenada() == false){
                            
                                jugador1->getCarta(x).ponerCadena();            //dar turno si la carta no está encadenada 
                                click = false;
                                turno = 1;
                            
                            }
                            else if (jugador1->getCarta(x).getEncadenada() == true) {  //Si la carta no es morada entonces ponerla morada 
                                vector<int> indicesAeliminar;
                                for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) {

                                    if (jugador1->getCarta(i).getEncadenada())
                                    {
                                        jugador1->getCarta(i).quitarCadena();
                                        indicesAeliminar.push_back(i);
                                    }

                                }
                                sort(indicesAeliminar.rbegin(), indicesAeliminar.rend());  //Aqui funcion de la libreria algoritmo de mayor a menor
                                for (int z : indicesAeliminar)
                                    mesa->llenarBuche(jugador1->QuitarCarta(z));
                                click = false;
                                lanzarCarta();
                                turno = 2;
                                return;
                            }
                            else {
                                for(int i=jugador1->numeroCartas()-1; i>=0; i-- ){ jugador1->getCarta(i).quitarCadena(); } //Quitar cadena a las demas cartas 
                                turno = 2;
                                click = false;
                                return;
                            }
                           
                            
                        }
                      
                    }
                }
            }
          
        

    }
 
}
void GamePlay::quitarCadenas() {
    // Si el jugador presiona click derecho entonces quitar cadenas

    if (clicDerecho) {

        for (int j = jugador1->numeroCartas() - 1; j >= 0; j--) {

          
                jugador1->getCarta(j).quitarCadena();
        }

        clicDerecho = false;
    }
}
void GamePlay::dejarCartas() {
    for (int i = jugador1->numeroCartas() - 1; i >= 0; i--) { jugador1->getCarta(i).quitarCadena(); }  //Quitar cartas encadenadas si se lanza una que no cumple con el multiple cartas 
    for (int x = jugador1->numeroCartas()-1; x >=0; x--) {   //Aquí con este for ayuda a dejar las cartas.
  

    
        Vector2 posicion = Vector2f(1320.f, 770.f);
        if (jugador1->getCarta(x).getGlobalBounds().contains(mousePos) && jugador1->getCartaHitBox(x) && turno == 1) {   //Si el jugador hizo click entonces...
           
            //Mecanica para el número 10
          
                if ((mesa->tamanoDelBuche() == 0 || jugador1->getCarta(x).getValor() >= mesa->getBuche().getValor() || jugador1->getCarta(x).getValor() == 10 || jugador1->getCarta(x).getValor() == 2)) {
                    if (jugador1->getCarta(x).getValor() == 10) { //Si la carta es un 10, se limpia el buche
                        mesa->llenarBuche(jugador1->QuitarCarta(x));
                        mesa->limpiarBuche();  // La mecanica es eliminar todo el buhce que hay con un 10 puesto
                        lanzarCarta();
                        click = false;
                        turno = 2;
                    }
                    else if (jugador1->getCarta(x).getValor() == 2)
                    {
                        mesa->llenarBuche(jugador1->QuitarCarta(x));
                        lanzarCarta();
                        click = false;
                        turno = 1;  //Esto hace que el poder del 2, le da otra posibilidad de tirar otra carta
                    }
                    else {
                        mesa->llenarBuche(jugador1->QuitarCarta(x)); // Mueve la carta al buche
                        click = false;
                        lanzarCarta();
                     
                        turno = 2;

                    }
                   
                    return;
                }
            
           
        }


    }
}
void GamePlay::jugarCartasReserva() {
    if (jugador1->numeroCartas() == 0 && jugador1->numeroCartas("reserva") > 0 && mesa->tamanoCartasTotales() == 0 && turno == 1) {  //Aquí le decimos al gamplay que si np hay cartas en la mano principal entonces pasar a la otra regla del gameplay
        for (int y = 0; y < jugador1->numeroCartas("reserva"); y++) { //For para las cartas de la mano reserva
            if (jugador1->getCarta(y, "reserva").getGlobalBounds().contains(mousePos)) {  //Si el jugador hizo click entonces...

                (*jugador1) + jugador1->QuitarCarta(y, "reserva");  //Le pasamos esas carta a la mano principal
                click = false;
                lanzarCarta();
                break;
            }

        }
    }//
}
void GamePlay::jugarCartasFinal() {
    if (jugador1->numeroCartas() == 0 && jugador1->numeroCartas("reserva") == 0 && turno == 1) {
        for (int z = 0; z < jugador1->numeroCartas("final"); z++) {
            if (jugador1->getCarta(z, "final").getGlobalBounds().contains(mousePos)) {

                Carta cartaFinal = jugador1->QuitarCarta(z, "final");  //Creamos una copia para mas tarde voltear esa carta
                cartaFinal.voltear();                   //Volteamos esa carta
                (*jugador1) + cartaFinal;  //Le pasamos esa carta a la mano principal
                click = false;
                lanzarCarta();
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

        agarrarCartas();
    }
}
void GamePlay::dibujar() {
    window.clear();
    window.draw(mesa->getBorde());
    window.draw(*mesa);

    //Sprite de Luigi
    if (luigiIcono) window.draw(*luigiIcono);

    //Sprite de jugadores
    vector<int> rivales;
    for (int i = 0; i < 4; i++)
        if (i != personajeElegido) rivales.push_back(i);

    if (iconos[personajeElegido]) window.draw(*iconos[personajeElegido]);
    if (iconos[rivales[0]])       window.draw(*iconos[rivales[0]]);
    if (iconos[rivales[1]])       window.draw(*iconos[rivales[1]]);
    if (iconos[rivales[2]])       window.draw(*iconos[rivales[2]]);

    // Jugador principal
    for (int i = 0; i < jugador1->numeroCartas(); i++)
        window.draw(jugador1->getCarta(i));
    for (int i = 0; i < jugador1->numeroCartas("final"); i++)
        window.draw(jugador1->getCarta(i, "final"));
    for (int i = 0; i < jugador1->numeroCartas("reserva"); i++)
        window.draw(jugador1->getCarta(i, "reserva"));

    //dibujar las cartas de la ia
    for (int b = 0; b < IA.size(); b++) {
        for (int i = 0; i < IA[b]->numeroCartas(); i++)
            window.draw(IA[b]->getCarta(i));
        for (int i = 0; i < IA[b]->numeroCartas("final"); i++)
            window.draw(IA[b]->getCarta(i, "final"));
        for (int i = 0; i < IA[b]->numeroCartas("reserva"); i++)
            window.draw(IA[b]->getCarta(i, "reserva"));
        
    }
    
    //buche y maso
    for (int i = 0; i < mesa->tamanoDelBuche(); i++)
        window.draw(mesa->getCartaBuche(i));
    if (mesa->tamanoCartasTotales() > 0)
        window.draw(mesa->getCarta());

    window.display();
}

//********************************************************************  Función donde se llaman las anterios mecanicnas para el jugador ********************************************************************
void GamePlay::juego() {
    // Reponer mano hasta 3 cartas si hay cartas en el mazo
    while (jugador1->numeroCartas() < 3 && mesa->tamanoCartasTotales() > 0) {
        Carta nueva = mesa->darCarta();
        nueva.voltear();
        (*jugador1) + nueva;
    }
    eventos();
    hitboxMano(); // Detecta el mouse sobre las cartas y las levanta
    cuantasCartasIgualesTienes();
    encontrarIndices();
    if (clicDerecho == true) quitarCadenas();
    if (!click) return; // Si no hubo click, no hacer nada
    if (clicDerecho == true) quitarCadenas();
    if (numeroCartasIguales > 1)
    {
        if (clicDerecho == true) quitarCadenas();
        dejarMultiplesCartas();
    }
    else
    {
        if (clicDerecho == true) quitarCadenas();
        dejarCartas();
    }
        
        comerCarta(); // Intentar comer carta del mazo
        comerCartaBuche(); // Intentar comer cartas del buche
      

    jugarCartasReserva(); // Intentar pasar cartas de reserva a mano principal
    jugarCartasFinal(); // Intentar pasar cartas de mano final a mano principal
    limpiar4Buhce(); // Verificar si se limpia el buche por 4 iguales
    mousePos = window.mapPixelToCoords(Mouse::getPosition(window)); // Actualizar posicion del mouse
    jugador1->separarCarta(mousePos); // Separar carta bajo el mouse
    click = false; // Resetear el click
    doubleClick = false;
}


/*---------------------------------------------------------------------------- Lógica para la IA ------------------------------------------------------------------------------*/
//La idea es tener una función para todas las IA, solo se necesita el parametro del objeto IA. Aquí no se necesita el mouse. Solo validar posiciones con if y hacer la acción 

bool GamePlay::puedeJugarCarta(Bot* ia, int indice) {
    int valor = ia->getCarta(indice).getValor(); // Verifica si la carta en el indice dado es válida para tirar al buche
    if (valor == 2 || valor == 10) return true; // Comodines siempre válidos
    if (mesa->tamanoDelBuche() == 0) return true; // Buche vacío, cualquier carta es válida
    return valor >= mesa->getBuche().getValor(); // Debe ser mayor o igual al tope
}

// Busca la mejor carta a jugar usando estrategia media
// Prefiere cartas normales sobre comodines para guardarlos
// Entre cartas normales, elige la más baja para conservar las altas
// Retorna -1 si no tiene ninguna carta válida para jugar
int GamePlay::mejorCartaIA(Bot* ia) {
    int mejorIndice = -1;
    int mejorValor = -1;

    for (int i = 0; i < ia->numeroCartas(); i++) {
        int valor = ia->getCarta(i).getValor();
        if (!puedeJugarCarta(ia, i)) continue; // Saltar cartas no válidas

        bool esComodin = (valor == 2 || valor == 10);

        if (mejorIndice == -1) {
            // Primera carta válida encontrada
            mejorIndice = i;
            mejorValor = valor;
        }
        else if (!esComodin && (mejorValor == 2 || mejorValor == 10)) {
            // Prefiere carta normal sobre comodin
            mejorIndice = i;
            mejorValor = valor;
        }
        else if (!esComodin && valor < mejorValor) {
            // Entre cartas normales, prefiere la más baja
            mejorIndice = i;
            mejorValor = valor;
        }
    }
    return mejorIndice;
}
void GamePlay::verificarMulitplesCartas(Bot* ia) {
    cartasMultipleIA = 0;  //reiniciamos el contador

    int indice = mejorCartaIA(ia);  //Ponemos una variable donde se ubica la mejor carta 

    if (indice == -1) return; //Si es indice no es valido entonces ahí muere 

    guardarCartaIA = ia->getCarta(indice).getValor(); //Guardamos el valor de las cartas para compararlo más tarde 

    for (int i = ia->numeroCartas() - 1; i >= 0; i--) {

        if (ia->getCarta(i).getValor() == guardarCartaIA)
            cartasMultipleIA++;  //Sabremos cuantas cartas puede lanzar la IA
    }
    cout << "Puede la IA: " << ia->getNumeroJugador() << " Lanzar este numero de cartas: " << cartasMultipleIA << endl;
}
void GamePlay::JugarManoIA(Bot* ia) {
    int indice = mejorCartaIA(ia);
    if (indice == -1) return; // No tiene carta válida

    int valor = ia->getCarta(indice).getValor();

    if (valor == 10) {
        mesa->llenarBuche(ia->QuitarCarta(indice));
        mesa->limpiarBuche(); // El 10 limpia todo el buche
        lanzarCarta();
        turno = (ia->getNumeroJugador() % 4) + 1;
    }
    else if (valor == 2) {
        
        mesa->llenarBuche(ia->QuitarCarta(indice));
        lanzarCarta();
        // turno extra: no cambia turno
    }
    else {
        mesa->llenarBuche(ia->QuitarCarta(indice));
        lanzarCarta();
        turno = (ia->getNumeroJugador() % 4) + 1;
    }

    limpiar4Buhce(); // Verificar si se limpian 4 iguales
}
void GamePlay::lanzarMultiple(Bot* ia) { //Reutilizamos la función anterior
    int indice = mejorCartaIA(ia);  
    if (indice == -1) return; // No tiene carta válida

    int valor = ia->getCarta(indice).getValor();  
    if(cartasMultipleIA >1){ //Aquí está la diferencia,  si hay más de dos cartas iguales entonces 
        for (int y = ia->numeroCartas() - 1;y >= 0; y-- ) {
           //Rocorremos toda la mano
            if (guardarCartaIA == ia->getCarta(y).getValor()) {  //Si la carta tiene el mismo valor entonces 
                mesa->llenarBuche(ia->QuitarCarta(y));  //Lanzar
        }
        
        } 
        lanzarCarta();
    
    }
    if (valor == 10)
        mesa->limpiarBuche();
    if (valor != 2)
    turno = (ia->getNumeroJugador() % 4) + 1;  //Aqui cambiamos de turno 
    limpiar4Buhce(); // Verificar si se limpian 4 iguales
}
// La IA toma una carta del mazo si tiene menos de 3 en mano
// La carta aparece de espaldas para que el jugador no la vea
void GamePlay::IAcomerCarta(Bot* ia) {
    if (mesa->tamanoCartasTotales() > 0 && ia->numeroCartas() < 3) {
        Carta nueva = mesa->darCarta();
        nueva.voltear();  // que aparezca de espaldas
        (*ia) + nueva;
        lanzarCarta();
    }
   
}

// La IA toma todas las cartas del buche cuando no puede jugar
// el turno pasa al siguiente jugador
void GamePlay::comerBuhceIA(Bot* ia) {
    while (mesa->tamanoDelBuche() > 0) {
        Carta delBuche = mesa->darCartaDelBuche();
        delBuche.voltear();  // que aparezca de espaldas
        (*ia) + delBuche;
    }
    agarrarCartas();
    turno = (ia->getNumeroJugador() % 4) + 1;
}

// Pasa una carta de la mano reserva a la mano principal
// Solo cuando la mano principal está vacía y el mazo se acabó
void GamePlay::jugarMAnoIAReserva(Bot* ia) {
    if (ia->numeroCartas() == 0 && ia->numeroCartas("reserva") > 0 && mesa->tamanoCartasTotales() == 0) {
        Carta reserva = ia->QuitarCarta(0, "reserva");
        (*ia) + reserva;
        lanzarCarta();
    }
   
}

// Pasa una carta de la mano final a la mano principal
// Solo cuando no tiene cartas en mano principal ni reserva
void GamePlay::jugarManoIAFinal(Bot* ia) {
    if (ia->numeroCartas() == 0 && ia->numeroCartas("reserva") == 0 && ia->numeroCartas("final") > 0) { 
        Carta cartaFinal = ia->QuitarCarta(0, "final");
		cartaFinal.voltear(); // Voltear la carta para el frrente
        (*ia) + cartaFinal;
        lanzarCarta();
    }
}

// Función principal del turno de la IA, controla el flujo completo
// Verifica si es su turno y espera 1.5 segundos entre jugadas
void GamePlay::IAJugar(Bot* ia) {
    if (turno != ia->getNumeroJugador()) return;
    if (relojIA.getElapsedTime().asSeconds() < 1.5f) return;
    relojIA.restart();

    // Si no tiene ninguna carta en ninguna mano, ganó
    if (ia->numeroCartas() == 0 && ia->numeroCartas("reserva") == 0 && ia->numeroCartas("final") == 0) {
        cout << "Bot " << ia->getNumeroJugador() << " gano!" << endl;
        turno = (ia->getNumeroJugador() % 4) + 1;
        return;
    }

    // Reponer mano hasta 3 cartas si hay cartas en el mazo
    while (ia->numeroCartas() < 3 && mesa->tamanoCartasTotales() > 0) {
        Carta nueva = mesa->darCarta();
        nueva.voltear();
        (*ia) + nueva;
    }

    // Si no tiene cartas en mano principal, pasar de reserva o final
    if (ia->numeroCartas() == 0) {
            jugarMAnoIAReserva(ia);
            jugarManoIAFinal(ia);
            return;
      
    }

    // Si tiene carta válida la tira, si no se come el buche
    int indice = mejorCartaIA(ia);
    verificarMulitplesCartas(ia);
    if (indice != -1) {
        if (cartasMultipleIA > 1) {
            lanzarMultiple(ia);
           
        }else{ JugarManoIA(ia); }
      
    }
    else {
        comerBuhceIA(ia);
        IAcomerCarta(ia);
    }
}

// Verifica si algún jugador se quedó sin cartas en todas sus manos
// El jugador principal también necesita que el mazo esté vacío para ganar
// Retorna true si hay un ganador y cierra el juego después de 3 segundos
bool GamePlay::verificarGanador() {
    // Verificar jugador principal
    if (jugador1->numeroCartas() == 0 &&
        jugador1->numeroCartas("reserva") == 0 &&
        jugador1->numeroCartas("final" ) == 0 &&
        mesa->tamanoCartasTotales() == 0) {
        cout << "Jugador 1 gano!" << endl;
        musica.stop();
        victoria();
        return true;
    }

    // Verificar bots
    for (int i = 0; i < IA.size(); i++) {
        if (IA[i]->numeroCartas() == 0 &&
            IA[i]->numeroCartas("reserva") == 0 &&
            IA[i]->numeroCartas("final") == 0) {
            cout << "Bot " << IA[i]->getNumeroJugador() << " gano!" << endl;
            musica.stop();
            perder();
            return true;
        }
    }
    return false;
}

// Alterna entre el turno del jugador y los turnos de las IAs
// Al detectar un ganador espera 3 segundos y cierra la ventana
void GamePlay::ejecutarJuego() {
    
    while (window.isOpen()) {
        eventos();
        dibujar();

        if (verificarGanador()) {
            window.close();
            break;
        }

        if (turno == 1) {
            juego();
        }
        else {
            for (int i = 0; i < IA.size(); i++) {
                if (IA[i]->getNumeroJugador() == turno) {
                    IAJugar(IA[i]);
                    break;
                }
            }
        }
    }
    delete mesa;
    delete jugador1;
    delete luigui;
	
	cout << " XD XD  XD >>> Retornar numero de cartas iguales----" << numeroCartasIguales << endl;
    for (int i = 0; i < IA.size(); i++)
        delete IA[i];
    IA.clear();
}


