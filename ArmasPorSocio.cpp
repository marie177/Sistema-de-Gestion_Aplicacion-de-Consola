#include "ArmasPorSocio.h"

ArmasPorSocio::ArmasPorSocio()
{
	_idSocio = 0;
	_cantidadArmas = 0;
}

void ArmasPorSocio::setIdSocio(int idsocio)
{
	_idSocio = idsocio;
}

void ArmasPorSocio::setCantidadArmas(int cant)
{
	_cantidadArmas = cant;
}

void ArmasPorSocio::setEstado(bool e)
{
	_estado = e;
}

int ArmasPorSocio::getIdSocio()
{
	return _idSocio;
}

int ArmasPorSocio::getCantidadArmas()
{
	return _cantidadArmas;
}

bool ArmasPorSocio::getEstado()
{
	return _estado;
}

void cantidad_de_armas_por_socio()
{
	int cantReg = CantidadRegistrosSocio();

	if (cantReg == 0) {
		cout << "No hay socios registrados";
		return;
	}

	ArmasPorSocio* vecArmas = new ArmasPorSocio[cantReg];
	if (vecArmas == NULL) return;

	inicializarVecArmas(vecArmas, cantReg);
	buscarArmasPorSocio(vecArmas, cantReg);
	ordenarVector(vecArmas, cantReg);
	listarVector(vecArmas, cantReg);

	delete vecArmas;
}

void inicializarVecArmas(ArmasPorSocio* vecArmas, int cantReg)
{
	Socio socio;

	for (int i = 0; i < cantReg; i++) {
		socio.leerDeDisco(i);

		vecArmas[i].setIdSocio(socio.getIdsocio());
		vecArmas[i].setEstado(socio.getEstado());
	}
}

void buscarArmasPorSocio(ArmasPorSocio* vecArmas, int cantReg)
{
	int pos = 0;
	int posSocio = 0;
	float totalArmas;

	Arma arma;

	while (arma.leerDeDisco(pos))
	{
		posSocio = buscarPosSocio(arma.getIdSocio(), vecArmas, cantReg);
		vecArmas[posSocio].setCantidadArmas(vecArmas[posSocio].getCantidadArmas() + 1);
		pos++;
	}
}

int buscarPosSocio(int idSocio, ArmasPorSocio* vecArmas, int cantReg)
{
	for (int pos = 0; pos < cantReg; pos++) {
		if (vecArmas[pos].getIdSocio() == idSocio) {
			return pos;
		}
	}
	return -1;
}
void ordenarVector(ArmasPorSocio* vecArmas, int cantReg)
{

	ArmasPorSocio aux;

	for (int i = 0; i < cantReg - 1; i++) {
		for (int j = i + 1; j < cantReg; j++) {
			if (vecArmas[j].getCantidadArmas() > vecArmas[i].getCantidadArmas()) {
				aux = vecArmas[i];
				vecArmas[i] = vecArmas[j];
				vecArmas[j] = aux;
			}
		}
	}

}

void listarVector(ArmasPorSocio* vecArmas, int cantReg)
{
	cout << endl << "--------------------------------------";
	cout << endl << "   -- Cantidad de armas por socio --   " << endl;
	cout << "--------------------------------------" << endl;

	cout << left;
	cout << setw(11) << "ID Socio";
	cout << setw(15) << "ARMAS" << endl;
	cout << "--------------------------------------" << endl;

	for (int i = 0; i < cantReg; i++) {
		if (vecArmas[i].getEstado())
		{
			cout << setw(12) << vecArmas[i].getIdSocio();
			cout << setw(15) << vecArmas[i].getCantidadArmas() << endl;
		}
	}

	cout << "--------------------------------------" << endl;
}