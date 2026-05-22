#include "Mesa.h"
#include "Luigui.h"
/* Privado */
void Mesa::crearMazo(const sf::Font& font, const Font& font2) {

    Color colores[] = { Color::Red, Color::Green, Color::Black, Color::Blue };
    string especiales[] = { "J", "Q", "K", "A" };

    // Bucle para crear el mazo completo 
    for (int j = 0; j < 4; j++) {
        vector<Carta> pinta;
        for (int i = 2; i <= 14; i++) {
            // Si el número es mayor a 10, usa las letras (J, Q, K, A)
            string v = (i <= 10) ? to_string(i) : especiales[i - 11];
            string u = v;
            Carta carta(colores[j], v, &font, &font2, u);
            carta.voltear("a");//para que aparezca al revez
            pinta.push_back(carta);//Agrega la carta al vector temporal de esa fila
        }
        cartasTotales.push_back(pinta);

    }

    cout<<"se creo el mazo"<<endl;

}
void Mesa::estatica() {
    setFillColor(Color(0, 80, 0));
    setPosition(Vector2f(50.f, 50.f));
    borde.setFillColor(Color(128, 64, 0));

    cout << "se creo el borde"<<endl;

}
//Publico

Mesa::Mesa(const sf::Font& font, const Font& font2) : RectangleShape(Vector2f(1700.f, 950.f)), borde(Vector2f(1800.f, 1050.f)) {
    estatica();
    crearMazo(font, font2);

    cout << "se creo la mesa"<<endl;
}
vector<vector<Carta>> Mesa::darTodasLasCartas() {
    vector<vector<Carta>> todas = cartasTotales;
    cartasTotales.clear();
    return todas;
}
void Mesa::recibirCartasBarajeadas(Luigui& mario) {
    cartasTotales = mario.darCartasBarajeadas();
    cout << "se recibieron las cartas barajeadas";
}
Carta Mesa::darCarta() {
    //Este for se adapta al tamaño del vector, el -1 es porque los vectores inician desde 0.
    //Recorre hasta i>=0  y se reduce hasta llegar a 0.
    for (int i = cartasTotales.size() - 1; i >= 0; i--) {
        if (!cartasTotales[i].empty()) {          //Si en esa fila no hay objetos entonces para el siguiente ciclo va  a la otra fila
            Carta carta = cartasTotales[i].back();  //Se tiene que llenar la memoria con este objeto porque con apuntador no funciona |_|
            cartasTotales[i].pop_back();   //Y de hecho, al utilizar apuntadores se borra el objeto :(
            return carta; //Regresa la copia guardada del objeto eliminado
        }
    }
    throw runtime_error("No hay cartas disponibles");

    cout << "se dieron todas las cartas";
}
Carta& Mesa::getCarta() {
    //Este for se adapta al tamaño del vector, el -1 es porque los vectores inician desde 0.
   //Recorre hasta i>=0  y se reduce hasta llegar a 0.
    for (int i = cartasTotales.size() - 1; i >= 0; i--) {
        if (!cartasTotales[i].empty()) {
            return cartasTotales[i].back();
        }
    }
    throw runtime_error("No hay cartas en el mazo");

    cout << "se tomo una carta";
}
int Mesa::tamanoCartasTotales() {      //Función para saber cuantas cartas hay en total en la mesa
    int totalDeCartas = 0; //Variable temporal
    for (const auto& fila : cartasTotales) {  //Como es un vector de vectores, entonces sumamos a la variable temporal el tamaño de cada fila en cada ciclo
        totalDeCartas += fila.size();
    }
    return totalDeCartas; // Regresamos el resultado del for 

	cout << "se obtuvo el tamaño de las cartas totales" << endl;
}
RectangleShape& Mesa::getBorde() { return borde; }

void Mesa::llenarBuche(Carta carta) {
    carta.voltear();                          // Voltear para que se vea el frente
    carta.setRotation(sf::degrees(0.f));      // Quitar rotación
    carta.setPosition(Vector2f(750.f, 600.f));
    bucheDeCartas.push_back(carta);

	cout << "se lleno el buche" << endl;
}
Carta& Mesa::getBuche() {  //Obtemenos la carta del buche 
    return bucheDeCartas.back();
}
int Mesa::tamanoDelBuche() {  //Tamaño del buche
    return bucheDeCartas.size();
}
Carta Mesa::darCartaDelBuche() {  //Función para comer la carta del buche
    if (bucheDeCartas.empty()) {
        throw std::runtime_error("Buche vacio");
    }
    else {
   
            if (!bucheDeCartas.empty()) {
                Carta carta = bucheDeCartas.back(); // Guarda la última carta del buche antes de eliminarla
                bucheDeCartas.pop_back(); // Elimina la carta del buche
                return carta; // Regresa la copia guardada del objeto eliminado
            }
        
    }

	cout << "se dio una carta del buche" << endl;
}
int Mesa::valorDeCartaBuche(int a) { //Obtenemos el valor de la ultima carta 
    return bucheDeCartas[a].getValor();
}
void Mesa::limpiarBuche() {
    bucheDeCartas.clear(); //Limpiamos el vector 
}
Carta& Mesa::getCartaBuche(int i) {
    return bucheDeCartas[i];
}