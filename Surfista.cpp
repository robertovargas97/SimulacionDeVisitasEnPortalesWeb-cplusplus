/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Surfista.cpp
 * Author: Alan
 * 
 * Created on 1 de septiembre de 2017, 02:23 PM
 */

#include "Surfista.h"

Surfista::Surfista() {
    portalActual = 0;
    portalAnterior = -1;
}

Surfista::Surfista(const Surfista& orig) {
    portalActual = orig.portalActual;
    portalAnterior = orig.portalAnterior;
}

Surfista::~Surfista() {
}

int Surfista::obtPortalActual() {
    return portalActual;
}

int Surfista::obtPortalAnterior() {
    return portalAnterior;
}

void Surfista::asgPortalActual(int posPortal) {
    portalActual = posPortal;
}

void Surfista::actualizaPortalAnterior() {
    portalAnterior = portalActual;
}