#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>
#include <algorithm> 
#include <random>  
using namespace sf;
using namespace std;
class Mesa;

// CLASE CARTA: Define cómo se ven y se comportan las cartas
class Carta : public Drawable, public Transformable {
private:
    Color color;
    string valor;
    string valor2;
    bool enJuego;
    const Font* font;
    const Font* font2;
    Text numero;
    Text numeroAbajo;// para mostrar el número 
    RectangleShape forma; // El cuerpo de la carta
	RectangleShape cartaReves; // La parte de atrás de la carta.
    RectangleShape marcoInterior; //Marco interior para el reves de la carta
    ConvexShape simbolo;  // El rombo o figura de la baraja

	// Esta función le dice a la ventana qué orden seguir para dibujar la carta. Estoy aquí redefiniendo la función draw de la clase Drawable
    virtual void draw(RenderTarget& target, RenderStates states) const override {  
       if(enJuego==true) {
            states.transform *= getTransform(); // Aplica movimiento y rotación
            target.draw(forma, states);         // 1. Dibuja el fondo
            target.draw(numero, states);            // 2. Dibuja el número arriba
            target.draw(numeroAbajo, states);        // 3. Dibuja el número arriba
            target.draw(simbolo, states);       // 4. Dibuja el símbolo
	   }
	   else if (enJuego==false) {
		   states.transform *= getTransform();  //Aplica movimiento y rotación
		   target.draw(cartaReves, states); //1. Dibuja el fondo del reverso de la carta

		   target.draw(marcoInterior, states); //2. Dibuja el marco interior del reverso de la carta
	   }
    }

public:

    // Constructor: Aquí se hace la carta
    Carta(Color color, string valor, const sf::Font* font, const Font* font2, string valor2) : enJuego(true), color(color), valor(valor), font(font), font2(font2), numero(*font, valor), numeroAbajo(*font2, valor2) {
        setPosition(Vector2f(800.f, 300.f)); // Posición inicial (se puede cambiar después)
        // Configuramos el cuerpo de la carta (rectángulo blanco con borde)
        forma.setSize(sf::Vector2f(100.f, 150.f));
        forma.setFillColor(Color::White);
        forma.setOutlineColor(sf::Color::Black);
        forma.setOutlineThickness(3.f);

		//Configuramos la parte de atrás de la carta 
        cartaReves.setSize(Vector2f(100.f, 150.f));
        cartaReves.setFillColor(Color(30, 50, 180));
        cartaReves.setOutlineThickness(3.f);
        cartaReves.setOutlineColor(Color::White);

		// Configuramos el marco interior del reverso de la carta
         marcoInterior.setSize(Vector2f(84.f, 134.f));
        marcoInterior.setFillColor(Color(20, 30, 120));
        marcoInterior.setOutlineThickness(2.f);
     
    

        // Configuramos el texto del número
        numero.setFont(*font);
        numero.setFillColor(color);
        numero.setCharacterSize(20);
        numero.setPosition(Vector2f(5.f, 5.f));
     
        // Configuramos el numero de abajo
        numeroAbajo.setFont(*font2);        
        numeroAbajo.setFillColor(color);
        numeroAbajo.setCharacterSize(20);
        numeroAbajo.setPosition(Vector2f(80.f, 110.f));


        // Creamos un rombo geométrico como símbolo central
        if (color == Color::Red) {
            simbolo.setPointCount(8);
            simbolo.setPoint(0, Vector2f(0, 10));    // Centro superior (la hendidura)
            simbolo.setPoint(1, Vector2f(-15, -10)); // Curva superior izquierda
            simbolo.setPoint(2, Vector2f(-30, 0));   // Extremo izquierdo
            simbolo.setPoint(3, Vector2f(-30, 15));  // Lateral izquierdo
            simbolo.setPoint(4, Vector2f(0, 45));    // Punta inferior (el pico)
            simbolo.setPoint(5, Vector2f(30, 15));   // Lateral derecho
            simbolo.setPoint(6, Vector2f(30, 0));    // Extremo derecho
            simbolo.setPoint(7, Vector2f(15, -10));  // Curva superior derecha
            marcoInterior.setOutlineColor(Color::Red);//El marco tiene color
        }
        else if (color == Color::Black) {
            //  Usamos 13 puntos para definir la silueta (3 hojas + tallo)
            simbolo.setPointCount(13);
            // --- Hoja Superior ---
            simbolo.setPoint(0, Vector2f(0.f, -10.f));   // Centro superior (hendidura)
            simbolo.setPoint(1, Vector2f(-15.f, -30.f)); // Pico izquierdo arriba
            simbolo.setPoint(2, Vector2f(15.f, -30.f));  // Pico derecho arriba
            // --- Hoja Derecha ---
            simbolo.setPoint(3, Vector2f(10.f, -5.f));   // Unión
            simbolo.setPoint(4, Vector2f(30.f, 5.f));    // Punta derecha
            simbolo.setPoint(5, Vector2f(10.f, 15.f));   // Unión inferior derecha
            // --- Tallo ---
            simbolo.setPoint(6, Vector2f(5.f, 15.f));    // Inicio tallo derecho
            simbolo.setPoint(7, Vector2f(0.f, 35.f));    // Punta del tallo (abajo)
            simbolo.setPoint(8, Vector2f(-5.f, 15.f));   // Inicio tallo izquierdo
            // --- Hoja Izquierda ---
            simbolo.setPoint(9, Vector2f(-10.f, 15.f));  // Unión inferior izquierda
            simbolo.setPoint(10, Vector2f(-30.f, 5.f));  // Punta izquierda
            simbolo.setPoint(11, Vector2f(-10.f, -5.f)); // Unión superior izquierda
            simbolo.setPoint(12, Vector2f(0.f, -10.f));  // Cerrar en el centro
            marcoInterior.setOutlineColor(Color::Black);
        }
        else if (color == Color::Blue) {
            // 1. Usamos 11 puntos para definir la forma de pica y su tallo
            simbolo.setPointCount(11);
            // --- Punta superior ---
            simbolo.setPoint(0, Vector2f(0.f, -35.f));   // La punta de arriba
            // --- Curva derecha (hoja) ---
            simbolo.setPoint(1, Vector2f(15.f, -15.f));  // Hombro derecho
            simbolo.setPoint(2, Vector2f(30.f, 10.f));   // Extremo derecho
            simbolo.setPoint(3, Vector2f(10.f, 15.f));   // Base curva derecha
            // --- Tallo ---
            simbolo.setPoint(4, Vector2f(5.f, 15.f));    // Inicio tallo derecho
            simbolo.setPoint(5, Vector2f(8.f, 35.f));    // Base tallo derecha
            simbolo.setPoint(6, Vector2f(-8.f, 35.f));   // Base tallo izquierda
            simbolo.setPoint(7, Vector2f(-5.f, 15.f));   // Inicio tallo izquierdo
            // --- Curva izquierda (hoja) ---
            simbolo.setPoint(8, Vector2f(-10.f, 15.f));  // Base curva izquierda
            simbolo.setPoint(9, Vector2f(-30.f, 10.f));  // Extremo izquierdo
            simbolo.setPoint(10, Vector2f(-15.f, -15.f));// Hombro izquierdo
            marcoInterior.setOutlineColor(Color::Blue);
        }
        else {
            simbolo.setPointCount(4);
            simbolo.setPoint(0, sf::Vector2f(0.f, -40.f));
            simbolo.setPoint(1, sf::Vector2f(30.f, 0.f));
            simbolo.setPoint(2, sf::Vector2f(0.f, 40.f));
            simbolo.setPoint(3, sf::Vector2f(-30.f, 0.f));
            marcoInterior.setOutlineColor(Color::Green);
        }
        simbolo.setFillColor(color);
        marcoInterior.setPosition(Vector2f(8.f, 8.f));
        // Centramos el símbolo para que no aparezca en una esquina
        FloatRect bounds = simbolo.getLocalBounds();

        simbolo.setOrigin(Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
        simbolo.setPosition(Vector2f(80.f, 115.f));
   


    }
    int getValor() {

        if (valor == "J")       
            return 11;
        if (valor == "Q")
            return 12;
        if (valor == "K")
            return 13;
        if (valor == "A")
            return 14;
        return stoi(valor); //Funcion de la libreria #String para transformar string a enteros
    }
    // Calcula el área que ocupa la carta en la pantalla (para saber si le haces clic)
    FloatRect getGlobalBounds() const {
        return getTransform().transformRect(forma.getGlobalBounds());
    }

    Vector2f getPos() const { return Transformable::getPosition(); } //Función para tener la posición de la carta
    void voltear() { enJuego = true;
	cout << "Se volteo la carta";
    }
	void aparecerAlreves() { //Funcion para aparecer la carta alreves
        enJuego = false;
     
    }
};
/*---------------------------------------------------Clase Jugador---------------------------------------------------------------------*/
class Jugador {  //Clase jugador para que el usuario juegue con sus cartas.
private:
    vector <Carta>  mano;         //Vector para la mano del jugador del inicio
    vector<Carta> manoReserva;    //Venctor para la mano de reserva 
	vector<Carta> manoFinal;      //Vector para la mano que se uitliza al final con las cartas volteadas
    int numeroJugador;

public:
    Jugador() : numeroJugador(1) {}
    Jugador(Carta  carta1, Carta carta2, Carta carta3, Carta  carta4, Carta  carta5, Carta  carta6, Carta  carta7, Carta  carta8, Carta  carta9,int num = 1) : numeroJugador(num) {

        // Metemnos todas las cartas de las  manos
        mano.push_back(carta1);
        mano.push_back(carta2);
        mano.push_back(carta3);
        manoReserva.push_back(carta4);
        manoReserva.push_back(carta5);
        manoReserva.push_back(carta6);
        manoFinal.push_back(carta7);
        manoFinal.push_back(carta8);
        manoFinal.push_back(carta9);

      

        if (numeroJugador == 1) {
            for (int i = 0; i < mano.size(); i++) {
                mano[i].setPosition(Vector2f(700.f - i * 50.f, 700.f)); //Posicion de las cartas de la mano principal
            }
            for (int i = 0; i < manoReserva.size(); i++) {
                manoReserva[i].setPosition(Vector2f(700.f - i * 50.f, 520.f)); // Posiciona las cartas de la mano reserva
            }
            for (int i = 0; i < manoFinal.size(); i++) {
                manoFinal[i].setPosition(Vector2f(1000.f - i * 50.f, 700.f)); // Posiciona las cartas de la mano final
            }
        }
        else if (numeroJugador == 2) {
            for (int i = 0; i < mano.size(); i++) {
                mano[i].setPosition(Vector2f(700.f - i * 50.f, 200.f)); // Posiciona las cartas en la parte superior de la pantalla
            }
            for (int i = 0; i < manoReserva.size(); i++) {
                manoReserva[i].setPosition(Vector2f(700.f - i * 50.f, 100.f)); // Posiciona las cartas en la parte superior de la pantalla
            }
        }
        for(auto& carta : manoFinal) { //Aquí volteamos las cartas de la mano final
            carta.aparecerAlreves();
        }
    }

    void operator+(Carta carta) {  //Función sobrecargada para comer 
        mano.push_back(carta); // Agrega la carta a la última  de la mano
        mano.back().setPosition(Vector2f(700.f - (mano.size() - 1) * 50.f, 700.f)); // Aquí acomoda la posicion de la nueva carta a la mano
    }
    Carta& getCarta(int  posicion) {   //Obtenemos una carta especifica
		return mano.at(posicion); //Comprovamos los limites y luego regresamos la carta en esa posición   (Lo utilizo porque con [] se me crashea al momento de los for en el main ):(
    }
  
    Carta& getCartaReserva(int  posicion) {  
        return manoReserva.at(posicion);//Comprovamos los limites y luego regresamos la carta en esa posición 
    }
   
    Carta  QuitarCarta(int x) {
        Carta carta = mano[x]; // Crea una copia del objeto carta para devolverlo después de eliminarlo de la mano
        mano.erase(mano.begin() + x); // Elimina la carta de la mano
        return carta; //Regresa la copia.         La razón de porque decidi no utilizar apuntadores es porque se eliminaba todo el objeto del programa :(
    }
    Carta  QuitarCartaReserva(int x) {
        Carta carta = manoReserva[x]; // Crea una copia del objeto carta para devolverlo después de eliminarlo de la mano
        manoReserva.erase(manoReserva.begin() + x); // Elimina la carta de la mano
        return carta; //Regresa la copia.         La razón de porque decidi no utilizar apuntadores es porque se eliminaba todo el objeto del programa :(
    }
    int numeroCartas() {  //Para saber cuantas cartas tiene el muchacho
        return mano.size();
    }
    int numeroCartasReserva() {  //Para saber cuantas cartas tiene el muchacho en la reserva
        return manoReserva.size();
    }
   
	Carta darCartaDeReserva(int x) {   //Función para dar una carta de la mano reserva
        if (x >= 0 && x < manoReserva.size()) {  //validamos si el indice es correcto
            Carta carta = manoReserva[x]; // Crea una copia del obj
			manoReserva.erase(manoReserva.begin() + x);  // Elimina la carta de la mano reserva
			cout << "Sacaste la carta de la mano reserva" << x << endl;  
            return carta;
        }
        else {
			throw out_of_range("Índice fuera de rango");  //Detenemos el programa si el indice es incorrecto y lanzamos un mensaje de error
        }
    }


	void voltearCarta(int x) {
		if (x >= 0 && x < mano.size()) {   //Validamos si el indice es correcto
			mano[x].voltear();
            cout << "Volteaste la carta" << x << endl;
		}
		else {
			throw out_of_range("Índice fuera de rango");//Detenemos el programa si el indice es incorrecto y lanzamos un mensaje de error 
		}
	}

    //Funciones para la mano final

	Carta& getCartaManoFinal(int  posicion) { //Función para obtener una carta de la mano final
		return manoFinal.at(posicion); //Comprovamos los limites y luego regresamos la carta en esa posición
    }
	int tamanoManoFinal() { //Función para saber cuantas cartas tiene la mano final
		return manoFinal.size(); //Regresa el tamaño de la mano final
	}
	Carta& gettamanoManoFinal(int  posicion) {  //Función para obtener una carta de la mano final
        return manoFinal.at(posicion);
    }
    Carta darCartaFinal(int x) {     //Damos la carta de la mano final
		if (x >= 0 && x < manoFinal.size()) {  //Validamos si el indice es correcto
            Carta carta = manoFinal[x];  //Creamos una copia
			manoFinal.erase(manoFinal.begin() + x); // Elimina la carta de la mano final
			cout << "Sacaste la carta de la mano final" << x << endl;
            return carta; //Regresamos la copia
        }
        else {
			throw out_of_range("Índice fuera de rango");//Detenemos el programa si el indice es incorrecto y lanzamos un mensaje de error 
        }
    }

};
/*------------------------------------Clase Liugi o diller -----------------------------------------------------*/
class Liugui {
private:
    vector<vector<Carta>> cartas;
    random_device semilla;
    mt19937 aleatorio{ semilla() };  //intancia de un generador pseudoaleatorio 
public:
    void recibirBaraja(vector<vector<Carta>> cartasdeMesa) {
        cartas = cartasdeMesa;
        cout << "Se recibio con exito";
    }
    void mesclarBaraja() {
        vector<Carta> temporal; //Creamos un vector temporal porque si uticisamos la matriz solo va barajear las filas pero no las cartas de cada fila
        for (const auto& fila : cartas) {  //For por rango que fila tiene 0 elemntos hasta los elemntos del vector de vectores de cartas
            temporal.insert(temporal.end(), fila.begin(), fila.end()); //Agregamos a la matriz temporal primero la posicon, desde donde copiar y hasta donde termianr de copiar
        }
        shuffle(temporal.begin(), temporal.end(), aleatorio);    //La funcion reorganiza el ultimo elemento

        int llenarMatriz = 0;
        for (auto& fila : cartas) {  //Aquí se recorremos cada fila en cartas
            for (Carta& cartita : fila) {  //Recorremos cada carta de las filas
                cartita = temporal[llenarMatriz]; //La carta mezclada la pone en la matriz
                llenarMatriz++;//Sumamos uno para la posicon de la matriz
            }
        }
    }
    vector<vector<Carta>> darCartasBarajeadas() {
        vector<vector<Carta>> totales = cartas;
        cartas.clear();
        return totales;
    }
};

// CLASE MESA: El tablero donde se colocan las cartas 
class Mesa : public RectangleShape {
private:
    vector<vector<Carta>> cartasTotales; // Un contenedor organizado por vectores (simula una base de datos)
    vector<Carta> bucheDeCartas; // Un contenedor para las cartas que ya se han usado
    RectangleShape borde;                // El marco de madera de la mesa

public:
    Mesa(const sf::Font& font, const Font& font2) : RectangleShape(Vector2f(1300.f, 800.f)), borde(Vector2f(1400.f, 900.f)) {
        // Estética de la mesa (Verde casino y borde café)
        setFillColor(Color(0, 80, 0));
        setPosition(Vector2f(50.f, 50.f));
        borde.setFillColor(Color(128, 64, 0));

        Color colores[] = { Color::Red, Color::Green, Color::Black, Color::Blue };
        string especiales[] = { "J", "Q", "K", "A" };

        // Bucle para crear el mazo completo 
        for (int j = 0; j < 4; j++) {
            vector<Carta> pinta;
            for (int i = 2; i <= 14; i++) {
                // Si el número es mayor a 10, usa las letras (J, Q, K, A)
                string v = (i <= 10) ? to_string(i) : especiales[i - 11];
                string u = v;
                pinta.push_back(Carta(colores[j], v, &font, &font2, u));
            }
            cartasTotales.push_back(pinta);

        }
    }
    vector<vector<Carta>> darTodasLasCartas() {
        vector<vector<Carta>> todas = cartasTotales;
        cartasTotales.clear();
        return todas;
    }
    void recibirCartasBarajeadas(Liugui& mario) {
        cartasTotales = mario.darCartasBarajeadas();
    }

    // Funciones para obtener objetos específicos de la mesa
    Carta darCarta() {
        //Este for se adapta al tamaño del vector, el -1 es porque los vectores inician desde 0.
        //Recorre hasta i>=0  y se reduce hasta llegar a 0.
        for (int i = cartasTotales.size() - 1; i >= 0; i--) {
            if (!cartasTotales[i].empty()) {          //Si en esa fila no hay objetos entonces para el siguiente ciclo va  a la otra fila
                Carta carta = cartasTotales[i].back();  //Se tiene que llenar la memoria con este objeto porque con apuntador no funciona |_|
                cartasTotales[i].pop_back();   //Y de hecho, al utilizar apuntadores se borra el objeto :(
                return carta; //Regresa la copia guardada del objeto eliminado
            }
        }
    }
    Carta& getCarta() {
        //Este for se adapta al tamaño del vector, el -1 es porque los vectores inician desde 0.
       //Recorre hasta i>=0  y se reduce hasta llegar a 0.
        for (int i = cartasTotales.size() - 1; i >= 0; i--) {
            if (!cartasTotales[i].empty()) {
                return cartasTotales[i].back();
            }
        }
    }
	int tamanoCartasTotales() {      //Función para saber cuantas cartas hay en total en la mesa
		int totalDeCartas = 0; //Variable temporal
		for (const auto& fila : cartasTotales) {  //Como es un vector de vectores, entonces sumamos a la variable temporal el tamaño de cada fila en cada ciclo
			totalDeCartas+=fila.size();
		}
		return totalDeCartas; // Regresamos el resultado del for 
	}
    RectangleShape& getBorde() { return borde; }

    void llenarBuche(Carta carta) {  //Mecanica de 4 amigos como el UNO, recibe las cartas del jugador y los mete en el buche
        carta.setPosition(Vector2f(650.f, 360.f)); // Aquí se coloca las cartas en el centro
		bucheDeCartas.push_back(carta);//Agrega la carta al buche
    }
    Carta& getBuche() {  //Obtemenos la carta del buche 
        return bucheDeCartas.back();
    }
    int tamanoDelBuche() {  //Tamaño del buche
        return bucheDeCartas.size();
    }
	Carta darCartaDelBuche() {  //Función para comer la carta del buche
        if (bucheDeCartas.empty()) {
            cout << "No hay cartas en el buche para comer." << endl;
        }
        else {
            for (int i = bucheDeCartas.size() - 1; i >= 0; i--) { 
                if (!bucheDeCartas.empty()) {
                    Carta carta = bucheDeCartas.back(); // Guarda la última carta del buche antes de eliminarla
                    bucheDeCartas.pop_back(); // Elimina la carta del buche
                    return carta; // Regresa la copia guardada del objeto eliminado
                }
            }
        }
    }
    int valorDeCartaBuceh(int a) { //Obtenemos el valor de la ultima carta 
        return bucheDeCartas[a].getValor();
    }
	void  limpiarBuche() {
		bucheDeCartas.clear(); //Limpiamos el vector 
	}
};


//motor del juego
int main() {
    // Intentamos cargar la fuente de letra de Windows
    Font font, font2;
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;   //Validamos si la fuente es correcta 
    if (!font2.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1; //Validamos si la fuente es correcta 
    Mesa mesa(font, font2);
    Liugui mario;

    RenderWindow window(VideoMode(Vector2u(1400, 900)), "4 amigos");
    mario.recibirBaraja(mesa.darTodasLasCartas());
    mario.mesclarBaraja();
    mesa.recibirCartasBarajeadas(mario);
    Jugador jugador1(mesa.darCarta(), mesa.darCarta(), mesa.darCarta(), mesa.darCarta(), mesa.darCarta(), mesa.darCarta(), mesa.darCarta(), mesa.darCarta(), mesa.darCarta());

    //En esta parte se coloca el panel donde Luigi, el dealer, estará presente.
    RectangleShape panelLuigi;
    panelLuigi.setSize(Vector2f(320.f, 100.f));
    panelLuigi.setFillColor(Color(20, 60, 20, 220));
    panelLuigi.setOutlineThickness(3.f);
    panelLuigi.setOutlineColor(Color(200, 200, 200));


    Vector2u windowSize = window.getSize();

    panelLuigi.setPosition(
        Vector2f((static_cast<float>(windowSize.x) - panelLuigi.getSize().x) / 2.f, 15.f)
    );
    auto primeratirada = true;
    bool siguiendo = false;         // Indica si estamos arrastrando una carta
    Carta* cartaSeleccionada = nullptr; // Guarda qué carta tenemos agarrada
    Vector2f offset;               // Distancia entre el mouse y la esquina de la carta (para que no "salte")

    // Ponemos una carta en una posición visible para probar


    // Asignamos una carta a la mano del jugador


    mesa.llenarBuche(mesa.darCarta());
    //Se repite constantemente mientras la ventana esté abierta
    while (window.isOpen()) {

        // Revisar si pasó algo (clics, cerrar ventana, etc.)
        while (const auto event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();

            // Si el usuario presiona el botón izquierdo del mouse
            if (auto mouseEvent = event->getIf<Event::MouseButtonPressed>()) {
                if (mouseEvent->button == Mouse::Button::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                        // ¿El clic fue dentro de la carta (posicion o posiciones)?
                        if (mesa.getCarta().getGlobalBounds().contains(mousePos) && jugador1.numeroCartas() < 3) {  //Aquí es donde sucede la mágia para comer cartas
                            jugador1 + mesa.darCarta();

                        }
                        else   if (mesa.tamanoDelBuche() > 0 && mesa.getBuche().getGlobalBounds().contains(mousePos) ) { //En si no se porque no agarra todas las cartas del buche de una. 
                            while (mesa.tamanoDelBuche() > 0) {  //Un while mientras haya cartas en el buche entonces agarrar  para agarrar las cartas
                                jugador1 + mesa.darCartaDelBuche(); // Aquí se come la carta del buche                      

                            }

                        }
                      else {
                            for (int x = 0; x < jugador1.numeroCartas(); x++) {   //Aquí con este for ayuda a dejar las cartas.
                                if (jugador1.getCarta(x).getGlobalBounds().contains(mousePos) ) {   //Si el jugador hizo click entonces...

                                    //Mecanica para el número 10
                                    if ((mesa.tamanoDelBuche() == 0 || jugador1.getCarta(x).getValor() >= mesa.getBuche().getValor() || jugador1.getCarta(x).getValor() == 10 || jugador1.getCarta(x).getValor() == 2)) {
                                        if (jugador1.getCarta(x).getValor() == 10) { //Si la carta es un 10, se limpia el buche
                                            mesa.llenarBuche(jugador1.QuitarCarta(x));
                                            mesa.limpiarBuche();  // La mecanica es eliminar todo el buhce que hay con un 10 puesto
                                        }
                                        else {
                                        mesa.llenarBuche(jugador1.QuitarCarta(x)); // Mueve la carta al buche
                                    }

                                    }
                                }
                            

                            }
                            if (jugador1.numeroCartas() == 0 && jugador1.numeroCartasReserva() > 0) {  //Aquí le decimos al gamplay que si np hay cartas en la mano principal entonces pasar a la otra regla del gameplay
                                for (int y = 0; y < jugador1.numeroCartasReserva(); y++) { //For para las cartas de la mano reserva
									if (jugador1.getCartaReserva(y).getGlobalBounds().contains(mousePos)) {  //Si el jugador hizo click entonces...
										 
                                         jugador1 + jugador1.QuitarCartaReserva(y);  //Le pasamos esas carta a la mano principal
                                        break;
                                    }
                                    
                                }
                            }//
                            if (jugador1.numeroCartas() == 0 && jugador1.numeroCartasReserva() == 0) {
                                for (int z = 0; z < jugador1.tamanoManoFinal(); z++) {
                                    if (jugador1.getCartaManoFinal(z).getGlobalBounds().contains(mousePos)) {

                                        Carta cartaFinal = jugador1.darCartaFinal(z);  //Creamos una copia para mas tarde voltear esa carta
                                        cartaFinal.voltear();                   //Volteamos esa carta
										jugador1 + cartaFinal;  //Le pasamos esa carta a la mano principal
                                        break;
                                    }
                                }}
                            if (mesa.tamanoDelBuche() >= 4) {   //Mecanica para eliminar el buche cuando hay 4 cartas con el mismo valor
                                int a = mesa.tamanoDelBuche() -1;  //variable temporal del mismo tamaño del vector 
                                int valorCarta1 = mesa.valorDeCartaBuceh(a);  //Variables temporales 
                                int valorCarta2 = mesa.valorDeCartaBuceh(a - 1);
                                int valorCarta3 = mesa.valorDeCartaBuceh(a - 2);
                                int valorCarta4 = mesa.valorDeCartaBuceh(a - 3);
                                if (valorCarta1 == valorCarta2 && valorCarta2 == valorCarta3 && valorCarta3 == valorCarta4)  //Si las 4 son iguales entonces limpiar buhce 
                                    mesa.limpiarBuche();
                            }
                        }//
                    }
                

            }

           
            //Si hay cartas en la reserva dibjuar sí o n
             //Limpiamos la pantalla y redibujamos todo en su nueva posición
            window.clear();
            window.draw(mesa.getBorde()); // Dibujar el marco
            window.draw(mesa);           // Dibujar el tapete verde
            window.draw(panelLuigi); //Dibujar panel del dealer
            for (int i = 0; i < jugador1.numeroCartas(); i++) {  //Dibjuar las cartas y este for se adapta al tamaño de la mano del jugador
                window.draw(jugador1.getCarta(i)); // Dibujar las cartas del jugador
            }
            for (int i = 0; i < jugador1.numeroCartasReserva(); i++) {  //Dibjuar las cartas y este for se adapta al tamaño de la mano del jugador
                window.draw(jugador1.getCartaReserva(i)); // Dibujar las cartas del jugador
            }
            for (int i = 0; i < jugador1.tamanoManoFinal(); i++) {  //Dibjuar las cartas y este for se adapta al tamaño de la mano del jugador
                window.draw(jugador1.getCartaManoFinal(i)); // Dibujar las cartas del jugador
            }
            for (int i = 0; i < mesa.tamanoDelBuche(); i++) {// Dibuja la ultima carta del buche
                window.draw(mesa.getBuche()); // Dibujar las cartas en el buche
            }
                             

            window.draw(mesa.getCarta());
            window.display();
        }
    }

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