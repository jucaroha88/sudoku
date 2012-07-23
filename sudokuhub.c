
#include <pvm3.h>
#include "sudokupsr.h"
#include "sudokupvmcommon.h"


int main(int argc, char **argv){
	NodoBusqueda nodo_problema;
	int mintareas=4, cantidad_tareas, numt, *tids,i;
	GList *tareas, *tarptr;
	int problema[_SUDOK_FILAS][_SUDOK_COLUMNAS] = {		{1,0,0,0,0,7,0,9,0},
														{0,3,0,0,2,0,0,0,8},
														{0,0,9,6,0,0,5,0,0},
														{0,0,5,3,0,0,9,0,0},
														{0,1,0,0,8,0,0,0,2},
														{6,0,0,0,0,4,0,0,0},
														{3,0,0,0,0,0,0,1,0},
														{0,4,0,0,0,0,0,0,7},
														{0,0,7,0,0,0,3,0,0}

												};

	inicializarMatrizAdyacencia();
	nodo_problema= nodoInicial(problema);

	tareas=generarTareas(nodo_problema,mintareas);
	cantidad_tareas = g_list_length(tareas);

	numt=pvm_spawn("sudokuterm",NULL,0,"",cantidad_tareas,tids);

	if(numt<cantidad_tareas){
		fprintf(stderr, "ERROR. sudokuhub: no se pudo hacer spawn de todas las tareas");
		exit(1);
	}

	//iteramos sobre las tareas y les pasamos los datos
	tarptr=g_list_first(tareas);
	for(i=0;i<cantidad_tareas;i++){
		pvm_initsend(PvmDataDefault);
		pvm_pkNodoBusqueda((NodoBusqueda*)(tarptr->data));
		pvm_send(tids[i],1);
		tarptr=tarptr->next;
	}

	return 0;
}
