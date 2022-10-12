#pragma once

#include "Domicilio.h"
#include <cstring>
#include <iostream>
#include "funciones.h"
#include "Fecha.h"

class Persona {

protected:
	int _dni;
	char _nombre[30];
	char _apellido[30];
	Fecha _fecha_nacimiento;
	Domicilio _domicilio;
	char _email[30];
	char _telefono[15];
	bool _estado;

public:
	Persona();

	//Setters
	void setDni(int dni);
	void setNombre(char* nombre);
	void setApellido(char* apelldo);
	void setFechanacimiento(Fecha fecha_nacimiento);
	void setDomicilio(Domicilio domicilio);
	void setEmail(char* email);
	void setTelefono(char* telefono);
	void setEstado(bool estado);

	// Getters
	int getDni();
	const char* getNombre();
	const char* getApellido();
	Fecha getFechaNacimiento();
	Domicilio getDomicilio();
	const char* getEmail();
	const char* getTelefono();
	bool getEstado();

	//Cargar y Mostrar
	int CargarPersona();
	void MostrarPersona();

};