#pragma once

#include "Pago.h"
#include "PagoSolicitud.h"
#include "Administrador.h"
#include "rlutil.h"

class RecaudacionesPorAdmin
{
private:
	int idAdmin;
	float recaudacionTotalCuotas;
	float recaudacionTotalSolicitud;

public:
	RecaudacionesPorAdmin();

	void setIdAdmin(int _idAdmin);
	void setRecaudacionTotalCuotas(float _recaudacionCuota);
	void  setRecaudacionTotalSolicitudes(float _recaudacionSolicitud);

	int getIdAdmin();
	float getRecaudacionTotalCuotas();
	float getRecaudacionTotalSolicitudes();

};

void recaudacionPorAdmin();
void inicializarVecRecaudacionPorAdmin(RecaudacionesPorAdmin* vecRecaudacion, int tam);
void buscarRecaudacionesPorAdmin(RecaudacionesPorAdmin* vecRecaudacion, int tam);
int buscarPosAdmin(int idAdmin, RecaudacionesPorAdmin* vecRecaudacion, int tam);
void listarRecaudacionesPorAdmin(RecaudacionesPorAdmin* vecRecaudacion, int tam);


