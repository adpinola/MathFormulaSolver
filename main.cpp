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
	string formulaKPI(argv[1]);
	Formula testFormula;
	testFormula.addVariable("A", 13.54);
	testFormula.addVariable("B", 0.04);
	testFormula.addVariable("C", 10);
	testFormula.addVariable("D", 100);
	testFormula.addVariable("E", 5.3);
	testFormula.addVariable("F", 2);
	testFormula.addVariable("G", 7);
	testFormula.addVariable("H", 1.43);
	testFormula.addVariable("I", 0.8);
	testFormula.addVariable("J", 6);
	testFormula.addVariable("K", 11.45);
	testFormula.addVariable("L", 3);
	testFormula.showVariables();
	cout << "Formula Original: " << formulaKPI << endl;
	testFormula.Parse(formulaKPI);
	testFormula.showFormula();
	cout << "Resultado testFormula = " << testFormula.calculate() << endl;
	return 0;
}