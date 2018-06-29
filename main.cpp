/* 
 * File:   main.cpp
 * Author: alan.calderon
 *
 * Created on 1 de septiembre de 2016, 06:48 PM
 */

#include <iostream>
#include <memory>
#include <iostream>
using namespace std;

#include "Digrafo.h"
#include "SimuladorDifusion.h"
#include "SimuladorSurfista.h"

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream archivo;
    archivo.open("nArch1.txt");
    DigrafoGnr <Portal> digrafoG(archivo);

    int a = digrafoG[1].obtVisitas();
    cout << a << endl;
    digrafoG[1].modVisitas(a);
    a = digrafoG[1].obtVisitas();
    cout << a << endl;



    return 0;
}

