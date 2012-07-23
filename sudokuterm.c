

#include <pvm3.h>
#include "sudokupsr.h"
#include "sudokupvmcommon.h"

int main(int argc, char **argv){
	int bufid,ptid;
	NodoBusqueda nodo_inicial, *resul;

	ptid=pvm_parent();
	bufid=pvm_recv(ptid,1);
	pvm_upkNodoBusqueda(&nodo_inicial);

	resul=resolverRecursivo(nodo_inicial);

	if(resul){
		//enviar la solucion de vuelta
	}else{
		//enviar senhal de que no se alcanzo solucion por esta rama
	}

}
