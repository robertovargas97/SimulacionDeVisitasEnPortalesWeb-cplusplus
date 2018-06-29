/* 
 * File:   Digrafo.h
 * Author: alan.calderon
 *
 * Created on 1 de septiembre de 2016, 06:49 PM
 */

#ifndef Digrafo_H
#define Digrafo_H

#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <math.h>



using namespace std;

#include "DigrafoGnr.h"
#include "Portal.h"

class Digrafo {
    // Representa la red de portales sobre la cual se simulará el "rankeo".
    // Los portales están representados por los vértices (Vrt) del digrafo.
    // Los enlaces entre los portales están representados por los arcos dirigidos
    // o adyacencias (Ady).

public:

    /* CONSTRUCTORES */
    // REQ: cantidadVrt > 0. En este caso, N es igual a cantidadVrt.
    // Construye un Digrafo siguiendo el algoritmo de Barabási-Albert para redes de
    // "escala libre" siguiendo el algoritmo de "conexión preferencial" (o 
    // "preferential attachment".
    // Ver:https://en.wikipedia.org/wiki/Barab%C3%A1si%E2%80%93Albert_model
    // NOTA#1: los pesos siempre deben ser valores entre 0 y 1.
    // BOTA#2: para el cálculo de los pesos se toman en cuenta tanto arcos entrantes como salientes.
    Digrafo(int cantidadVrt);

    // REQ: cantidadVrt > 0. En este caso, N es igual a cantidadVrt.
    // REQ: 0 < probabilidadAdy < 1.
    // Construye un digrafo con cantidadVrt de vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando probabilidadAdy. Esto
    // implica que la probabilidad de que un arco exista entre cualesquiera dos
    // dos vértices es igual a probabilidadAdy
    Digrafo(int cantidadVrt, double probabilidadAdy);

    // Construye una copia idéntica a orig.
    Digrafo(const Digrafo& orig);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas o blancos.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices tienen un índice que va de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    Digrafo(ifstream& archivo);

    ~Digrafo();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= vrt < N.
    bool xstVrt(int vrt) const;

    // REQ: 0 <= vrtO < N && 0 <= vrtD < N.
    // EFE: retorna true si existe un arco desde el vértice con índice vrtO hacia vrtD.
    bool xstAdy(int vrtO, int vrtD) const;

    // REQ: 0 <= vrt < N.
    // EFE: retorna un vector de enteros con los índices de los vértices
    //      adyacentes al vértice indicado por el índice vrt.
    vector<int> obtAdy(int vrt) const;

    // EFE: retorna el total de vértices en *this.
    int obtTotVrt() const;

    // EFE: retorna el total de adyacencias o arcos en *this.
    int obtTotAdy() const;

    // REQ: 0 <= vrt < N.
    // EFE: retorna el total de adyacencias del vértice vrt.
    int obtTotAdy(int vrt) const;

    // EFE: retorna el promedio simple de adyacencias por nodo.
    double obtPrmAdy() const;

    // REQ: 0 <= vrt < N.
    // EFE: retorna el "rankeo" del vértice con índice vrt.
    double obtRankeo(int vrt) const;

    // REQ: 0 <= vrt < N.
    // EFE: retorna el "rankeo nuevo" del vértice con índice vrt.
    double obtRankeoNuevo(int vrt) const;

    // REQ: 0 <= vrt < N.
    // EFE: retorna la cantidad de visitas recibidas por el vértice con índice vrt.
    int obtVisitas(int vrt) const;

    // EFE: retorna la sumatoria de los rankeos de los vértices del digrafo.
    double totRankeo() const;

    /* MÉTODOS OBSERVADORES ESPECIALES */

    // REQ: 0 <= vrt < N.
    // EFE: retorna el "local clustering coefficient" o coeficiente local de agrupamiento
    //      para el vértice indicado por vrt.
    // La definición que aparece en: http://en.wikipedia.org/wiki/Clustering_coefficient
    // Se adapta de la siguiente forma:
    // 1. son vecinos del vértice vrt sólo los vértices que tienen un arco de 
    //    salida hacia vrt, se agrega vrt como parte del vecindario. (V)
    // 2. al contar los arcos efectivos, se incluyen todos los arcos entre los 
    //    vértices vecinos. (E)
    // 3. el coeficiente se calcula como E / (V*(V-1))
    double coeficienteAgrupamiento(int vrt) const;

    // EFE: retorna true si la sumatoria del coeficienteAgrupamiento del 20% de
    //      los vértices con coeficiente más alto es mayor o igual a la sumatoria del
    //      coeficienteAgrupamiento del 80% de los vértices con coeficiente más
    //      bajo.
    // NOTA: se basa en el principio de Paretto: https://en.wikipedia.org/wiki/Pareto_principle
    bool conformidadPareto() const;

    /* MÉTODOS MODIFICADORES SIMPLES */

    // REQ: 0 <= vrt < N.
    // MOD: *this.
    // EFE: cambia el "rankeo" del vértice cuyo índice es vrt a nRankeo.
    void modRankeo(int vrt, double nRankeo);

    // REQ: 0 <= vrt < N.
    // MOD: *this.
    // EFE: cambia el "rankeo nuevo" del vértice cuyo índice es vrt a nRankeo.
    void modRankeoNuevo(int vrt, double nRankeo);

    // REQ: 0 <= vrt < N.
    // MOD: *this.
    // EFE: incrementa el valor de las visitas del vértice con índice vrt.
    void incVisitas(int vrt);

private:

    DigrafoGnr < Portal > digrafoPortales;

};

#endif /* Digrafo_H */

