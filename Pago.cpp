#include "Pago.h"

using namespace rlutil;

PagoCuota::PagoCuota(int idSocio, float valorCuota, int idCuota, int idAdmin)
{
	Fecha fechaActual;

	_idSocio = idSocio;
	_importe = valorCuota;
	_fechaPago = fechaActual;
	_idCuota = idCuota;
	_idAdmin = idAdmin;
}

void PagoCuota::setIdCuota(int id)
{
	_idCuota = id;
}

void PagoCuota::setIdSocio(int id)
{
	_idSocio = id;
}

void PagoCuota::setImporte(float imp)
{
	_importe = imp;
}

void PagoCuota::setFechaPago(Fecha fecha)
{
	_fechaPago = fecha;
}

void PagoCuota::setIdAdmin(int idAdmin)
{
	_idAdmin = idAdmin;
}

int PagoCuota::getIdCuota()
{
	return _idCuota;
}

int PagoCuota::getIdSocio()
{
	return _idSocio;
}

float PagoCuota::getImporte()
{
	return _importe;
}

Fecha PagoCuota::getFechaPago()
{
	return _fechaPago;
}

int PagoCuota::getIdAdmin()
{
	return _idAdmin;
}

bool PagoCuota::grabarEnDisco()
{
	FILE* fReg = fopen("pagoscuota.dat", "ab");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		system("PAUSE < null");
		return false;
	}

	int escribio = fwrite(this, sizeof(PagoCuota), 1, fReg);

	fclose(fReg);

	return escribio;
}

bool PagoCuota::leerDeDisco(int pos)
{
	FILE* fReg = fopen("pagoscuota.dat", "rb");

	if (fReg == NULL)
	{
		cout << "No se puede abrir el archivo.";
		anykey();
		return false;
	}

	fseek(fReg, pos * sizeof(PagoCuota), SEEK_SET);

	int escribio = fread(this, sizeof(PagoCuota), 1, fReg);

	fclose(fReg);

	return escribio;
}

int generarIDCuota()
{
	PagoCuota aux;
	int id = 0;
	int pos = 0;

	while (aux.leerDeDisco(pos++)) {
		id = aux.getIdCuota();
	};

	return id;
}

int checkArchivoPagosCuota()
{
	FILE* solicReg = fopen("pagoscuota.dat", "rb");

	if (solicReg == NULL)
	{
		solicReg = fopen("pagoscuota.dat", "wb");

		if (solicReg == NULL)
		{
			cout << "Error al crear o leer archivo de pagos de cuotas." << endl;
			system("PAUSE > null");

			return -1;
		}
		else
		{
			fclose(solicReg);
			cout << "Archivo de pagos de cuotas creado correctamente" << endl;

			return 0;
		}
	}
	else
	{
		cout << "Pagos de cuotas: cargado OK" << endl;
	}

	fclose(solicReg);
	return 1;
}

void cobrar_cuota()
{
	int idaux;
	int pos = 0;
	int pos2 = 0;
	bool flag = false;
	bool flag2 = false;
	int ID = 0;

	Socio socio;
	Fecha fechaActual;
	Administrador admin;

	do {
		do {
			cout << "Ingrese el ID de socio a cobrar (0 para volver al menu anterior): ";
			cin >> idaux;

			if (idaux == 0)
			{
				return;
			}

			pos = buscarSocioPorID(idaux);

			if (idaux < 0)
			{
				cout << "ID inválido. Por favor, reintente." << endl << endl;
				anykey();
				cls();
				flag = false;
			}
			else if (pos < 0)
			{
				cout << "El ID de socio no existe. Por favor, reintente." << endl << endl;
				anykey();
				cls();
				flag = false;
			}
			else
			{
				socio.leerDeDisco(pos);

				if (!socio.getDeudor())
				{
					cout << "Ya se ha registrado un pago del socio para el mes actual";
					anykey();
					cls();
					flag = false;
				}
				else
				{
					flag = true;
				}
			}
		} while (!flag);

		cls();

		char confirm;

		socio.leerDeDisco(pos);
		socio.mostrar();
		int cantMesesAdeudados = 0;

		if (socio.getUltimoPago().getAnio() == fechaActual.getAnio())
		{
			cantMesesAdeudados = fechaActual.getMes() - socio.getUltimoPago().getMes();
		}
		else
		{
			cantMesesAdeudados = (12 - socio.getUltimoPago().getMes()) + fechaActual.getMes();
		}

		float valorCuota = getUltimoPrecioCuota();
		int idCuota = generarIDCuota() + 1;

		cout << endl << "Valor de la cuota: $" << valorCuota << endl;
		cout << "Cantidad de meses adeudados: " << cantMesesAdeudados << endl << endl;

		float totalAPagar = valorCuota * cantMesesAdeudados;

		cout << " -- Total a pagar: $" << totalAPagar << " --" << endl;

		cout << "Desea cobrar cuota al socio n° " << socio.getIdsocio() << "? (S/N)" << endl << endl;
		cin >> confirm;

		confirm = (tolower(confirm));

		if (confirm == 's')
		{
			PagoCuota pago(socio.getIdsocio(), totalAPagar, idCuota);
			Fecha fechaActual;
			do
			{
				cout << endl << "Ingrese el ID de administrador actual: ";
				cin >> ID;

				pos2 = buscarAdministradorPorID(ID);

				if (pos2 > -1) {
					admin.leerDeDisco(pos2);
					pago.setIdAdmin(admin.getIdAdmin());
					pago.grabarEnDisco();
					flag2 = true;
					anykey();
				}
				else
				{
					cout << "El ID no fue encontrado en el archivo de administradores" << endl;
					flag2 = false;
					anykey();
				}

			} while (!flag2);

			socio.setDeudor(false);
			socio.setUltimoPago(fechaActual);
			socio.modificarEnDisco(pos);
			flag2 = true;
			cout << " -- Pago registrado correctamente --" << endl;
			anykey();

		}
		else
		{
			cls();
			flag2 = false;
		}

	} while (!flag2);

}

void actualizarEstadoCuotasSocios()
{
	int cantReg = CantidadRegistrosSocio();
	if (cantReg == 0)
	{
		cout << endl << " -- No hay socios cargados al dia de la fecha. --" << endl;
		return;
	}

	Socio* vec = new Socio[cantReg];

	if (vec == NULL)
	{
		cout << "No hay memoria disponible." << endl;
		return;
	}

	copiarSocios(vec, cantReg);
	actualizarCarteraSocios(vec, cantReg);

	cout << endl << "Estado de socios actualizado correctamente" << endl;

	delete vec;
}

void actualizarCarteraSocios(Socio* vec, int cantReg) {

	Fecha fechaActual;
	int cantMesesAdeudados = 0;

	for (int i = 0; i < cantReg; i++)
	{
		cantMesesAdeudados = 12 - (vec[i].getUltimoPago().getMes() + fechaActual.getMes());

		if (vec[i].getEstado())
		{
			if (cantMesesAdeudados >= 12 && vec[i].getUltimoPago().getAnio() != fechaActual.getAnio())
			{
				eliminar_solicitudes_pendientes(vec[i].getIdsocio());
				vec[i].setEstado(false);
				vec[i].modificarEnDisco(i);
			}
			else if (vec[i].getUltimoPago().getMes() != fechaActual.getMes() && fechaActual.getDia() >= vec[i].getUltimoPago().getDia())
			{
				vec[i].setDeudor(true);
				vec[i].modificarEnDisco(i);
			}
		}
	}
}

void recaudacionPorSocio() {

	int cantReg = CantidadRegistrosSocio();

	if (cantReg == 0) {
		cout << "No hay socios registrados";
		anykey();
		return;
	}

	float* vecRecaudacionSocio = new float[cantReg];
	if (vecRecaudacionSocio == NULL) return;

	ponerCeroVectorRecaudacion(vecRecaudacionSocio, cantReg);
	buscarRecaudacionesPorSocio(vecRecaudacionSocio);
	listarRecaudacionesPorSocio(vecRecaudacionSocio, cantReg);

	delete vecRecaudacionSocio;
}
void ponerCeroVectorRecaudacion(float* vecRecaudacion, int tam) {

	for (int i = 0; i < tam; i++) {
		vecRecaudacion[i] = 0;
	}
}

void buscarRecaudacionesPorSocio(float* vecRecaudacion) {

	int pos = 0;
	PagoCuota cuotas;

	while (cuotas.leerDeDisco(pos++)) {
		int idSocio = cuotas.getIdSocio();
		float recaudacion = cuotas.getImporte();
		vecRecaudacion[idSocio - 1] += recaudacion;
	}

	pos = 0;

	PagoSolicitud solicitudesCobros;

	while (solicitudesCobros.leerEnDisco(pos++)) {
		int idSocio = solicitudesCobros.getIdSocio();
		float recaudacion = solicitudesCobros.getImporte();
		vecRecaudacion[idSocio - 1] += recaudacion;
	}

}
void listarRecaudacionesPorSocio(float* vecRecaudacion, int tam) {

	cout << endl << "-----------------------------------";
	cout << endl << "   -- Recaudación Por Socio --                " << endl;
	cout << "-----------------------------------" << endl;

	cout << left;
	cout << setw(11) << "ID SOCIO";
	cout << setw(1) << " ";
	cout << setw(15) << "RECAUDACION" << endl;
	cout << "-----------------------------------" << endl;

	for (int i = 0; i < tam; i++) {

		cout << setw(12) << i + 1;
		cout << setw(1) << "$";
		cout << setw(15) << vecRecaudacion[i] << endl;
	}

	cout << "-----------------------------------" << endl;

	anykey();
}

void Informe_Recaudacion_Anual() {

	int anio = 0;
	const int Meses = 12;
	float* vDinamicoCuota;
	vDinamicoCuota = new float[Meses];
	if (vDinamicoCuota == NULL) return;

	float* vDinamicoSolicitudes;
	vDinamicoSolicitudes = new float[Meses];
	if (vDinamicoSolicitudes == NULL) return;

	PonerEnCeroVector(vDinamicoCuota, Meses);
	PonerEnCeroVector(vDinamicoSolicitudes, Meses);

	do {

		cout << "Ingrese el año para consultar su recaudacion (0 para volver al menú anterior): ";
		cin >> anio;

		if (anio == 0)
		{
			return;
		}

		if (anio < 0)
		{
			cout << "Año inválido. Reintente por favor.";
			anykey();
			cls();
		}

	} while (anio < 0);

	RecaudacionAnualCuota(anio, vDinamicoCuota, Meses);
	RecaudacionAnualSolictudes(anio, vDinamicoSolicitudes, Meses);
	MostrarDetalleRecaudacionAnual(vDinamicoCuota, vDinamicoSolicitudes, Meses);
	anykey();

}
void RecaudacionAnualCuota(int anio, float* vec, int tam) {
	PagoCuota aux;
	int pos = 0;

	while (aux.leerDeDisco(pos))
	{
		if (aux.getFechaPago().getAnio() == anio) {
			vec[aux.getFechaPago().getMes() - 1] += aux.getImporte();
		}
		pos++;
	}
}
void RecaudacionAnualSolictudes(int anio, float* vec, int tam) {
	PagoSolicitud aux;
	int pos = 0;

	while (aux.leerEnDisco(pos++)) {
		if (aux.getFechaPago().getAnio() == anio) {
			vec[aux.getFechaPago().getMes() - 1] += aux.getImporte();
		}
	}
}
void PonerEnCeroVector(float* vec, int tam) {
	for (int i = 0; i < tam; i++)
	{
		vec[i] = 0;
	}
}
void MostrarDetalleRecaudacionAnual(float* vec, float* vec2, int tam) {
	string meses[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };
	float totalAnio = 0;
	float totalAnio2 = 0;

	cls();
	cout << "------------------------------------------------";
	cout << endl << "\t  -- Recaudación Anual --                " << endl;
	cout << "------------------------------------------------" << endl << endl;
	cout << left;
	cout << setw(11) << "MES";
	cout << setw(1) << " ";
	cout << setw(15) << "REC POR CUOTAS";
	cout << setw(1) << " ";
	cout << setw(10) << "REC POR SOLICITUD" << endl;
	cout << "------------------------------------------------" << endl;

	for (int i = 0; i < tam; i++) {

		cout << setw(12) << meses[i];
		cout << setw(1) << "$";
		cout << setw(15) << (long)vec[i];
		cout << setw(1) << "$";
		cout << setw(10) << (long)vec2[i] << endl;
		totalAnio += vec[i];
		totalAnio2 += vec2[i];

	}

	cout << "-------------------------------------------------" << endl;
	cout << setw(12) << "Total año";
	cout << setw(1) << "$";
	cout << setw(15) << (long)totalAnio;
	cout << setw(1) << "$";
	cout << setw(5) << (long)totalAnio2 << endl;
	cout << "-------------------------------------------------" << endl;
	cout << setw(21) << "Total recaudado";
	cout << setw(1) << "$";
	cout << setw(7) << (long)totalAnio + totalAnio2 << endl;
	cout << "-------------------------------------------------" << endl;


}