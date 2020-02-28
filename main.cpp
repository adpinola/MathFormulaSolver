/*
	Compilar:
	c++ --std=c++11 main.cpp formulaSolver.cpp -o MathFormulaSolver
*/
#include <iostream>
#include <fstream>
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
	map<string, Formula> Listado_KPIs;
	map<string, float> Contadores;

	//Vamos a abrir el listado de KPIs para agregar al reporte
	ifstream strTemplate(argv[1]);
	if (strTemplate.eof())
	{
		std::cout << "Archivo no encontrado..." << endl;
		return -1;
	}
	int i = 0;
	while (!strTemplate.eof())
	{
		string kpi_id, kpi_desc, kpi_formula;
		getline(strTemplate, kpi_id, ',');
		getline(strTemplate, kpi_desc, ',');
		getline(strTemplate, kpi_formula, '\r');
		//getline(strTemplate, kpi_id,'\n');
		Listado_KPIs[kpi_id].Parse(kpi_formula); // Cargamos el KPI en el mapa
		std::cout << "Formula #" << i << ": " << kpi_id << " - " << kpi_desc << endl
				  << Listado_KPIs[kpi_id].showFormula() << endl;
		std::cout << endl;
		Listado_KPIs[kpi_id].defineVarMap(&Contadores); // Apuntamos las variables de la formula al mapa de contadores
		i++;
	}
	strTemplate.close();

	// Ahora tenemos que abrir el reporte de contadores
	// Y a partir de este y las formulas, generamos el reporte de KPIs
	ifstream inputCounters(argv[2]);
	ofstream outputReport("Reporte_KPI_LTE.csv");
	string line;
	bool first_line = true;
	string period, MO;
	vector<string> counterList;
	while (getline(inputCounters, line))
	{

		if (first_line)
		{
			first_line = false;
		}
		// Aqui obtuve la linea
		// Ahora necesito separar en ,
		counterList.push_back(line.substr(line.find_last_of(","))); // Aca obtengo el ultimo contador
		while (1)
		{
			// Saco hasta el primero.
		}
	}
	outputReport.close();
	inputCounters.close();
	return 0;
}