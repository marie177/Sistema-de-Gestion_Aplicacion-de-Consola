#include "ArmasPorPais.h"

ArmasPorPais::ArmasPorPais()
{
	_idPais = 0;
	_cantidadArmas = 0;
}

void ArmasPorPais::setIdPais(int idPais)
{
	_idPais = idPais;
}

void ArmasPorPais::setCantidadArmas(int cant)
{
	_cantidadArmas = cant;
}

void ArmasPorPais::setEstado(bool e)
{
	_estado = e;
}

int ArmasPorPais::getIdPais()
{
	return _idPais;
}

int ArmasPorPais::getCantidadArmas()
{
	return _cantidadArmas;
}

bool ArmasPorPais::getEstado()
{
	return _estado;
}

int cantidadRegPaises()
{
	FILE* p = fopen("paises.dat", "rb");
	if (p == NULL) {
		return 0;
	}

	size_t bytes;
	int cant_reg;

	fseek(p, 0, SEEK_END);
	bytes = ftell(p);
	fclose(p);
	cant_reg = bytes / sizeof(Pais);
	return cant_reg;
}

void cantidad_de_armas_por_pais()
{
	int cantRegArmas = CantidadRegistroArmas();
	if (cantRegArmas == 0)
	{
		cout << "No se registraron armas al dia de la fecha.";
		return;
	}

	int cantRegPaises = cantidadRegPaises();
	if (cantRegPaises == 0)
	{
		cout << "No se registraron paises al dia de la fecha.";
		return;
	}

	const int PAISES = 10;
	ArmasPorPais* vPaises=new ArmasPorPais[cantRegPaises];

	inicializarVecPaises(vPaises, cantRegPaises);
	ordenarVectorPaises(vPaises, cantRegPaises);
	buscarArmasPorPais(vPaises, cantRegPaises);
	ordenarVectorPaises(vPaises, cantRegPaises);
	MostrarVectorPaises(vPaises, cantRegPaises);

	delete vPaises;

}

void inicializarVecPaises(ArmasPorPais* vPaises, int cantReg)
{
	Pais pais;

	for (int i = 0; i < cantReg; i++) {
		pais.leerDeDisco(i);

		vPaises[i].setIdPais(pais.getIdPais());
		vPaises[i].setEstado(pais.getEstado());
	}
}

void buscarArmasPorPais(ArmasPorPais* vPaises, int cantReg)
{
	int pos = 0;
	int posPais = 0;

	Arma arma;

	while (arma.leerDeDisco(pos))
	{
		posPais = buscarPosPais(arma.getidPaisFabricacion(), vPaises, cantReg);
		vPaises[posPais].setCantidadArmas(vPaises[posPais].getCantidadArmas() + 1);
		pos++;
	}
}

int buscarPosPais(int idPais, ArmasPorPais* vPaises, int cantReg)
{
	for (int pos = 0; pos < cantReg; pos++) {
		if (vPaises[pos].getIdPais() == idPais) {
			return pos;
		}
	}
	return -1;
}

void ordenarVectorPaises(ArmasPorPais* vPaises, int cantReg)
{
	ArmasPorPais aux;

	for (int i = 0; i < cantReg - 1; i++) {
		for (int j = i + 1; j < cantReg; j++) {
			if (vPaises[i].getCantidadArmas() < vPaises[j].getCantidadArmas()) {

				aux = vPaises[i];
				vPaises[i] = vPaises[j];
				vPaises[j] = aux;
			}
		}
	}
}

void MostrarVectorPaises(ArmasPorPais* vPaises, int cantReg)
{
	cout << left;
	cout << setw(17) << "PAIS";
	cout << setw(10) << "CANTIDAD" << endl;
	cout << "--------------------------------" << endl;

	for (int i = 0; i < cantReg; i++)
	{
		if (vPaises[i].getEstado())
		{
		cout << setw(15);
		mostrarPais(vPaises[i].getIdPais());
		cout << setw(10) << vPaises[i].getCantidadArmas() << endl;
		}
	}
}