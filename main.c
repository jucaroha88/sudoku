/*
 * main.c
 *
 *  Created on: Jul 17, 2012
 *      Author: jk
 */
#include "sudokupsr.h"

void printTarea(gpointer data, gpointer user_data){
	printNodoBusqueda((NodoBusqueda*)data);
}

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

	int ejodido[_SUDOK_FILAS][_SUDOK_COLUMNAS] = {	{1,0,0,0,0,7,0,9,0},
													{0,3,0,0,2,0,0,0,8},
													{0,0,9,6,0,0,5,0,0},
													{0,0,5,3,0,0,9,0,0},
													{0,1,0,0,8,0,0,0,2},
													{6,0,0,0,0,4,0,0,0},
													{3,0,0,0,0,0,0,1,0},
													{0,4,0,0,0,0,0,0,7},
													{0,0,7,0,0,0,3,0,0}

											};

	NodoBusqueda n, *resultado;
	GList *tareas;


	inicializarMatrizAdyacencia();

	n = nodoInicial(ejodido);

	tareas=generarTareas(n,10);

	g_list_foreach(tareas,printTarea,NULL);

//	resultado=resolverRecursivo(n);
//	printNodoBusqueda(resultado);

	return 0;
}
