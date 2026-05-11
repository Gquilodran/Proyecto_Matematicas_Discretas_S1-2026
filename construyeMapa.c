#include <math.h>
#include <string.h>
#include "estructuras.h"

#define UMBRAL 1e-5f
// Valor usado como umbral al comparar es para evitar problemas de precision con floats
// si bien es arbitrario se eligio un valor pequeño que es menor a la distancia mas pequena posible

void calcular_coordenadas_puntos(Datos *datos) {
    for (int i=0;i<datos->nPuntos;i++) {
        for (int j=0; j<datos->nCalles; j++) {
            if (strcmp(datos->puntos[i].ubicacion, datos->calles[j].nombreCalle)==0) {
                datos->puntos[i].indice_calle=j;
                calle *c=&datos->calles[j];

                if (c->sentido=='X') {
                    float dx=c->x2 - c->x1;
                    if (fabsf(dx)<UMBRAL) break; //fabsf es la funcion de valor absoluto para floats
                    float t=(datos->puntos[i].altura - c->x1) / dx;
                    datos->puntos[i].x=datos->puntos[i].altura;
                    datos->puntos[i].y=c->y1 + t * (c->y2 - c->y1);
                } else {
                    float dy=c->y2 - c->y1;
                    // Si la calle es horizontal (dy=0) y tiene sentido Y, el archivo esta mal formado
                    // No se puede determinar la posicion del punto, se ignora
                    if (fabsf(dy)<UMBRAL) break;
                    float t=(datos->puntos[i].altura - c->y1) / dy;
                    datos->puntos[i].y=datos->puntos[i].altura;
                    datos->puntos[i].x=c->x1 + t * (c->x2 - c->x1);
                }
                break;
            }
        }
    }
}

void agregar_calle_a_nodo(nodo *n,int calle) {
    for (int i=0;i<n->n_calles;i++)
        if (n->calles[i]==calle) return;
    n->calles[n->n_calles++]=calle;
}

int buscar_nodo(Grafo *g,float x,float y) {
    for (int i=0;i<g->n_nodos;i++)
        if (fabsf(g->nodos[i].x - x)<UMBRAL &&
            fabsf(g->nodos[i].y - y)<UMBRAL)
            return i;
    return -1;
}

int agregar_nodo(Grafo *g,float x,float y,int c1,int c2,int turistico) {
    int idx=buscar_nodo(g,x,y);
    if (idx!=-1) {
        if (c1!=-1) agregar_calle_a_nodo(&g->nodos[idx], c1);
        if (c2!=-1) agregar_calle_a_nodo(&g->nodos[idx], c2);
        if (turistico!=-1) g->nodos[idx].es_turistico=turistico;
        return idx;
    }
    int i=g->n_nodos++;
    g->nodos[i].x=x;
    g->nodos[i].y=y;
    g->nodos[i].n_calles=0;
    g->nodos[i].n_vecinos=0;
    g->nodos[i].es_turistico=turistico;
    if (c1!=-1) agregar_calle_a_nodo(&g->nodos[i], c1);
    if (c2!=-1) agregar_calle_a_nodo(&g->nodos[i], c2);
    return i;
}

void conectar(Grafo *g,int u,int v) {
    for (int i=0;i<g->nodos[u].n_vecinos;i++)
        if (g->nodos[u].vecinos[i]==v) return;
    g->nodos[u].vecinos[g->nodos[u].n_vecinos++]=v;
    g->nodos[v].vecinos[g->nodos[v].n_vecinos++]=u;
}

int interseccion_segmentos(calle a,calle b,float *ix,float *iy) {
    float dx1=a.x2 - a.x1, dy1=a.y2 - a.y1;
    float dx2=b.x2 - b.x1, dy2=b.y2 - b.y1;
    float denom=dx1 * dy2 - dy1 * dx2;

    if (fabsf(denom)<UMBRAL) return 0;

    float t=((b.x1 - a.x1) * dy2 - (b.y1 - a.y1) * dx2) / denom;
    float s=((b.x1 - a.x1) * dy1 - (b.y1 - a.y1) * dx1) / denom;

    if (t<UMBRAL*-1 || t > UMBRAL+1 || s<UMBRAL*-1 || s > UMBRAL+1) return 0;

    *ix=a.x1 + t * dx1;
    *iy=a.y1 + t * dy1;
    return 1;
}

void construir_grafo(Datos *datos, Grafo *g) {
    g->n_nodos=0;

    // agregar puntos turisticos
    for (int i=0;i<datos->nPuntos;i++)
        agregar_nodo(g,datos->puntos[i].x, datos->puntos[i].y,
                     datos->puntos[i].indice_calle, -1, i);

    // calcular intersecciones
    float ix, iy;
    for (int i=0;i<datos->nCalles;i++)
        for (int j=i+1; j<datos->nCalles; j++)
            if (interseccion_segmentos(datos->calles[i], datos->calles[j], &ix, &iy))
                agregar_nodo(g, ix, iy, i, j, -1);

    // 3. Conectar nodos por calle
    for (int c=0; c<datos->nCalles; c++) {
        int indices[MAX_NODOS];
        int count=0;

        for (int n=0; n<g->n_nodos; n++) {
            int pertenece=0;
            for (int k=0; k<g->nodos[n].n_calles; k++)
                if (g->nodos[n].calles[k]==c) { pertenece=1; break; }
            if (pertenece) indices[count++]=n;
        }

        // ordenar por posicion en la calle
        char sentido=datos->calles[c].sentido;
        for (int a=0; a<count-1; a++) {
            for (int b=a+1; b<count; b++) {
                float pos_a=(sentido=='X') ? g->nodos[indices[a]].x : g->nodos[indices[a]].y;
                float pos_b=(sentido=='X') ? g->nodos[indices[b]].x : g->nodos[indices[b]].y;
                if (pos_a > pos_b) {
                    int tmp=indices[a];
                    indices[a]=indices[b];
                    indices[b] = tmp;
                }
            }
        }

        // conectar consecutivos
        for (int k = 0; k<count-1; k++)
            conectar(g, indices[k], indices[k+1]);
    }
}