/*
 * nodo.h
 *
 *  Created on: Jul 17, 2012
 *      Author: jk
 */

#ifndef SUDOKUPSR_H_
#define SUDOKUPSR_H_

#include <stdio.h>

#define true 1
#define false 0

#define _SUDOK_COLUMNAS 9 //cantidad de columnas
#define _SUDOK_FILAS 9	//cantidad de filas
#define _SUDOK_COLORES 9	//cantidad de colores

#define _ADJAC_ANCHO 81 //ancho de la matriz de adjacencia (cantidad de elementos tambien)

#define _SUDOK_CUADRANTES 9 //cantidad de cuadrantes
#define _SUDOK_ELEMSCUADRANTE 9 //cantidad de elementos en un cuadrante


/* MACROS DE CONVERSION DE DIRECCIONES EN EL TABLERO
 * la matriz del tablero de sudoku se puede direccionar de 3 maneras:
 *
 * 		-MATRIZ: una matriz de 9x9, direccionado como [fila][columna], indices empiezan en 0
 * 		-VECTOR: un vector de 81, indice empieza en 0
 * 		-CUADRANTES: el tablero esta dividido en 9 cuadrantes, cada uno de 9 casillas.
 * 						se cuentan de izquierda a derecha, luego de arriba a abajo empezando por el cuadrante 0.
 * 						asi tambien como las casillas que componen los cuadrantes
 */

#define mat_to_vec(fila,columna) ((fila)*_SUDOK_COLUMNAS + (columna))
#define vec_to_fila(i) (((int)(i))/9)
#define vec_to_columna(i) (((int)(i))%9)

#define mat_to_cuad_n(fila,columna) (((fila)/3)*3+((columna)/3))
#define mat_to_cuad_i(fila,columna) (((fila)%3)*3+((columna)%3))
#define cuad_to_fila(n,i) ((n)/3+(i)/3)
#define cuad_to_columna(n,i) (((n)%3)*3+((i)%3))

typedef int bool;
typedef int color;

bool matriz_adyacencia[_ADJAC_ANCHO][_ADJAC_ANCHO];

/* representa un nodo en el arbol de busqueda */
struct NodoBusqueda{
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
typedef struct NodoBusqueda NodoBusqueda;

//TODO hacer procedure para imprimir NodoBusqueda
void printNodoBusqueda(NodoBusqueda *nodo){
	int i,j;
	printf("##TABLERO#\n");
	for(i=0;i<_SUDOK_FILAS;i++){
		if(!(i%3)) printf("\n");
		printf("#");
		for(j=0;j<_SUDOK_COLUMNAS;j++){
			if(!(j%3)) printf(" ");
			printf(" ");
			printf("%d",nodo->tablero[i][j]);
		}
		printf(" #\n");
	}
	printf("#RECORRIDO\n");
	for(i=0;i<_ADJAC_ANCHO;i++){
		printf("#%d. ",i);
		for(j=1;j<_SUDOK_COLORES+1;j++){
			if(nodo->recorrido[vec_to_fila(i)][vec_to_columna(i)][j]==true){
				printf("%d",j);
			}
		}
		printf("\n");
	}
	printf("#ASIGNABLE\n");
	for(i=0;i<_ADJAC_ANCHO;i++){
		printf("#%d. ",i);
		for(j=1;j<_SUDOK_COLORES+1;j++){
			if(nodo->asignable[vec_to_fila(i)][vec_to_columna(i)][j]==true){
				printf("%d",j);
			}
		}
		printf("\n");
	}
	printf("##########");
}

void inicializarMatrizAdyacencia(){
	int i,j;
	for(i=0;i<_ADJAC_ANCHO;i++){
		for(j=0;j<_ADJAC_ANCHO;j++){
			matriz_adyacencia[i][j]=false;
		}
	}
	{
		int nodo,otrnodo,fila,columna,cuadr;
		for(nodo=0;nodo<_ADJAC_ANCHO;nodo++){
			//conectamos con toda su fila
			fila=vec_to_fila(nodo);
			for(columna=0;columna<_SUDOK_COLUMNAS;columna++){
				otrnodo=mat_to_vec(fila,columna);
				matriz_adyacencia[nodo][otrnodo]=true;
			}
			//y toda su columna
			columna=vec_to_columna(nodo);
			for(fila=0;fila<_SUDOK_FILAS;fila++){
				otrnodo=mat_to_vec(fila,columna);
				matriz_adyacencia[nodo][otrnodo]=true;
			}
			//y todito su cuadrante
			cuadr=mat_to_cuad_n(vec_to_fila(nodo),vec_to_columna(nodo));
			for(i=0;i<_SUDOK_ELEMSCUADRANTE;i++){
				otrnodo=mat_to_vec(cuad_to_fila(cuadr,i),cuad_to_columna(cuadr,i));
			}
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


void asignarColor(int fila, int columna, color color, NodoBusqueda *nodo){
	int nronodo,i;
	nodo->tablero[fila][columna]=color;
	nodo->recorrido[fila][columna][color]=true;
	//propagamos (por ahora solo comprobacion hacia adelante... mas adelante cambiamos esto por un algoritmo de propagacion)
	//usando la matriz de adjacencia
	nronodo=mat_to_vec(fila,columna);
	for(i=0;i<_ADJAC_ANCHO;i++){
		if(matriz_adyacencia[nronodo][i] == true){
			nodo->asignable[vec_to_fila(i)][vec_to_columna(i)][color]=false;
		}
	}
}

NodoBusqueda nodoInicial(int tablero[_SUDOK_FILAS][_SUDOK_COLUMNAS]){
	int i,j,k,c;
	NodoBusqueda newnodo;

	//reseteamso recorrido y asignable del Nodo (nada fue recorrido y todos son asignables)
	for(i=0;i<_SUDOK_FILAS;i++){
		for(j=0;j<_SUDOK_COLUMNAS;j++){
			for(k=1;k<=_SUDOK_COLORES;k++){
				newnodo.recorrido[i][j][k]=false;
				newnodo.asignable[i][j][k]=true;
			}
		}
	}
	//copiamos los valores
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
	return newnodo;
}

#endif /* NODO_H_ */
