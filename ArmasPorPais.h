#include "Socio.h"
#include "rlutil.h"
#include "Arma.h"

using namespace std;
using namespace rlutil;

class ArmasPorPais
{
private:
	int _idPais;
	int _cantidadArmas;
	bool _estado;

public:
	ArmasPorPais();

	void setIdPais(int);
	void setCantidadArmas(int);
	void setEstado(bool);

	int getIdPais();
	int getCantidadArmas();
	bool getEstado();
};

int cantidadRegPaises();

void cantidad_de_armas_por_pais();

void inicializarVecPaises(ArmasPorPais *vecPaises, int cantReg);
void ordenarVectorPaises(ArmasPorPais* vecPaises, int cantReg);
int buscarPosPais(int idPais, ArmasPorPais* vPaises, int cantReg);
void MostrarVectorPaises(ArmasPorPais* vecPaises, int cantReg);
void buscarArmasPorPais(ArmasPorPais* vecPaises, int cantReg);


