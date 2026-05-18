#include "Luigui.h"
#include "Mesa.h"
#include "Carta.h"
void Luigui::recibirBaraja(vector<vector<Carta>> cartasdeMesa) {
    cartas = cartasdeMesa;
    cout << "Se recibio con exito";
}
void Luigui::mesclarBaraja() {
    vector<Carta> temporal; //Creamos un vector temporal porque si uticisamos la matriz solo va barajear las filas pero no las cartas de cada fila
    for (const auto& fila : cartas) {  //For por rango que fila tiene 0 elemntos hasta los elemntos del vector de vectores de cartas
        temporal.insert(temporal.end(), fila.begin(), fila.end()); //Agregamos a la matriz temporal primero la posicon, desde donde copiar y hasta donde termianr de copiar
    }
    shuffle(temporal.begin(), temporal.end(), aleatorio);    //La funcion reorganiza el ultimo elemento

    int llenarMatriz = 0;
    for (auto& fila : cartas) {  //Aquí se recorremos cada fila en cartas
        for (Carta& cartita : fila) {  //Recorremos cada carta de las filas
            cartita = temporal[llenarMatriz]; //La carta mezclada la pone en la matriz
            llenarMatriz++;//Sumamos uno para la posicon de la matriz
        }
    }
}
vector<vector<Carta>> Luigui::darCartasBarajeadas() {
    vector<vector<Carta>> totales = cartas;
    cartas.clear();
    return totales;
}