#ifndef __FORMULA_SOLVER_H_
#define __FORMULA_SOLVER_H_

#include <iostream>
#include <string.h>
#include <string>
#include <map>

using namespace std;

#define OPERATOR_PRIORITY_LEVELS 2

// Estructura que contiene la configuracion de Parseo
struct eqNode
{
    string equation;
    float result;
    char operation;
    eqNode *left;  // Hoja del arbol izquierda
    eqNode *right; // Hoja del arbol derecha
};

class Formula
{
private:
    eqNode *root;                // Arbol que contiene la formula completa
    map<string, float>* lista_variables; // Listado de variables que intervienen en la formula

    void Parse(string, eqNode *); // parsea una formula y la coloca en el arbol correspondiente
    string showFormula(eqNode *);
    float calculate(eqNode *);
    void deleteFormula(eqNode *);

public:
    void defineVarMap(map<string, float> *); // Se apunta aqui a la variable global que contiene el mapa de variables
    void addVariable(string, float); //Agrega variable
    void showVariables();

    void Parse(string); // parsea una formula y la coloca en el arbol correspondiente
    string showFormula();
    float calculate(); // Calcula el resultado de la formula
    void deleteFormula();

    Formula();       // Constructor por omision
    Formula(string); //Constructor con formula de entrada
    ~Formula();
};

#endif