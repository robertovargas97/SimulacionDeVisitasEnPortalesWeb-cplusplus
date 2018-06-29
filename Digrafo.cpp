/* 
 * File:   Digrafo.cpp
 * Author: Alan
 * 
 * Created on 2 de abril de 2015, 02:25 PM
 */

#include "Digrafo.h"

Digrafo::Digrafo(int N) : digrafoPortales(N) {

}

Digrafo::Digrafo(const Digrafo& orig) : digrafoPortales(orig.digrafoPortales) {

}

Digrafo::Digrafo(int cantidadVrt, double probabilidadAdy) : digrafoPortales(cantidadVrt, probabilidadAdy) {
}

Digrafo::Digrafo(ifstream& archivo) : digrafoPortales(archivo) {

}

Digrafo::~Digrafo() {
}

bool Digrafo::xstVrt(int vrt) const {
    bool existe = true;
    if ((0 <= vrt)&& (vrt > digrafoPortales.obtTotVrt())) {
        existe = false; //vrt no existe
    }
    return existe;
}

bool Digrafo::xstAdy(int vrtO, int vrtD) const {
    bool existe = false;
    if (digrafoPortales.xstArcSal(vrtO, vrtD)) {
        existe = true;
    }
    return true;
}

vector< int > Digrafo::obtAdy(int vrt) const {
    vector <int> vectorAdyacencias;
    if ((0 <= vrt) && (vrt < digrafoPortales.obtTotVrt())) { //Asegura que exista el vertice vrt
        digrafoPortales.obtIdVrtArcSal(vrt, vectorAdyacencias);
    }
    return vectorAdyacencias; //Retorna ya sea el vector correspondiente con adyacencias o vacio en caso de que no existan adyacencias
}

int Digrafo::obtTotVrt() const {
    return digrafoPortales.obtTotVrt();
}

int Digrafo::obtTotAdy() const {
    return digrafoPortales.obtTotArc();
}

int Digrafo::obtTotAdy(int vrt) const {
    return digrafoPortales.obtTotArcSal(vrt);
}

double Digrafo::obtPrmAdy() const {
    double promedio = 0.0;
    for (int i = 0; i < digrafoPortales.obtTotVrt(); ++i) { //Recorre las adyacencias
        promedio += digrafoPortales.obtTotArcSal(i); //Acumula las adyacencia en promedio
    }
    promedio /= obtTotVrt();
    return promedio;
}

double Digrafo::obtRankeo(int vrt) const {
    return digrafoPortales[vrt].obtRankeo();
}

double Digrafo::obtRankeoNuevo(int vrt) const {
    return digrafoPortales[vrt].obtNuevoRankeo();
}

int Digrafo::obtVisitas(int vrt) const {
    return digrafoPortales[vrt].obtVisitas();
}

double Digrafo::coeficienteAgrupamiento(int vrt) const {
    return digrafoPortales.coeficienteAgrupamiento(vrt);
}

bool Digrafo::conformidadPareto() const {
    bool result = false;
    double total = 0.0, veinte = 0.0, ochenta = 0.0, veintePorc = 0.0, ochentaPorc = 0.0;
    vector<double> arr;
    int veinteInt = 0;
    //Se procede a conocer y almacenar cada uno de los coeficientes de agrupamiento de los vectores
    for (int i = 0; i < digrafoPortales.obtTotVrt(); ++i) {
        double temp = coeficienteAgrupamiento(i);
        //printf("coefAgr(Nodo %3d) = %0.4f\n", i, temp);
        total += temp;
        arr.push_back(temp);
    }
    //Ahora se procede a un ordenamiento de menor a mayor
    for (int a = arr.size() - 1; a >= 0; --a) {
        double menor = arr[a];
        int lastIndex = a;
        for (int b = a; b >= 0; --b) {
            if (menor > arr[b] && a != b) {
                menor = arr[b];
                lastIndex = b;
            }
        }
        arr.erase(arr.begin() + lastIndex);
        arr.push_back(menor);
    }


    veinteInt = (int) ceil(digrafoPortales.obtTotVrt() * 0.20); //cantidad de nodos que representa el 20% del total de nodos
    //Esta parte se encarga de ver el peso que tiene el 20% de los vertices de mayor peso
    for (int i = digrafoPortales.obtTotVrt() - 1; i >= digrafoPortales.obtTotVrt() - veinteInt; --i) {
        veinte += arr[i];
    }
    ochenta = total - veinte;
    //Ahora vemos si el 20% de los coeficientes mas grandes representas mas del 80% del total
    veintePorc = (double) ((veinte / total)*100);
    ochentaPorc = (double) ((ochenta / total)*100);
    if (veintePorc >= ochentaPorc) {
        result = true;
    }
    return result;
}

void Digrafo::modRankeo(int vrt, double nRankeo) {
    digrafoPortales[vrt].modRankeo(nRankeo);
}

void Digrafo::modRankeoNuevo(int vrt, double nRankeo) {
    digrafoPortales[vrt].modNuevoRankeo(nRankeo);
}

void Digrafo::incVisitas(int vrt) {
    digrafoPortales[vrt].modVisitas(digrafoPortales[vrt].obtVisitas() + 1);
}

double Digrafo::totRankeo() const {
    double totalRankeo = 0.0;
    for (int i = 0; i < digrafoPortales.obtTotVrt(); i++) {
        totalRankeo = totalRankeo + digrafoPortales[i].obtRankeo();
    }
    return totalRankeo;
}