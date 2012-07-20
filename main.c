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

	NodoBusqueda n;
	int filselected,colselected;


	inicializarMatrizAdyacencia();
	imprimirMatrizAdyacencia();

	imprimirAdyacentesApuntadosYApuntadores(4,5);

	n = nodoInicial(ej);

	if(seleccionarCasilla(&n,&filselected,&colselected)){
		printf("nodo seleccionado %d %d \n", filselected, colselected);
		printf("color seleccionado %d \n", seleccionarColor(&n,filselected,colselected));
		printf("esta resuelto? %d \n", isResuelto(&n));
	}
	printNodoBusqueda(&n);
	return 0;
}
