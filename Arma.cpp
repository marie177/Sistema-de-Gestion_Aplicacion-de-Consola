#include "Arma.h"

using namespace std;
using namespace rlutil;

Arma::Arma(int idArma, const char* modelo, float calibre, int tipoArma, int numSerie, bool estado, int _idPais, int idSocio) {
	_idArma = idArma;
	strcpy(_modelo, modelo);
	_calibre = calibre;
	_idPaisFabricacion = _idPais;
	_tipoArma = tipoArma;
	_numSerie = numSerie;
	_idSocio = idSocio;
	_estado = estado;
};

void Arma::setIdArma(int idArma) {
	_idArma = idArma;
};

void Arma::setIdSocio(int idSocio) {
	_idSocio = idSocio;
};

void Arma::setModelo(const char* modelo) {
	strcpy(_modelo, modelo);
};

void Arma::setCalibre(float calibre) {
	_calibre = calibre;
};

void Arma::setidPaisFabricacion(int idPaisFabricacion) {
	_idPaisFabricacion = idPaisFabricacion;
};

void Arma::setTipoArma(int tipoArma) {
	_tipoArma = tipoArma;
};

void Arma::setNumSerie(int numSerie) {
	_numSerie = numSerie;
};

void Arma::setEstado(bool estado) {
	_estado = estado;
};

int Arma::getIdArma() {
	return _idArma;
};

int Arma::getIdSocio() {
	return _idSocio;
};

const char* Arma::getModelo() {
	return _modelo;
};

float Arma::getCalibre() {
	return _calibre;
};

int Arma::getidPaisFabricacion() {
	return _idPaisFabricacion;
};

int Arma::getTipoArma() {
	return _tipoArma;
};

int Arma::getNumSerie() {
	return _numSerie;
};

bool Arma::getEstado() {
	return _estado;
};

void Arma::cargarArma() {

	int aux;
	char aux2[30];
	bool flag = false;
	int pos = 0;

	cout << "Ingrese el Modelo del Arma: ";

	cin >> aux2;
	this->setModelo(aux2);

	//cin.ignore();
	//cin.getline(_modelo, 29);

	// Usar metodo set para ingreso	automatizado con 
	// excel o getline para ingreso manual (comentar uno y descomentar el otro)

	cout << "Ingrese el Calibre del Arma: ";
	cin >> _calibre;

	do {
		cout << "1 - Argentina" << endl;
		cout << "2 - Brasil" << endl;
		cout << "3 - USA" << endl;
		cout << "4 - Rusia" << endl;
		cout << "5 - Alemania" << endl;
		cout << "6 - Israel" << endl;
		cout << "7 - Belgica" << endl;
		cout << "8 - Francia" << endl;
		cout << "9 - Italia" << endl;
		cout << "10 - Austria" << endl << endl;
		cout << "Ingrese el Pais de Fabricacion: ";
		cin >> aux;

		if (aux < 1 || aux > 10)
		{
			cout << "ID de pais incorrecto." << endl;
			flag = false;
		}
		else
		{
			flag = true;
		}

	} while (!flag);

	this->setidPaisFabricacion(aux);

	do {

		cout << "1 - Pistolas" << endl;
		cout << "2 - Escopetas" << endl;
		cout << "3 - Subfusiles" << endl;
		cout << "4 - Carabinas" << endl;
		cout << "5 - Fusiles automaticos" << endl << endl;
		cout << "Ingrese el tipo de arma: ";
		cin >> aux;

		if (aux < 1 || aux > 5)
		{
			cout << endl << "Tipo de arma inválido." << endl;
			anykey();
			cls();
			flag = false;
		}
		else
		{
			flag = true;
		}

	} while (!flag);

	this->setTipoArma(aux);

	do {
		cout << "Ingrese número de serie: ";
		cin >> aux;

		if (aux < 1)
		{
			cout << "Número de serie inválido." << endl;
			flag = false;
		}
		else
		{
			pos = buscarArmaPorNumSerie(aux);

			if (pos != -1)
			{
				cout << "El número de serie ya ha sido registrado";
				anykey();
				cls();
				flag = false;
			}
			else
			{
				flag = true;
			}
		}

	} while (!flag);

	this->setNumSerie(aux);

	this->setIdArma(generarIdArma() + 1);

	this->setEstado(true);

	cout << endl << "-- Arma agregada con exito. --" << endl << endl;

	this->mostrarArma();

};

void Arma::mostrarArma() {

	cout << "Id del Arma: " << this->getIdArma();
	cout << endl;
	cout << "Modelo del Arma: " << this->getModelo();
	cout << endl;
	cout << "Calibre del Arma: " << this->getCalibre();
	cout << endl;
	cout << "Pais de Fabricacion: ";
	mostrarPais(this->getidPaisFabricacion());
	cout << endl;
	cout << "Tipo de Arma: " << this->getTipoArma();
	cout << endl;
	cout << "Numero de Serie: " << this->getNumSerie();
	cout << endl;

};

void Arma::listar()
{
	cout << left;
	cout << setw(5) << this->getIdArma();
	cout << setw(18) << this->getModelo();
	cout << setw(10) << this->getCalibre();
	cout << setw(15);
	mostrarPais(this->getidPaisFabricacion());
	cout << setw(18);
	mostrarTipoArma(this->getTipoArma());
	cout << setw(15) << this->getNumSerie();
	cout << endl;

}

void Arma::listarPorNumSerie()
{
	if (this->getEstado())
	{
		cout << left;
		cout << setw(18) << this->getNumSerie();
		cout << setw(9) << this->getIdArma();
		cout << setw(18) << this->getModelo();
		cout << setw(10) << this->getCalibre();
		cout << setw(15);
		mostrarPais(this->getidPaisFabricacion());
		cout << setw(20);
		mostrarTipoArma(this->getTipoArma());
		cout << endl;
	}
}

void Arma::listarPorTipoArma()
{
	if (this->getEstado())
	{
		cout << left;
		cout << setw(18);
		mostrarTipoArma(this->getTipoArma());
		cout << setw(9) << this->getIdArma();
		cout << setw(18) << this->getModelo();
		cout << setw(10) << this->getCalibre();
		cout << setw(15);
		mostrarPais(this->getidPaisFabricacion());
		cout << setw(18) << this->getNumSerie();
		cout << endl;

	}
}

void Arma::listarPorTipoCalibre() {
	if (this->getEstado())
	{
		cout << left;
		cout << setw(10) << this->getCalibre();
		cout << setw(9) << this->getIdArma();
		cout << setw(18) << this->getModelo();
		cout << setw(18);
		mostrarTipoArma(this->getTipoArma());
		cout << setw(15);
		mostrarPais(this->getidPaisFabricacion());
		cout << setw(18) << this->getNumSerie();
		cout << endl;
	}
}

void Arma::listarPorIdArma() {
	if (this->getEstado())
	{
		cout << left;
		cout << setw(9) << this->getIdArma();
		cout << setw(18) << this->getNumSerie();
		cout << setw(18) << this->getModelo();
		cout << setw(10) << this->getCalibre();
		cout << setw(15);
		mostrarPais(this->getidPaisFabricacion());
		cout << setw(18);
		mostrarTipoArma(this->getTipoArma());
		cout << endl;
	}
}

bool Arma::grabarEnDisco() {
	FILE* fReg = fopen("armas.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(Arma), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Arma::leerDeDisco(int pos) {
	FILE* fReg = fopen("armas.dat", "rb");
	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}
	fseek(fReg, pos * sizeof(Arma), SEEK_SET);

	int escribio = fread(this, sizeof(Arma), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool Arma::modificarEnDisco(int pos) {
	FILE* armaReg = fopen("armas.dat", "rb+");

	if (armaReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}
	fseek(armaReg, pos * sizeof(Arma), SEEK_SET);
	int escribio = fwrite(this, sizeof(Arma), 1, armaReg);
	fclose(armaReg);

	return escribio;
}

/////////////////////////////////////
// Funciones globales Armas
/////////////////////////////////////

int generarIdArma() {

	Arma arma;
	int id = 0;
	int pos = 0;

	while (arma.leerDeDisco(pos++)) {
		id = arma.getIdArma();
	};

	return id;
}

int checkArchivoArmas() {

	FILE* solicReg = fopen("armas.dat", "rb");

	if (solicReg == NULL)
	{
		solicReg = fopen("armas.dat", "wb");

		if (solicReg == NULL)
		{
			cout << "Error al crear o leer archivo de armas." << endl;
			system("PAUSE > null");

			return -1;
		}
		else
		{
			fclose(solicReg);
			cout << "Archivo de armas creado correctamente" << endl;

			return 0;
		}
	}
	else
	{
		cout << "Armas: cargado OK" << endl;
	}

	fclose(solicReg);
	return 1;
}

//Funcion que busca el Arma por su ID y retorna su posición en el Archivo, si no encuentra el Arma con ese ID retorna -1 
int buscarArmaPorId(int id) {
	Arma arma;
	int pos = 0;
	while (arma.leerDeDisco(pos))
	{
		if (arma.getIdArma() == id && arma.getEstado())
		{
			return pos;
		}
		pos++;
	}

	return -1;

}

void mostrarTipoArma(int tipo) {

	switch (tipo)
	{
	case 1:
		cout << "PISTOLA";
		break;
	case 2:
		cout << "ESCOPETA";
		break;
	case 3:
		cout << "SUBFUSIL";
		break;
	case 4:
		cout << "CARABINA";
		break;
	case 5:
		cout << "FUSIL AUTOMÁTICO";
		break;
	default:
		break;
	}
};

void crear_nueva_arma()
{
	Arma arma;

	arma.cargarArma();
	arma.grabarEnDisco();

}

void eliminarArma(int idArma) {
	Arma reg;
	int pos = buscarArmaPorId(idArma);
	if (pos > -1) {
		reg.leerDeDisco(pos);
		reg.setEstado(false);
		reg.modificarEnDisco(pos);
	}
}

void modificar_arma() {
	int opcion;
	char confirmarSalida;
	bool salir = false;
	bool flag = false;
	int idaux;
	int pos = 0;
	Arma aux;

	while (!salir) {

		do
		{
			cout << "Ingrese ID de arma a modificar (0 para volver al menu anterior): ";
			cin >> idaux;

			if (idaux == 0)
			{
				return;
			}

			pos = buscarArmaPorId(idaux);

			if (idaux < 0)
			{
				cout << "ID inválido. Reintente por favor." << endl << endl;
				anykey();
				cls();
				flag = false;
			}
			else 
				if (pos < 0)
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
		aux.mostrarArma();

		cout << "--------------------------------" << endl;
		cout << "  Seleccione campo a modificar" << endl;
		cout << "--------------------------------" << endl;
		cout << "1 - Modificar modelo " << endl;
		cout << "2 - Modificar calibre " << endl;
		cout << "3 - Modificar pais de fabricación " << endl;
		cout << "4 - Modificar número de serie" << endl;
		cout << "--------------------------------" << endl;
		cout << "0 - Volver al menú Armas" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			ModificarModelo(aux, pos);
			break;
		case 2:
			ModificarCalibre(aux, pos);
			break;
		case 3:
			ModificarPais(aux, pos);
			break;
		case 4:
			ModificarNumSerie(aux, pos);
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

void listadoGeneralArmas()
{
	Arma arma;
	int pos = 0;

	cout << left;
	cout << setw(5) << "ID";
	cout << setw(18) << "MODELO";
	cout << setw(10) << "CALIBRE";
	cout << setw(15) << "PAIS FABR.";
	cout << setw(18) << "TIPO DE ARMA";
	cout << setw(16) << "NÚMERO DE SERIE" << endl;
	cout << "-----------------------------------------------------------------------------------" << endl;

	while (arma.leerDeDisco(pos++))
	{
		if (arma.getEstado())
		{
			arma.listar();
		}
	}
}

void listadoDeArmasPorNumDeSerie() {

	int cantRegArmas = buscarCantidadArmas();

	if (cantRegArmas == 0) {
		cout << "No existen Armas registradas." << endl;
		return;
	}

	Arma* armas = new Arma[cantRegArmas];

	if (armas == NULL) { return; }

	copiarArmas(armas, cantRegArmas);
	ordernarVecPorNumSerie(armas, cantRegArmas);
	mostrarListadoArmas(armas, cantRegArmas);

	delete armas;
}

int buscarCantidadArmas() {

	FILE* p = fopen("armas.dat", "rb");

	if (p == NULL) { return 0; }

	fseek(p, 0, SEEK_END);
	size_t bytes = ftell(p);
	fclose(p);

	unsigned int cantidadArmas = bytes / sizeof Arma;
	return cantidadArmas;
}
void copiarArmas(Arma* vArma, int tam) {
	for (int i = 0; i < tam; i++)
	{
		vArma[i].leerDeDisco(i);
	}
}
void ordernarVecPorNumSerie(Arma* vArma, int tam) {

	Arma aux;

	for (int i = 0; i < tam - 1; i++) {
		for (int j = i + 1; j < tam; j++) {
			if (vArma[i].getNumSerie() > vArma[j].getNumSerie()) {
				aux = vArma[i];
				vArma[i] = vArma[j];
				vArma[j] = aux;
			}
		}
	}
}
void mostrarListadoArmas(Arma* vArma, int tam) {

	cout << left;
	cout << setw(15) << "NÚM DE SERIE";
	cout << setw(9) << "ID ARMA";
	cout << setw(18) << "MODELO";
	cout << setw(10) << "CALIBRE";
	cout << setw(15) << "PAIS FABR.";
	cout << setw(18) << "TIPO DE ARMA" << endl;
	cout << "-----------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < tam; i++) {
		vArma[i].listarPorNumSerie();
	}
}

void listados_Armas_Por_Tipo() {
	int cantReg = CantidadRegistroArmas();
	if (cantReg == 0) {
		cout << "No hay armas registrados";
		return;
	}

	Arma* vDinamico;
	vDinamico = new Arma[cantReg];
	if (vDinamico == NULL) return;
	copiarArmas(vDinamico, cantReg);
	ordenarVector(vDinamico, cantReg);
	MostrarVector(vDinamico, cantReg);
}
int CantidadRegistroArmas() {
	FILE* p = fopen("armas.dat", "rb");
	if (p == NULL) {
		return 0;
	}

	size_t bytes;
	int cant_reg;

	fseek(p, 0, SEEK_END);
	bytes = ftell(p);
	fclose(p);
	cant_reg = bytes / sizeof(Arma);
	return cant_reg;
}
void ordenarVector(Arma* vec, int tam) {
	Arma aux;

	for (int i = 0; i < tam - 1; i++) {
		for (int j = i + 1; j < tam; j++) {
			if (vec[i].getTipoArma() > vec[j].getTipoArma()) {
				aux = vec[i];
				vec[i] = vec[j];
				vec[j] = aux;
			}
		}
	}
}
void MostrarVector(Arma* vec, int tam) {

	cout << left;
	cout << setw(18) << "TIPO DE ARMA";
	cout << setw(9) << "ID ARMA";
	cout << setw(18) << "MODELO";
	cout << setw(10) << "CALIBRE";
	cout << setw(15) << "PAIS FABR.";
	cout << setw(18) << "NÚMERO DE SERIE" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < tam; i++)
	{
		vec[i].listarPorTipoArma();
	}
}

void consultaArmasPorNumSerie() {

	int cantArmas = buscarCantidadArmas();
	int numSerie;

	if (cantArmas == 0) {
		cout << "No se encontraron Registros de Armas cargados.";
		return;
	}

	Arma* vecArmas = new Arma[cantArmas];

	if (vecArmas == NULL) { return; }

	copiarArmas(vecArmas, cantArmas);

	cout << "Ingrese el Numero de Serie: ";
	cin >> numSerie;

	mostrarConsultaArmasPorNumSerie(vecArmas, cantArmas, numSerie);

}
void mostrarConsultaArmasPorNumSerie(Arma* vecArma, int tamVec, int numSerie) {

	cls();

	cout << " -- CONSULTAS DE ARMAS POR NUMERO DE SERIE --" << endl;

	cout << left;
	cout << setw(18) << "NÚMERO DE SERIE";
	cout << setw(9) << "ID ARMA";
	cout << setw(18) << "MODELO";
	cout << setw(10) << "CALIBRE";
	cout << setw(15) << "PAIS FABR.";
	cout << setw(20) << "TIPO DE ARMA" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;


	for (int i = 0; i < tamVec; i++) {
		if (vecArma[i].getNumSerie() == numSerie) {
			vecArma[i].listarPorNumSerie();
		}
	}
}

void consultaArmasPorIdArma() {
	int cantArmas = buscarCantidadArmas();
	int numID;

	if (cantArmas == 0) {
		cout << "No se encontraron Registros de Armas cargados.";
		return;
	}

	Arma* vecArmas = new Arma[cantArmas];

	if (vecArmas == NULL) { return; }

	copiarArmas(vecArmas, cantArmas);

	cout << "Ingrese el Numero de ID: ";
	cin >> numID;

	mostrarConsultaArmasPorId(vecArmas, cantArmas, numID);
}
void mostrarConsultaArmasPorId(Arma* vecArma, int tamVec, int numId) {
	cls();

	cout << " -- CONSULTAS DE ARMAS POR NUMERO DE SERIE --" << endl;

	cout << left;
	cout << setw(9) << "ID ARMA";
	cout << setw(18) << "NÚMERO DE SERIE";
	cout << setw(18) << "MODELO";
	cout << setw(10) << "CALIBRE";
	cout << setw(15) << "PAIS FABR.";
	cout << setw(18) << "TIPO DE ARMA" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;


	for (int i = 0; i < tamVec; i++) {
		if (vecArma[i].getIdArma() == numId) {
			vecArma[i].listarPorIdArma();
		}
	}
}

int buscarArmaPorNumSerie(int id)
{
	Arma arma;
	int pos = 0;

	while (arma.leerDeDisco(pos))
	{
		if (arma.getNumSerie() == id && arma.getEstado())
		{
			return pos;
		}
		pos++;
	}

	return -1;
}

void listados_Armas_Por_Calibre() {
	int cantReg = CantidadRegistroArmas();
	if (cantReg == 0) {
		cout << "No hay armas registrados";
		return;
	}

	Arma* vDinamico;
	vDinamico = new Arma[cantReg];
	if (vDinamico == NULL) return;
	copiarArmas(vDinamico, cantReg);
	ordenarVectorPorCalibre(vDinamico, cantReg);
	MostrarVectorPorCalibre(vDinamico, cantReg);
}
void ordenarVectorPorCalibre(Arma* vec, int tam) {
	Arma aux;

	for (int i = 0; i < tam - 1; i++) {
		for (int j = i + 1; j < tam; j++) {
			if (vec[i].getCalibre() > vec[j].getCalibre()) {
				aux = vec[i];
				vec[i] = vec[j];
				vec[j] = aux;
			}
		}
	}
}
void MostrarVectorPorCalibre(Arma* vec, int tam) {
	cout << left;
	cout << setw(10) << "CALIBRE";
	cout << setw(9) << "ID ARMA";
	cout << setw(18) << "MODELO";
	cout << setw(18) << "TIPO DE ARMA";
	cout << setw(15) << "PAIS FABR.";
	cout << setw(18) << "NÚMERO DE SERIE" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < tam; i++)
	{
		vec[i].listarPorTipoCalibre();
	}
}

void ModificarModelo(Arma aux, int pos)
{
	bool flag = false;
	bool confirmar = false;
	char newModel[30];

	cout << "Ingrese modelo nuevo: ";
	cin.ignore();
	cin.getline(newModel, 29);
	aux.setModelo(newModel);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;

	anykey();
	cls();
}
void ModificarCalibre(Arma aux, int pos)
{
	bool flag = false;
	bool confirmar = false;
	float newCalibre;

	do {

		cout << "Ingrese nuevo calibre: ";
		cin >> newCalibre;

		if (newCalibre <= 0)
		{
			cout << endl << "Calibre invalido. Reingrese de nuevo, por favor";
			anykey();
			cls();
			flag = false;
		}
		else
		{
			flag = true;
		}
	} while (!flag);

	aux.setCalibre(newCalibre);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;

	anykey();
	cls();
}
void ModificarPais(Arma aux, int pos)
{
	bool flag = false;
	bool confirmar = false;
	int newPais;

	do {

		cout << "Ingrese nuevo ID de Pais: ";
		cin >> newPais;

		if (newPais <= 0)
		{
			cout << endl << "Pais inválido. Reingrese de nuevo por favor";
			anykey();
			cls();
			flag = false;
		}
		else
		{
			flag = true;
		}
	} while (!flag);

	aux.setidPaisFabricacion(newPais);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;

	anykey();
	cls();
}
void ModificarNumSerie(Arma aux, int pos)
{
	bool flag = false;
	bool confirmar = false;
	int newNum;

	do {

		cout << "Ingrese nuevo número de serie: ";
		cin >> newNum;

		if (newNum <= 0)
		{
			cout << endl << "Número de serie inválido. Reingrese de nuevo por favor";
			anykey();
			cls();
			flag = false;
		}
		else if (buscarArmaPorId(newNum) != -1)
		{
			cout << endl << "El número de serie ingresado ya existe.";
			anykey();
			cls();
			flag = false;
		}
		else
		{
			flag = true;
		}
	} while (!flag);

	aux.setNumSerie(newNum);
	aux.modificarEnDisco(pos);

	cout << " -- Los cambios han sido guardados -- " << endl;

	anykey();
	cls();
}

void porcentaje_armas_por_tipo()
{
	int cantReg = CantidadRegistroArmas();

	if (cantReg == 0)
	{
		cout << "No se registraron armas al dia de la fecha" << endl;
		return;
	}

	Arma arma;
	int pos = 0;
	int cantArmasActivas = 0;
	const int TIPOSARMAS = 5;
	int vArmas[TIPOSARMAS] = { 0 };
	float porc[TIPOSARMAS] = { 0 };

	while (arma.leerDeDisco(pos))
	{
		if (arma.getEstado())
		{
			cantArmasActivas++;

			vArmas[arma.getTipoArma() - 1]++;

		}
		pos++;
	}

	for (int i = 0; i < TIPOSARMAS; i++)
	{
		porc[i] = (float)vArmas[i] * 100 / cantArmasActivas;
	}

	MostrarVectorArmas(vArmas, porc, TIPOSARMAS);

}
void MostrarVectorArmas(int* vArmas, float* porc, int tam)
{
	string tipo[5] = { "Pistola","Escopeta","Subfusil","Carabina","Fusil Automático" };
	cout << left;
	cout << setw(17) << "TIPO";
	cout << setw(10) << "CANTIDAD";
	cout << setw(9) << "PORCENTAJE" << endl;
	cout << "--------------------------------" << endl;

	for (int i = 0; i < tam; i++)
	{
		cout << setw(17) << tipo[i];
		cout << setw(10) << vArmas[i];
		cout << setw(1) << "% ";
		cout << setw(9) << porc[i] << endl;
	}
}

void consultaArmasPorModelo()
{

	Arma arma;
	int pos = 0;
	char modeloABuscar[30];
	char modeloArchivo[30];

	cout << "Ingrese el modelo a buscar: ";
	cin.ignore();
	cin.getline(modeloABuscar, 29);

	todoAMayus(modeloABuscar);

	cout << left;
	cout << setw(5) << "ID";
	cout << setw(18) << "MODELO";
	cout << setw(10) << "CALIBRE";
	cout << setw(15) << "PAIS FABR.";
	cout << setw(18) << "TIPO DE ARMA";
	cout << setw(15) << "NÚMERO DE SERIE" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;

	while (arma.leerDeDisco(pos++))
	{
		strcpy(modeloArchivo, arma.getModelo());
		todoAMayus(modeloArchivo);

		if (arma.getEstado() && strcmp(modeloABuscar, modeloArchivo) == 0)
		{
			arma.listar();
		}
	}
}

void eliminar_armas_socio(int id)
{
	Arma arma;
	int pos = 0;

	while (arma.leerDeDisco(pos))
	{
		if (arma.getIdSocio() == id)
		{
			arma.setEstado(false);
			arma.modificarEnDisco(pos);
		}
		pos++;
	}
}