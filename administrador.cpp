#include "administrador.h"

using namespace std;
using namespace rlutil;

///Constructor
Administrador::Administrador(int id, int dni, const char* apellido, const char* nombre, const char* contrasenia, bool estado)
{
	_idAdministrador = id;
	_dni = dni;
	strcpy(_apellido, apellido);
	strcpy(_nombre, nombre);
	strcpy(_contrasenia, contrasenia);
	_estado = estado;
}

/// Setters
void Administrador::setIdAdmin(int idAdmin)
{
	_idAdministrador = idAdmin;
}

void Administrador::setDNI(int dni)
{
	_dni = dni;
}

void Administrador::setNombre(const char* nombre)
{
	strcpy(_nombre, nombre);
}

void Administrador::setApellido(const char* apellido)
{
	strcpy(_apellido, apellido);
}

void Administrador::setContrasenia(const char* contrasenia)
{
	strcpy(_contrasenia, contrasenia);
}

void Administrador::setEstado(bool estado)
{
	_estado = estado;
}

/// Getters
int Administrador::getIdAdmin()
{
	return _idAdministrador;
}

int Administrador::getDNI()
{
	return _dni;
}

const char* Administrador::getContrasenia()
{
	return _contrasenia;
}

const char* Administrador::getApellido()
{
	return _apellido;
}

const char* Administrador::getNombre()
{
	return _nombre;
}

bool Administrador::getEstado()
{
	return _estado;
}

void Administrador::cargar()
{
	int aux;
	string pass;
	string pass2;
	bool flag = false;

	srand(time(NULL));

	do {
		cout << "Ingrese el DNI (0 para volver al menu anterior): ";
		cin >> aux;

		if (aux == 0)
		{
			return;
		}

		if (aux < 1000000)
		{
			cout << "DNI inválido. Por favor, reintente." << endl << endl;
			anykey();
			cls();
			flag = false;
		}
		else if (buscarAdministradorPorDni(aux) > -1)
		{
			cout << "El DNI ya ha sido registrado anteriormente." << endl << endl;
			anykey();
			cls();
			flag = false;
		}
		else
		{
			flag = true;
		}

	} while (!flag);

	this->setDNI(aux);

	cout << "Ingrese apellido: ";
	cin.ignore();
	cin.getline(_apellido, 29);

	cout << "Ingrese nombre: ";
	cin.getline(_nombre, 29);

	do {
		cout << "Ingrese contraseña nueva (sin espacios, máximo 15 caracteres): ";

		pass = pedirContrasenia();

		if (pass.length() > 15)
		{
			cout << "Contraseña demasiado larga." << endl << endl;
			flag = false;
		}
		else
		{
			cout << "\nRepita la contraseña ingresada: ";

			pass2 = pedirContrasenia();

			if (pass != pass2)
			{
				cout << "La contraseña es diferente a la primera ingresada. Por favor, reintente." << endl << endl;
				flag = false;
			}
			else
			{
				flag = true;
			}
		}

	} while (!flag);

	char contrasenia[30];

	strcpy(contrasenia, pass.c_str());

	this->setContrasenia(contrasenia);

	do {
		aux = 1 + rand() % 9999;

		if (buscarAdministradorPorID(aux) > -1)
		{
			flag = false;
		}
		else
		{
			flag = true;
		}

	} while (!flag);

	this->setIdAdmin(aux);

	this->setEstado(true);

	this->grabarEnDisco();

	cout << endl << " -- Administrador creado correctamente --" << endl << endl;
	cout << "Nombre: " << this->getNombre() << endl;
	cout << "Apellido: " << this->getApellido() << endl << endl;
	cout << " - Datos para iniciar sesión: " << endl << endl;
	cout << "ID: " << this->getIdAdmin() << endl;
	anykey();

}

void Administrador::mostrar()
{
	cout << "--------------------------------" << endl;
	cout << "DNI: " << this->getDNI() << endl;
	cout << "ID: " << this->getIdAdmin() << endl;
	cout << "Nombre: " << this->getNombre() << endl;
	cout << "Apellido: " << this->getApellido() << endl;

}

void Administrador::listar()
{
	if (this->getEstado())
	{

		cout << left;
		cout << setw(5) << this->getIdAdmin();
		cout << setw(15) << this->getDNI();
		cout << setw(20) << this->getNombre();
		cout << setw(20) << this->getApellido();
		cout << endl;
	}

}

bool Administrador::grabarEnDisco()
{
	FILE* fReg = fopen("administradores.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(Administrador), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Administrador::leerDeDisco(int pos)
{
	FILE* fReg = fopen("administradores.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(Administrador), SEEK_SET);

	int escribio = fread(this, sizeof(Administrador), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Administrador::modificarEnDisco(int pos)
{
	FILE* fReg = fopen("administradores.dat", "rb+");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(Administrador), SEEK_SET);

	int escribio = fwrite(this, sizeof(Administrador), 1, fReg);

	fclose(fReg);

	return escribio;
}


/////////////////////////////////////
// Funciones globales Administrador
/////////////////////////////////////


int buscarAdministradorPorDni(int DNI)
{
	Administrador admin;
	int pos = 0;

	while (admin.leerDeDisco(pos))
	{
		if (admin.getDNI() == DNI && admin.getEstado())
		{
			return pos;
		}
		pos++;
	}

	return -1;
}

int buscarAdministradorPorID(int id)
{
	Administrador admin;
	int pos = 0;

	while (admin.leerDeDisco(pos))
	{
		if (admin.getIdAdmin() == id && admin.getEstado())
		{
			return pos;
		}
		pos++;
	}

	return -1;
}

int buscarCantidadRegistrosAdmin() {

	FILE* p = fopen("administradores.dat", "rb");
	if (p == NULL) {
		return 0;
	}

	size_t bytes;
	int cant_reg;

	fseek(p, 0, SEEK_END);
	bytes = ftell(p);
	fclose(p);
	cant_reg = bytes / sizeof(Administrador);
	return cant_reg;
}

int checkArchivoAdmins() {

	FILE* fReg = fopen("administradores.dat", "rb");

	if (fReg == NULL)
	{
		fReg = fopen("administradores.dat", "wb");

		if (fReg == NULL)
		{
			cout << "Error al crear o leer archivo de administradores." << endl;
			system("PAUSE > null");

			return -1;
		}
		else
		{
			fclose(fReg);
			cout << "Archivo de administradores creado correctamente" << endl;

			return 0;
		}
	}
	else
	{
		cout << "Administradores: cargado OK" << endl;
	}

	fclose(fReg);

	return 1;

}

void crear_nuevo_admin()
{
	Administrador aux;

	aux.cargar();
	
}

void modificar_admin()
{
	int opcion;
	char confirmarSalida;
	bool salir = false;
	bool flag = false;
	int idaux;
	int pos = 0;
	Administrador aux;

	while (!salir) {

		do
		{
			cout << "Ingrese ID de administrador a modificar (0 para volver al menu anterior): ";
			cin >> idaux;

			if (idaux == 0)
			{
				return;
			}

			pos = buscarAdministradorPorID(idaux);

			if (idaux < 0)
			{
				cout << "ID inválido. Reintente por favor." << endl << endl;
				anykey();
				cls();
				flag = false;
			}
			else if (pos <= -1)
			{
				cout << "El ID no se encuentra. Reintente por favor." << endl << endl;
				anykey();
				cls();
				flag = false;

			}
			else
			{
				flag = true;
			}
		} while (!flag);

		cls();

		aux.leerDeDisco(pos);
		aux.mostrar();

		cout << "--------------------------------" << endl;
		cout << "  Seleccione campo a modificar" << endl;
		cout << "--------------------------------" << endl;
		cout << "1 - Modificar DNI " << endl;
		cout << "2 - Modificar nombre " << endl;
		cout << "3 - Modificar apellido " << endl;
		cout << "4 - Modificar contraseña" << endl;
		cout << "--------------------------------" << endl;
		cout << "0 - Volver al menú Admins" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			ModificarDNIAdmin(aux, pos);
			break;
		case 2:
			ModificarNombreAdmin(aux, pos);
			break;
		case 3:
			ModificarApellidoAdmin(aux, pos);
			break;
		case 4:
			ModificarContrasenia(aux, pos);
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

void baja_admin()
{
	Administrador aux;
	int id;
	bool flag = false;
	int pos = 0;
	char confirm;

	do {
		do {
			cout << "Ingrese ID de administrador a dar de baja (0 para volver al menu anterior): ";
			cin >> id;

			if (id == 0)
			{
				return;
			}

			pos = buscarAdministradorPorID(id);
			if (id < 0)
			{
				cout << "ID inválido. Reintente por favor";
				anykey();
				cls();
				flag = false;
			}
			else if (pos <= -1)
			{
				cout << "El ID no se encuentra. Reintente por favor." << endl << endl;
				anykey();
				cls();
				flag = false;
			}
			else
			{
				flag = true;
			}
		} while (!flag);

		cls();

		aux.leerDeDisco(pos);
		aux.mostrar();
		cout << endl;

		cout << "¿Desea dar de baja el administrador  N°" << id << "? (S/N): ";
		cin >> confirm;

		confirm = (tolower(confirm));

		if (confirm == 's')
		{
			flag = true;
		}
		else
		{
			cls();
			flag = false;
		}
	} while (!flag);

	aux.setEstado(!aux.getEstado());
	aux.modificarEnDisco(pos);
	cout << endl << " -- El administrador ha sido dado de baja -- " << endl;
	anykey();
	cls();
}

void listado_general_admin()
{
	Administrador admin;
	int pos = 0;

	cout << left;
	cout << setw(5) << "ID";
	cout << setw(15) << "  DNI";
	cout << setw(20) << "    NOMBRE";
	cout << setw(20) << "   APELLIDO" << endl;

	cout << "------------------------------------------------------" << endl;

	while (admin.leerDeDisco(pos++))
	{
		admin.listar();
	}
}

void ModificarDNIAdmin(Administrador aux, int pos)
{
	int newDni;
	bool flag = false;
	char confirm;
	bool confirmar = false;

	do {
		cout << "Ingrese el dni nuevo (0 para volver al menu anterior): ";
		cin >> newDni;

		if (newDni == 0)
		{
			cls();
			return;
		}

		if (newDni < 1000000)
		{
			cout << " El dni ingresado es incorrecto, intente nuevamente." << endl;
			flag = false;
		}
		else
			if (buscarAdministradorPorDni(newDni))
			{
				cout << "El DNI ya se encuentra registrado." << endl;
				flag = false;
			}
			else
			{
				cls();
				cout << "Nuevo DNI: " << newDni << endl << endl;
				cout << "¿Confirma los cambios? (S/N): ";
				cin >> confirm;

				confirm = (tolower(confirm));

				if (confirm == 's')
				{
					flag = true;
				}
				else
				{
					cls();
					flag = false;
				}
			}

	} while (!flag);

	aux.setDNI(newDni);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;

	anykey();
	cls();
}
void ModificarNombreAdmin(Administrador aux, int pos) {

	char newName[30];
	char confirm;
	bool flag = false;

	do {

		cout << "Ingrese nombre nuevo: ";
		cin.ignore();
		cin.getline(newName, 29);
		cls();
		cout << "Nuevo nombre: " << newName << endl << endl;

		cout << "¿Confirma los cambios? (S/N): ";
		cin >> confirm;

		confirm = (tolower(confirm));

		if (confirm == 's')
		{
			flag = true;
		}
		else
		{
			cls();
			flag = false;
		}
	} while (!flag);

	aux.setNombre(newName);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();
}
void ModificarApellidoAdmin(Administrador aux, int pos)
{
	char newName[30];
	char confirm;
	bool flag = false;

	do
	{
		cout << "Ingrese apellido nuevo: ";
		cin.ignore();
		cin.getline(newName, 29);
		cls();
		cout << "Nuevo apellido: " << newName << endl << endl;

		cout << "¿Confirma los cambios? (S/N): ";
		cin >> confirm;

		confirm = (tolower(confirm));

		if (confirm == 's')
		{
			flag = true;
		}
		else
		{
			cls();
			flag = false;
		}
	} while (!flag);

	aux.setApellido(newName);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();
}
void ModificarContrasenia(Administrador aux, int pos)
{
	char aux2[30];
	char aux3[30];
	bool flag = false;

	do {
		cout << "Ingrese contraseña nueva (sin espacios, máximo 15 caracteres): ";
		cin >> aux2;

		if (strlen(aux2) > 15)
		{
			cout << "Contraseña demasiado larga." << endl << endl;
			flag = false;
		}
		else
		{
			cout << "Repita la contraseña ingresada: ";
			cin >> aux3;

			if (strcmp(aux2, aux3) != 0)
			{
				cout << "La contraseña es diferente a la primera ingresada. Por favor, reintente." << endl << endl;
				flag = false;
			}
			else
			{
				flag = true;
			}
		}

	} while (!flag);

	aux.setContrasenia(aux2);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();

}

void consulta_admin_Por_ID()
{
	int ID = 0;
	int pos = 0;
	Administrador admin;

	cout << "Ingrese el ID a consultar: ";
	cin >> ID;

	pos = buscarAdministradorPorID(ID);

	if (pos > -1) {
		admin.leerDeDisco(pos);
		cout << endl;
		admin.mostrar();
		anykey();
	}
	else
	{
		cout << "El ID no fue encontrado en el archivo de administradores" << endl;
		anykey();
	}
}

string pedirContrasenia()
{
	string pass;
	char caracter;

	caracter = getch();

	while (caracter != 13)
	{
		if (caracter != 8)
		{
			pass.push_back(caracter);
			cout << "*";
		}
		else
		{
			if (pass.length() > 0)
			{
				cout << "\b \b";
				pass.pop_back();
			}
		}
		caracter = getch();
	}

	return pass;
}