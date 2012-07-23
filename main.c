/*
 * main.c
 *
 *  Created on: Jul 17, 2012
 *      Author: jk
 */
#include "sudokupsr.h"

int main(int argc, char **argv){
	int ej[_SUDOK_FILAS][_SUDOK_COLUMNAS] = {	{0,4,0,0,0,7,9,3,0},
												{0,0,3,2,8,0,0,0,5},
												{1,0,9,0,0,5,8,6,7},
												{0,0,0,0,7,4,2,0,0},
												{0,0,0,0,0,3,4,0,8},
												{0,5,0,6,1,0,0,0,0},
												{3,9,0,0,0,6,0,0,0},
												{5,7,0,0,9,0,0,0,0},
												{0,0,0,7,5,0,0,0,0}
											};

	NodoBusqueda n, *resultado;


	inicializarMatrizAdyacencia();

	n = nodoInicial(ej);

	//printNodoBusqueda(&n);

	printf("iniciando busqueda\n");
	resultado=resolverRecursivo(n);
	printf("busqueda finalizada\n");
	if(resultado){
		printNodoBusqueda(resultado);
	}

	return 0;
}
