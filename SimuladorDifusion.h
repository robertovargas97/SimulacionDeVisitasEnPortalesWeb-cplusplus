/* 
 * File:   SimuladorDifusion.h
 * Author: Alan
 *
 * Created on 1 de setiembre de 2017, 12:44 PM
 */

#ifndef SIMULADORDIFUSION_H
#define	SIMULADORDIFUSION_H

#include <memory>
using namespace std;

#include "Digrafo.h"

class SimuladorDifusion {
    // Representa el proceso de simulación de la difusión del "rankeo" en la
    // red de portales.
    
public:
    
    // EFE: Construye un simulador que transformará el "rankeo" de los vértices
    // del grafo g mediante la difusión del rankeo.
    SimuladorDifusion(Digrafo& redPortales);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~SimuladorDifusion();


    // REQ: 0 <= dampingFactor <= 1 && cantidadIteraciones > 0.
    // MOD: *this.    
    // EFE: inicializa el estado del simulador.
    void inicializar(double dampingFactor, int cantidadIteraciones);
    
    // REQ: *this haya sido correctamente inicializado.
    // MOD: el "rankeo" de los vértices del grafo asociado.
    // EFE: calcula durante cantidadIteraciones el "rankeo" de cada vértice
    //      mediante el algoritmo de "rankeo".  
    void simular();
    
    // REQ: *this haya sido correctamente inicializado.
    // MOD: el "rankeo" de los vértices del grafo asociado.
    // EFE: ejecuta una iteración de la simulación recalculando los rankeos
    //      mediante el algoritmo de difusión del ranqueo.
    void simularUnTic();

private:
    Digrafo& redPortales;
    double dampingFactor;
    int cantidadIteraciones;
};

#endif	/* SIMULADORDIFUSION_H */

/* ALGORITMO DE DIFUSIÓN DEL RANKEO:
 * INICIALIZACIÓN: el rankeo actual se inicializa igual a 1 / N (N cantidad de vértices)
 * 1. para cada vértice distribuir el rankeo actual: 
 * 1.1 Se distribuye equitativamente el rankeo actual propio entre sus adyacentes
 *     sumándolo al rankeo actual y guardándolo en el rankeo nuevo.
 * 1.2 Si un vértice no tiene adyacentes, distribuye su rankeo actual equitativamente
 *     entre todos los demás vértices de la red de forma similar.
 * 2. calcular rankeo nuevo aplicando el dampingFactor:
 * 2.1 rankeo nuevo = (1 - dampingFactor) / cantidad de portales + dampingFactor * rankeo nuevo.
 * NOTA: el rankeo actual se actualiza para todos los portales a la vez sólo cuando
 *       se haya terminado de calcular el rankeo nuevo para todos.
 */