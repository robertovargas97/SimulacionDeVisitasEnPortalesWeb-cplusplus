/* 
 * File:   Portal.h
 * Author: alan.calderon
 *
 * Created on 26 de octubre de 2017, 02:32 PM
 */

#ifndef PORTAL_H
#define PORTAL_H

class Portal {
public:
    Portal();
    Portal(const Portal& orig);
    virtual ~Portal();

    /* MÉTODOS OBSERVADORES: */

    double obtRankeo();
    double obtNuevoRankeo();
    int obtVisitas();

    /* MÉTODOS MODIFICADORES: */

    void modRankeo(double nr);
    void modNuevoRankeo(double nnr);

    // MOD: *this.
    // EFE: modifica el valor de las visitas del portal.
    void modVisitas(int nv);

private:
    // para la simulación de dispersión del "rankeo":
    double rankeo; // representa el rankeo actual (iteración t) de un vértice.
    double nuevoRankeo; // representa el rankeo siguiente (iteración t+1) de un vértice.

    // para la simulación del surfista: 
    int visitas; // representa la cantidad de visitas recibidas por un vértice
};

#endif /* PORTAL_H */

