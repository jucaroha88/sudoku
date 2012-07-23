/*
 * sudokupvmcommon.h
 *
 *  Created on: Jul 23, 2012
 *      Author: jk
 */

#ifndef SUDOKUPVMCOMMON_H_
#define SUDOKUPVMCOMMON_H_

#define _TIPOMSG_NODOBUSQUEDA 1
#define _TIPOMSG_EXITOFRACASO 2

#include "sudokupsr.h"

int pvm_pkNodoBusqueda(NodoBusqueda *nodo){
	int nitem=_SUDOK_FILAS*_SUDOK_COLUMNAS + 2*_SUDOK_FILAS*_SUDOK_COLUMNAS*(_SUDOK_COLORES+1);
	return pvm_pkint((int*)nodo,nitem,1);

}

int pvm_upkNodoBusqueda(NodoBusqueda *nodo){
	int nitem=_SUDOK_FILAS*_SUDOK_COLUMNAS + 2*_SUDOK_FILAS*_SUDOK_COLUMNAS*(_SUDOK_COLORES+1);
	return pvm_upkint((int*)nodo,nitem,1);
}

#endif /* SUDOKUPVMCOMMON_H_ */
