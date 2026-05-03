#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;
using namespace std;
class Carta : public RectangleShape {  //Es una clase derivada de la clase de SFML RectangleShape porque permite dibujar desde la clase sus propiedads
private:
    string color;
    string valor;
    bool enJuego;                                               //|
public:                                                         //V  Se define los coles de la carta
    Carta() : valor(" "), color(" "), enJuego(true), RectangleShape(Vector2f(100.f, 150.f)) {}
    Carta(string color, string valor) : color(color), valor(valor), RectangleShape(Vector2f(100.f, 150.f)) {
        setPosition(Vector2f(750.f, 600.f));   //Practicamente el constructo define los valroes de las cartas y su estructura
    }

    const string getValor() {
        return valor;
    }
    const string getColor() {
        return color;
    }
    void setValor(string valor) {
        this->valor = valor;
    }
    void setColor(string color) {
        this->color = color;

    }

};
class Mesa : public RectangleShape {
private:
    vector<Carta> cartasEnMesa;
public:
    Mesa() : cartasEnMesa(NULL), RectangleShape(Vector2(1300.f, 800.f)) { //En vez de usar el main. La clase mesa ya imprime la mesa al crear el objeto
        setFillColor(Color(0, 80, 0)); // Color del borde
        setPosition(Vector2f(50.f, 50.f));
    }
    Mesa(Carta& carta) {
        cartasEnMesa.push_back(carta);

    }
    const vector<Carta>& getCartasEnMesa() {  //Es un metodo que devuelve el vector de cartas en mesa, para poder usarlo en el main
        return cartasEnMesa;
    }
    string mostrarCarta(Carta& carta) {  //Es un metodo que devuelve el valor de la carta, para poder usarlo en el main.
        string valor = carta.getValor();

        return valor;
    }
};

int main() {
    //Aqui por medio de un vector se peude crear de golpe las cartas de la mesa, en este caso de la pinta roja.
    vector <Carta> manoJugador;       //Se declara un vector de tipo carta                            
    for (int i = 2; i < 15; i++) {//IMPORTANTE: Es un forcito que permite crear un ciclo para crear las 14 cartas 
        if (i < 11) { //Del 2 al 10 son números normales
            string valor = to_string(i); //Transformamos el número 1 a una variable string para inicializar la carta
            manoJugador.push_back(Carta("rojo", valor)); //En el vector de la mano, empujamos una variable nueva tipo cara con el constructro con parametros
        }
        else { //Del 11 al 14 son los valores J;Q;J;A
            switch (i)
            {
            case 11:
                manoJugador.push_back(Carta("rojo", "J"));
                break;
            case 12:
                manoJugador.push_back(Carta("rojo", "Q"));
                break;
            case 13:
                manoJugador.push_back(Carta("rojo", "K"));
                break;
            case 14:
                manoJugador.push_back(Carta("rojo", "A"));
                break;
            default:
                break;
            }
        }
    }
    Mesa mesa;

    RenderWindow window(VideoMode(Vector2u(1400, 900)), "Carta");


    RectangleShape borde(Vector2f(1400.f, 900.f));
    borde.setFillColor(Color(128, 64, 0));

    // Diamante (hecho con un círculo deformado)
    CircleShape diamante(20.f, 4); // 4 puntos = rombo
    diamante.setFillColor(Color::Red);
    diamante.setPosition(Vector2f(780.f, 655.f));

    // Letra A en la carta
    Font font;
    // Intenta cargar una fuente del sistema. Ajusta la ruta si es necesario.
    if (!font.openFromFile("C:\\Windows\\Fonts\\times.ttf")) {
        // Si no se pudo cargar, el texto podría no mostrarse; seguir para evitar fallo en compilación
    }
    Text A(font, mesa.mostrarCarta(manoJugador[12]));
    A.setFillColor(Color::Red); // Color
    A.setPosition(Vector2f(755.f, 600.f));


    Text A2(font, mesa.mostrarCarta(manoJugador[12]));
    A2.setFillColor(Color::Red); // Color
    A2.setPosition(Vector2f(843.f, 750.f));
    // Voltear la A para que quede al revés (sf::rotate expects sf::Angle in SFML 3)
    A2.rotate(degrees(180.f));



    // Otro diamante arriba
    CircleShape diamante2 = diamante;
    diamante2.setScale(Vector2f(0.5f, 0.5f));
    diamante2.setPosition(Vector2f(755.f, 630.f));

    // Otro diamante abajo
    CircleShape diamante3 = diamante2;
    diamante3.setPosition(Vector2f(825.f, 700.f));

    while (window.isOpen()) {
        while (const optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.draw(borde);
        window.draw(mesa);
        window.draw(manoJugador[12]);
        window.draw(diamante);
        window.draw(diamante2);
        window.draw(diamante3);
        window.draw(A);
        window.draw(A2);
        window.display();
    }

    return 0;
}