#pragma once

#include <iostream>
#include <string>

using namespace std;

class Fecha
{
private:
	int _dia, _mes, _anio;

public:

	///Constructor
	Fecha();

	///Setters
	void setDia(int dia);
	void setMes(int mes);
	void setAnio(int anio);

	///Getters
	int getDia();
	int getMes();
	int getAnio() ;

	void cargarFecha();
	void mostrarFecha();
	string toString();

	void cargarFechaConsultas();

	bool operator>(Fecha aux);
	bool operator== (Fecha aux);
};

bool validaDia(int mes, int dia, int anio);