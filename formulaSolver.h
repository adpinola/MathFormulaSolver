#ifndef __FORMULA_SOLVER_H_
#define __FORMULA_SOLVER_H_

#include <iostream>
#include <string.h>
#include <string>
#include <map>

using namespace std;

// Estructura que contiene la configuracion de Parseo
struct eqNode
{
    string equation;
    float result;
    char operation;
    eqNode *left;
    eqNode *right;
};

class Formula
{
private:
    eqNode *root;                //Arbol que contiene la formula completa
    map<string, float> variable; // Listado de variables que intervienen en la formula

public:
    Formula();       // Constructor por omision
    Formula(string); //Constructor con formula de entrada
    ~Formula();
    bool Parse(string);              // parsea una formula y la coloca en el arbol correspondiente
    float calculate();               // Calcula el resultado de la formula
    bool addVariable(string, float); //Agrega variable
};

#endif