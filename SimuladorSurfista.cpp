/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimuladorSurfista.cpp
 * Author: Alan
 * 
 * Created on 1 de septiembre de 2017, 01:58 PM
 */

#include <iostream>
using namespace std;

#include "SimuladorSurfista.h"

SimuladorSurfista::SimuladorSurfista(Digrafo& redPortales) : redPortales(redPortales) {
    srand(time(NULL)); 
}

SimuladorSurfista::~SimuladorSurfista() {
}

//REQ:
//cantidadSurfistas > 0 && cantidadIteraciones > 0.

void SimuladorSurfista::inicializar(double dampingFactor, int cantidadSurfistas, int cantidadIteraciones) {
    this-> dampingFactor = dampingFactor;
    this-> cantidadIteraciones = cantidadIteraciones;
    this-> cantidadSurfistas = cantidadSurfistas;
    vectorSurfistas.resize(cantidadSurfistas);
    double inicio = redPortales.obtTotVrt();
    double inicioR = (1 / inicio);

    for (int i = 0; i < cantidadSurfistas; i++) { //ciclo para asignar un portal al azar a cada surfista del arreglo
        vectorSurfistas[i].asgPortalActual(rand() % redPortales.obtTotVrt());
        // cout << "Posicion del surfista :" << vectorSurfistas[i].obtPortalActual() << endl;
    }

    for (int i = 0; i < redPortales.obtTotVrt(); i++) {
        redPortales.modRankeo(i, inicioR);
    }
}

double SimuladorSurfista::totalVisitasRed() {
    double totalVisitasPortal = 0;
    int numeroDePortales = redPortales.obtTotVrt();
    if (numeroDePortales > 0) {
        for (int i = 0; i < numeroDePortales; ++i) { //Recorre toda la red 
            totalVisitasPortal += redPortales.obtVisitas(i); //Acumula las visita de cada portal
        }
        return totalVisitasPortal;
    } else {
        return 0;
    }
}

void SimuladorSurfista::simular() {
    for (int repeticiones = 0;repeticiones < cantidadIteraciones;repeticiones++){
        simularUnTic();
    }
}

void SimuladorSurfista::simularUnTic() {
    double visitasPortal = 0.0;
    double rankeoNuevo = 0.0;
    double totalDeVisitas = 0.0;
    double aleatorioParaComparacion = 0.0;
    int adyacencia = 0;
    vector<int> adyacenciasDelPortal; //Se usará para poder saltar aleatoriamente con un surfista entre las adyacencias de un portal 

    //------------- Se realiza el algoritmo del Surfista unicamente una vez --------------------------------//

    //Se procede a mover los surfistas
    for (int j = 0; j < cantidadSurfistas; j++) { //Se recorre el arreglo de surfistas

        //Caso en el que no existen adyacencias en el portalActual que se encuentre un surfista
        if (redPortales.obtTotAdy(vectorSurfistas[j].obtPortalActual()) == 0) {
            vectorSurfistas[j].actualizaPortalAnterior(); //Actualiza la posicion del portalAterior para poder asignar un portalActual nuevo
            vectorSurfistas[j].asgPortalActual(rand() % redPortales.obtTotVrt()); //Mueve el surfista a otro portal de la red aleatoriamente actulizando portalActual
            // cout << "EL SURFISTA SE MOVIO DEL PORTAL " << vectorSurfistas[j].obtPortalAnterior() << " AL " << vectorSurfistas[j].obtPortalActual() << endl;
            redPortales.incVisitas(vectorSurfistas[j].obtPortalAnterior()); //Incrementa en uno la cantidad de visitas del portal que visitó un surfista
            // cout << "Se incrementaron las visitas del portal " << vectorSurfistas[j].obtPortalAnterior() << " a : " << redPortales.obtVisitas(vectorSurfistas[j].obtPortalAnterior()) << endl;
        }//Caso en el que si exiten adyacencias en el portal
        else {
            aleatorioParaComparacion = (rand() % (100 + 1)) / 100.0; //Genera un numero aleatorio entre 0 y 1
            // cout << aleatorioParaComparacion << endl;

            if (aleatorioParaComparacion < dampingFactor) {
                vectorSurfistas[j].actualizaPortalAnterior(); //Actualiza la posicion del portalAterior para poder asignar un portalActual nuevo
                vectorSurfistas[j].asgPortalActual(rand() % redPortales.obtTotVrt()); //Mueve el surfista a otro portal de la red aleatoriamente actulizando portalActual
                //   cout << "EL SURFISTA SE MOVIO DEL PORTAL " << vectorSurfistas[j].obtPortalAnterior() << " AL " << vectorSurfistas[j].obtPortalActual() << endl;
                redPortales.incVisitas(vectorSurfistas[j].obtPortalAnterior()); //Incrementa en uno la canttidad de visitas del portal que visitó un surfista
                //  cout << "Se incrementaron las visitas del portal " << vectorSurfistas[j].obtPortalAnterior() << " a : " << redPortales.obtVisitas(vectorSurfistas[j].obtPortalAnterior()) << endl;
            } 
            
            else {
                
                adyacenciasDelPortal = redPortales.obtAdy(vectorSurfistas[j].obtPortalActual()); //Guarda la lista de adyacencias del portalAcual
                adyacencia = (rand() % redPortales.obtTotAdy(vectorSurfistas[j].obtPortalActual())); //Genera un numero aleatorio entre las adyacencias del portalActual
                vectorSurfistas[j].actualizaPortalAnterior(); //Actualiza la posicion del portalAterior para poder asignar un portalActual nuevo
                vectorSurfistas[j].asgPortalActual(adyacenciasDelPortal[adyacencia]); //Mueve los surfistas a otro portal seleccionado aleatoriamente en las adyacencias del portalActual
                // cout << "EL SURFISTA SE MOVIO DEL PORTAL " << vectorSurfistas[j].obtPortalAnterior() << " AL " << vectorSurfistas[j].obtPortalActual() << endl;
                redPortales.incVisitas(vectorSurfistas[j].obtPortalAnterior()); //Incrementa en uno la canttidad de visitas del portal que visitó un surfista
                //  cout << "Se incrementaron las visitas del portal " << vectorSurfistas[j].obtPortalAnterior() << " a : " << redPortales.obtVisitas(vectorSurfistas[j].obtPortalAnterior()) << endl;
                //delete []adyacenciasDelPortal; //Evita fugas de memoria   
            }
        }

        //Se procede a modificar el rankeo del portal que visitó un surfista
        visitasPortal = redPortales.obtVisitas(vectorSurfistas[j].obtPortalAnterior()); //Se obtiene el numero de visitas del portal que visitó un surfista
        // cout << " Visitas del Portal " << vectorSurfistas[j].obtPortalAnterior() << " son : " << visitasPortal << " Las visitas totales de la red son : " << totalVisitasRed() << endl;
        // cout << endl;
        rankeoNuevo = (visitasPortal / totalVisitasRed()); //Rankeo = visitasDelPortal / total de visitas en la red
        redPortales.modRankeoNuevo(vectorSurfistas[j].obtPortalAnterior(), rankeoNuevo); //Asigna un valor al rankeoNuevo del portal que se visitó
        redPortales.modRankeo(vectorSurfistas[j].obtPortalAnterior(), redPortales.obtRankeoNuevo(vectorSurfistas[j].obtPortalAnterior())); //Se modifica el rankeo del portal que se visitó
    }
}