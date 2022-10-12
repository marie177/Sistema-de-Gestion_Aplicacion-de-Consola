#include "Fecha.h"
#include <ctime>
#include <iomanip>

/// Constructor
Fecha::Fecha() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	_dia = timeinfo->tm_mday;
	_mes = timeinfo->tm_mon + 1;
	_anio = timeinfo->tm_year + 1900;
}

/// Setters
void Fecha::setDia(int dia) { _dia = dia; }
void Fecha::setMes(int mes) { _mes = mes; }
void Fecha::setAnio(int anio) { _anio = anio; }

/// Getters
int  Fecha::getDia() { return _dia; }
int  Fecha::getMes() { return _mes; }
int  Fecha::getAnio() { return _anio; }

bool Fecha::operator> (Fecha aux)
{
	if (_anio < aux.getAnio())
	{
		return false;
	}

	if (_mes < aux.getMes())
	{
		return false;
	}

	if (_dia < aux.getDia())
	{
		return false;

	}
	else
	{
		return true;
	}
}

/// Desarrollo cargar
void Fecha::cargarFecha() {

	Fecha actual;
	int aux = 0;
	const int MayorEdad = actual.getAnio() - 18;

	do {
		cout << "Año: ";
		cin >> aux;

		if (aux <1900 || aux > MayorEdad)
		{
			cout << " El año ingresado es incorrecto, intente nuevamente" << endl;
		}
	} while (aux<1900 || aux> MayorEdad);

	this->setAnio(aux);

	do {
		cout << "Mes: ";
		cin >> aux;

		if (aux <= 0 || aux > 12)
		{
			cout << " El mes ingresado es incorrecto, intente nuevamente" << endl;
		}

	} while (aux <= 0 || aux > 12);

	this->setMes(aux);

	do {
		cout << "Dia: ";
		cin >> aux;

		if (!validaDia(this->getMes(), aux, this->getAnio()))
		{
			cout << " El dia ingresado es incorrecto, intente nuevamente" << endl;
		}
	} while (!validaDia(this->getMes(), aux, this->getAnio()));

	this->setDia(aux);

}

/// Desarrollo Mostrar

void Fecha::mostrarFecha() {
	cout << setw(2);
	cout << this->getDia();
	cout << setw(1) << "/";
	cout << setw(1) << this->getMes();
	cout << setw(1) << "/";
	cout << setw(2) << this->getAnio();

}

string Fecha::toString() {
	string fecha;
	fecha = to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio);
	return fecha;
}

bool Fecha::operator== (Fecha aux)
{
	if (_anio == aux.getAnio() && _mes == aux.getMes() && _dia == aux.getDia())
	{
		return true;
	}

	return false;
}

void Fecha::cargarFechaConsultas() {

	int aux = 0;

	do {
		cout << "Año: ";
		cin >> aux;

		if (aux < 0 || aux < 1980)
		{
			cout << " El año ingresado es incorrecto, intente nuevamente" << endl;
		}

	} while (aux < 0 || aux < 1980);

	this->setAnio(aux);

	do {
		cout << "Mes: ";
		cin >> aux;

		if (aux <= 0 || aux > 12)
		{
			cout << " El mes ingresado es incorrecto, intente nuevamente" << endl;
		}

	} while (aux <= 0 || aux > 12);

	this->setMes(aux);

	do {
		cout << "Dia: ";
		cin >> aux;

		if (!validaDia(this->getMes(), aux, this->getAnio()))
		{
			cout << " El dia ingresado es incorrecto, intente nuevamente" << endl;
		}
	} while (!validaDia(this->getMes(), aux, this->getAnio()));

	this->setDia(aux);
}
/////////////////////////////////////
// Funciones globales Fecha
/////////////////////////////////////

bool validaDia(int mes, int dia, int anio) {

	switch (mes)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (dia >= 1 && dia <= 31)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	case 2:
		if (anio % 4 != 0 || (anio % 100 == 0 && anio % 400 != 0))
		{
			if (dia >= 1 && dia <= 28)
			{
				return true;
			}
		}
		else {

			if (dia >= 1 && dia <= 29)
			{

				return true;
			}
		}
		return false;
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		if (dia >= 1 && dia <= 30)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	default:
		return false;
		break;
	}
}