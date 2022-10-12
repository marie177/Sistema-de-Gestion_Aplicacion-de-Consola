#include "Solicitud.h"

using namespace std;
using namespace rlutil;

Solicitud::Solicitud(int idSolicitud, int idAdmin, int idSocio, bool estado, int idArma, int a, bool editable) {

	_idSolicitud = idSolicitud;
	_idAdministrador = idAdmin;
	_idSocio = idSocio;
	Fecha _FechaSolicitud;
	_idArma = idArma;
	_aprobado = a;
	_estado = estado;
	_editable = editable;
};

void Solicitud::setIdSolicitud(int idSolicitud) {
	_idSolicitud = idSolicitud;
};
void Solicitud::setIdAdministrador(int idAdmin) {
	_idAdministrador = idAdmin;
};
void Solicitud::setIdSocio(int idSocio) {
	_idSocio = idSocio;
};
void Solicitud::setIdArma(int idArma) {
	_idArma = idArma;
};
void Solicitud::setFechaSolicitud(Fecha FechaSolicitud) {
	_FechaSolicitud = FechaSolicitud;
}
void Solicitud::setAprobado(int a)
{
	_aprobado = a;
};
void Solicitud::setEditable(bool e)
{
	_editable = e;
}
void Solicitud::setEstado(bool estado) {
	_estado = estado;
};

int Solicitud::getIdSolicitud() { return _idSolicitud; }
int Solicitud::getIdAdministrador() { return _idAdministrador; }
int Solicitud::getIdSocio() { return _idSocio; }
int Solicitud::getIdArma() { return _idArma; }
Fecha Solicitud::getFechaSolicitud() { return _FechaSolicitud; }
int Solicitud::getAprobado() { return _aprobado; }
bool Solicitud::getEditable() { return _editable; }
bool Solicitud::getEstado() { return _estado; }

void Solicitud::cargarSolicitud() {

	int aux;
	int pos = 0;
	int posSocio = 0;
	Arma armaRegistro;
	Fecha fechaSolicitud;
	Administrador admin;
	Socio socio;
	bool verifica = false;

	do {
		cout << "Ingrese el ID del Administrador (0 para volver al menu anterior): ";
		cin >> aux;

		if (aux == 0)
		{
			return;
		}

		pos = buscarAdministradorPorID(aux);

		if (aux < 0)
		{
			cout << "ID inválido. Reintente por favor";
			anykey();
			cls();
			verifica = false;
		}
		else if (pos <= -1)
		{
			cout << "El ID ingresado no esta registrado. Reintente por favor." << endl;
			anykey();
			cls();
			verifica = false;
		}
		else
		{
			verifica = true;
		}

	} while (verifica == false);

	admin.leerDeDisco(pos);
	this->setIdAdministrador(admin.getIdAdmin());
	verifica = false;

	do {
		cout << "Ingrese el ID del Socio: ";
		cin >> aux;

		posSocio = buscarSocioPorID(aux);

		if (aux < 0)
		{
			cout << "ID inválido. Reintente por favor";
			anykey();
			cls();
			verifica = false;
		}
		else if (posSocio < 0)
		{
			cout << "El ID de socio no esta registrado o es incorrecto. Ingrese de nuevo por favor." << endl;
		}
		else
		{
			socio.leerDeDisco(posSocio);

			if (socio.getDeudor())
			{
				cout << "El socio n° " << socio.getIdsocio() << " registra deuda al dia de la fecha." << endl;
				cout << "No puede generar solicitudes nuevas." << endl;
				cout << "Para registrar solicitudes nuevas, regularize su situación.";
				anykey();
				cls();
				verifica = false;
			}
			else
			{
				verifica = true;
			}
		}

	} while (verifica == false);

	this->setIdSocio(aux);

	armaRegistro.cargarArma();
	armaRegistro.setIdSocio(aux);

	this->setIdArma(armaRegistro.getIdArma());

	this->setFechaSolicitud(fechaSolicitud);

	this->setEstado(true);
	this->setAprobado(0);
	this->setIdSolicitud(generarIdSolicitud() + 1);
	this->setEditable(true);

	float valorSolicitud = getUltimoPrecioSolicitud();

	cout << endl << "Valor de la solicitud: $" << valorSolicitud << endl;

	int idPago = generarIDPagoSolicitud() + 1;

	PagoSolicitud pago(aux, idPago, valorSolicitud, admin.getIdAdmin());
	pago.grabarEnDisco();

	armaRegistro.grabarEnDisco();

	if (this->grabarEnDisco()) {
		cout << "La Solicitud " << this->getIdSolicitud() << " fue Ingresada correctamente.";
		cout << endl;
	}
	else {
		cout << "Hubo un Error al crear la Solicitud." << endl;
	}
}
void Solicitud::mostrarSolicitud() {

	Arma arma;
	int posArma;

	if (this->getEstado())
	{
		cout << endl;
		cout << "SOLICITUD N° " << this->getIdSolicitud();
		cout << endl;
		cout << "Id de Solicitud: " << this->getIdSolicitud();
		cout << endl;
		cout << "Id del Socio: " << this->getIdSocio();
		cout << endl;
		cout << "Id del Administrador: " << this->getIdAdministrador();
		cout << endl;
	}

	//Falta mostrar el Arma de la Solicitud
	posArma = buscarArmaPorId(this->getIdArma());
	if (posArma == -1) {
		cout << "Hubo un error. No se encontró el Arma de La Solicitud: " << this->getIdSolicitud();
		cout << endl;
	}
	else {
		arma.leerDeDisco(posArma);
		arma.mostrarArma();
	}

	cout << endl;
	cout << "Fecha en la que se Registró la Solicitud: ";
	this->_FechaSolicitud.mostrarFecha();
	cout << endl;

};

bool Solicitud::grabarEnDisco() {

	FILE* solicReg = fopen("solicitudes.dat", "ab");
	if (solicReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}
	bool escribio = fwrite(this, sizeof(Solicitud), 1, solicReg);
	fclose(solicReg);

	return escribio;
}
bool Solicitud::leerDeDisco(int pos) {
	FILE* solicReg = fopen("solicitudes.dat", "rb");
	if (solicReg == NULL) {
		cout << "No se puede abrir el archivo.";
		return false;
	}
	fseek(solicReg, pos * sizeof(Solicitud), SEEK_SET);
	bool leyo = fread(this, sizeof(Solicitud), 1, solicReg);
	fclose(solicReg);

	return leyo;
}
bool Solicitud::modificarEnDisco(int pos) {
	FILE* solicReg = fopen("solicitudes.dat", "rb+");
	if (solicReg == NULL) {
		cout << "No se puede abrir el archivo.";
		return false;
	}
	fseek(solicReg, pos * sizeof(Solicitud), SEEK_SET);
	bool leyo = fwrite(this, sizeof(Solicitud), 1, solicReg);
	fclose(solicReg);
	return leyo;
}

bool Solicitud::grabarBackupSolicitudes() {
	FILE* fReg = fopen("backupSolicitudes.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(Solicitud), 1, fReg);

	fclose(fReg);

	return escribio;
}

int checkArchivoSolicitud() {

	FILE* solicReg = fopen("solicitudes.dat", "rb");

	if (solicReg == NULL)
	{
		solicReg = fopen("solicitudes.dat", "wb");

		if (solicReg == NULL)
		{
			cout << "Error al crear o leer archivo de Solicitudes." << endl;
			system("PAUSE > null");

			return -1;
		}
		else
		{
			fclose(solicReg);
			cout << "Archivo de Solicitudes creado correctamente" << endl;

			return 0;
		}
	}
	else
	{
		cout << "Solicitudes: cargado OK" << endl;
	}

	fclose(solicReg);
	return 1;
}

int generarIdSolicitud() {

	return buscarCantidadSolicitudes();
}

void listadoSolicitudes() {

	Solicitud solic;
	int p = 0;

	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(12) << "ID SOCIO";
	cout << setw(12) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "------------------------------------------------------------------------------------------";
	cout << endl;

	while (solic.leerDeDisco(p++))
	{
		solic.listarSolicitud();
	}
}

void SolicitudesPendientesPorSocio(int idSocio) {

	Solicitud solic;
	int p = 0;

	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(12) << "ID SOCIO";
	cout << setw(12) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "------------------------------------------------------------------------------------------";
	cout << endl;

	while (solic.leerDeDisco(p++))
	{
		if (solic.getIdSocio() == idSocio && solic.getAprobado() == 0)
		{
			solic.listarSolicitud();
		}
	}
}

void Solicitud::listarSolicitud() {

	if (this->getEstado()) {
		cout << left;
		cout << setw(15) << this->getIdSolicitud();
		cout << setw(20) << this->getIdAdministrador();
		cout << setw(10) << this->getIdSocio();
		cout << setw(10) << this->getIdArma();
		cout << setw(15);
		mostrarEstadoApSolicitud(this->getAprobado());
		this->getFechaSolicitud().mostrarFecha();

		cout << endl;
	}
}

void mostrarEstadoApSolicitud(int estadoAprobacion) {
	switch (estadoAprobacion)
	{
	case -1:
		cout << "DESAPROBADA";
		break;
	case 0:
		cout << "PENDIENTE";
		break;
	case 1:
		cout << "APROBADA";
		break;
	default:
		break;
	}
};

void cargarNuevaSolicitud() {

	Solicitud solicitud;

	solicitud.cargarSolicitud();

}

void listadoSolicitudesAprobadas()
{
	Solicitud solic;
	int p = 0;

	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(12) << "ID SOCIO";
	cout << setw(12) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "------------------------------------------------------------------------------------------";
	cout << endl;

	while (solic.leerDeDisco(p))
	{
		if (solic.getAprobado() == 1)
		{
			solic.listarSolicitud();
		}
		p++;
	}
}
void listadoSolicitudesPendientes() {

	Solicitud solic;
	int p = 0;

	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(12) << "ID SOCIO";
	cout << setw(12) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "------------------------------------------------------------------------------------------";
	cout << endl;

	while (solic.leerDeDisco(p++))
	{
		if (solic.getAprobado() == 0)
		{
			solic.listarSolicitud();
		}

	}
}
void listadoSolicitudesDesaprobadas() {
	Solicitud solic;
	int p = 0;

	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(12) << "ID SOCIO";
	cout << setw(12) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "------------------------------------------------------------------------------------------";
	cout << endl;

	while (solic.leerDeDisco(p))
	{
		if (solic.getAprobado() == -1)
		{
			solic.listarSolicitud();
		}
		p++;
	}
}

void listarSolicitudesPorIdDesc() {

	int cantSolicitudes = buscarCantidadSolicitudes();

	if (cantSolicitudes == 0) {
		cout << "No hay solicitudes registradas.";
		return;
	}

	Solicitud* solicitudes = new Solicitud[cantSolicitudes];

	if (solicitudes == NULL) { return; }

	copiarSolicitudes(solicitudes, cantSolicitudes);
	ordernarVecSolicPorIdDesc(solicitudes, cantSolicitudes);
	mostrarSolicitudes(solicitudes, cantSolicitudes);

	delete solicitudes;
}

void ordernarVecSolicPorIdDesc(Solicitud* vSolicitudes, int tam) {
	Solicitud aux;
	for (int i = 0; i < tam - 1; i++) {
		for (int j = i + 1; j < tam; j++) {
			if (vSolicitudes[i].getIdSolicitud() < vSolicitudes[j].getIdSolicitud()) {
				aux = vSolicitudes[i];
				vSolicitudes[i] = vSolicitudes[j];
				vSolicitudes[j] = aux;
			}
		}
	}
}
void listarSolicitudPorFechaDesc() {
	int cantReg = buscarCantidadSolicitudes();

	if (cantReg == 0) {
		cout << "No hay Solicitudes registradas";
		return;
	}

	Solicitud* vSolicitudes;
	vSolicitudes = new Solicitud[cantReg];
	if (vSolicitudes == NULL) return;

	copiarSolicitudes(vSolicitudes, cantReg);
	ordernarVectorSolicPorFechaDesc(vSolicitudes, cantReg);
	mostrarSolicitudes(vSolicitudes, cantReg);

	delete vSolicitudes;

}

void ordernarVectorSolicPorFechaDesc(Solicitud* vec, int tam) {
	Solicitud aux;

	for (int i = 0; i < tam - 1; i++) {
		for (int j = i + 1; j < tam; j++) {
			if (vec[i].getFechaSolicitud() > vec[j].getFechaSolicitud()) {
				aux = vec[i];
				vec[i] = vec[j];
				vec[j] = aux;
			}
		}
	}
}
void mostrarSolicitudes(Solicitud* vSolicitudes, int tam) {
	cout << " -- Listado de solicitudes --" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(15) << "ID SOCIO";
	cout << setw(15) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < tam; i++) {
		vSolicitudes[i].listarSolicitud();
	}
};

int buscarCantidadSolicitudes() {

	FILE* p = fopen("solicitudes.dat", "rb");
	if (p == NULL) {
		return 0;
	}

	size_t bytes;
	int cant_reg;

	fseek(p, 0, SEEK_END);
	bytes = ftell(p);
	fclose(p);
	cant_reg = bytes / sizeof(Solicitud);
	return cant_reg;
	}

void consultaSolicitudesPorAnio() {

	int cantidadSolicitudes = buscarCantidadSolicitudes();
	if (cantidadSolicitudes <= 0) {
		cout << "No hay Solicitudes Registradas.";
		return;
	}

	Solicitud* vecSolicitudes;

	vecSolicitudes = new Solicitud[cantidadSolicitudes];

	if (vecSolicitudes == NULL) { return; }

	for (int i = 0; i < cantidadSolicitudes; i++) {
		vecSolicitudes[i].leerDeDisco(i);
	}

	int anioConsulta = 0;

	cout << " - Listado de Solicitudes por Año - ";
	cout << endl;

	do {
		cout << "Año: ";
		cin >> anioConsulta;

		if (anioConsulta < 0 || anioConsulta < 1980)
		{
			cout << " El año ingresado es incorrecto, intente nuevamente" << endl;
		}

	} while (anioConsulta < 0 || anioConsulta < 1980);

	mostrarConsultasPorAnio(vecSolicitudes, cantidadSolicitudes, anioConsulta);

	delete vecSolicitudes;
}

void mostrarConsultasPorAnio(Solicitud* vecSolicitudes, int tam, int anioConsulta) {

	cls();
	cout << "   -- Solictudes creadas en el año " << anioConsulta << " --" << endl << endl;
	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(10) << "ID SOCIO";
	cout << setw(10) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < tam; i++) {
		if (vecSolicitudes[i].getFechaSolicitud().getAnio() == anioConsulta) {
			vecSolicitudes[i].listarSolicitud();
		}
	}
}

void consultaSolicitudesPorId() {

	Solicitud solicitud;
	int idSolicitud;

	cout << " - Consulta de Solicitudes por Id - ";
	cout << endl;
	cout << "Ingrese el Id: ";

	cin >> idSolicitud;
	cls();

	int posReg = buscarSolicitudPorId(idSolicitud) - 1;
	if (posReg >= 0) {

		cout << left;
		cout << setw(15) << "ID SOLICITUD";
		cout << setw(20) << "ID ADMINISTRADOR";
		cout << setw(10) << "ID SOCIO";
		cout << setw(10) << "ID ARMA";
		cout << setw(15) << "ESTADO";
		cout << setw(15) << "FECHA CREACION" << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;

		solicitud.leerDeDisco(posReg);
		solicitud.listarSolicitud();
	}
	else {
		cout << "No se encontró una Solicitud Registrada con ese Id.";
	}

}

int buscarSolicitudPorId(int id) {

	Solicitud solicitud;
	int pos = 0;

	while (solicitud.leerDeDisco(pos++))
	{
		if (solicitud.getIdSolicitud() == id)
		{
			if (solicitud.getEstado())
			{
				return pos;
			}
			else
			{
				return -1;
			}
		}
	}
	return -1;
}

void copiarSolicitudes(Solicitud* vecSoli, int tam) {

	for (int i = 0; i < tam; i++) { vecSoli[i].leerDeDisco(i); }
}

void consultaSolicitudesPorFecha() {

	int cantidadSolicitudes = buscarCantidadSolicitudes();
	if (cantidadSolicitudes <= 0) {
		cout << "No hay Solicitudes Registradas.";
		return;
	}

	Solicitud* vecSolicitudes;

	vecSolicitudes = new Solicitud[cantidadSolicitudes];

	if (vecSolicitudes == NULL) { return; }

	copiarSolicitudes(vecSolicitudes, cantidadSolicitudes);

	Fecha fechaConsulta;

	cout << " - Consulta de Solicitudes por Fecha de Creación- ";
	cout << endl;
	cout << "Ingrese la Fecha: ";
	cout << endl;

	fechaConsulta.cargarFechaConsultas();
	cls();

	cout << "   -- Solictudes creadas el ";
	fechaConsulta.mostrarFecha();
	cout << " --" << endl << endl;

	mostrarConsultasPorFecha(vecSolicitudes, cantidadSolicitudes, fechaConsulta);

	delete vecSolicitudes;
}

void mostrarConsultasPorFecha(Solicitud* vecSolicitudes, int tam, Fecha fechaConsulta) {

	Fecha fechaSoli;
	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(10) << "ID SOCIO";
	cout << setw(10) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < tam; i++) {
		fechaSoli = vecSolicitudes[i].getFechaSolicitud();
		if (fechaSoli == fechaConsulta) {
			vecSolicitudes[i].listarSolicitud();
		}
	}
}

void bajaSolicitud(Solicitud aux, int pos)
{
	bool flag = false;
	char confirm;

	cout << "¿Desea dar de baja la solicitud  N°" << aux.getIdSolicitud() << "? (S/N): ";
	cin >> confirm;

	confirm = (tolower(confirm));

	if (confirm == 's')
	{
		/// Elimina el arma en archivo armas
		eliminarArma(aux.getIdArma());
		aux.setEstado(false);
		aux.modificarEnDisco(pos);
		cout << endl << " -- La solicitud ha sido eliminada -- " << endl;
		anykey();
	}
	cls();
}

void modificar_solicitud()
{
	int opcion;
	char confirmarSalida;
	bool salir = false;
	bool flag = false;
	int idaux;
	int pos = 0;

	while (!salir) {

		Solicitud aux;

		do
		{
			cout << "Ingrese ID de solicitud a modificar (0 para volver al menu Solicitud): ";
			cin >> idaux;

			if (idaux == 0)
			{
				return;
			}

			pos = buscarSolicitudPorId(idaux) - 1;

			if (pos <= -1)
			{
				cout << "La Solicitud no se encuentra. Reintente por favor." << endl << endl;
				anykey();
				cls();
				flag = false;
			}
			else
			{
				aux.leerDeDisco(pos);

				if (aux.getEditable())
				{
					flag = true;
				}
				else
				{
					cout << endl << " -- La solicitud ya ha sido aprobada o desaprobada. No se puede editar --" << endl;
					anykey();
					cls();
					flag = false;
				}
			}

		} while (!flag);

		cls();

		aux.mostrarSolicitud();
		cout << endl;

		cout << "\tSeleccione opción" << endl;
		cout << "--------------------------" << endl;
		cout << "1 - Aprobar solicitud " << endl;
		cout << "2 - Desaprobar solicitud " << endl;
		cout << "3 - Eliminar registro de solicitud" << endl;
		cout << "--------------------------" << endl;
		cout << "0 - Volver al menú Solicitudes" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			aprobarSolicitud(aux, pos);
			break;
		case 2:
			desaprobarSolicitud(aux, pos);
			break;
		case 3:
			bajaSolicitud(aux, pos);
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

void aprobarSolicitud(Solicitud aux, int pos)
{
	bool flag = false;
	char confirm;

	cout << "¿Desea aprobar la solicitud  N°" << aux.getIdSolicitud() << "? (S/N): ";
	cin >> confirm;

	confirm = (tolower(confirm));

	if (confirm == 's')
	{
		aux.setAprobado(1);
		aux.setEditable(false);
		aux.modificarEnDisco(pos);
		cout << endl << " -- La solicitud ha sido aprobada -- " << endl;
		anykey();
	}
	cls();
}

void desaprobarSolicitud(Solicitud aux, int pos)
{
	bool flag = false;
	char confirm;

	cout << "¿Desea desaprobar la solicitud  N°" << aux.getIdSolicitud() << "? (S/N): ";
	cin >> confirm;

	confirm = (tolower(confirm));

	if (confirm == 's')
	{
		aux.setAprobado(-1);
		aux.setEditable(false);
		aux.modificarEnDisco(pos);
		cout << endl << " -- La solicitud ha sido desaprobada -- " << endl;
		anykey();
	}
	cls();
}

void cantidad_solicitudes_desap_por_anio()
{
	int anio;
	bool flag = false;

	do
	{
		cout << "Ingrese el año (0 para volver al menu anterior): ";
		cin >> anio;

		if (anio == 0)
		{
			return;
		}

		if (anio < 0)
		{
			cout << "Año invalido. Reingrese de nuevo por favor" << endl;
			anykey();
			cls();
		}
		else
		{
			flag = true;
		}

	} while (!flag);

	int aux = solicitudesDesaprobadasPorAnio(anio);

	if (aux == 0)
	{
		cout << " -- No se desaprobaron solicitudes en el año " << anio << " --" << endl;
	}
	else if (aux == 1)
	{
		cout << " -- Se desaprobó " << aux << " solicitud en el año " << anio << " --" << endl;
	}
	else
	{
		cout << " -- Se desaprobaron " << aux << " solicitudes en el año " << anio << " --" << endl;
	}

}

int solicitudesDesaprobadasPorAnio(int anio)
{
	Solicitud solic;
	int p = 0;
	int cant = 0;

	while (solic.leerDeDisco(p++))
	{
		if (solic.getEstado())
		{
			if (solic.getAprobado() == -1 && solic.getFechaSolicitud().getAnio() == anio)
			{
				cant++;
			}
		}

	}

	return cant;

}

void backup_solicitudes()
{
	Solicitud aux;
	int pos = 0;

	while (aux.leerDeDisco(pos++))
	{
		aux.grabarBackupSolicitudes();
	}

	cout << "Archivo de backup de solicitudes 'backupSolicitudes.dat' grabado correctamente" << endl;
}

void promedio_solictudes_aprobadas()
{
	int cantSolicitudes = buscarCantidadSolicitudes();

	if (cantSolicitudes == 0) {
		cout << "No se registran solicitudes al dia de la fecha" << endl;
		return;
	}

	Solicitud solicitud;
	int pos = 0;
	int cont = 0;
	int anio = 0;
	int totalSolicitudes = 0;
	bool flag = false;

	while (solicitud.leerDeDisco(pos))
	{
		if (solicitud.getEstado())
		{
			totalSolicitudes++;

			if (solicitud.getAprobado() == 1)
			{
				cont++;
			}
		}
		pos++;
	}

	double prom = (double)cont / cantSolicitudes;

	cout << " -- El promedio de solicitudes aprobadas es de: " << setprecision(2) << prom << endl;

}

void eliminar_solicitudes_pendientes(int id)
{
	Solicitud solicitud;
	int pos = 0;

	while (solicitud.leerDeDisco(pos))
	{
		if (solicitud.getAprobado() == 0 && solicitud.getIdSocio() == id)
		{
			solicitud.setEstado(false);
			solicitud.modificarEnDisco(pos);
		}
		pos++;
	}

}

void listadoSolicitudesPorIdSocio()
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

	mostrarSolicitudesPorSocio(ID);
}

void mostrarSolicitudesPorSocio(int id)
{
	Solicitud solic;
	int p = 0;

	cout << left;
	cout << setw(15) << "ID SOLICITUD";
	cout << setw(20) << "ID ADMINISTRADOR";
	cout << setw(12) << "ID SOCIO";
	cout << setw(12) << "ID ARMA";
	cout << setw(15) << "ESTADO";
	cout << setw(15) << "FECHA CREACION" << endl;
	cout << "------------------------------------------------------------------------------------------";
	cout << endl;

	while (solic.leerDeDisco(p))
	{
		if (solic.getIdSocio() == id)
		{
			solic.listarSolicitud();
		}
		p++;
	}
}