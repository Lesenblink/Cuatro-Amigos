#include "Carta.h"
#include <iostream>

using namespace sf;
using namespace std;
//Private 
void Carta::crearFrente() {
    forma.setSize(Vector2f(100.f, 150.f));  // Configuramos el cuerpo de la carta 
    forma.setFillColor(Color::White);
    forma.setOutlineColor(Color::Black);
    forma.setOutlineThickness(3.f);
}

void Carta::crearReverso() {
    numero.setFont(*font);
    cartaReves.setSize(Vector2f(100.f, 150.f));  // Configuramos el cuerpo de la carta. El diseño de al reves 
    cartaReves.setFillColor(Color(30, 50, 180));
    cartaReves.setOutlineThickness(3.f);
    cartaReves.setOutlineColor(Color::White);
    numeroAbajo.setFont(*font2);
    marcoInterior.setSize(Vector2f(84.f, 134.f));
    marcoInterior.setFillColor(Color(20, 30, 120));
    marcoInterior.setOutlineThickness(2.f);
    marcoInterior.setPosition(Vector2f(8.f, 8.f));

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

    FloatRect bounds = simbolo.getLocalBounds();
    simbolo.setOrigin(Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    simbolo.setPosition(Vector2f(80.f, 115.f));

}
void Carta::configurarTexto() {
	numero.setCharacterSize(20);   // Configuramos el texto del número
	numero.setFillColor(color);
	numero.setPosition(Vector2f(5.f, 5.f));
	numeroAbajo.setCharacterSize(20);   // Configuramos el texto del número de abajo
	numeroAbajo.setFillColor(color);
    numeroAbajo.setPosition(Vector2f(80.f, 110.f)); // Gira el número para que se vea al revés
}


// Esta función le dice a la ventana qué orden seguir para dibujar la carta. Estoy aquí redefiniendo la función draw de la clase Drawable
 void Carta::draw(RenderTarget& target, RenderStates states) const  {
    if (enJuego == true) {
        states.transform *= getTransform(); // Aplica movimiento y rotación
        target.draw(forma, states);         // 1. Dibuja el fondo
        target.draw(numero, states);            // 2. Dibuja el número arriba
        target.draw(numeroAbajo, states);        // 3. Dibuja el número arriba
        target.draw(simbolo, states);       // 4. Dibuja el símbolo
    }
    else if (enJuego == false) {
        states.transform *= getTransform();  //Aplica movimiento y rotación
        target.draw(cartaReves, states); //1. Dibuja el fondo del reverso de la carta

        target.draw(marcoInterior, states); //2. Dibuja el marco interior del reverso de la carta
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
    setPosition(Vector2f(800.f, 300.f));  //Posición inicial
    
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
    return getTransform().transformRect(forma.getGlobalBounds());
}
Vector2f Carta::getPos() const { return Transformable::getPosition(); } //Función para tener la posición de la carta
void Carta::voltear() {
    enJuego = true;
    cout << "Se volteo la carta";
}
void Carta::aparecerAlreves() { //Funcion para aparecer la carta alreves
    enJuego = false;

}