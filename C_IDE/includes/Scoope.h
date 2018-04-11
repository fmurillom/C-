//
// Created by loop on 10/04/18.
//

#ifndef PROYECTO_1_V0_SCOOPE_H
#define PROYECTO_1_V0_SCOOPE_H
#include <iostream>
#include <string.h>
using namespace std;
class Scoope
{
public:
    int profundidad;
    string lineas;

public:
    Scoope();
    Scoope(int profundidad, string lineas);
    string getString();
};

#endif //PROYECTO_1_V0_SCOOPE_H
