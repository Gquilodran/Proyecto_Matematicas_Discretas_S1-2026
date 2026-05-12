#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct {
	char nombreCalle[50];
	float x1,y1;
	float x2,y2;
	char sentido;
} calle;

typedef struct {
	char nombre[50];
	char ubicacion[50];
	float altura;
	float x,y;
	int indice_calle;
} punto;

typedef struct {
	calle calles[50];
	punto puntos[150];
	int nCalles;
	int nPuntos;
	int nX;
	int nY;
} Datos;

#define MAX_NODOS 1300
#define MAX_VECINOS 100
#define MAX_CALLES_NODO 50

typedef struct {
	float x, y;
	int calles[MAX_CALLES_NODO];
	int n_calles;
	int es_turistico;
	int vecinos[MAX_VECINOS];
	int n_vecinos;
} nodo;

typedef struct {
	nodo nodos[MAX_NODOS];
	int n_nodos;
} Grafo;

#endif