#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;
using namespace std;

// CLASE CARTA: Define cómo se ven y se comportan las cartas
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
    vector <Carta*>  mano;
    vector<Carta*> manoReserva;
    int numeroJugador;
public:
    Jugador() : mano(NULL), manoReserva(NULL), numeroJugador(1) {}
    Jugador(vector <Carta*>  resivido, vector<Carta*> manoReserva = vector<Carta*>(0), int num = 1) : numeroJugador(num) {

        for (int i = 0;i < 3;i++) {  // Todos los jugadores empiezan con 3 cartas, este for es si resive un vector con más cartas-
            mano.push_back(resivido[i]);
        }

        for (int i = 0;i < 3;i++) {  // Todos los jugadores empiezan con 3 cartas, este for es si resive un vector con más cartas-
            this->manoReserva.push_back(manoReserva[i]);
        }

        if (numeroJugador == 1) {
            for (int i = 0; i < mano.size(); i++) {
                mano[i]->setPosition(Vector2f(700.f - i * 50.f, 700.f)); // Posiciona las cartas en la parte inferior de la pantalla
            }

        }
        else if (numeroJugador == 2) {
            for (int i = 0; i < mano.size(); i++) {
                mano[i]->setPosition(Vector2f(700.f - i * 50.f, 200.f)); // Posiciona las cartas en la parte superior de la pantalla
            }

        }
    }

    void operator+(Carta& carta) {  //Función sobrecargada para comer 

        mano.push_back(&carta); // Agrega la carta a la última  de la mano
        mano.back()->setPosition(Vector2f(700.f - (mano.size() - 1) * 50.f, 700.f)); // Aquí acomoda la posicion de la nueva carta a la mano
    }
    Carta& getCarta(int  posicion) {
        return *mano[posicion];
    }
};

// CLASE MESA: El tablero donde se colocan las cartas 
class Mesa : public RectangleShape {
private:
    vector<vector<Carta>> cartasTotales; // Un contenedor organizado por vectores (simula una base de datos)
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
    Carta& darCarta(int pinta, int valor) {
        //Primero necesito que regrese la carta antes de eliminarla.
        return cartasTotales[pinta][valor];

        // Luego la elimino para que no se pueda volver a usar
        //El vector utiliza la funcion erase para eliminar carta, pero como es un vector de vectores, la pinta representa la fila
        // Entonces .begin apunta al primer elemnto de la fila MÄS el valor de la columna (columna represanta la posicion de la carta)
        cartasTotales[pinta].erase(cartasTotales[pinta].begin() + valor);
    }
    Carta& getCarta(int pinta, int valor) { return cartasTotales[pinta][valor]; }
    RectangleShape& getBorde() { return borde; }
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
    jugador1 + mesa.darCarta(2, 9);
    jugador1 + mesa.darCarta(0, 9);
    jugador1 + mesa.darCarta(1, 12);

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
                    if (jugador1.getCarta(0).getGlobalBounds().contains(mousePos)) {
                        siguiendo = true; // Empezamos a arrastrar
                        cartaSeleccionada = &jugador1.getCarta(0);
                        // Calculamos la distancia
                        offset = cartaSeleccionada->getPosition() - mousePos;
                    }
                    else if (jugador1.getCarta(1).getGlobalBounds().contains(mousePos)) {
                        siguiendo = true; // Empezamos a arrastrar
                        cartaSeleccionada = &jugador1.getCarta(1);
                        // Calculamos la distancia
                        offset = cartaSeleccionada->getPosition() - mousePos;
                    }
                    else if (jugador1.getCarta(2).getGlobalBounds().contains(mousePos)) {
                        siguiendo = true; // Empezamos a arrastrar
                        cartaSeleccionada = &jugador1.getCarta(2);
                        // Calculamos la distancia
                        offset = cartaSeleccionada->getPosition() - mousePos;
                    }
                    else if (mesa.getCarta(3, 11).getGlobalBounds().contains(mousePos)) {
                        siguiendo = true; // Empezamos a arrastrar
                        cartaSeleccionada = &mesa.getCarta(3, 11);
                        // Calculamos la distancia
                        offset = cartaSeleccionada->getPosition() - mousePos;
                    }
                }
            }

            // Si soltamos el botón, dejamos de arrastrar
            if (event->is<Event::MouseButtonReleased>()) {
                siguiendo = false;
                cartaSeleccionada = nullptr;
            }
        }

        //Si hay una carta agarrada, que siga al mouse
        if (siguiendo && cartaSeleccionada) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            cartaSeleccionada->setPosition(mousePos + offset);
        }

        //Limpiamos la pantalla y redibujamos todo en su nueva posición
        window.clear();
        window.draw(mesa.getBorde()); // Dibujar el marco
        window.draw(mesa);           // Dibujar el tapete verde
        window.draw(panelLuigi); //Dibujar panel del dealer
        window.draw(jugador1.getCarta(0)); // Dibujar la carta encima de todo
        window.draw(jugador1.getCarta(1));
        window.draw(jugador1.getCarta(2));
        window.draw(mesa.getCarta(3, 11));
        window.display();            // Mostrar el resultado en pantalla
    }

    return 0;
}

/*
COSAS OBSERVADAS:
-Puede salir error si seleccionas una posicon de un vector vacio.  (paso muchas veces (|_|)  )
-Todavia falta optimizar más la memoria.
- IMPORTANTE Y VIENE CON EL PRIMER AVISO: Falta hacer validacion.
*/