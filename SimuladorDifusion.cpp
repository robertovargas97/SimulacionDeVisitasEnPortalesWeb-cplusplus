/* 
 * File:   SimuladorDifusion.h
 * Author: Alan
 *
 * Created on 1 de setiembre de 2017, 12:44 PM
 */

#include "SimuladorDifusion.h"

SimuladorDifusion::SimuladorDifusion(Digrafo& redPortales) : redPortales(redPortales) {
}

SimuladorDifusion::~SimuladorDifusion() {
}

void SimuladorDifusion::inicializar(double dampingFactor, int cantidadIteraciones) {
    this->dampingFactor = dampingFactor;
    this->cantidadIteraciones = cantidadIteraciones;

    //Ahora se inicializa el rankeo de cada nodo
    for (int i = 0; i < redPortales.obtTotVrt(); ++i) {
        redPortales.modRankeo(i, ((double) 1 / redPortales.obtTotVrt()));
    }
}

void SimuladorDifusion::simular() {

    for (int iteraciones = 0; iteraciones < cantidadIteraciones; ++iteraciones) {
        simularUnTic();
    }
}

void SimuladorDifusion::simularUnTic() { //Un solo tic
    //Variables de apoyo
    double rankeoTemp = 0.0, rankeoDistribuido = 0.0, rankeoNuevo = 0.0, rankeoActualTemp = 0.0;
    int nodos = 0, adyacenciasTemporales = 0, nodoAdyacente = 0;

    nodos = redPortales.obtTotVrt(); //Cantidad de nodos/vertices en el grafo
    for(int i=0; i<nodos; ++i){//Se emplea el cambio a todos los nodos que representan el grafo
        
        adyacenciasTemporales = redPortales.obtTotAdy(i); //Conociendo la cantidad de adyacencias que tiene el nodo (i) en estudio

        //Posteriormente se hace el tic acorde a la cantidad de adyacencias que tiene el nodo
        if(adyacenciasTemporales == 0){ //Cuando el nodo no tiene adyacencias se distribute el rankeo entre todos los demas nodos del grafo
            
            rankeoTemp = redPortales.obtRankeo(i); //Se toma el rankeo del nodo en estudio
            rankeoDistribuido = (double)rankeoTemp/nodos; //Se obtiene el valor distribuido del rankeo del nodo en estudio

            //Ahora se distribuye el rankeoDistribuido entre todos los nodos del grafo, modificando unicamente los rankeosNuevos de cada nodo del mismo
            for(int b=0; b<nodos; ++b){
                rankeoNuevo = redPortales.obtRankeoNuevo(b); //Obtencion del rankeoNuevo del nodo adyacente en estudio al nodo en estudio
                rankeoNuevo += rankeoDistribuido;
                redPortales.modRankeoNuevo(b, rankeoNuevo);
            }
        }else{ //Para el caso en el que el nodo SI tiene nodos adyacentes
            vector<int> arreglo = redPortales.obtAdy(i); //Posteriormente se obtiene el arreglo de adyacencias del nodo en estudio
            rankeoTemp = redPortales.obtRankeo(i); //Se da el rankeo actual
            rankeoDistribuido = (double) rankeoTemp/adyacenciasTemporales;//Ahora se procede a obtener el valor distribuido del rankeo del nodo en estudio

            //Ahora se recorre el arreglo de adyacenccias de cada nodo en estudio
            for(int b=0; b<adyacenciasTemporales; ++b){
                rankeoNuevo = redPortales.obtRankeoNuevo(arreglo[b]); //Obtencion del rankeo del nodo adyacente en estudio al nodo en estudio
                rankeoNuevo += rankeoDistribuido;
                redPortales.modRankeoNuevo(arreglo[b], rankeoNuevo);
            }
        }
    
        //Posteriormente se calcula el rankep Nuevo con el dampingFactor especificado
        rankeoNuevo = redPortales.obtRankeoNuevo(i);//rankeoNuevo viejo
        rankeoNuevo = (1-dampingFactor)/(nodos + dampingFactor * rankeoNuevo);
        redPortales.modRankeoNuevo(i, rankeoNuevo);
    }

    for(int i=0; i<nodos; i++){
        redPortales.modRankeo(i, redPortales.obtRankeoNuevo(i));
        redPortales.modRankeoNuevo(i, 0);
    }
}