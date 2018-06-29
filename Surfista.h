/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Surfista.h
 * Author: Alan
 *
 * Created on 1 de septiembre de 2017, 02:23 PM
 */

#ifndef SURFISTA_H
#define SURFISTA_H

class Surfista {
    // Representa un ciber-surfista que navega la red de portales.
    
public:
    
    // Construye un surfista asignándole un portal actual y -1 al portal anterior.
    Surfista();
    
    // Construye una copia del surfista orig.
    Surfista(const Surfista& orig);
    
    // Retorna al sistema la memoria ocupada por un surfista.
    virtual ~Surfista();
    
    // EFE: retorna el portal actualmente ocupado por el surfista.
    int obtPortalActual();
    
    // EFE: retorna el portal anteriormente ocupado por el surfista.
    // Si el reloj de la simulación está en cero, retorna -1.
    int obtPortalAnterior();
    
    // REQ: 0 <= porPortal < N y que sea adyacente o esté enlazado con el portal actual.
    // MOD: *this.
    // EFE: cambia el portal actual del surfista por posPortal.
    void asgPortalActual(int posPortal);
    
    // MOD: *this.
    // EFE: asigna al portal anterior la posición del portal actual.
    void actualizaPortalAnterior();
    
private:
    
    // representan identificadores de portales o vértices en el digrafo de portales.
    int portalActual;
    int portalAnterior;
};

#endif /* SURFISTA_H */

