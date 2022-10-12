#include <iomanip>
#include "Socio.h"
#include "rlutil.h"
#include "Pago.h"
#include "funciones.h"
#include "ValorCuota.h"
#include "administrador.h"
#include "Solicitud.h"

using namespace rlutil;

Socio::Socio() {

	Persona();
	Fecha _fechaIngreso;
	_deudor = false;
	_idsocio = 0;
	_estado = false;
}

void Socio::setIdsocio(int idsocio) {
	_idsocio = idsocio;
}

void Socio::setEstado(bool estado) {
	_estado = estado;
}

void Socio::setFechaIngreso(Fecha fechaIng)
{
	_fechaIngreso = fechaIng;
}

void Socio::setDeudor(bool d)
{
	_deudor = d;
}

void Socio::setUltimoPago(Fecha pago)
{
	_UltimoPago = pago;
}

int	 Socio::getIdsocio() {
	return _idsocio;
}

Fecha Socio::getFechaIngreso()
{
	return _fechaIngreso;
}

bool Socio::getEstado() {
	return _estado;
}

bool Socio::getDeudor()
{
	return _deudor;
}

Fecha Socio::getUltimoPago()
{
	return _UltimoPago;
}

//METODOS DE DISCO
bool Socio::grabarEnDisco() {
	FILE* fReg = fopen("socios.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(Socio), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Socio::grabarBackupSocios() {
	FILE* fReg = fopen("backupSocios.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(Socio), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Socio::leerDeDisco(int pos) {
	FILE* fReg = fopen("socios.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(Socio), SEEK_SET);

	int escribio = fread(this, sizeof(Socio), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Socio::leerBackupSocios(int pos)
{
	FILE* fReg = fopen("backupSocios.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(Socio), SEEK_SET);

	int escribio = fread(this, sizeof(Socio), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Socio::modificarEnDisco(int pos) {
	FILE* fReg = fopen("socios.dat", "rb+");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(Socio), SEEK_SET);

	int escribio = fwrite(this, sizeof(Socio), 1, fReg);

	fclose(fReg);

	return escribio;
}

//Cargar y Mostrar
void Socio::cargar() {

	bool flag = false;
	bool flag2 = false;
	int aux = 0;
	int pos = 0;
	int ID = 0;

	Fecha fechaActual;
	Administrador admin;

	srand(time(NULL));

	aux = CargarPersona();

	if (aux == 0)
	{
		return;
	}

	this->setFechaIngreso(fechaActual);

	this->setIdsocio(generarIDSocio() + 1);

	this->setUltimoPago(fechaActual);

	this->setDeudor(false);

	this->setEstado(true);

	int idCuota = generarIDCuota() + 1;

	float valorCuota = getUltimoPrecioCuota();

	PagoCuota cuotaInicial(this->getIdsocio(), valorCuota, idCuota);

	cout << endl << " -- Valor de cuota a pagar: $ " << valorCuota << " --" << endl;

	do
	{
		cout << endl << "Ingrese el ID de administrador actual: ";
		cin >> ID;

		if (ID < 1)
		{
			cout << "ID inválido. Reintente por favor" << endl;
			flag2 = false;
			anykey();
		}
		else
		{

			pos = buscarAdministradorPorID(ID);

			if (pos > -1) {
				admin.leerDeDisco(pos);
				cuotaInicial.setIdAdmin(admin.getIdAdmin());
				cuotaInicial.grabarEnDisco();
				flag2 = true;
			}
			else
			{
				cout << "El ID no fue encontrado en el archivo de administradores" << endl;
				flag2 = false;
				anykey();
			}
		}

	} while (!flag2);

	this->grabarEnDisco();

	cout << endl << " -- Socio creado correctamente --" << endl << endl;

	this->mostrar();

}

void Socio::mostrar() {

	cout << "ID de socio: " << this->getIdsocio() << endl;
	cout << "Fecha de ingreso: ";
	_fechaIngreso.mostrarFecha();
	MostrarPersona();
	cout << endl;
	cout << "Fecha de último pago: ";
	_UltimoPago.mostrarFecha();

}

void Socio::mostrarSimplificado()
{

	if (this->getEstado())
	{
		cout << left;
		cout << setw(5) << this->getIdsocio();
		cout << setw(15) << this->getDni();
		cout << setw(20) << this->getApellido();
		cout << setw(20) << this->getNombre();
		cout << setw(20);
		if (this->getDeudor()) { cout << "ADEUDA"; }
		else { cout << "AL DIA"; }
		cout << setw(20);
		this->getUltimoPago().mostrarFecha();
		cout << setw(11) << " ";
		this->getFechaIngreso().mostrarFecha();
		cout << endl;
	}
}

void Socio::listar() {

	cout << left;
	cout << setw(5) << this->getIdsocio();
	cout << setw(15) << this->getDni();
	cout << setw(20) << this->getNombre();
	cout << setw(20) << this->getApellido();
	cout << setw(20);

	if (this->getDeudor()) { cout << "    ADEUDA"; }
	else { cout << "    AL DIA"; }

	this->getFechaIngreso().mostrarFecha();
	cout << endl;
}

/////////////////////////////////////
// Funciones globales Socio
/////////////////////////////////////

int generarIDSocio()
{
	return CantidadRegistrosSocio();
}

int buscarSocioPorID(int id)
{
	Socio socio;
	int pos = 0;

	while (socio.leerDeDisco(pos))
	{
		if (socio.getIdsocio() == id && socio.getEstado())
		{
			return pos;
		}
		pos++;
	}

	return -1;
}

bool buscarSocioPorDNI(int dni)
{
	Socio socio;
	int pos = 0;

	while (socio.leerDeDisco(pos++))
	{
		if (socio.getDni() == dni && socio.getEstado())
		{
			return true;
		}
	}

	return false;
}
int checkArchivoSocios() {

	FILE* fReg = fopen("socios.dat", "rb");

	if (fReg == NULL)
	{
		fReg = fopen("socios.dat", "wb");

		if (fReg == NULL)
		{
			cout << "Error al crear o leer archivo de socios." << endl;
			system("PAUSE > null");
			system("cls");
			return -1;
		}
		else
		{
			fclose(fReg);
			cout << "Archivo de socios creado correctamente" << endl;
			return 0;
		}
	}
	else
	{
		cout << "Socios: cargado OK" << endl;
	}

	fclose(fReg);

	return 1;

}
void listado_general_socios()
{
	Socio socio;
	int pos = 0;

	cout << left;
	cout << setw(5) << "ID";
	cout << setw(15) << "DNI";
	cout << setw(20) << "NOMBRE";
	cout << setw(20) << "APELLIDO";
	cout << setw(20) << "ESTADO DE CUOTA";
	cout << setw(10) << "FECHA INGRESO" << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;

	while (socio.leerDeDisco(pos++))
	{
		if (socio.getEstado())
		{
			socio.listar();
		}
	}
}

void cargar_nuevo_socio()
{
	Socio aux;

	aux.cargar();
}

void modificar_socio()
{
	int opcion;
	char confirmarSalida;
	bool salir = false;
	bool flag = false;
	int idaux;
	int pos = 0;
	Socio aux;

	while (!salir) {

		do
		{
			cout << "Ingrese ID de socio a modificar (0 para volver al menu anterior): ";
			cin >> idaux;

			if (idaux == 0)
			{
				return;
			}

			pos = buscarSocioPorID(idaux);

			if (pos <= -1)
			{
				cout << "El ID no se encuentra. Reintente por favor.";
				anykey();
				cls();
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

		cout << "\tSeleccione campo a modificar" << endl;
		cout << "--------------------------" << endl;
		cout << "1 - Modificar DNI " << endl;
		cout << "2 - Modificar nombre " << endl;
		cout << "3 - Modificar apellido " << endl;
		cout << "4 - Modificar fecha de nacimiento" << endl;
		cout << "5 - Modificar domicilio" << endl;
		cout << "6 - Modificar email" << endl;
		cout << "7 - Modificar telefono" << endl;
		cout << "--------------------------" << endl;
		cout << "0 - Volver al menú Socios" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			ModificarDNISocio(aux, pos);
			break;
		case 2:
			ModificarNombreSocio(aux, pos);
			break;
		case 3:
			ModificarApellidoSocio(aux, pos);
			break;
		case 4:
			ModificarFechaNac(aux, pos);
			break;
		case 5:
			ModificarDomicilio(aux, pos);
			break;
		case 6:
			ModificarEmail(aux, pos);
			break;
		case 7:
			ModificarTelefono(aux, pos);
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

void baja_socio()
{
	Socio aux;
	int id;
	bool flag = false;
	int pos = 0;
	char confirm;

	do {
		do {
			cout << "Ingrese ID de socio a dar de baja (0 para volver al menu anterior): ";
			cin >> id;

			if (id == 0)
			{
				return;
			}

			pos = buscarSocioPorID(id);

			if (pos <= -1 && id != 0)
			{
				cout << "El ID no se encuentra. Reintente por favor.";
				anykey();
				cls();
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

		cout << "¿Desea dar de baja el socio  N°" << id << "? (S/N): ";
		cin >> confirm;

		confirm = (tolower(confirm));

		if (confirm == 's')
		{
			eliminar_armas_socio(id);
			eliminar_solicitudes_pendientes(id);
			aux.setEstado(false);
			aux.modificarEnDisco(pos);
			cout << endl << " -- El socio N° " << aux.getIdsocio() << "ha sido dado de baja -- " << endl;
			cout << "Todas los solicitudes pendientes han sido dadas de baja" << endl;
			anykey();
			cls();
			flag = true;
		}
		else
		{
			cls();
			flag = false;
		}
	} while (!flag);

}

/////////////////////////////////////
// Funciones globales ModificarSocio
/////////////////////////////////////

void ModificarDNISocio(Socio aux, int pos)
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
			if (buscarSocioPorDNI(newDni))
			{
				cout << "El socio ya se encuentra registrado." << endl;
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

	aux.setDni(newDni);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();
}

void ModificarApellidoSocio(Socio aux, int pos)
{
	char newName[30];
	char confirm;
	bool flag = false;

	do
	{
		cout << "Ingrese apellido nuevo: ";
		cin.ignore();
		cin.getline(newName, 29);

		todoAMayus(newName);
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
void ModificarNombreSocio(Socio aux, int pos)
{
	char newName[30];
	char confirm;
	bool flag = false;

	do
	{
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
void ModificarFechaNac(Socio aux, int pos)
{
	Fecha nuevaFecha;
	char confirm;
	bool flag = false;

	do {
		nuevaFecha.cargarFecha();
		cls();

		cout << "Nueva fecha: ";
		nuevaFecha.mostrarFecha();

		cout << endl << "¿Confirma los cambios? (S/N): ";
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


	aux.setFechanacimiento(nuevaFecha);
	aux.modificarEnDisco(pos);

	cout << endl << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();
}
void ModificarDomicilio(Socio aux, int pos)
{
	Domicilio nuevoDomicilio;
	char confirm;
	bool flag = false;
	bool ok = false;

	do {
		nuevoDomicilio.cargarDomicilio();
		cls();

		cout << " -- Nuevo domicilio -- " << endl << endl;
		nuevoDomicilio.mostrarDomicilio();

		cout << endl << "¿Confirma los cambios? (S/N): ";
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

	aux.setDomicilio(nuevoDomicilio);
	aux.modificarEnDisco(pos);
	cout << endl << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();
}
void ModificarEmail(Socio aux, int pos)
{
	char confirm;
	bool flag = false;
	bool ok = false;
	char newMail[30];

	do {
		cout << "Ingrese nuevo E-Mail: ";
		cin.ignore();
		cin.getline(newMail, 29);
		cls();

		cout << "Nuevo E-mail: " << newMail << endl << endl;

		cout << endl << "¿Confirma los cambios? (S/N): ";
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

	aux.setEmail(newMail);
	aux.modificarEnDisco(pos);
	cout << endl << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();
}
void ModificarTelefono(Socio aux, int pos)
{
	char confirm;
	bool flag = false;
	bool ok = false;
	char tel[15];

	do {
		cout << "Ingrese nuevo telefono: ";
		cin.ignore();
		cin.getline(tel, 14);
		cls();

		cout << "Nuevo telefono: " << tel << endl << endl;

		cout << endl << "¿Confirma los cambios? (S/N): ";
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

	aux.setTelefono(tel);
	aux.modificarEnDisco(pos);
	cout << endl << " -- Los cambios han sido guardados -- " << endl;
	anykey();
	cls();
}

void listarSocioAlfabeticamente() {

	int cantReg = CantidadRegistrosSocio();

	if (cantReg == 0) {
		cout << "No hay socios registrados";
		anykey();
		return;
	}

	Socio* vDinamico;
	vDinamico = new Socio[cantReg];
	if (vDinamico == NULL) return;

	copiarSocios(vDinamico, cantReg);
	ordenarVector(vDinamico, cantReg);
	MostrarVector(vDinamico, cantReg);

	delete vDinamico;

}
void ordenarVector(Socio* vec, int tam) {
	Socio aux;

	for (int i = 0; i < tam - 1; i++) {
		for (int j = i + 1; j < tam; j++) {
			if (strcmp(vec[i].getApellido(), vec[j].getApellido()) > 0) {
				aux = vec[i];
				vec[i] = vec[j];
				vec[j] = aux;
			}
		}
	}
}
void copiarSocios(Socio* vec, int tam)
{
	for (int i = 0; i < tam; i++) {
		vec[i].leerDeDisco(i);
	}
}
int CantidadRegistrosSocio()
{
	FILE* p = fopen("socios.dat", "rb");
	if (p == NULL) {
		return 0;
	}

	size_t bytes;
	int cant_reg;

	fseek(p, 0, SEEK_END);
	bytes = ftell(p);
	fclose(p);
	cant_reg = bytes / sizeof(Socio);
	return cant_reg;
}
void MostrarVector(Socio* vec, int tam) {


	cout << left;
	cout << setw(5) << "ID";
	cout << setw(15) << "DNI";
	cout << setw(20) << "APELLIDO";
	cout << setw(20) << "NOMBRE";
	cout << setw(20) << "ESTADO DE CUOTA";
	cout << setw(20) << "FECHA ULTIMO PAGO";
	cout << setw(10) << "FECHA INGRESO" << endl;

	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < tam; i++)
	{
		vec[i].mostrarSimplificado();
	}

}

void listarSocioPorFecha() {
	int cantReg = CantidadRegistrosSocio();

	if (cantReg == 0) {
		cout << "No hay socios registrados";
		anykey();
		return;
	}

	Socio* vDinamico;
	vDinamico = new Socio[cantReg];
	if (vDinamico == NULL) return;


	copiarSocios(vDinamico, cantReg);
	ordenarVectorPorFecha(vDinamico, cantReg);
	MostrarVector(vDinamico, cantReg);

	delete vDinamico;

}
void ordenarVectorPorFecha(Socio* vec, int tam) {
	Socio aux;

	for (int i = 0; i < tam - 1; i++) {
		for (int j = i + 1; j < tam; j++) {
			if (vec[j].getFechaIngreso() > vec[i].getFechaIngreso()) {
				aux = vec[i];
				vec[i] = vec[j];
				vec[j] = aux;
			}
		}
	}
}

void listadoSolicitudesPendientesPorSocio()
{
	int ID = 0;
	int pos = 0;
	bool flag = false;
	Socio socio;
	Solicitud solicitud;

	do {

		cls();
		cout << "Ingrese el ID de socio a consultar (0 para volver al menu anterior): ";
		cin >> ID;


		if (ID == 0)
		{
			return;
		}

		if (ID < 1)
		{
			cout << endl << "ID invalido. Reintente por favor." << endl;
			flag = false;
			anykey();
		}
		else
		{
			pos = BuscarIdArchivo(ID);

			if (pos < 0)
			{
				cout << endl << "El ID no fue encontrado en el archivo de socios" << endl;
				flag = false;
				anykey();
			}

			else
			{
				flag = true;
			}
		}
	} while (!flag);

	SolicitudesPendientesPorSocio(ID);

}

void consulta_Por_Id() {

	int ID = 0;
	int pos = 0;
	bool flag = false;
	Socio socio;

	do {

		cls();
		cout << "Ingrese el ID a consultar (0 para volver al menu anterior): ";
		cin >> ID;


		if (ID == 0)
		{
			return;
		}

		if (ID < 1)
		{
			cout << endl << "ID invalido. Reintente por favor." << endl;
			flag = false;
			anykey();
		}
		else
		{
			pos = BuscarIdArchivo(ID);

			if (pos < 0)
			{
				cout << endl << "El ID no fue encontrado en el archivo de socios" << endl;
				flag = false;
				anykey();
			}

			else
			{
				flag = true;
			}
		}
	} while (!flag);

	if (pos > -1) {
		socio.leerDeDisco(pos);
		cout << endl;
		socio.mostrar();
		anykey();
	}
	else {
		cout << "El ID no fue encontrado en el archivo de socios" << endl;
	}
}
int BuscarIdArchivo(int Id) {
	Socio reg;
	int pos = 0;
	while (reg.leerDeDisco(pos))
	{
		if (reg.getIdsocio() == Id && reg.getEstado())return pos;
		pos++;
	}
	return -1;
}

void consultaPorDni() {

	int dniConsulta;
	int pos = 0;
	Socio socio;
	bool flag = false;

	do {

		cls();
		cout << "Ingrese el dni a consultar (0 para volver al menu anterior): ";
		cin >> dniConsulta;


		if (dniConsulta == 0)
		{
			return;
		}

		if (dniConsulta < 1)
		{
			cout << endl << "DNI invalido. Reintente por favor." << endl;
			flag = false;
			anykey();
		}
		else
		{
			pos = BuscarDniArchivo(dniConsulta);

			if (pos <= -1)
			{
				cout << endl << "El dni no fue encontrado en el archivo de socios" << endl;
				flag = false;
				anykey();
			}

			else
			{
				flag = true;
			}
		}
	} while (!flag);

	socio.leerDeDisco(pos);
	cout << endl;
	socio.mostrar();
	anykey();

}

int BuscarDniArchivo(int dniconsulta)
{
	Socio reg;
	int pos = 0;
	while (reg.leerDeDisco(pos))
	{
		if (reg.getDni() == dniconsulta)return pos;
		pos++;
	}
	return -1;
}

void consulta_Por_Apellido() {

	char apellidoConsulta[30];
	int pos = 0;
	Socio socio;
	cout << "Ingrese el apellido: ";
	cin.ignore();
	cin.getline(apellidoConsulta, 29);

	todoAMayus(apellidoConsulta);

	pos = BuscarApellidoArchivo(apellidoConsulta);

	if (pos == -1) {
		cout << "El apellido " << apellidoConsulta << " no existe en el archivo." << endl;
		anykey();
	}

}
int BuscarApellidoArchivo(const char* apellidoconsulta) {
	Socio reg;
	int pos = 0;
	bool flag = false;

	while (reg.leerDeDisco(pos))
	{
		if (strcmp(apellidoconsulta, reg.getApellido()) == 0 && reg.getEstado())
		{
			flag = true;
			reg.leerDeDisco(pos);
			reg.mostrar();
			anykey();
			cout << endl;
		};
		pos++;
	}

	if (!flag)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void backup_socios()
{
	Socio aux;
	int pos = 0;

	while (aux.leerDeDisco(pos++))
	{
		aux.grabarBackupSocios();
	}

	cout << "Archivo de backup de socios 'backupSocios.dat' grabado correctamente" << endl;
}