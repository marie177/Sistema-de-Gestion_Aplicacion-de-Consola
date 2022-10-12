#pragma once
#include <iomanip>
#include "Fecha.h"
#include "rlutil.h"

class ValorCuota
{
private:
	float _valorCuota;
	Fecha _fechaActualizacion;

public:
	void setValorCuota(int valor);
	void setFechaActualizacion(Fecha nuevaFecha);
	float getvalorCuota();
	Fecha getFechaActualizacion();

	//Funciones de disco
	bool grabarEnDisco();
	int leerEnDisco(int pos);

	void mostrar();
	void mostrarSimplificado();

};

int cantidadRegistrosPreciosCuota();

float getUltimoPrecioCuota();

int checkArchivoPrecioCuota();

void modificar_precio_cuota();

void modificarPrecio(float nuevoPrecio);

void listarPrecios();

void listar_historial_precios_cuota();