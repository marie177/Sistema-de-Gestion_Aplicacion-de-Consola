#include "Pais.h"
#include "rlutil.h"
using namespace rlutil;

using std::setprecision;
using namespace std;

///Setters

void Pais::setId(int idpais) {
	_IdPais = idpais;
}

void Pais::setNombre(const char* nombre) {
	strcpy(_Nombre, nombre);
}
void Pais::setEstado(bool estado) {
	_Estado = estado;
}


///Getters
const char* Pais::getNombre() {
	return _Nombre;
}

bool Pais::getEstado() {
	return _Estado;
}
void Pais::CargarPais()
{
	int aux;
	char nom[50];

	do
	{
		cout << "Ingrese ID de Pais";
		cin >> aux;
		if (aux < 1)
		{
			cout << "El ID no puede ser negativo." << endl;
			anykey();
		}
	} while (aux < 1);

	this->setId(aux);

	cout << "Ingrese nombre de pais: ";
	cin.ignore();
	cin.getline(_Nombre, 49);

	this->setEstado(true);

}
int Pais::getIdPais() {
	return _IdPais;
}

bool Pais::grabarEnDisco()
{
	FILE* fReg = fopen("paises.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(Pais), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Pais::leerDeDisco(int pos)
{
	FILE* fReg = fopen("paises.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(Pais), SEEK_SET);

	int escribio = fread(this, sizeof(Pais), 1, fReg);

	fclose(fReg);

	return escribio;
}

void mostrarPais(int pais) {
	switch (pais)
	{
	case 1:
		cout << "ARGENTINA";
		break;
	case 2:
		cout << "BRASIL";
		break;
	case 3:
		cout << "USA";
		break;
	case 4:
		cout << "RUSIA";
		break;
	case 5:
		cout << "ALEMANIA";
		break;
	case 6:
		cout << "ISRAEL";
		break;
	case 7:
		cout << "BELGICA";
		break;
	case 8:
		cout << "FRANCIA";
		break;
	case 9:
		cout << "ITALIA";
		break;
	case 10:
		cout << "AUSTRIA";
		break;
	default:
		break;
	}
};