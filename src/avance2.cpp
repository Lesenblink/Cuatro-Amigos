#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;
using namespace std;
class Carta {
private:
    string color;
    string valor;
    bool enJuego;
public:
    Carta() : valor(" "), color(" "), enJuego(true) {}
    Carta(string c, string v) : color(c), valor(v) {}

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
class Mesa {
private:
    vector<Carta> cartasEnMesa;
public:
    Mesa() : cartasEnMesa(NULL) {}
    Mesa(Carta& carta) {
        cartasEnMesa.push_back(carta);
    }
    const vector<Carta>& getCartasEnMesa() {
        return cartasEnMesa;
    }
    string mostrarCarta(Carta& carta) {
        string valor = carta.getValor();

        return valor;
    }
};

int main() {
    Carta carta1("rojo", "Q");
    Mesa table;

    RenderWindow window(VideoMode(Vector2u(1400, 900)), "Carta");

    // Carta (rectángulo)
    RectangleShape carta(Vector2f(100.f, 150.f));
    carta.setFillColor(Color::White);
    carta.setOutlineColor(Color::Black);
    carta.setOutlineThickness(4.f);
    carta.setPosition(Vector2f(750.f, 600.f));

    //borde de la mesa
    RectangleShape borde(Vector2f(1400.f, 900.f));
    borde.setFillColor(Color(128, 64, 0)); // Color del borde

    //mesa
    RectangleShape mesa(Vector2f(1300.f, 800.f));
    mesa.setFillColor(Color(0, 80, 0)); // Color del borde
    mesa.setPosition(Vector2f(50.f, 50.f));


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
    Text A(font, table.mostrarCarta(carta1));
    A.setFillColor(Color::Red); // Color
    A.setPosition(Vector2f(755.f, 600.f));


    Text A2(font, table.mostrarCarta(carta1));
    A2.setFillColor(Color::Red); // Color
    A2.setPosition(Vector2f(843.f, 750.f));
    // Voltear la A para que quede al revés (sf::rotate expects sf::Angle in SFML 3)
    A2.rotate(sf::degrees(180.f));



    // Otro diamante arriba
    sf::CircleShape diamante2 = diamante;
    diamante2.setScale(sf::Vector2f(0.5f, 0.5f));
    diamante2.setPosition(sf::Vector2f(755.f, 630.f));

    // Otro diamante abajo
    sf::CircleShape diamante3 = diamante2;
    diamante3.setPosition(sf::Vector2f(825.f, 700.f));

    while (window.isOpen()) {
        while (const std::optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.draw(borde);
        window.draw(mesa);
        window.draw(carta);
        window.draw(diamante);
        window.draw(diamante2);
        window.draw(diamante3);
        window.draw(A);
        window.draw(A2);
        window.display();
    }

    return 0;
}