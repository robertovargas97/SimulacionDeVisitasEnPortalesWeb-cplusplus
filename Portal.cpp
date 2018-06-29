/* 
 * File:   Portal.cpp
 * Author: alan.calderon
 * 
 * Created on 26 de octubre de 2017, 02:32 PM
 */

#include "Portal.h"
#include <iostream>

using namespace std;

Portal::Portal() : rankeo(0), visitas(0), nuevoRankeo(0) {
}

Portal::Portal(const Portal& orig) {
    rankeo = orig.rankeo;
    nuevoRankeo = orig.nuevoRankeo;
    visitas = orig.visitas;

}

Portal::~Portal() {
}

double Portal::obtNuevoRankeo() {
    return nuevoRankeo;
}

double Portal::obtRankeo() {
    return rankeo;

}

int Portal::obtVisitas() {
    return visitas;
}

void Portal::modNuevoRankeo(double nnr) {
    nuevoRankeo = nnr;
}

void Portal::modRankeo(double nr) {
    rankeo = nr;
}

//No es necesario el paramentro ya que solo es incrementar las visitas en 1 y en la clase Digrafo se manda como parametro el vertice al que se le desea incrementar las visitas

void Portal::modVisitas(int nv) {
    visitas = nv;
}