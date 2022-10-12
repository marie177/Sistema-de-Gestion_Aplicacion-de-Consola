#include "Domicilio.h"

using std::setprecision;
using namespace std;

Domicilio::Domicilio() {
	strcpy(_pais, " ");
	strcpy(_provincia, " ");
	strcpy(_localidad, " ");
	strcpy(_calle, " ");
	_altura = 0;
	strcpy(_dpto, " ");
	_cp = 0;
	_estado = true;
}

/// Setters
void Domicilio::setPais(const char* pais) {
	strcpy(_pais, pais);
}

void Domicilio::setProvincia(const char* provincia) {
	strcpy(_provincia, provincia);
}

void Domicilio::setLocalidad(const char* localidad) {
	strcpy(_localidad, localidad);
}

void Domicilio::setCalle(const char* calle) {
	strcpy(_calle, calle);
}

void Domicilio::setAltura(int altura) {
	_altura = altura;
}

void Domicilio::setDpto(const char* dpto) {
	strcpy(_dpto, dpto);
}

void Domicilio::setCP(int cp) {
	_cp = cp;
}

void Domicilio::setEstado(bool estado) {
	_estado = estado;
}

/// Getters
const char* Domicilio::getPais() {
	return _pais;
}

const char* Domicilio::getProvincia() {
	return _provincia;
}

const char* Domicilio::getLocalidad() {
	return _localidad;
}

const char* Domicilio::getCalle() {
	return _calle;
}

int Domicilio::getAltura() {
	return _altura;
}

const char* Domicilio::getDpto() {
	return _dpto;
}

int Domicilio::getCP() {
	return _cp;
}

bool Domicilio::getEstado() {
	return _estado;
}

// Cargar y Mostrar
void Domicilio::cargarDomicilio() {
	char aux[50];
	cout << "País: ";
	//cin.ignore();
	//cin.getline(_pais, 49);

	cin >> aux;
	this->setPais(aux);

	// Usar metodo set para ingreso	automatizado con 
	// excel o getline para ingreso manual (comentar uno y descomentar el otro)

	cout << "Provincia: ";
	//cin.getline(_provincia, 49);

	cin >> aux;
	this->setProvincia(aux);

	cout << "Localidad: ";
	//cin.getline(_localidad, 49);

	cin >> aux;
	this->setLocalidad(aux);

	// Usar metodo set para ingreso	automatizado con 
	// excel o getline para ingreso manual (comentar uno y descomentar el otro)

	cout << "Calle: ";
	//cin.getline(_calle, 49);

	cin >> aux;
	this->setCalle(aux);

	// Usar metodo set para ingreso	automatizado con 
	// excel o getline para ingreso manual (comentar uno y descomentar el otro)

	do {
		cout << "Altura: ";
		cin >> _altura;
		if (_altura <= 0) {
			cout << "La altura es incorrecta. Ingrese nuevamente." << endl;
		}
	} while (_altura < 0);

	do {
		cout << "Departamento o piso (si es casa, ingrese PB): ";
		//cin.ignore();
		//cin.getline(_dpto, 9);

		cin >> aux;
		this->setDpto(aux);

		// Usar metodo set para ingreso	automatizado con 
		// excel o getline para ingreso manual (comentar uno y descomentar el otro)

		if (strlen(_dpto) < 0) {
			cout << "El depto ingresado es incorrecto. Ingrese nuevamente." << endl;
		}
	} while (strlen(_dpto) < 0);

	do {
		cout << "Código Postal: ";
		cin >> _cp;
		if (_cp <= 0) {
			cout << "El código postal ingresado es incorrecto. Ingrese nuevamente." << endl;
		}
	} while (_cp <= 0);


	_estado = true;

}

void Domicilio::mostrarDomicilio() {
	if (_estado) {

		cout << "País: " << _pais << endl;

		cout << "Provincia: " << _provincia << endl;

		cout << "Localidad: " << _localidad << endl;

		cout << "Calle: " << _calle << endl;

		cout << "Altura: " << _altura << endl;

		cout << "Dpto: " << _dpto << endl;

		cout << "Código Postal: " << _cp;

	}
}