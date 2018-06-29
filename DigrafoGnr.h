/* 
 * File:   DigrafoGnr.h
 * Author: alan.calderon
 *
 * Created on 25 de octubre de 2017, 11:45 AM
 */

#ifndef DIGRAFOGNR_H
#define DIGRAFOGNR_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iterator>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>    // std::copy

using namespace std;

// V es el tipo de vértice.

template < typename V >
class DigrafoGnr {
    // Representa una red compleja con vértices de tipo V.
    /* SUPUESTOS:
     * 1. Los vértices son identificados con números de 0 a N-1, dada N la cantidad
     * total de vértices.
     * 2. El tipo V tiene definido su constructor estándar V().
     * 3. El tipo v tiene definido su constructor de copias V(const V& orig);
     * 4.El tipo V tiene sobrecargado el operador de asignacion (operaton =).
     */

public:

    /* CONSTRUCTORES */

    // REQ: cantidadVrt > 0. En este caso, N es igual a cantidadVrt.
    // Construye un Digrafo siguiendo el algoritmo de Barabási-Albert para redes de
    // "escala libre" siguiendo el algoritmo de "conexión preferencial" (o 
    // "preferential attachment".
    // Ver:https://en.wikipedia.org/wiki/Barab%C3%A1si%E2%80%93Albert_model
    // NOTA: para calcular los pesos de cada vértice se cuentan tanto los arcos
    // entrantes como los salientes.
    DigrafoGnr(int cantidadVrt);

    // REQ: cantidadVrt > 0. En este caso, N es igual a cantidadVrt.
    // REQ: 0 < probabilidadAdy < 1.
    // Construye un digrafo con cantidadVrt de vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando probabilidadAdy. Esto
    // implica que la probabilidad de que un arco exista entre cualesquiera dos
    // dos vértices es igual a probabilidadAdy
    DigrafoGnr(int cantidadVrt, double probabilidadAdy);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices tienen un índice que va de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con V().
    DigrafoGnr(ifstream& archivo);

    // Construye una copia idéntica a orig.
    DigrafoGnr(const DigrafoGnr< V > & orig);

    ~DigrafoGnr();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= indVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe un arco-saliente desde el vértice con identificador
    //      idVrtO hacia el vértice con identificador idVrtD.
    bool xstArcSal(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los arcos 
    // <idVrt,idVrtj> que salen desde idVrt en el digrafo.
    void obtIdVrtArcSal(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los arcos 
    // <idVrtj,idVrt> que entran a idVrt en el digrafo.
    void obtIdVrtArcEnt(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    V operator[](int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el total de arcos salientes de idVrt.
    int obtTotArcSal(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el total de arcos entrantes a idVrt.
    int obtTotArcEnt(int idVrt) const;

    // EFE: retorna el total de arcos en el digrafo.
    int obtTotArc() const;

    // EFE: retorna el total de vértices en el digrafo.
    int obtTotVrt() const;

    /* MÉTODOS OBSERVADORES ESPECIALES */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el "local clustering coefficient" o coeficiente local de agrupamiento
    //      para el vértice indicado por vrt.
    //      La definición aparece en: http://en.wikipedia.org/wiki/Clustering_coefficient
    //      Se calcula como el cociente entre la cantidad efectiva de arcos entre los
    //      vecinos del vértice indicado por vrt dividida por la cantidad total de posibles
    //      arcos entre todos los vecinos del vértice indicado por vrt.
    // NOTA el conjunto de vecinos a idVrt SÓLO incluye los conectados mediante arcos ENTRANTES.
    double coeficienteAgrupamiento(int idVrt) const;

    /* MÉTODOS MODIFICADORES SIMPLES */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    V& operator[](int idVrt);

private:

    template < typename W >
    struct Nodo {
        W w;
        list< int > listaAdy;

        Nodo< W >() : w(W()), listaAdy() {
        };

        Nodo< W >(const W& ww) : w(ww), listaAdy() {
        };
    };
    vector < Nodo < V > > vectorNodos;
};

template < typename V >
DigrafoGnr< V >::DigrafoGnr(int cantidadVrt) {
    //Variables de opoyo
    int iActual = 0, nodoInvestigado = 0, lastIndex = 0, max = 0, mo = 0, resultRandom = 0;
    srand(time(NULL));

    vectorNodos.resize(cantidadVrt, DigrafoGnr::Nodo<V>()); //Inicializacion del vector de nodos
    vector<int> vApoyo;
    vApoyo.resize(cantidadVrt, 0); //Inicializacion del vector de apoyo

    //Ahora se define por parte del programador que mo va a tener una valor en dependecia de la cantidad de vertices del Digrafo
    //(cantidadVrt > 20) ? mo = (int)(N*0.10) : mo = 2;
    mo = 2;

    //Inicializacion del arreglo de ayuda complementario
    for (int i = 0; i < vectorNodos.size(); ++i) {
        vApoyo[i] = vectorNodos[i].listaAdy.size();
    }

    //Primero se hace la union simple de los primeros dos primeros nodos del 0 con el 1 por obligacion
    vectorNodos[0].listaAdy.push_back(1);
    ++vApoyo[0];
    ++vApoyo[1];

    while (nodoInvestigado < vectorNodos.size()) { //Primero de define la cantidad de adyacencias que va a tener el nodoInvestigado
        (nodoInvestigado == 0) ? iActual = 1 : iActual = 0;
        while (iActual < mo) { //Esto es para la cantidad de adyacencias acorde al parametro (mo)
            for (int i = 0; i < vectorNodos.size(); ++i) {//Primero vemos el maximo de nodos que se pueden implementar
                max += vApoyo[i];
            }
            resultRandom = (rand() % (max + 1)); //De (0 - max)
            for (int i = 0; resultRandom >= vApoyo[i] && resultRandom != 0; ++i) {
                resultRandom -= vApoyo[i];
                ++lastIndex;
            }
            //Evitando adyacencia hacia si mismo y que ya exista la adyacencia 
            //AGREGADO DE MANERA INICIAL
            if (lastIndex != nodoInvestigado && !xstArcSal(nodoInvestigado, lastIndex)) {
                vectorNodos[nodoInvestigado].listaAdy.push_back(lastIndex);
                ++vApoyo[nodoInvestigado];
                ++vApoyo[lastIndex];
            }
            lastIndex = max = resultRandom = 0;
            ++iActual;
        }
        ++nodoInvestigado;
    }
}

template < typename V >
DigrafoGnr< V >::DigrafoGnr(int cantidadVrt, double probabilidadAdy) {
    vectorNodos.resize(cantidadVrt, DigrafoGnr::Nodo<V>()); //Inicializacion del vector de nodos
    for (int x = 0; x < cantidadVrt; ++x) {
        for (int y = 0; y < cantidadVrt; ++y) {
            double proba = (rand() % (100 + 1)) / 100.0; //de 0.0 a 1.0
            if (proba <= probabilidadAdy && x != y) { //Tiene que ser una probabilidad mayor que la del parametro, y no puede haber nodos con enlaces a si mismo
                vectorNodos[x].listaAdy.push_back(y);
            }
        }
    }
}

template < typename V >
DigrafoGnr< V >::DigrafoGnr(const DigrafoGnr< V >& orig) {
    vectorNodos.resize(orig.obtTotVrt(), DigrafoGnr::Nodo<V>()); //Inicializacion del vector de nodos
    for (int nodoEnEstudio = 0; nodoEnEstudio < vectorNodos.size(); ++nodoEnEstudio) {
        for (list<int>::const_iterator it = orig.vectorNodos[nodoEnEstudio].listaAdy.begin(); it != orig.vectorNodos[nodoEnEstudio].listaAdy.end(); ++it) {
            vectorNodos[nodoEnEstudio].listaAdy.push_back(*it);
        }
    }
}

template < typename V >
DigrafoGnr< V >::DigrafoGnr(ifstream& archivo) {

    int cantidadVertices = 0;
    if (archivo.fail()) { //En caso de que al archivo falle
        cerr << "No se pudo abrir el archivo correctamente" << endl;
        exit(1);
    } else if (archivo.is_open()) {

        int numeroDeLinea = 0;
        string tDato = ""; //Se utliza para saber la cantidad de caracteres que tiene el tamaño del grafo (por ejemlo un 2 tiene un digito,10 tiene 2, 100 tiene 3 etc)
        vector < char > datoEvaluado(1); //Vector que almacena el caracter que se leera del archivo

        int posVector = 0;
        int ady = 0;
        cantidadVertices = 0;
        archivo >> tDato; //Se extrae el primer dato del archivo que representa el tamaño del grafo
        cantidadVertices = atoi(tDato.c_str()); //Convierte la string de tamaño del grafo a un int
        // cout << cantidadVertices << endl;

        // Arreglo que se utilizara para almacenar los datos del grafo
        //Se emplea para poder guardar numeros de mas de un digito
        char dato[tDato.size()]; //Se emplea como arreglo y no vector ya que más adelante se necesita convertir el numero representado por el arreglo a un int y si se usa vector de la STL no se podria realizar la conversion

        archivo.get(dato[0]); //Consume el blanco seguido del tamaño del grafo
        archivo.get(dato[0]); //Consume el salto de linea seguido del tamaño del grafo
        vectorNodos.resize(cantidadVertices, Nodo <V> ()); //Crea el arreglo que representa el Digrafo deacuerdo a la cantidad de Nodos que indica el archivo

        while (!archivo.eof()) { //Mientras el archivo no termine
            archivo.get(datoEvaluado[0]); // Extrae un caracter del archivo
            posVector = 0;

            if (datoEvaluado[0] == '\n') { //En caso de que no exista adyacencia en el nodo cambia de linea
                numeroDeLinea++;
            }

            while ((posVector < tDato.size()) && (datoEvaluado[0] != '\n')&&(datoEvaluado[0] != ' ')) {

                dato[posVector] = datoEvaluado[0]; // Guarda el dato leido del archivo en la posicion del vector que representa un numero ya sea de 1 o mas digitos
                archivo.get(datoEvaluado[0]); // Extrae un caracter del archivo
                ++posVector;
                if (((datoEvaluado[0] == '\n') && (posVector == 1)) || ((datoEvaluado[0] == ' ') && (posVector == 1))) { //Esto sucede en caso de que el numero del archivo sea de un digito
                    if (tDato.size() != 1) { //Si el numero es de 1 digito no es necesario lo que está dentro del if
                        dato[1] = '\0'; //Se realiza para asegurar el numero dentro
                    }
                    ady = atoi(dato); //Convirte a entero el numero que representa el vector "dato"
                    vectorNodos[numeroDeLinea].listaAdy.push_front(ady); //Agrega la adyacencia a lista

                    //  cout << "Se agrego " << ady << endl;

                    if ((datoEvaluado[0] == '\n')) {
                        numeroDeLinea++; //Se aumenta el numeroLinea para cambiar de Nodo
                        //  cout << "Cambio de Nodo" << endl;
                    }
                }
                if ((posVector == tDato.size()) &&(tDato.size() != 1)) { //En caso de que el numero sea de 2 digitos o mas
                    ady = atoi(dato); //Convirte a entero el numero que representa el vector "dato"
                    vectorNodos[numeroDeLinea].listaAdy.push_front(ady);
                    // cout << "Se agrego " << ady << endl;

                    if ((datoEvaluado[0] == '\n')) {
                        numeroDeLinea++; //Se aumenta el numeroLinea para cambiar de Nodo
                        //  cout << "Cambio de Nodo" << endl;
                    }
                }
            }
        }
        archivo.close(); //Cierra el archivo
    }
}

template < typename V >
DigrafoGnr< V >::~DigrafoGnr() {

}

template < typename V >
bool DigrafoGnr< V >::xstVrt(int idVrt) const {
    bool existe = false;
    if ((idVrt >= 0) && (idVrt < obtTotVrt())) {
        existe = true;
    }
    return existe;
}

template < typename V >
bool DigrafoGnr< V >::xstArcSal(int idVrtO, int idVrtD) const {
    list<int>::const_iterator it = find(vectorNodos[idVrtO].listaAdy.begin(), vectorNodos[idVrtO].listaAdy.end(), idVrtD);
    return it != vectorNodos[idVrtO].listaAdy.end();
}

template < typename V >
void DigrafoGnr< V >::obtIdVrtArcSal(int idVrt, vector< int >& rsp) const {
    for (list<int>::const_iterator i = vectorNodos[idVrt].listaAdy.begin(); i != vectorNodos[idVrt].listaAdy.end(); ++i) {
        rsp.push_back(*i);
    }
}

template < typename V >
void DigrafoGnr< V >::obtIdVrtArcEnt(int idVrt, vector< int >& rsp) const {

    for (int i = 0; i < obtTotVrt(); i++) {
        if ((xstArcSal(i, idVrt)) && (i != idVrt)) {
            rsp.push_back(i);
        }
    }
}

template < typename V >
int DigrafoGnr< V >::obtTotArcSal(int idVrt) const {
    return vectorNodos[idVrt].listaAdy.size();
}

template < typename V >
int DigrafoGnr< V >::obtTotArcEnt(int idVrt) const {
    int arcosEntrantes = 0;

    for (int i = 0; i < obtTotVrt(); i++) {
        if ((xstArcSal(i, idVrt))) {
            arcosEntrantes++;
        }
    }
    return arcosEntrantes;
}

template < typename V >
int DigrafoGnr< V >::obtTotArc() const {
    int arcosTotales = 0;
    int i = 0;

    while (i < obtTotVrt()) {
        arcosTotales += vectorNodos[i].listaAdy.size();
        ++i;
    }
    return arcosTotales;
}

template < typename V >
int DigrafoGnr< V >::obtTotVrt() const {
    return vectorNodos.size();
}

template < typename V >
double DigrafoGnr< V >::coeficienteAgrupamiento(int idVrt) const {

    if ((0 <= idVrt) && (idVrt < obtTotVrt())) { //Si el vertice existe 

        vector <int> adyaVecEntrante;
        double coeficienteDeAgrupamiento = 0.0; //Guarda el resultado del coeficiente
        double arcosEfectivos = 0.0; //Almacena los arcos efectivos del vertice en estudio (incluye los del vecindario)
        double verticesVecinos = 0.0; //Indica la cantidad de vecino que tiene idVrt

        //Se procede a Identificar los arcos efectivos de los vertices que tienen adyacencia hacia vrt (es decir los arcos entrantes a idVrt)
        for (int i = 0; i < obtTotVrt(); i++) { //Se Recorre la red de nodos
            if (i != idVrt) { //Entra al if solo si el vertice en estudio es disntino a idVrt para no ejecutar operaciones en vano ya que no pueden haber conexiones entre el mismo vertice
                if (xstArcSal(i, idVrt)) { //Si donde estoy parado (el vertice donde esta i esta conectado con idVrt es decir manda un arco entrante a idVrt)
                    arcosEfectivos++; //Acumula la cantidad de Arcos efectivos entrantes hacia idVrt
                    verticesVecinos++; //Se aumenta la cantidad de vertices del vecindario gracias a que existe conexion entrante hacia idVrt
                    obtIdVrtArcSal(i, adyaVecEntrante); //Guarda las adyacencias del vertice vecino con arco hacia idVrt

                    for (int n = 0; n < obtTotArcSal(i); n++) {
                        if (xstArcSal(adyaVecEntrante[n], idVrt)) { //Se verifica conexion entre vecinos con arco entrante a idVrt
                            arcosEfectivos++; //Acumula los arcos efectivos del vecindario de idVrt desde un vertice con arco entrante a idVrt hacia otro con arco entrante a idVrt (ambos parte del vecindario de idVrt)
                        }
                    }
                    adyaVecEntrante.clear();
                } else { //En caso de que no existan adyacencias entrantes para calcular el coeficiente
                    coeficienteDeAgrupamiento = 0;
                }
            }
        }

        // cout << " -Numero de vertices en el vecindario contemplando vrt:                        " << verticesVecinos + 1 << endl;
        // cout << " -ArcosEfectivos:                                                              " << arcosEfectivos << endl;
        // cout << " -Arcos posibles ( CantidadMaximaDeArcosPorVertice * (VerticesDelVecindario)): " << (verticesVecinos * (verticesVecinos + 1)) << endl;

        if (arcosEfectivos > 0) { //Si existen arcos para realizar el calculo
            coeficienteDeAgrupamiento = (arcosEfectivos / (verticesVecinos * (verticesVecinos + 1))); //( verticesVecinos * verticesVecinos + 1) representa la cantidad de arcos posibles en el vecindario de vrt
        }
        return coeficienteDeAgrupamiento;
    } else { //En caso de que el vertice no exista 
        return 0;
    }
}

template < typename V >
V DigrafoGnr< V >::operator[](int idVrt) const {
    return vectorNodos[idVrt].w;
}

template < typename V >
V& DigrafoGnr< V >::operator[](int idVrt) {
    return vectorNodos[idVrt].w;
}
#endif /* DIGRAFOGNR_H */

