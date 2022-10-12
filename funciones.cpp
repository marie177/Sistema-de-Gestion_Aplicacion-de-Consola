#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <clocale>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "funciones.h"
#include "rlutil.h"
#include "Administrador.h"
#include "Persona.h"
#include "Solicitud.h"
#include "Pago.h"
#include "Arma.h"
#include "ValorCuota.h"
#include "ValorSolicitud.h"
#include "RecaudacionesPorAdmin.h"
#include "ArmasPorSocio.h"
#include "ArmasPorPais.h"

using namespace std;
using namespace rlutil;

void instalacionArchivos()
{

	setBackgroundColor(CYAN);
	setColor(WHITE);
	cls();

	checkArchivoSocios();
	checkArchivoAdmins();
	checkArchivoSolicitud();
	checkArchivoArmas();

	checkArchivoPagosCuota();
	checkArchivoPagosSolicitud();

	checkArchivoPrecioCuota();
	checkArchivoPrecioSolicitud();

	actualizarEstadoCuotasSocios();

	cout << endl << "\t-- Presione enter para continuar --";
	system("PAUSE > null");
	system("cls");
}

bool login() {

	int aux;
	bool flag = false;
	bool flag2 = false;
	int pos = 0;
	string aux2;
	string password;
	int cont = 0;

	Administrador admin;

	do {

		cout << "    Bienvenido a Sistema ARMAC" << endl;
		cout << "    --------------------------" << endl;
		cout << "    ID Administrador: " << endl;
		cout << "    Contraseña: " << endl;
		cout << "    --------------------------" << endl;

		locate(23, 3);
		cin >> aux;

		pos = buscarAdministradorPorID(aux);

		if (pos == -1)
		{
			cls();
			setColor(RED);
			locate(11, 6);
			cout << "ID incorrecto." << endl;
			flag = false;
			setColor(WHITE);
			setBackgroundColor(CYAN);
			locate(1, 1);
		}
		else
		{
			locate(17, 4);
			admin.leerDeDisco(pos);
			password = admin.getContrasenia();

			aux2 = pedirContrasenia();

			if (aux2 != password)
			{
				cls();
				locate(8, 6);
				setColor(RED);
				cout << "Contraseña incorrecta." << endl;
				flag = false;
				setColor(WHITE);
				locate(1, 1);
				cont++;
			}
			else
			{
				locate(4, 6);
				setColor(LIGHTGREEN);
				setBackgroundColor(GREEN);
				cout << "ID y Contraseña correctos." << endl;
				locate(11, 7);
				cout << "Bienvenido!" << endl << endl;
				setColor(WHITE);
				setBackgroundColor(CYAN);
				system("PAUSE");
				cls();
				return true;

			}
		}

		if (cont == 3)
		{
			cls();
			setBackgroundColor(RED);
			setColor(YELLOW);
			cout << endl << "\t-- Ha superado el límite de intentos. Contacte a Ángel Simón. --" << endl;
			anykey();
			setColor(WHITE);
			return false;
		}

	} while (!flag);

	return true;
}

bool menuPrincipal() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {
		setBackgroundColor(BLUE);
		setColor(WHITE);
		cls();
		cout << "\tSistema ARMAC" << endl;
		cout << "-------------------------------" << endl;
		cout << "    1 - Menú Socios" << endl;
		cout << "    2 - Menú Administradores" << endl;
		cout << "    3 - Menú Solicitudes" << endl;
		cout << "    4 - Menú Armas" << endl;
		cout << "    5 - Menú Informes" << endl;
		cout << "    6 - Menú Configuraciones" << endl;
		cout << "-------------------------------" << endl;
		cout << "    9 - Cerrar sesion" << endl;
		cout << "-------------------------------" << endl;
		cout << "    0 - Salir del programa" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			menuSocios();
			break;
		case 2:
			menuAdmins();
			break;
		case 3:
			menuSolicitudes();
			break;
		case 4:
			menuArmas();
			break;
		case 5:
			menuInformes();
			break;
		case 6:
			menuConfiguracion();
			break;
		case 9:
			cout << "¿Desea cerrar la sesion? (S/N) ";
			cin >> confirmarSalida;

			if (tolower(confirmarSalida) == 's')
			{
				cls();
				return true;
			}
			else
			{
				salir = false;
			}
			break;
		case 0:
			cout << "¿Confirma salir? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			return false;
		}
	}
	return true;
}

////////////////////////////
/// Menu Socios y submenus
////////////////////////////
void menuSocios() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(BLUE);
		cls();
		cout << "\tSocios" << endl;
		cout << "---------------------------------" << endl;
		cout << "    1 - Cargar nuevo Socio" << endl;
		cout << "    2 - Modificar Socio" << endl;
		cout << "    3 - Eliminar Socio" << endl;
		cout << "    4 - Cobrar Cuota" << endl;
		cout << "---------------------------------" << endl;
		cout << "    5 - Listados" << endl;
		cout << "    6 - Consultas" << endl;
		cout << "---------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			cargar_nuevo_socio();
			break;
		case 2:
			modificar_socio();
			break;
		case 3:
			baja_socio();
			break;
		case 4:
			cobrar_cuota();
			break;
		case 5:
			menuListadosSocios();
			break;
		case 6:
			menuConsultasSocios();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');

			break;
		}
	}
}

void menuListadosSocios() {
	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(BLUE);
		cls();
		cout << "\tListados Socios" << endl;
		cout << "-------------------------------" << endl;
		cout << "    1 - Listar todos los Socios" << endl;
		cout << "    2 - Listar socios ordenados alfabeticamente" << endl;
		cout << "    3 - Listar socios por antigüedad" << endl;
		cout << "---------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			listado_general_socios();
			anykey();
			break;
		case 2:
			listarSocioAlfabeticamente();
			anykey();
			break;
		case 3:
			listarSocioPorFecha();
			anykey();
			break;
		case 4:

			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');

			break;
		}
	}
}

void menuConsultasSocios() {
	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(BLUE);
		cls();
		cout << "\tConsultas Socios" << endl;
		cout << "-------------------------------" << endl;
		cout << "    1 - Consulta por DNI" << endl;
		cout << "    2 - Consulta por ID" << endl;
		cout << "    3 - Consulta por Apellido" << endl;
		cout << "---------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			consultaPorDni();
			break;
		case 2:
			consulta_Por_Id();
			break;
		case 3:
			consulta_Por_Apellido();
			break;
		case 4:


			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');

			break;
		}
	}
}

////////////////////////////
/// Menu Administradores y submenus
////////////////////////////

void menuAdmins() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\tAdministradores" << endl;
		cout << "---------------------------------" << endl;
		cout << "    1 - Crear nuevo Administrador " << endl;
		cout << "    2 - Modificar Administrador " << endl;
		cout << "    3 - Eliminar Administrador " << endl;
		cout << "---------------------------------" << endl;
		cout << "    4 - Listados de administradores" << endl;
		cout << "    5 - Buscar Administrador por ID" << endl;
		cout << "---------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			crear_nuevo_admin();
			break;
		case 2:
			modificar_admin();
			break;
		case 3:
			baja_admin();
			break;
		case 4:
			menuListadosAdmin();
			break;
		case 5:
			consulta_admin_Por_ID();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

void menuListadosAdmin() {
	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\t Listados administradores" << endl;
		cout << "---------------------------------" << endl;
		cout << "    1 - Listados general de administradores" << endl;
		cout << "---------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			listado_general_admin();
			anykey();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

////////////////////////////
///Menu Solicitudes y submenus
////////////////////////////
void menuSolicitudes() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(BLUE);
		cls();
		cout << "\tSolicitudes" << endl;
		cout << "---------------------------------" << endl;
		cout << "    1 - Crear nueva Solicitud" << endl;
		cout << "    2 - Modificar Solicitud" << endl;
		cout << "---------------------------------" << endl;
		cout << "    3 - Listados" << endl;
		cout << "    4 - Consultas" << endl;
		cout << "---------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			cargarNuevaSolicitud();
			anykey();
			break;
		case 2:
			modificar_solicitud();
			break;
		case 3:
			menuListadosSolicitudes();
			break;
		case 4:
			menuConsultasSolicitudes();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

void menuListadosSolicitudes() {
	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\tListados Solicitudes" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "    1 - Listar todas las Solicitudes" << endl;
		cout << "    2 - Listar solicitudes por ID de socio" << endl;
		cout << "    3 - Listar Solicitudes por orden descendente" << endl;
		cout << "    4 - Listar Solicitudes por fecha Descendente" << endl;
		cout << "    5 - Listar Solicitudes aprobadas" << endl;
		cout << "    6 - Listar Solicitudes pendientes" << endl;
		cout << "    7 - Listar Solicitudes desaprobadas" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			listadoSolicitudes();
			anykey();
			break;
		case 2:
			listadoSolicitudesPorIdSocio();
			anykey();
			break;
		case 3:
			listarSolicitudesPorIdDesc();
			anykey();
			break;
		case 4:
			listarSolicitudPorFechaDesc();
			anykey();
			break;
		case 5:
			listadoSolicitudesAprobadas();
			anykey();
			break;
		case 6:
			listadoSolicitudesPendientes();
			anykey();
			break;
		case 7:
			listadoSolicitudesDesaprobadas();
			anykey();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

void menuConsultasSolicitudes()
{
	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\tConsultas Solicitudes" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "    1 - Consulta por ID de Solicitud" << endl;
		cout << "    2 - Consulta por Fecha" << endl;
		cout << "    3 - Consulta por Año" << endl;
		cout << "    4 - Consulta Solicitudes pendientes por Socio" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			consultaSolicitudesPorId();
			anykey();
			break;
		case 2:
			consultaSolicitudesPorFecha();
			anykey();
			break;
		case 3:
			consultaSolicitudesPorAnio();
			anykey();
			break;
		case 4:
			listadoSolicitudesPendientesPorSocio();
			anykey();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}

////////////////////////////
///Menu Armas y submenus
////////////////////////////

void menuArmas() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();

		cout << "\tArmas" << endl;
		cout << "---------------------------------" << endl;
		cout << "    1 - Modificar arma " << endl;
		cout << "---------------------------------" << endl;
		cout << "    2 - Listados" << endl;
		cout << "    3 - Consultas" << endl;
		cout << "---------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			modificar_arma();
			break;
		case 2:
			menuListadosArmas();
			break;
		case 3:
			menuConsultasArmas();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');
			break;
		}
	}
}
//Case 4 del menú ARMAS
void menuListadosArmas() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\tListados Armas" << endl;
		cout << "----------------------------------" << endl;
		cout << "    1 - Listar todas los armas" << endl;
		cout << "    2 - Listado por N° de serie" << endl;
		cout << "    3 - Listar por tipo de arma" << endl;
		cout << "    4 - Listar armas por calibre" << endl;
		cout << "----------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			listadoGeneralArmas();
			anykey();
			break;
		case 2:
			listadoDeArmasPorNumDeSerie();
			anykey();
			break;
		case 3:
			listados_Armas_Por_Tipo();
			anykey();
			break;
		case 4:
			listados_Armas_Por_Calibre();
			anykey();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');

			break;
		}
	}
}

//Case 5 del menú ARMAS
void menuConsultasArmas() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\tConsultas Armas" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "    1 - Consultas de armas por número de serie" << endl;
		cout << "    2 - Consultas por ID de armas" << endl;
		cout << "    3 - Consulta de armas por modelo" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			consultaArmasPorNumSerie();
			anykey();
			break;
		case 2:
			consultaArmasPorIdArma();
			anykey();
			break;
		case 3:
			consultaArmasPorModelo();
			anykey();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');

			break;
		}
	}
}

////////////////////////////
///Menu Informes
////////////////////////////
void menuInformes() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\t\t\t\tInformes" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "    1 - Recaudación anual" << endl;
		cout << "    2 - Recaudación por socio" << endl;
		cout << "    3 - Recaudación por administrador" << endl;
		cout << "    4 - Cantidad de armas por socio " << endl;
		cout << "    5 - Cantidad de armas por pais " << endl;
		cout << "    6 - Cantidad de solicitudes desaprobadas por año" << endl;
		cout << "    7 - Promedio de solicitudes aprobadas con respecto al total" << endl;
		cout << "    8 - Porcentaje de armas por tipo" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "    9 - Listar historial de precios de cuota" << endl;
		cout << "    10 - Listar historial de precios de solicitud" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			Informe_Recaudacion_Anual();
			break;
		case 2:
			recaudacionPorSocio();
			break;
		case 3:
			recaudacionPorAdmin();
			break;
		case 4:
			cantidad_de_armas_por_socio();
			anykey();
			break;
		case 5:
			cantidad_de_armas_por_pais();
			anykey();
			break;
		case 6:
			cantidad_solicitudes_desap_por_anio();
			anykey();
			break;
		case 7:
			promedio_solictudes_aprobadas();
			anykey();
			break;
		case 8:
			porcentaje_armas_por_tipo();
			anykey();
			break;
		case 9:
			listar_historial_precios_cuota();
			break;
		case 10:
			listar_historial_precios_solicitud();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');

			break;
		}
	}
}

////////////////////////////
///Menu Configuracion
////////////////////////////
void menuConfiguracion() {

	int opcion;
	char confirmarSalida;
	bool salir = false;

	while (!salir) {

		setColor(WHITE);
		setBackgroundColor(DARKGREY);
		cls();
		cout << "\t\tConfiguraciones" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "            - Estado de cuotas -            " << endl;
		cout << "    1 - Actualizar deudores en archivo" << endl << endl;
		cout << "               - Precios -              " << endl;
		cout << "    2 - Modificar precio de cuota" << endl;
		cout << "    3 - Modificar precio de solicitud" << endl << endl;
		cout << "               - Archivos -              " << endl;
		cout << "    4 - Hacer copia de seguridad Socios" << endl;
		cout << "    5 - Hacer copia de seguridad Solicitudes" << endl;
		cout << "    6 - Exportar archivo CSV de Socios" << endl;
		cout << "    7 - Exportar archivo CSV de Solicitudes" << endl;
		cout << "    8 - Exportar archivo CSV de Armas" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "    0 - Volver al menú principal" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		cls();

		switch (opcion) {
		case 1:
			actualizarEstadoCuotasSocios();
			anykey();
			break;
		case 2:
			modificar_precio_cuota();
			break;
		case 3:
			modificar_precio_solicitud();
			break;
		case 4:
			backup_socios();
			anykey();
			break;
		case 5:
			backup_solicitudes();
			anykey();
			break;
		case 6:
			exportarCSVSocios();
			break;
		case 7:
			exportarCSVSolicitudes();
			break;
		case 8:
			exportarCSVArmas();
			break;
		case 0:
			cout << "¿Volver al menu anterior? (S/N) ";
			cin >> confirmarSalida;

			salir = (tolower(confirmarSalida) == 's');

			break;
		}
	}
}

void todoAMayus(char* apellido)
{

	int len = strlen(apellido);

	for (int i = 0; i < len; i++)
	{
		apellido[i] = toupper(apellido[i]);
	}
}

bool exportarCSVSocios() {

	ofstream myFile;
	myFile.open("listadoSocios.csv");

	FILE* p = fopen("socios.dat", "rb");

	Socio reg;

	if (p == NULL) {
		cout << "No se pudo abrir el archivo";
		return false;
	}

	int pos = 0;

	myFile << "ID SOCIO" << ';' << "DNI" << ';' << "APELLIDO" << ';' << "NOMBRE" << ';' << "ULTIMO PAGO" << ';' << "FECHA INGRESO" << endl;
	//Variable para ultimo pago
	string fecha1;
	//Variable para fecha de ingreso
	string fecha2;

	while (reg.leerDeDisco(pos++)) {
		fecha1 = reg.getUltimoPago().toString();
		fecha2 = reg.getFechaIngreso().toString();

		myFile << reg.getIdsocio() << ';' << reg.getDni() << ';' << reg.getApellido() << ';' << reg.getNombre() << ';' << fecha1 << ';' << fecha2 << endl;
	}

	cout << "Listado 'listadoSocios.csv' exportado correctamente" << endl;
	system("pause");
	system("cls");

	return true;
}

bool exportarCSVSolicitudes()
{
	ofstream myFile;
	myFile.open("listadoSolicitudes.csv");

	FILE* p = fopen("solicitudes.dat", "rb");
	Solicitud reg;

	if (p == NULL) {
		cout << "No se pudo abrir el archivo";
		return false;
	}

	int pos = 0;

	myFile << "ID SOLICITUD" << ';' << "ID ADMIN" << ';' << "ID SOCIO" << ';' << "ID ARMA" << ';' << "FECHA INICIO" << ';' << "ESTADO" << endl;

	string fecha;
	string estado;

	while (reg.leerDeDisco(pos++)) {
		fecha = reg.getFechaSolicitud().toString();

		if (reg.getAprobado() == -1)
		{
			estado = "DESAPROBADO";
		}

		if (reg.getAprobado() == 0)
		{
			estado = "PENDIENTE";
		}

		if (reg.getAprobado() == 1)
		{
			estado = "APROBADO";
		}

		myFile << reg.getIdSolicitud() << ';' << reg.getIdAdministrador() << ';' << reg.getIdSocio() << ';' << reg.getIdArma() << ';' << fecha << ';' << estado << endl;
	}

	cout << "Listado 'listadoSolicitudes.csv' exportado correctamente" << endl;
	system("pause");
	system("cls");

	return true;
}

bool exportarCSVArmas()
{
	ofstream myFile;
	myFile.open("listadoArmas.csv");

	FILE* p = fopen("armas.dat", "rb");
	Arma reg;

	if (p == NULL) {
		cout << "No se pudo abrir el archivo";
		return false;
	}

	int pos = 0;

	myFile << "ID ARMA" << ',' << "MODELO" << ',' << "CALIBRE" << ',' << "ID PAIS" << ',' << "TIPO DE ARMA" << ',' << "NUM SERIE" << endl;

	string modelo;
	string tipo;

	while (reg.leerDeDisco(pos++)) {

		modelo = reg.getModelo();

		switch (reg.getTipoArma())
		{
		case 1:
			tipo = "PISTOLA";
			break;
		case 2:
			tipo = "ESCOPETA";
			break;
		case 3:
			tipo = "SUBFUSIL";
			break;
		case 4:
			tipo = "CARABINA";
			break;
		case 5:
			tipo = "FUSIL AUTOMÁTICO";
			break;
		default:
			break;
		}

		myFile << reg.getIdArma() << ',' << modelo << ',' << reg.getCalibre() << ',' << reg.getidPaisFabricacion() << ',' << tipo << ',' << reg.getNumSerie() << endl;
	}

	cout << "Listado 'listadoArmas.csv' exportado correctamente" << endl;
	system("pause");
	system("cls");

	return true;
}

