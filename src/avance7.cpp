#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>
using namespace sf;
using namespace std;
// CLASE CARTA: Define cómo se ven y se comportan las cartas
class Luigi {



};
class Carta : public Drawable, public Transformable {
private:
    Color color;
    string valor;
    bool enJuego;
    const Font* font;
    Text numero;         // para mostrar el número 
    RectangleShape forma; // El cuerpo de la carta
    ConvexShape simbolo;  // El rombo o figura de la baraja

    // Esta función le dice a la ventana qué orden seguir para dibujar la carta
    virtual void draw(RenderTarget& target, RenderStates states) const override {
        states.transform *= getTransform(); // Aplica movimiento y rotación
        target.draw(forma, states);         // 1. Dibuja el fondo
        target.draw(numero, states);        // 2. Dibuja el número arriba
        target.draw(simbolo, states);       // 3. Dibuja el símbolo
    }

public:
    Carta() : valor(" "), color(), enJuego(true), numero(*font, " ") {}

    // Constructor: Aquí se hace la carta
    Carta(Color color, string valor, const sf::Font* font)
        : enJuego(true), color(color), valor(valor), font(font), numero(*font, valor) {
        setPosition(Vector2f(800.f, 300.f)); // Posición inicial (se puede cambiar después)
        // Configuramos el cuerpo de la carta (rectángulo blanco con borde)
        forma.setSize(sf::Vector2f(100.f, 150.f));
        forma.setFillColor(Color::White);
        forma.setOutlineColor(sf::Color::Black);
        forma.setOutlineThickness(3.f);

        // Configuramos el texto del número
        numero.setFillColor(color);
        numero.setCharacterSize(25);
        numero.setPosition(Vector2f(5.f, 5.f));

        // Creamos un rombo geométrico como símbolo central
        simbolo.setPointCount(4);
        simbolo.setPoint(0, sf::Vector2f(0.f, -40.f));
        simbolo.setPoint(1, sf::Vector2f(30.f, 0.f));
        simbolo.setPoint(2, sf::Vector2f(0.f, 40.f));
        simbolo.setPoint(3, sf::Vector2f(-30.f, 0.f));
        simbolo.setFillColor(color);

        // Centramos el símbolo para que no aparezca en una esquina
        FloatRect bounds = simbolo.getLocalBounds();
        simbolo.setOrigin(Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
        simbolo.setPosition(Vector2f(80.f, 115.f));
    }

    // Calcula el área que ocupa la carta en la pantalla (para saber si le haces clic)
    FloatRect getGlobalBounds() const {
        return getTransform().transformRect(forma.getGlobalBounds());
    }

    Vector2f getPos() const { return Transformable::getPosition(); }

};

class Jugador {  //Clase jugador para que el usuario juegue con sus cartas.
private:
    vector <Carta>  mano;
    vector<Carta*> manoReserva;
    int numeroJugador;

public:
    Jugador() : numeroJugador(1) {}
    Jugador(vector <Carta*>  resivido, vector<Carta*> manoReserva = vector<Carta*>(0), int num = 1) : numeroJugador(num) {

        for (int i = 0;i < 3;i++) {  // Todos los jugadores empiezan con 3 cartas, este for es si resive un vector con más cartas-
            mano.push_back(*resivido[i]);
        }

        for (int i = 0;i < 3;i++) {  // Todos los jugadores empiezan con 3 cartas, este for es si resive un vector con más cartas-
            this->manoReserva.push_back(manoReserva[i]);
        }

        if (numeroJugador == 1) {
            for (int i = 0; i < mano.size(); i++) {
                mano[i].setPosition(Vector2f(700.f - i * 50.f, 700.f)); // Posiciona las cartas en la parte inferior de la pantalla
            }

        }
        else if (numeroJugador == 2) {
            for (int i = 0; i < mano.size(); i++) {
                mano[i].setPosition(Vector2f(700.f - i * 50.f, 200.f)); // Posiciona las cartas en la parte superior de la pantalla
            }

        }
    }

    void operator+(Carta carta) {  //Función sobrecargada para comer 
        mano.push_back(carta); // Agrega la carta a la última  de la mano
        mano.back().setPosition(Vector2f(700.f - (mano.size() - 1) * 50.f, 700.f)); // Aquí acomoda la posicion de la nueva carta a la mano
    }
    Carta& getCarta(int  posicion) {
        return mano[posicion];
    }
    Carta  QuitarCarta(int x) {
        Carta carta = mano[x]; // Crea una copia del objeto carta para devolverlo después de eliminarlo de la mano
        mano.erase(mano.begin() + x); // Elimina la carta de la mano
        return carta; //Regresa la copia.         La razón de porque decidi no utilizar apuntadores es porque se eliminaba todo el objeto del programa :(
    }

    int numeroCartas() {  //Para saber cuantas cartas tiene el muchacho
        return mano.size();
    }
};

// CLASE MESA: El tablero donde se colocan las cartas 
class Mesa : public RectangleShape {
private:
    vector<vector<Carta>> cartasTotales; // Un contenedor organizado por vectores (simula una base de datos)
    vector<Carta> bucheDeCartas; // Un contenedor para las cartas que ya se han usado
    RectangleShape borde;                // El marco de madera de la mesa

public:
    Mesa(const sf::Font& font) : RectangleShape(Vector2f(1300.f, 800.f)), borde(Vector2f(1400.f, 900.f)) {
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
                pinta.push_back(Carta(colores[j], v, &font));
            }
            cartasTotales.push_back(pinta);

        }
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
    RectangleShape& getBorde() { return borde; }

    void llenarBuche(Carta carta) {  //Mecanica de 4 amigos como el UNO, recibe las cartas del jugador y los mete en el buche
        carta.setPosition(Vector2f(650.f, 360.f)); // Aquí se coloca las cartas en el centro
        bucheDeCartas.push_back(carta);
    }
    Carta& getBuche() {
        return bucheDeCartas.back();
    }
    int tamanoDelBuche() {
        return bucheDeCartas.size();
    }
    Carta darCartaDelBuche() {
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
};




//motor del juego
int main() {
    // Intentamos cargar la fuente de letra de Windows
    Font font;
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

    Mesa mesa(font);
    RenderWindow window(VideoMode(Vector2u(1400, 900)), "4 amigos");

    Jugador jugador1;

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

    bool siguiendo = false;         // Indica si estamos arrastrando una carta
    Carta* cartaSeleccionada = nullptr; // Guarda qué carta tenemos agarrada
    Vector2f offset;               // Distancia entre el mouse y la esquina de la carta (para que no "salte")

    // Ponemos una carta en una posición visible para probar


    // Asignamos una carta a la mano del jugador
    jugador1 + mesa.darCarta();
    jugador1 + mesa.darCarta();
    jugador1 + mesa.darCarta();
    jugador1 + mesa.darCarta();

    //Se repite constantemente mientras la ventana esté abierta
    while (window.isOpen()) {
        // Revisar si pasó algo
        // (clics, cerrar ventana, etc.)
        while (const auto event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();

            // Si el usuario presiona el botón izquierdo del mouse
            if (auto mouseEvent = event->getIf<Event::MouseButtonPressed>()) {
                if (mouseEvent->button == Mouse::Button::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    /**/
                    // ¿El clic fue dentro de la carta (posicion o posiciones)?
                    if (mesa.getCarta().getGlobalBounds().contains(mousePos)) {  //Aquí es donde sucede la mágia para comer cartas
                        jugador1 + mesa.darCarta();

                    }
                    else if (jugador1.getCarta(1).getGlobalBounds().contains(mousePos)) {
                        siguiendo = true; // Empezamos a arrastrar
                        cartaSeleccionada = &jugador1.getCarta(1);
                        // Calculamos la distancia
                        offset = cartaSeleccionada->getPosition() - mousePos;

                            }
                        }
                        if (mesa.getBuche().getGlobalBounds().contains(mousePos)) { //En si no se porque no agarra todas las cartas del buche de una. 
                            for (int i = 0; i < mesa.tamanoDelBuche(); i++) {  //Un for  para agarrar las cartas
                                jugador1 + mesa.darCartaDelBuche(); // Aquí se come la carta del buche                      

                            }

                        }
                    }
                }


            }
            //Si hay cartas en la reserva dibjuar sí o n
             //Limpiamos la pantalla y redibujamos todo en su nueva posición
            window.clear();
            window.draw(mesa.getBorde()); // Dibujar el marco
            window.draw(mesa);           // Dibujar el tapete verde
            window.draw(panelLuigi); //Dibujar panel del dealer
            window.draw(jugador1.getCarta(0)); // Dibujar la carta encima de todo
            window.draw(jugador1.getCarta(1));
            window.draw(jugador1.getCarta(2));
            window.draw(mesa.getCarta(3, 8));
            window.display();            // Mostrar el resultado en pantalla
        }
    }

    return 0;
}

/*
COSAS OBSERVADAS:
-Posiblemente está muy mal optimizado por la cuestion de las cartas. Practicamente se elimino algunos apuntadores de funciones porque
para la mecanica del dar carta y quitar carta, se eliminaba el objeto Carta del programa.
-Se crashea el programa cuando ya no hay cartas para comer.

*/