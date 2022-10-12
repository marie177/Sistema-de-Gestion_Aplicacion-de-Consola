#include "RecaudacionesPorAdmin.h"

using namespace std;
using namespace rlutil;

RecaudacionesPorAdmin::RecaudacionesPorAdmin() {
	idAdmin = 0;
	recaudacionTotalCuotas = 0;
	recaudacionTotalSolicitud = 0;
}

void RecaudacionesPorAdmin::setIdAdmin(int _idAdmin) { idAdmin = _idAdmin; };
void RecaudacionesPorAdmin::setRecaudacionTotalCuotas(float _recaudacionCuota) {
	recaudacionTotalCuotas = _recaudacionCuota;
};
void  RecaudacionesPorAdmin::setRecaudacionTotalSolicitudes(float _recaudacionSolicitud) {
	recaudacionTotalSolicitud = _recaudacionSolicitud;
};

int RecaudacionesPorAdmin::getIdAdmin() { return idAdmin; };
float RecaudacionesPorAdmin::getRecaudacionTotalCuotas() { return recaudacionTotalCuotas; };
float RecaudacionesPorAdmin::getRecaudacionTotalSolicitudes() { return recaudacionTotalSolicitud; };

void recaudacionPorAdmin() {

	int cantReg = buscarCantidadRegistrosAdmin();

	if (cantReg == 0) {
		cout << "No hay Administradores registrados";
		anykey();
		return;
	}

	RecaudacionesPorAdmin* vecRecaudacionAdmin;
	vecRecaudacionAdmin = new RecaudacionesPorAdmin[cantReg];
	if (vecRecaudacionAdmin == NULL) return;

	inicializarVecRecaudacionPorAdmin(vecRecaudacionAdmin, cantReg);
	buscarRecaudacionesPorAdmin(vecRecaudacionAdmin, cantReg);
	listarRecaudacionesPorAdmin(vecRecaudacionAdmin, cantReg);

	delete vecRecaudacionAdmin;

}

void inicializarVecRecaudacionPorAdmin(RecaudacionesPorAdmin* vecRecaudacion, int tam) {
	Administrador admin;

	for (int i = 0; i < tam; i++) {
		admin.leerDeDisco(i);

		vecRecaudacion[i].setIdAdmin(admin.getIdAdmin());
		vecRecaudacion[i].setRecaudacionTotalCuotas(0);
		vecRecaudacion[i].setRecaudacionTotalSolicitudes(0);
	}
}

void buscarRecaudacionesPorAdmin(RecaudacionesPorAdmin* vecRecaudacion, int tam) {

	int pos = 0;
	int idAdmin;
	int posAdmin;
	float totalRecaudacion;

	PagoCuota cuotas;

	while (cuotas.leerDeDisco(pos++)) {
		idAdmin = cuotas.getIdAdmin();
		posAdmin = buscarPosAdmin(idAdmin, vecRecaudacion, tam);

		totalRecaudacion = vecRecaudacion[posAdmin].getRecaudacionTotalCuotas() + cuotas.getImporte();
		vecRecaudacion[posAdmin].setRecaudacionTotalCuotas(totalRecaudacion);
	}

	pos = 0;

	PagoSolicitud solicitudesCobros;

	while (solicitudesCobros.leerEnDisco(pos++)) {
		idAdmin = solicitudesCobros.getIdAdmin();
		posAdmin = buscarPosAdmin(idAdmin, vecRecaudacion, tam);

		totalRecaudacion = vecRecaudacion[posAdmin].getRecaudacionTotalSolicitudes() + solicitudesCobros.getImporte();
		vecRecaudacion[posAdmin].setRecaudacionTotalSolicitudes(totalRecaudacion);
	}
}
int buscarPosAdmin(int idAdmin, RecaudacionesPorAdmin* vecRecaudacion, int tam) {
	for (int pos = 0; pos < tam; pos++) {
		if (vecRecaudacion[pos].getIdAdmin() == idAdmin) {
			return pos;
		}
	}
	return -1;
}
void listarRecaudacionesPorAdmin(RecaudacionesPorAdmin* vecRecaudacion, int tam) {
	cout << endl << "--------------------------------------";
	cout << endl << "   -- Recaudación Por Administrador --                " << endl;
	cout << "--------------------------------------" << endl;

	cout << left;
	cout << setw(11) << "ID ADMIN";
	cout << setw(1) << " ";
	cout << setw(15) << "RECAUDACION" << endl;
	cout << "--------------------------------------" << endl;

	for (int i = 0; i < tam; i++) {

		if (vecRecaudacion[i].getIdAdmin() != 0)
		{
		cout << setw(12) << vecRecaudacion[i].getIdAdmin();
		cout << setw(1) << "$";
		cout << setw(15) << vecRecaudacion[i].getRecaudacionTotalCuotas() + vecRecaudacion[i].getRecaudacionTotalSolicitudes() << endl;
		}
	}
	cout << "--------------------------------------" << endl;

	anykey();
}