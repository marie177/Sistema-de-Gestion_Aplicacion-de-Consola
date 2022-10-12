#pragma once

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "rlutil.h"
#include <iomanip>
#include "administrador.h"


using namespace std;
class Administrador
{

private:
	int _idAdministrador;
	int _dni;
	char _apellido[30];
	char _nombre[30];
	char _contrasenia[30];
	bool _estado;

public:
	/// Constructor
	Administrador(int id = 0, int dni = 0, const char* apellido = "-", const char* nombre = "-", const char* contrasenia = "-", bool estado = false);

	/// Setters
	void setIdAdmin(int);
	void setDNI(int);
	void setNombre(const char*);
	void setApellido(const char*);
	void setContrasenia(const char*);
	void setEstado(bool);

	/// Getters
	int getIdAdmin();
	int getDNI();
	const char* getContrasenia();
	const char* getApellido();
	const char* getNombre();
	bool getEstado();

	void cargar();
	void mostrar();
	void listar();

	bool grabarEnDisco();
	bool leerDeDisco(int);
	bool modificarEnDisco(int pos);
};

/////////////////////////////////////
// Funciones globales Administrador
/////////////////////////////////////

void crear_nuevo_admin();
void modificar_admin();
void baja_admin();

void listado_general_admin();

int buscarAdministradorPorDni(int);
int buscarAdministradorPorID(int);

int buscarCantidadRegistrosAdmin();

int checkArchivoAdmins();

void ModificarDNIAdmin(Administrador aux, int pos);
void ModificarNombreAdmin(Administrador aux, int pos);
void ModificarApellidoAdmin(Administrador aux, int pos);
void ModificarContrasenia(Administrador aux, int pos);

void consulta_admin_Por_ID();

string pedirContrasenia();