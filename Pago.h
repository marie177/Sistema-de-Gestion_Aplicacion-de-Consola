#pragma once
#include "PagoSolicitud.h"
#include "administrador.h"
#include "Solicitud.h"
#include "Fecha.h"
#include "Socio.h"
#include "rlutil.h"
#include "ValorCuota.h"

class PagoCuota {

private:
	int _idCuota;
	int _idSocio;
	float _importe;
	Fecha _fechaPago;
	int _idAdmin;

public:
	PagoCuota(int idSocio = 0, float valorCuota = 0, int idCuota = 0, int idAdmin = 0);

	/// Setters
	void setIdCuota(int );
	void setIdSocio(int);
	void setImporte(float);
	void setFechaPago(Fecha);
	void setIdAdmin(int);

	/// Getters
	int getIdCuota();
	int getIdSocio();
	float getImporte();
	Fecha getFechaPago();
	int getIdAdmin();

	bool grabarEnDisco();
	bool leerDeDisco(int);

};

int generarIDCuota();

int checkArchivoPagosCuota();

void cobrar_cuota();

void actualizarEstadoCuotasSocios();

void actualizarCarteraSocios(Socio *vec, int cantReg);

void recaudacionPorSocio();
void ponerCeroVectorRecaudacion(float* vecRecaudacion, int tam);
void buscarRecaudacionesPorSocio(float* vecRecaudacion);
void listarRecaudacionesPorSocio(float* vecRecaudacion, int tam);

void PonerEnCeroVector(float* vec, int tam);
void Informe_Recaudacion_Anual();
void RecaudacionAnualCuota(int anio, float *vec, int tam);
void RecaudacionAnualSolictudes(int anio, float *vec, int tam);
void MostrarDetalleRecaudacionAnual(float* vec, float* vec2, int tam);