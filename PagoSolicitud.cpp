#include "PagoSolicitud.h"

using namespace std;

PagoSolicitud::PagoSolicitud(int id, int idPago, float importe, int idAdmin) {

	_idSocio = id;
	_idAdmin = idAdmin;
	_idPagoSolicitud = idPago;
	_importe = importe;
}

void PagoSolicitud::setIdSocio(int id) {
	_idSocio = id;
}
void PagoSolicitud::setIdPagosolicitud(int idPago) {
	_idPagoSolicitud = idPago;
}
void PagoSolicitud::setIdAdmin(int idAdmin)
{
	_idAdmin = idAdmin;
}
void PagoSolicitud::setImporte(float importe) {
	_importe = importe;
}
void PagoSolicitud::setFechaPago(Fecha fechaPago) {
	_fechaPago = fechaPago;
}

int PagoSolicitud::getIdSocio() {
	return _idSocio;
}
int PagoSolicitud::getIdPago() {
	return _idPagoSolicitud;
}
int PagoSolicitud::getIdAdmin()
{
	return _idAdmin;
}
float PagoSolicitud::getImporte() {
	return _importe;
}
Fecha PagoSolicitud::getFechaPago() {
	return _fechaPago;
}

bool  PagoSolicitud::grabarEnDisco() {
	FILE* fReg = fopen("pagosolicitudes.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(PagoSolicitud), 1, fReg);

	fclose(fReg);

	return escribio;
}
int  PagoSolicitud::leerEnDisco(int pos) {
	FILE* fReg = fopen("pagosolicitudes.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(PagoSolicitud), SEEK_SET);

	int escribio = fread(this, sizeof(PagoSolicitud), 1, fReg);

	fclose(fReg);

	return escribio;
}
bool  PagoSolicitud::modificarEnDisco(int pos) {
	FILE* fReg = fopen("pagosolicitudes.dat", "rb+");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(PagoSolicitud), SEEK_SET);

	bool escribio = fwrite(this, sizeof(PagoSolicitud), 1, fReg);

	fclose(fReg);

	return escribio;
}

int checkArchivoPagosSolicitud()
{
	FILE* solicReg = fopen("pagosolicitudes.dat", "rb");

	if (solicReg == NULL)
	{
		solicReg = fopen("pagosolicitudes.dat", "wb");

		if (solicReg == NULL)
		{
			cout << "Error al crear o leer archivo de pagos de solicitudes." << endl;
			system("PAUSE > null");

			return -1;
		}
		else
		{
			fclose(solicReg);
			cout << "Archivo de pagos de solicitudes creado correctamente" << endl;

			return 0;
		}
	}
	else
	{
		cout << "Pagos de solicitudes: cargado OK" << endl;
	}

	fclose(solicReg);
	return 1;
}

int generarIDPagoSolicitud()
{
	PagoSolicitud aux;
	int id = 0;
	int pos = 0;

	while (aux.leerEnDisco(pos++)) {
		id = aux.getIdPago();
	};

	return id;
}