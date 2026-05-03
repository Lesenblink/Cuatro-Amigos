#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;  //Esto es como std::, solo que es de la libreria SFML
using namespace std;


class Carta : public  Drawable, public Transformable {  //Es una clase derivada de la clase de SFML RectangleShape porque permite dibujar desde la clase sus propiedads
private:
    Color color;   //Variable tipo color para el color
    string valor;  //String imporatnte para el valor
    bool enJuego;
    const Font* font;
    Text numero;
    RectangleShape forma;
    ConvexShape simbolo;
    ConvexShape simboloAlreves;
    virtual void draw(RenderTarget& target, RenderStates states) const {
        states.transform *= Transformable::getTransform(); // aplica posición global
        target.draw(forma, states);
        target.draw(numero, states);
        target.draw(simbolo, states);
    }

public:                                                         //V  Se las dimensiopnes de la carta
    Carta() : valor(" "), color(), enJuego(true), numero(*font, " ") {}

    Carta(Color color, string valor, const sf::Font* font) : color(color), valor(valor), font(font), numero(*font, valor) {
        //Practicamente el constructo define los valroes de las cartas y su estructura
        forma.setSize(sf::Vector2f(100.f, 150.f));
        forma.setFillColor(Color::White);
        forma.setOutlineColor(sf::Color::Black);
        forma.setOutlineThickness(3.f);


        // 2. Configurar el texto del valor (Ej: "A" o "10")

        numero.setString(valor);
        numero.setFillColor(color);
        numero.setCharacterSize(25);
        numero.setPosition(Vector2f(5.f, 5.f)); // Posición relativa al cuerpo

        simbolo.setPointCount(4);

        simbolo.setPoint(0, sf::Vector2f(0.f, -40.f));  // arriba
        simbolo.setPoint(1, sf::Vector2f(30.f, 0.f));   // derecha
        simbolo.setPoint(2, sf::Vector2f(0.f, 40.f));   // abajo
        simbolo.setPoint(3, sf::Vector2f(-30.f, 0.f));  // izquierda

        simbolo.setFillColor(color);

        FloatRect bounds = simbolo.getLocalBounds();
        simbolo.setOrigin(Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
        simbolo.setPosition(Vector2f(80.f, 110.f)); // centro de la carta



    }
    void setPosicion(float& x, float& y) {
        forma.setPosition(Vector2f(x, y));
    }


};


class Mesa : public RectangleShape, Font {
private:
    vector<vector<Carta>> cartasTotales;

    RectangleShape borde;

public:
    Mesa() : cartasTotales(NULL), RectangleShape(Vector2(1300.f, 800.f)), borde(Vector2f(1400.f, 900.f)) { //En vez de usar el main. La clase mesa ya imprime la mesa al crear el objeto
        setFillColor(Color(0, 80, 0)); // Color del borde
        setPosition(Vector2f(50.f, 50.f));
        borde.setFillColor(Color(128, 64, 0));

    }
    Mesa(vector<vector<Carta>>& cartas) : cartasTotales(cartas), RectangleShape(Vector2(1300.f, 800.f)), borde(Vector2f(1400.f, 900.f)) {

        setFillColor(Color(0, 80, 0)); // Color del borde
        setPosition(Vector2f(50.f, 50.f));
        borde.setFillColor(Color(128, 64, 0));

    }
    Carta& getCarta(int pinta, int valor) {  //Es un metodo que devuelve una carta, para poder usarlo en el main
        return cartasTotales[pinta][valor];
    }

    RectangleShape getBorde() {
        return borde;
    }
    void ponerCarta(Carta& carta, float x, float y) {
        carta.setPosicion(x, y);
    }

};
vector <vector <Carta> >cartasTotales; // declara un vector de tipo carta      
Color colorcito;


int main() {
    //Aqui por medio de un vector se peude crear de golpe las cartas de la mesa, en este caso de la pinta roja.
    Font font;
    font.openFromFile("C:\\Windows\\Fonts\\arial.ttf");
    for (int j = 0; j < 4;j++) {
        vector<Carta> pinta;
        if (j == 0) colorcito = Color::Red;   //Color de los corazones
        else if (j == 1) colorcito = Color::Green;  //Color de los treboles
        else if (j == 2) colorcito = Color::Black;     //Color de las picas
        else colorcito = Color::Blue;  //Color de los diamantes
        for (int i = 2; i < 15; i++) {//IMPORTANTE: Es un forcito que permite crear un ciclo para crear las 14 cartas 
            if (i < 11) { //Del 2 al 10 son números normales
                string valor = to_string(i); //Transformamos el número 1 a una variable string para inicializar la carta
                pinta.push_back(Carta(colorcito, valor, &font)); //En el vector de la mano, empujamos una variable nueva tipo cara con el constructro con parametros
            }
            else { //Del 11 al 14 son los valores J;Q;J;A
                switch (i)
                {
                case 11:
                    pinta.push_back(Carta(colorcito, "J", &font));
                    break;
                case 12:
                    pinta.push_back(Carta(colorcito, "Q", &font));
                    break;
                case 13:
                    pinta.push_back(Carta(colorcito, "K", &font));
                    break;
                case 14:
                    pinta.push_back(Carta(colorcito, "A", &font));
                    break;
                default:
                    break;
                }
            }
        }
        cartasTotales.push_back(pinta);
    }
    Mesa mesa(cartasTotales);  //Aqui se asignamos las cartas creadas
    Carta carta1 = mesa.getCarta(3, 12);
    carta1.setPosition(sf::Vector2f(760.f, 655.f));

    Carta carta2 = mesa.getCarta(1, 0);
    carta2.setPosition(sf::Vector2f(600.f, 655.f));

    Carta carta3 = mesa.getCarta(0, 11);
    carta3.setPosition(sf::Vector2f(460.f, 655.f));
    RenderWindow window(VideoMode(Vector2u(1400, 900)), "4 amigos");




    while (window.isOpen()) {
        while (const optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.draw(mesa.getBorde());
        window.draw(mesa);
        window.draw(carta1);
        window.draw(carta2);
        window.draw(carta3);
        window.display();

    }

    return 0;
}