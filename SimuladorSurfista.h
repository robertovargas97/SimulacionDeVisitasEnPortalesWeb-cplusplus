/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimuladorSurfista.h
 * Author: Alan
 *
 * Created on 1 de septiembre de 2017, 01:58 PM
 */

#include "Digrafo.h"

#ifndef SIMULADORSURFISTA_H
#define SIMULADORSURFISTA_H

#include <vector>
using namespace std;

#include "Surfista.h"

class SimuladorSurfista {
    // Representa el proceso de simulación de la navegación de los ciber-surfistas 
    // en la red de portales.

public:

    // EFE: Construye un simulador que transformará el "rankeo" de los vértices
    // del grafo g mediante la dispersión del rankeo.
    SimuladorSurfista(Digrafo& redPortales);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~SimuladorSurfista();

    // REQ: cantidadSurfistas > 0 && cantidadIteraciones > 0.
    // MOD: inicializa a *this y conjunto de surfistas, ubicándolos en algún portal
    //      al azar.
    // EFE: inicializa el estado del simulador.
    void inicializar(double dampingFactor, int cantidadSurfistas, int cantidadIteraciones);

    // REQ: *this haya sido correctamente inicializado.
    // MOD: el "rankeo" de los vértices del grafo asociado.
    // EFE: calcula durante cantidadIteraciones el "rankeo" de cada vértice
    //      mediante el algoritmo del surfista.  
    void simular();

    // REQ: *this haya sido correctamente inicializado.
    // MOD: el "rankeo" de los vértices del grafo asociado.
    // EFE: ejecuta una iteración de la simulación recalculando los rankeos
    //      mediante el algoritmo del surfista aleatorio.
    void simularUnTic();

private:

    //EFE: retorna el numero total de visitas presentes en la Red
    double totalVisitasRed();

    // arreglo de surfistas:
    vector< Surfista > vectorSurfistas;

    Digrafo& redPortales;
    double dampingFactor;
    int cantidadIteraciones;
    int cantidadSurfistas;
};

#endif /* SIMULADORSURFISTA_H */

/* ALGORITMO DEL SURFISTA ALEATORIO
 * INICIALIZACIÓN: el rankeo actual se inicializa igual a 1 / N (N cantidad de vértices)
 * 1. Se incrementa en uno la cantidad de visitas en los portales en que se encuentra
 *    un surfista.
 * 2. mover surfistas:
 * 2.1 Si el surfista está en un portal que no tiene adyacencias salta al azar
 *     hacia cualquier otro en la red.
 * 2.2 Si el surfista está en un portal que sí tiene adyacencias:
 * 2.2.1 Se genera un número al azar entre 0 y 1.
 * 2.2.2 Si el número generado es menor que el dampingFactor, salta al azar
 *       hacia cualquier otro portal en la red.
 *       De lo contrario, salta al azar hacia cualquier portal adyacente o 
 *       enlazado con el actual portal en que se encuentra.
 * 3. calcular rankeo nuevo con base en las visitas:
 * 3.1 rankeo nuevo = visitas / total de visitas en la red
 * NOTA: el rankeo actual se actualiza para todos los portales a la vez sólo cuando
 *       se haya terminado de calcular el rankeo nuevo para todos.
 */