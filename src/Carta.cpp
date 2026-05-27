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

    cout << "se creo el frente de las cartas"<<endl;
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
	cout << "se creo el reverso y el marco de las cartas" << endl;
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

        hoja1.setRadius(r);
        hoja1.setOrigin(Vector2f(r, r));
        hoja1.setPosition(Vector2f(40.f, 87.f));
        hoja1.setFillColor(Color::Black);

        hoja2.setRadius(r);
        hoja2.setOrigin(Vector2f(r, r));
        hoja2.setPosition(Vector2f(50.f, 69.f));
        hoja2.setFillColor(Color::Black);

        hoja3.setRadius(r);
        hoja3.setOrigin(Vector2f(r, r));
        hoja3.setPosition(Vector2f(60.f, 87.f));
        hoja3.setFillColor(Color::Black);

        tallo.setSize(Vector2f(6.f, 30.f));
        tallo.setOrigin(Vector2f(3.f, 0.f));
        tallo.setPosition(Vector2f(50.f, 78.f));
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
        simbolo.setPointCount(4);
        //1. Usamos 4 puntos para definir la forma de diamante
        simbolo.setPoint(0, Vector2f(0.f, -40.f));
        //2. El orden de los puntos es importante para que se dibuje correctamente
        simbolo.setPoint(1, Vector2f(30.f, 0.f));
        //3. El punto 2 es la punta inferior del diamante
        simbolo.setPoint(2, Vector2f(0.f, 40.f));
        //4. El punto 3 es la punta izquierda del diamante
>>>>>>> 0cb4faacb84d8c46680c17aef0860b37bf9a8e78
        simbolo.setPoint(3, Vector2f(-30.f, 0.f));
    }

    simbolo.setFillColor(color);

    FloatRect bounds = simbolo.getLocalBounds();
    simbolo.setOrigin(Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    simbolo.setPosition(Vector2f(90.f, 125.f));
    if(color==Color::Red)
        simbolo.setPosition(Vector2f(85.f, 90.f));
    if (color == Color::Green)
        simbolo.setPosition(Vector2f(85.f, 110.f));
    if (color == Color::Blue)
        simbolo.setPosition(Vector2f(82.f, 100.f));

	cout << "se creo el simbolo de las cartas" << endl;
}
void Carta::configurarTexto() {
	numero.setCharacterSize(20);   // Configuramos el texto del número
	numero.setFillColor(color);
	numero.setPosition(Vector2f(5.f, 5.f));
	numeroAbajo.setCharacterSize(20);   // Configuramos el texto del número de abajo
    numeroAbajo.setFillColor(color);
    numero.setCharacterSize(20);   // Configuramos el texto del número
    numero.setFillColor(color);
    numero.setPosition(Vector2f(5.f, 5.f));
    numeroAbajo.setCharacterSize(20);   // Configuramos el texto del número de abajo
    numeroAbajo.setFillColor(color);

    numeroAbajo.setPosition(Vector2f(80.f, 110.f)); // Gira el número para que se vea al revés
}


// Esta función le dice a la ventana qué orden seguir para dibujar la carta. Estoy aquí redefiniendo la función draw de la clase Drawable
 void Carta::draw(RenderTarget& target, RenderStates states) const  {
void Carta::draw(RenderTarget& target, RenderStates states) const {
    if (enJuego == true) {
        states.transform *= getTransform(); // Aplica movimiento y rotación
        target.draw(forma, states);         // 1. Dibuja el fondo
        target.draw(numero, states);            // 2. Dibuja el número arriba
        target.draw(numeroAbajo, states);        // 3. Dibuja el número arriba
        target.draw(simbolo, states);       // 4. Dibuja el símbolo

        if(encadenada ==true){
            target.draw(bordemorado, states);
        }
           

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
    else if (enJuego == false) {
        states.transform *= getTransform();  //Aplica movimiento y rotación
        target.draw(cartaReves, states); //1. Dibuja el fondo del reverso de la carta

        target.draw(marcoInterior, states); //2. Dibuja el marco interior del reverso de la carta
    }

    static bool yaImprimio = false;
    if (!yaImprimio) {
        cout << "se dibujaron las cartas" << endl;
        yaImprimio = true;
    }
}


//Public
Carta::Carta(Color color, string valor, const sf::Font* font, const Font* font2, string valor2) : enJuego(true), color(color), valor(valor), font(font), font2(font2), numero(*font, valor), numeroAbajo(*font2, valor2) {
    crearFrente();
    crearReverso();
    numero.setFont(*font);
    numero.setString(valor);
    encadenada = false;
    numeroAbajo.setFont(*font2);
    numeroAbajo.setString(valor2);
    crearSimbolo();
    configurarTexto();
    setPosition(Vector2f(850.f, 420.f));  //Posición inicial
    bordeMorado();
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
    cout << "se volteo la carta" << endl;
}
void Carta::voltear(bool tipo) { //Funcion para aparecer la carta alreves
    enJuego = false;
<<<<<<< HEAD


=======
	cout << "se volteo la carta" << endl;
>>>>>>> 70f5719d16e1a00a49b78eeaf07915e22b276042
}
bool Carta::getHItBox() const { //Función para obtener el valor de la hitbox
    return hitBox;
}
void Carta::setHitBox(bool valor) { //Función para establecer el valor de la hitbox
    hitBox = valor;
}
bool Carta::getEncadenada() { return encadenada; }
void Carta::quitarCadena() { encadenada = false; }
void Carta::ponerCadena() { encadenada = true; }
void Carta::bordeMorado() {
    bordemorado.setSize(Vector2f(108.f, 158.f));
    bordemorado.setFillColor(Color::Transparent);

    bordemorado.setOutlineThickness(5.f);
    bordemorado.setOutlineColor(Color(180, 0, 255));

    // Ajuste para que el borde quede afuera de la carta
    bordemorado.setPosition(Vector2f(-4.f, -4.f));

   
}

