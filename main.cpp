/*
	Compilar:
	c++ --std=c++11 main.cpp formulaSolver.cpp -o MathFormulaSolver
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <string.h>

#include "formulaSolver.h"

using namespace std;

int main(int argc, char *argv[])
{
	string formulaKPI="(( A + B * C + D ) / ( E - F / G - I ) + ( J / K + L ) )";
	Formula LTE_5051a;
	LTE_5051a.addVariable("M8018C1",13.54);
	LTE_5051a.addVariable("M8031C51",0.04);
	LTE_5051a.addVariable("M8000C51",10);
	cout << "Formula Original: " << formulaKPI << endl;
	LTE_5051a.Parse(formulaKPI);
	LTE_5051a.showVariables();
    return 0;
}