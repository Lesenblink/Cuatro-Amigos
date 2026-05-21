#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
// CLASE CARTA: Define cómo se ven y se comportan las cartas
class Carta : public Drawable, public Transformable {
private:
    Color color;
    string valor;
    string valor2;
    bool enJuego;
    const Font* font;
    const Font* font2;
    bool hitBox; // Variable para hacer validaciones con la hitbox
    Text numero;
    Text numeroAbajo;// para mostrar el número 
    RectangleShape forma; // El cuerpo de la carta
    RectangleShape cartaReves; // La parte de atrás de la carta.
    RectangleShape marcoInterior; //Marco interior para el reves de la carta
    ConvexShape simbolo;  // El rombo o figura de la baraja
    CircleShape hoja1, hoja2, hoja3;
    RectangleShape tallo;

    void crearFrente();   //Decidimos separar la lógica del constructor en funciones privadas
    void crearReverso();
    void crearSimbolo();
    void configurarTexto();


    // Esta función le dice a la ventana qué orden seguir para dibujar la carta. Estoy aquí redefiniendo la función draw de la clase Drawable
    virtual void draw(RenderTarget& target, RenderStates states) const override;
public:
    Carta(Color color, string valor, const sf::Font* font, const Font* font2, string valor2);
    int getValor(); // Retorna el valor numérico de la carta (J=11, Q=12, K=13, A=14)
    FloatRect getGlobalBounds() const; // Retorna el área que ocupa la carta en pantalla (para detectar clicks)
    Vector2f getPos() const; //Función para tener la posición de la carta
    void voltear(); // Voltea la carta para mostrar el frente
    void aparecerAlreves(); //Funcion para aparecer la carta alreves
    bool getHItBox() const; //Función para obtener el valor de la hitbox
    void setHitBox(bool valor); //Función para establecer el valor de la hitbox
};