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
    Text* numero = nullptr;         // para mostrar el número 
    RectangleShape forma; // El cuerpo de la carta
    ConvexShape simbolo;  // El rombo o figura de la baraja

    // Esta función le dice a la ventana qué orden seguir para dibujar la carta
    virtual void draw(RenderTarget& target, RenderStates states) const override {
        states.transform *= getTransform(); // Aplica movimiento y rotación
        target.draw(forma, states);         // 1. Dibuja el fondo
        if (numero) target.draw(static_cast<const sf::Drawable&>(*numero), states);        // 2. Dibuja el número arriba
        target.draw(simbolo, states);       // 3. Dibuja el símbolo
    }

public:
    Carta() : valor(" "), color(), enJuego(true), font(nullptr) {}

    // Destructor
    ~Carta() {
        delete numero;
    }

    // Constructor de copia
    Carta(const Carta& other)
        : color(other.color), valor(other.valor), enJuego(other.enJuego),
        font(other.font), forma(other.forma), simbolo(other.simbolo) {
        if (other.font && other.numero) {
            numero = new Text(*other.font, other.valor);
            numero->setFillColor(other.numero->getFillColor());
            numero->setCharacterSize(other.numero->getCharacterSize());
            numero->setPosition(other.numero->getPosition());
        }
        else {
            numero = nullptr;
        }
    }

    // Operador de asignación
    Carta& operator=(const Carta& other) {
        if (this != &other) {
            delete numero;
            color = other.color;
            valor = other.valor;
            enJuego = other.enJuego;
            font = other.font;
            forma = other.forma;
            simbolo = other.simbolo;
            if (other.font && other.numero) {
                numero = new Text(*other.font, other.valor);
                numero->setFillColor(other.numero->getFillColor());
                numero->setCharacterSize(other.numero->getCharacterSize());
                numero->setPosition(other.numero->getPosition());
            }
            else {
                numero = nullptr;
            }
        }
        return *this;
    }

    // Constructor: Aquí se hace la carta
    Carta(Color color, string valor, const sf::Font* font)
        : enJuego(true), color(color), valor(valor), font(font) {
        setPosition(Vector2f(800.f, 300.f)); // Posición inicial (se puede cambiar después)
        // Configuramos el cuerpo de la carta (rectángulo blanco con borde)
        forma.setSize(sf::Vector2f(100.f, 150.f));
        forma.setFillColor(Color::White);
        forma.setOutlineColor(sf::Color::Black);
        forma.setOutlineThickness(3.f);

        //Inicializar numero antes de usarlo (corregido porque crasheaba)
        numero = new sf::Text(*font, valor);

        // Configuramos el texto del número
        numero->setFillColor(color);
        numero->setCharacterSize(25);
        numero->setPosition(Vector2f(5.f, 5.f));

        // Creamos un rombo geométrico como símbolo central
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
        }
        else if (color == Color::Black) {
            // 1. Usamos 13 puntos para definir la silueta (3 hojas + tallo)
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
        }
        else {
            simbolo.setPointCount(4);
            simbolo.setPoint(0, sf::Vector2f(0.f, -40.f));
            simbolo.setPoint(1, sf::Vector2f(30.f, 0.f));
            simbolo.setPoint(2, sf::Vector2f(0.f, 40.f));
            simbolo.setPoint(3, sf::Vector2f(-30.f, 0.f));
        }
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
class Mesa {
private:
    RectangleShape tapete;
    vector<vector<Carta>> cartasTotales; // Un contenedor organizado por vectores (simula una base de datos)
    vector<Carta> bucheDeCartas; // Un contenedor para las cartas que ya se han usado
    RectangleShape borde;                // El marco de madera de la mesa

public:
    Mesa(const sf::Font& font) : tapete(Vector2f(1300.f, 800.f)), borde(Vector2f(1400.f, 900.f)) {
        printf("Dentro de Mesa constructor\n"); fflush(stdout);
        // Estética de la mesa (Verde casino y borde café)
        tapete.setFillColor(Color(0, 80, 0));
        tapete.setPosition(Vector2f(50.f, 50.f));
        borde.setFillColor(Color(128, 64, 0));
        printf("Colores OK\n"); fflush(stdout);

        Color colores[] = { Color::Red, Color::Green, Color::Black, Color::Blue };
        string especiales[] = { "J", "Q", "K", "A" };
        printf("Arrays OK\n"); fflush(stdout);

        // Bucle para crear el mazo completo 
        for (int j = 0; j < 4; j++) {
            printf("Pinta %d\n", j); fflush(stdout);
            vector<Carta> pinta;
            for (int i = 2; i <= 14; i++) {
                // Si el número es mayor a 10, usa las letras (J, Q, K, A)
                string v = (i <= 10) ? to_string(i) : especiales[i - 11];
                pinta.push_back(Carta(colores[j], v, &font));
            }
            cartasTotales.push_back(pinta);
            printf("Pinta %d OK\n", j); fflush(stdout);

        }

        printf("Mesa constructor OK\n"); fflush(stdout);
    }

    //Verificar si hay cartas en el mazo
    bool hayCartas() {
        for (int i = cartasTotales.size() - 1; i >= 0; i--) {
            if (!cartasTotales[i].empty()) return true;
        }
        return false;
    }

    //Verificar si hay cartas en el buche
    bool hayBuche() {
        return !bucheDeCartas.empty();
    }

    // Funciones para obtener objetos específicos de la mesa
    Carta darCarta() {
        for (int i = cartasTotales.size() - 1; i >= 0; i--) {
            if (!cartasTotales[i].empty()) {
                Carta carta = cartasTotales[i].back();
                cartasTotales[i].pop_back();
                return carta;
            }
        }
        return Carta(); //fallback si no hay cartas
    }

    Carta& getCarta() {
        for (int i = cartasTotales.size() - 1; i >= 0; i--) {
            if (!cartasTotales[i].empty()) {
                return cartasTotales[i].back();
            }
        }
        //fallback seguro
        return cartasTotales[0][0];
    }

    RectangleShape& getBorde() { return borde; }
    RectangleShape& getTapete() { return tapete; }

    void llenarBuche(Carta carta) {  //Mecanica de 4 amigos como el UNO, recibe las cartas del jugador y los mete en el buche
        carta.setPosition(Vector2f(650.f, 360.f)); // Aquí se coloca las cartas en el centro
        bucheDeCartas.push_back(carta);
    }

    Carta& getBuche() {
        return bucheDeCartas.back(); // Solo llamar si hayBuche() es true
    }

    int tamanoDelBuche() {
        return bucheDeCartas.size();
    }

    Carta darCartaDelBuche() {
        if (bucheDeCartas.empty()) {
            cout << "No hay cartas en el buche para comer." << endl;
            return Carta(); 
        }
        Carta carta = bucheDeCartas.back();
        bucheDeCartas.pop_back();
        return carta;
    }
};




//motor del juego
int main() {
    printf("Iniciando main\\\n"); fflush(stdout);
    // Intentamos cargar la fuente de letra de Windows
    Font font; printf("Font creado\\n"); fflush(stdout);
    printf("Abriendo fuente\\n"); fflush(stdout); bool loaded = font.openFromFile("../assets/arial.ttf"); printf(loaded ? "Fuente OK\\n" : "Fuente FALLO\\n"); fflush(stdout); if (!loaded) return -1;

    printf("Creando mesa\\n"); fflush(stdout); Mesa mesa(font); printf("Mesa OK\\n"); fflush(stdout);
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

    // Asignamos una carta a la mano del jugador
    jugador1 + mesa.darCarta();
    jugador1 + mesa.darCarta();
    jugador1 + mesa.darCarta();
    jugador1 + mesa.darCarta();

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

                    //verificar si hay cartas antes de acceder
                    if (mesa.hayCartas() && mesa.getCarta().getGlobalBounds().contains(mousePos)) {
                        jugador1 + mesa.darCarta();
                    }
                    else {
                        for (int x = 0; x < jugador1.numeroCartas(); x++) {
                            if (jugador1.getCarta(x).getGlobalBounds().contains(mousePos)) {
                                mesa.llenarBuche(jugador1.QuitarCarta(x));
                            }
                        }
                        //verificar buche antes de acceder
                        if (mesa.hayBuche() && mesa.getBuche().getGlobalBounds().contains(mousePos)) {
                            int tamano = mesa.tamanoDelBuche();
                            for (int i = 0; i < tamano; i++) {
                                jugador1 + mesa.darCartaDelBuche();
                            }
                        }
                    }
                }
            }

            // Limpiamos la pantalla y redibujamos todo en su nueva posición
            window.clear();
            window.draw(mesa.getBorde());
            window.draw(mesa.getTapete());
            window.draw(panelLuigi);

            for (int i = 0; i < jugador1.numeroCartas(); i++) {
                window.draw(jugador1.getCarta(i));
            }

            //verificar si hay cartas en el buche antes de dibujar
            if (mesa.hayBuche()) {
                window.draw(mesa.getBuche());
            }

            //verificar si hay cartas en el mazo antes de dibujar
            if (mesa.hayCartas()) {
                window.draw(mesa.getCarta());
            }

            window.display();
        }
    }

    return 0;
}

/*
COSAS OBSERVADAS:
-Posiblemente está muy mal optimizado por la cuestion de las cartas. Practicamente se elimino algunos apuntadores de funciones porque
para la mecanica del dar carta y quitar carta, se eliminaba el objeto Carta del programa.
-Se crashea el programa cuando ya no hay cartas para comer. ✅ CORREGIDO
*/
