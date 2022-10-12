#include "ValorCuota.h"

using namespace rlutil;

void ValorCuota::setValorCuota(int valor) {
	_valorCuota = valor;
}

void ValorCuota::setFechaActualizacion(Fecha nuevaFecha) {
	_fechaActualizacion = nuevaFecha;
}

float ValorCuota::getvalorCuota() {
	return _valorCuota;
}

Fecha ValorCuota::getFechaActualizacion() 
{
	return _fechaActualizacion;
}

//Funciones de disco
bool ValorCuota::grabarEnDisco() {
	FILE* fReg = fopen("precioscuota.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(ValorCuota), 1, fReg);

	fclose(fReg);

	return escribio;
}

int ValorCuota::leerEnDisco(int pos) {
	FILE* fReg = fopen("precioscuota.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	fseek(fReg, pos * sizeof(ValorCuota), SEEK_SET);

	int escribio = fread(this, sizeof(ValorCuota), 1, fReg);

	fclose(fReg);

	return escribio;
}

void ValorCuota::mostrar()
{
	cout << left;
	cout << setw(1) << "$";
	cout << setw(10) << (long)this->getvalorCuota();
	this->getFechaActualizacion().mostrarFecha();
	cout << endl;

}

void ValorCuota::mostrarSimplificado()
{
	Fecha fechaActualizacion = this->getFechaActualizacion();

	cout << this->getvalorCuota();
	fechaActualizacion.mostrarFecha();
}

int cantidadRegistrosPreciosCuota() {
	FILE* p = fopen("precioscuota.dat", "rb");
	if (p == NULL) {
		return 0;
	}

	size_t bytes;
	int cant_reg;

	fseek(p, 0, SEEK_END);
	bytes = ftell(p);
	fclose(p);
	cant_reg = bytes / sizeof(ValorCuota);
	return cant_reg;
}

float getUltimoPrecioCuota()
{
	ValorCuota aux;

	int pos = cantidadRegistrosPreciosCuota() - 1;

	aux.leerEnDisco(pos);

	return aux.getvalorCuota();

}

int checkArchivoPrecioCuota()
{
	FILE* fReg = fopen("precioscuota.dat", "rb");

	if (fReg == NULL)
	{
		fReg = fopen("precioscuota.dat", "wb");

		if (fReg == NULL)
		{
			cout << "Error al crear o leer archivo de precio de cuotas." << endl;
			system("PAUSE > null");

			return -1;
		}
		else
		{
			float aux;
			cout << endl<<" -- Ingrese precio de cuota inicial: ";
			cin >> aux;

			modificarPrecio(aux);

			cout << "Archivo de precio de cuotas creado correctamente con precio inicial: "<< aux << endl << endl;

			fclose(fReg);
			return 0;
		}
	}
	else
	{
		cout << "Precio de cuotas: cargado OK" << endl;
	}

	fclose(fReg);

	return 1;

}

void modificar_precio_cuota()
{
	float aux = 0;
	Fecha fechaActual;

	cls();
	cout << "Ingrese el precio nuevo: $";
	cin >> aux;

	modificarPrecio(aux);

	cls();
	cout << "\t -- Precio modificado correctamente --" << endl <<endl;
	cout << "Precio: $" << aux << endl;
	cout << "Fecha: ";
	fechaActual.mostrarFecha();

	anykey();

}

void modificarPrecio(float nuevoPrecio)
{
	ValorCuota aux;
	Fecha fechaActual;

	aux.setValorCuota(nuevoPrecio);
	aux.setFechaActualizacion(fechaActual);

	aux.grabarEnDisco();

}

void listar_historial_precios_cuota()
{
	ValorCuota aux;
	int pos = 0;

	cout << left;
	cout << " -- Precios históricos de cuota -- " << endl << endl;
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