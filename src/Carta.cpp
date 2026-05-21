#include "Carta.h"
#include <iostream>

using namespace sf;
using namespace std;
//Private 
void Carta::crearFrente() {
    forma.setSize(Vector2f(80.f, 130.f));  // Configuramos el cuerpo de la carta 
    forma.setFillColor(Color::White);
    forma.setOutlineColor(Color::Black);
    forma.setOutlineThickness(3.f);
    forma.setOrigin(Vector2f(40.f, 65.f));
    forma.setPosition(Vector2f(0.f, 0.f));
    setOrigin(Vector2f(40.f, 65.f));
}

void Carta::crearReverso() {
    numero.setFont(*font);
    cartaReves.setSize(Vector2f(80.f, 130.f));  // Configuramos el cuerpo de la carta. El diseño de al reves 
    cartaReves.setFillColor(Color(30, 50, 180));
    cartaReves.setOutlineThickness(3.f);
    cartaReves.setOutlineColor(Color::White);
    cartaReves.setOrigin(Vector2f(40.f, 65.f));
    cartaReves.setPosition(Vector2f(0.f, 0.f));
    numeroAbajo.setFont(*font2);
    marcoInterior.setSize(Vector2f(64.f, 114.f));
    marcoInterior.setFillColor(Color(20, 30, 120));
    marcoInterior.setOutlineThickness(2.f);
    marcoInterior.setOrigin(Vector2f(32.f, 57.f));
    marcoInterior.setPosition(Vector2f(0.f, 0.f));
   

    if (color == Color::Red) {  //Colroes de los bordes 
        marcoInterior.setOutlineColor(Color::Red);
    }
    else if (color == Color::Black) {
        marcoInterior.setOutlineColor(Color::Black);
    }
    else if (color == Color::Blue) {
        marcoInterior.setOutlineColor(Color::Blue);
    }
    else {
        marcoInterior.setOutlineColor(Color::Green);
    }
}
void Carta::crearSimbolo() {
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
        float r = 12.f; // radio de cada hoja

        // Hoja superior
        hoja1.setRadius(r);
        hoja1.setOrigin(Vector2f(r, r));
        hoja1.setPosition(Vector2f(0.f, -10.f));
        hoja1.setFillColor(Color::Black);

        // Hoja izquierda
        hoja2.setRadius(r);
        hoja2.setOrigin(Vector2f(r, r));
        hoja2.setPosition(Vector2f(-11.f, 4.f));
        hoja2.setFillColor(Color::Black);

        // Hoja derecha
        hoja3.setRadius(r);
        hoja3.setOrigin(Vector2f(r, r));
        hoja3.setPosition(Vector2f(11.f, 4.f));
        hoja3.setFillColor(Color::Black);

        // Tallo
        tallo.setSize(Vector2f(5.f, 18.f));
        tallo.setOrigin(Vector2f(2.5f, 0.f));
        tallo.setPosition(Vector2f(0.f, 10.f));
        tallo.setFillColor(Color::Black);
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
        //1. Usamos 4 puntos para definir la forma de diamante
        simbolo.setPoint(0, Vector2f(0.f, -40.f));
        //2. El orden de los puntos es importante para que se dibuje correctamente
        simbolo.setPoint(1, Vector2f(30.f, 0.f));
        //3. El punto 2 es la punta inferior del diamante
        simbolo.setPoint(2, Vector2f(0.f, 40.f));
        //4. El punto 3 es la punta izquierda del diamante
        simbolo.setPoint(3, Vector2f(-30.f, 0.f));
    }

    simbolo.setFillColor(color);

    FloatRect bounds = simbolo.getLocalBounds(); // Calcula el área local del símbolo para centrar su origen
    simbolo.setOrigin(Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f)); // Establece el origen en el centro del símbolo para que rote y escale correctamente
    simbolo.setPosition(Vector2f(30.f, 35.f)); // Posiciona el símbolo en el centro de la carta

}
void Carta::configurarTexto() {
    numero.setCharacterSize(15);   // Configuramos el texto del número
    numero.setFillColor(color);
    numero.setPosition(Vector2f(-35.f, -60.f));
    numeroAbajo.setCharacterSize(15);   // Configuramos el texto del número de abajo
    numeroAbajo.setFillColor(color);
    numeroAbajo.setPosition(Vector2f(25.f, 45.f)); // Gira el número para que se vea al revés
}


// Esta función le dice a la ventana qué orden seguir para dibujar la carta. Estoy aquí redefiniendo la función draw de la clase Drawable
void Carta::draw(RenderTarget& target, RenderStates states) const {
    if (enJuego == true) {
        states.transform *= getTransform();
        target.draw(forma, states);
        target.draw(numero, states);
        target.draw(numeroAbajo, states);

        if (color == Color::Black) {
            // Dibujar trébol con círculos
            target.draw(hoja1, states);
            target.draw(hoja2, states);
            target.draw(hoja3, states);
            target.draw(tallo, states);
        }
        else {
            target.draw(simbolo, states);
        }
    }
    else {
        states.transform *= getTransform();
        target.draw(cartaReves, states);
        target.draw(marcoInterior, states);
    }
}


//Public
Carta::Carta(Color color, string valor, const sf::Font* font, const Font* font2, string valor2) : enJuego(true), color(color), valor(valor), font(font), font2(font2), numero(*font, valor), numeroAbajo(*font2, valor2) {
    crearFrente();
    crearReverso();
    numero.setFont(*font);
    numero.setString(valor);

    numeroAbajo.setFont(*font2);
    numeroAbajo.setString(valor2);
    crearSimbolo();
    configurarTexto();
    setPosition(Vector2f(850.f, 420.f));  //Posición inicial

}
int Carta::getValor() {

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
FloatRect Carta::getGlobalBounds() const {
    FloatRect local = forma.getLocalBounds();
    local.position -= Vector2f(40.f, 65.f);  // compensar el origen
    return getTransform().transformRect(local);
}
Vector2f Carta::getPos() const { return Transformable::getPosition(); } //Función para tener la posición de la carta
void Carta::voltear() {
    enJuego = true;
}
void Carta::aparecerAlreves() { //Funcion para aparecer la carta alreves
    enJuego = false;

}
bool Carta::getHItBox() const { //Función para obtener el valor de la hitbox
    return hitBox;
}
void Carta::setHitBox(bool valor) { //Función para establecer el valor de la hitbox
    hitBox = valor;
}

