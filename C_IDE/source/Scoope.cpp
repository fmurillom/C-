//
// Created by loop on 10/04/18.
//
#include <iostream>
#include <string.h>
#include "../includes/Scoope.h"

using namespace std;

Scoope::Scoope(){}
Scoope::Scoope(int profundidad, string lineas)
{
    this->profundidad = profundidad;
    this->lineas = lineas;
}

string Scoope::getString()
{
    return "[" + to_string(profundidad) + ", " + lineas + "]";
}