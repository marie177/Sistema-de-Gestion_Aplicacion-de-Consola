#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void instalacionArchivos();

bool login();

void todoAMayus(char*);

/// Menu
bool menuPrincipal();

/// Menu Socios y submenus
void menuSocios();
void menuListadosSocios();
void menuConsultasSocios();

///Menu Administradores y submenus
void menuAdmins();
void menuListadosAdmin();

///Menu Solicitudes y submenus
void menuSolicitudes();
void menuListadosSolicitudes();
void menuConsultasSolicitudes();

///Menu Armas y submenus
void menuArmas();
void menuListadosArmas();
void menuConsultasArmas();

//Menu Informes
void menuInformes();

//Menu Configuracion
void menuConfiguracion();

bool exportarCSVSocios();
bool exportarCSVSolicitudes();
bool exportarCSVArmas();

#endif // FUNCIONES_H_INCLUDED
