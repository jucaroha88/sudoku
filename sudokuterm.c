#include <pvm3.h>
#include "sudokupsr.h"
#include "sudokupvmcommon.h"

int main(int argc, char **argv){
	int bufid,ptid;
	NodoBusqueda nodo_inicial, *resul;
	int exito=1,fracaso=0;

	ptid=pvm_parent();
	bufid=pvm_recv(ptid,_TIPOMSG_NODOBUSQUEDA);
	pvm_upkNodoBusqueda(&nodo_inicial);

	resul=resolverRecursivo(nodo_inicial);

	if(resul){
		//enviamos que tuvimos exito, para luego enviar el NodoBusqueda
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&exito,1,1);
		pvm_send(ptid,_TIPOMSG_EXITOFRACASO);

		pvm_initsend(PvmDataDefault);
		pvm_pkNodoBusqueda(resul);
		pvm_send(ptid,_TIPOMSG_NODOBUSQUEDA);
	}else{
		//enviar mensaje de que no se alcanzo solucion por esta rama
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&fracaso,1,1);
		pvm_send(ptid,_TIPOMSG_EXITOFRACASO);
	}
	pvm_exit();
	exit(0);
}
