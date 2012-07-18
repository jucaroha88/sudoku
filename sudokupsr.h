/*
 * nodo.h
 *
 *  Created on: Jul 17, 2012
 *      Author: jk
 */

#ifndef SUDOKUPSR_H_
#define SUDOKUPSR_H_

#include <stdio.h>

#define true 1;
#define false 0;

#define _SUDOK_COLUMNAS 9
#define _SUDOK_FILAS 9
#define _SUDOK_COLORES 9

#define _ADJAC_ANCHO 81

#define mat_to_vec(fila,columna) ((fila)*_SUDOK_COLUMNAS + (columna))
#define vec_to_fila(i) (((int)(i))/9)
#define vec_to_columna(i) (((int)(i))%9)

typedef int bool;
typedef int color;

bool matriz_adyacencia[_ADJAC_ANCHO][_ADJAC_ANCHO];


struct Nodo{
	color tablero[_SUDOK_FILAS][_SUDOK_COLUMNAS];
	/* recorrido [fila][columna][color]
	 * true o false segun si el nodo ya fue visitado o no
	 * IMPORTANTE: desperdiciamos un espacio para que coincida el indice del color con su representacion entera
	 * */
	bool recorrido[_SUDOK_FILAS][_SUDOK_COLUMNAS][_SUDOK_COLORES+1];
	/* asignaciones_validas [fila][columna][color]
	 * true or false segun si el color es consistente con el tablero
	 * IMPORTANTE: desperdiciamos un espacio para que coincida el indice del color con su representacion entera
	 */
	bool asignable[_SUDOK_FILAS][_SUDOK_COLUMNAS][_SUDOK_COLORES+1];
};
typedef struct Nodo Nodo;

void inicializarMatrizAdyacencia(){
	int i,j;
	for(i=0;i<_ADJAC_ANCHO;i++){
		for(j=0;j<_ADJAC_ANCHO;j++){
			matriz_adyacencia[i][j]=0;
		}
	}
}

void imprimirMatrizAdyacencia(){
	int i,j;
	for(i=0;i<_ADJAC_ANCHO;i++){
		for(j=0;j<_ADJAC_ANCHO-1;j++){
			printf("%d",matriz_adyacencia[i][j]);
		}
		printf("\n");
	}
}


void asignarColor(int fila, int columna, color color, Nodo *nodo){
	nodo->tablero[fila][columna]=color;
	nodo->recorrido[fila][columna][color]=true;
	//propagamos (por ahora solo comprobacion hacia adelante... mas adelante cambiamos esto por un algoritmo de propagacion)

}

Nodo nodoInicial(int tablero[_SUDOK_FILAS][_SUDOK_COLUMNAS]){
	int i,j,k,c;
	Nodo newnodo;

	//reseteamso recorrido y asignable del Nodo (nada fue recorrido y todo es asignable)
	for(i=0;i<_SUDOK_FILAS;i++){
		for(j=0;j<_SUDOK_COLUMNAS;j++){
			for(k=1;k<=_SUDOK_COLORES;k++){
				newnodo.recorrido[i][j][k]=false;
				newnodo.asignable[i][j][k]=true;
			}
		}
	}

	for(i=0;i<_SUDOK_FILAS;i++){
		for(j=0;j<_SUDOK_COLUMNAS;j++){
			c=tablero[i][j];
			//copia del valor
			asignarColor(i,j,c,&newnodo);
			//si la casilla esta completada, marcamos todos sus colores como recorridos
			if(c)
				for(k=1;k<=_SUDOK_COLORES;k++)
					newnodo.recorrido[i][j][k]=true;
		}
	}
}

#endif /* NODO_H_ */
