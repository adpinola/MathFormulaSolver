/*
	Compilar:
	c++ --std=c++11 main.cpp formulaSolver.cpp -o MathFormulaSolver
*/
#include <iostream>
#include <sstream>
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
		ReplaceStringInPlace(kpi_id, "\n", "");
		Listado_KPIs[kpi_id + " - " + kpi_desc].Parse(kpi_formula);		   // Cargamos el KPI en el mapa
		Listado_KPIs[kpi_id + " - " + kpi_desc].defineVarMap(&Contadores); // Apuntamos las variables de la formula al mapa de contadores
		// std::cout << "Formula #" << i << ": " << kpi_id << " - " << kpi_desc << endl
		// 		  << Listado_KPIs[kpi_id].showFormula() << endl;
		// std::cout << endl;
	}
	strTemplate.close();

	// Ahora tenemos que abrir el reporte de contadores
	// Y a partir de este y las formulas, generamos el reporte de KPIs
	ifstream inputCounters(argv[2]);
	ofstream outputReport("Reporte_KPI_LTE.csv");
	string line;

	bool first_line = true;
	string period, MO, aux_counter;
	vector<string> counterList;
	while (getline(inputCounters, line))
	{
		istringstream aux_line(line);
		getline(aux_line, period, ',');
		getline(aux_line, MO, ',');
		outputReport << period << ",";
		outputReport << MO << ",";
		if (first_line)
		{
			first_line = false;
			while (getline(aux_line, aux_counter, ','))
			{
				counterList.push_back(aux_counter);
			}
			for (auto itr = Listado_KPIs.begin(); itr != Listado_KPIs.end(); ++itr)
			{
				outputReport << itr->first << ",";
			}
		}
		else
		{
			// Ahora estoy con las otras lineas
			// Uno a uno tengo q calcular y obtener datos
			int pos_counter = 0;
			while (getline(aux_line, aux_counter, ','))
			{
				// Tengo el valor del contador en aux_counter
				// en pos_counter es el numero de contador
				// guardo en el mapa contadores apuntando el nombre desde el vector
				Contadores[counterList.at(pos_counter)] = atof(aux_counter.c_str());
				pos_counter++;
			}
			// Ahora tengo cargado el mapa, puedo calcular los KPIs para cada fila
			for (auto itr = Listado_KPIs.begin(); itr != Listado_KPIs.end(); ++itr)
			{
				outputReport << itr->second.calculate() << ",";
			}
		}
		outputReport << endl;
	}
	outputReport.close();
	inputCounters.close();
	cout << "Reporte Generado: Reporte_KPI_LTE.csv" << endl;
	return 0;
}