#include "ValorSolicitud.h"


using namespace rlutil;

void ValorSolicitud::setValorSolicitud(int valor) {
	_valorSolicitud = valor;
}

void  ValorSolicitud::setFechaActualizacion(Fecha nuevaFecha) {
	_fechaActualizacion = nuevaFecha;
}

float ValorSolicitud::getValorSolicitud() {
	return _valorSolicitud;
}

Fecha ValorSolicitud::getFechaActualizacion() {
	return _fechaActualizacion;
}

//Funciones de disco
bool ValorSolicitud::grabarEnDisco() {

	FILE* fReg = fopen("preciossolicitud.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(ValorSolicitud), 1, fReg);

	fclose(fReg);

	return escribio;
}

int ValorSolicitud::leerEnDisco(int pos) {

	FILE* fReg = fopen("preciossolicitud.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(ValorSolicitud), SEEK_SET);

	int escribio = fread(this, sizeof(ValorSolicitud), 1, fReg);

	fclose(fReg);

	return escribio;
}
void ValorSolicitud::mostrar()
{
	cout << left;
	cout << setw(1) << "$";
	cout << setw(10) << this->getValorSolicitud();
	this->getFechaActualizacion().mostrarFecha();
	cout << endl;

}
void ValorSolicitud::mostrarSimplificado()
{
	Fecha fechaActualizacion = this->getFechaActualizacion();

	cout << this->getValorSolicitud();
	fechaActualizacion.mostrarFecha();
}
int cantidadRegistrosPreciosSolicitud() {
	FILE* p = fopen("preciossolicitud.dat", "rb");
	if (p == NULL) {
		return 0;
	}

	size_t bytes;
	int cant_reg;

	fseek(p, 0, SEEK_END);
	bytes = ftell(p);
	fclose(p);
	cant_reg = bytes / sizeof(ValorSolicitud);
	return cant_reg;
}

float getUltimoPrecioSolicitud()
{
	ValorSolicitud aux;

	int pos = cantidadRegistrosPreciosSolicitud() - 1;

	aux.leerEnDisco(pos);

	return aux.getValorSolicitud();

}
int checkArchivoPrecioSolicitud()
{
	FILE* fReg = fopen("preciossolicitud.dat", "rb");

	if (fReg == NULL)
	{
		fReg = fopen("preciossolicitud.dat", "wb");

		if (fReg == NULL)
		{
			cout << "Error al crear o leer archivo de precio de solicitud." << endl;
			system("PAUSE > null");

			return -1;
		}
		else
		{
			float aux;
			cout << " -- Ingrese precio inicial de la solicitud: ";
			cin >> aux;

			modificar_importe_solicitud(aux);

			cout << "Archivo de valor de solicitudes creado correctamente con precio inicial: " << aux << endl << endl;

			fclose(fReg);
			return 0;
		}
	}
	else
	{
		cout << "Precio de solicitud: cargado OK" << endl;
	}

	fclose(fReg);

	return 1;

}

void modificar_precio_solicitud()
{
	float aux = 0;
	Fecha fechaActual;

	cls();
	cout << "Ingrese el precio nuevo: $";
	cin >> aux;

	modificar_importe_solicitud(aux);

	cls();
	cout << "\t -- Precio modificado correctamente --" << endl << endl;
	cout << "Precio: $" << aux << endl;
	cout << "Fecha: ";
	fechaActual.mostrarFecha();

	anykey();
}
void modificar_importe_solicitud(float nuevoPrecio) {
	ValorSolicitud aux;
	Fecha fechaActual;

	aux.setValorSolicitud (nuevoPrecio);
	aux.setFechaActualizacion(fechaActual);

	aux.grabarEnDisco();
}

void listar_historial_precios_solicitud()
{
	ValorSolicitud aux;
	int pos = 0;

	cout << left;
	cout << " -- Precios históricos de solicitud -- " << endl << endl;
	cout << setw(10) << "IMPORTE";
	cout << setw(1) << " ";
	cout << setw(10) << "FECHA ACTUALIZACION" << endl;
	cout << "-------------------------------" << endl;

	while (aux.leerEnDisco(pos++))
	{
		aux.mostrar();
	}
	anykey();
}
