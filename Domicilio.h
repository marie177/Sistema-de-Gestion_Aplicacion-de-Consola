#pragma once
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <clocale>
#include <windows.h>
#include <string.h>
#include <iostream>

class Domicilio
{
private:
	char _pais[50];
	char _provincia[50];
	char _localidad[50];
	char _calle[50];
	int _altura;
	char _dpto[10];
	int _cp;
	bool _estado;

public:
	Domicilio();

	/// Setters
	void setPais(const char* pais);
	void setProvincia(const char* provincia);
	void setLocalidad(const char* localidad);
	void setCalle(const char* calle);
	void setAltura(int altura);
	void setDpto(const char* dpto);
	void setCP(int cp);
	void setEstado(bool estado);

	/// Getters
	const char* getPais();
	const char* getProvincia();
	const char* getLocalidad();
	const char* getCalle();
	int getAltura();
	const char* getDpto();
	int getCP();
	bool getEstado();

	///Cargar y mostrar
	void cargarDomicilio();
	void mostrarDomicilio();

};

