#include "Persona.h"
#include "Socio.h"

using namespace std;

Persona::Persona() {

	_dni = 0;
	strcpy(_nombre, " ");
	strcpy(_apellido, " ");
	Fecha _fecha_nacimiento;
	Domicilio _domicilio;
	strcpy(_email, " ");
	strcpy(_telefono, " ");
	_estado = true;
}

//SETTER
void Persona::setDni(int dni) { _dni = dni; }
void Persona::setNombre(char* nombre) { strcpy(_nombre, nombre); }
void Persona::setApellido(char* apelldo) { strcpy(_apellido, apelldo); }
void Persona::setFechanacimiento(Fecha fecha_nacimiento) { _fecha_nacimiento = fecha_nacimiento; }
void Persona::setDomicilio(Domicilio domicilio) { _domicilio = domicilio; }
void Persona::setEmail(char* email) { strcpy(_email, email); }
void Persona::setTelefono(char* telefono) { strcpy(_telefono, telefono); }
void Persona::setEstado(bool estado) { _estado = estado; }

//GETTER
int  Persona::getDni() { return _dni; }
const char* Persona::getNombre() { return _nombre; }
const char* Persona::getApellido() { return _apellido; }
Fecha Persona::getFechaNacimiento() { return _fecha_nacimiento; }
Domicilio Persona::getDomicilio() { return _domicilio; }
const char* Persona::getEmail() { return _email; }
const char* Persona::getTelefono() { return _telefono; }
bool Persona::getEstado() { return _estado; }

//	MOSTRAR Y CARGAR
int Persona::CargarPersona() 
{

	bool flag = false;
	int aux;
	char aux2[40];

	do {
		cout << "Ingrese el dni (0 para volver al menu anterior): ";
		cin >> aux;

		if (aux == 0)
		{
			return 0;
		}

		if (aux < 1000000)
		{
			cout << " El dni ingresado es incorrecto, intente nuevamente." << endl;
			flag = false;
		}
		else if (buscarSocioPorDNI(aux))
		{
			cout << "El socio ya se encuentra registrado." << endl;
			flag = false;
		}
		else
		{
			flag = true;
		}

	} while (!flag);

	this->setDni(aux);

	cout << "Ingrese el nombre: ";
	//cin.ignore();
	//cin.getline(_nombre, 29);

	 cin >> aux2;
	 this->setNombre(aux2);

	// Usar metodo set para ingreso	automatizado con 
	// excel o getline para ingreso manual (comentar uno y descomentar el otro)

	cout << "Ingrese el apellido: ";
	//cin.getline(aux2, 29);

	cin >> aux2;
	this->setApellido(aux2);

	// Usar metodo set para ingreso	automatizado con 
	// excel o getline para ingreso manual (comentar uno y descomentar el otro)
								
	todoAMayus(aux2);
	setApellido(aux2);

	cout << "- Ingrese la fecha de nacimiento -" << endl;
	_fecha_nacimiento.cargarFecha();
	cout << "- Domicilio -" << endl;
	_domicilio.cargarDomicilio();
	cout << "Ingrese email: ";
	//cin.ignore();
	//cin.getline(_email, 29);

	cin >> aux2;
	this->setEmail(aux2);

	// Usar metodo set para ingreso	automatizado con 
	// excel o getline para ingreso manual (comentar uno y descomentar el otro)

	cout << "Ingrese el telefono: ";
	cin >> aux2;
	this->setTelefono(aux2);

	_estado = true;

	return 1;
}

void Persona::MostrarPersona() {

	if (_estado) {
		cout << endl << "Dni: " << this->getDni() << endl;
		cout << "Nombre: " << this->_nombre << endl;
		cout << "Apellido: " << this->_apellido << endl;
		cout << "Fecha nacimiento: ";
		_fecha_nacimiento.mostrarFecha();
		cout << endl;
		_domicilio.mostrarDomicilio();
		cout << endl;
		cout << "Email : " << this->getEmail() << endl;
		cout << "Telefono: " << this->getTelefono() << endl;
	}
}