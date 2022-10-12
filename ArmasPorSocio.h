#pragma once

#include "Socio.h"
#include "rlutil.h"
#include "Arma.h"

using namespace std;
using namespace rlutil;

class ArmasPorSocio
{
private:
	int _idSocio;
	int _cantidadArmas;
	bool _estado;

public:
	ArmasPorSocio();

	void setIdSocio(int);
	void setCantidadArmas(int);
	void setEstado(bool);

	int getIdSocio();
	int getCantidadArmas();
	bool getEstado();
};

void cantidad_de_armas_por_socio();

void inicializarVecArmas(ArmasPorSocio* vecArmas, int cantReg);

void buscarArmasPorSocio(ArmasPorSocio* vecArmas, int cantReg);
void ordenarVector(ArmasPorSocio* vecArmas, int cantReg);
void listarVector(ArmasPorSocio* vecArmas, int cantReg);

int buscarPosSocio(int idSocio, ArmasPorSocio* vecArmas, int cantReg);