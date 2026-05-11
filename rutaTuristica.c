#include <stdio.h>
#include <math.h>
#include "estructuras.h"

int bfs(Grafo *g,int origen,int destino,int camino[],int *largo) {
    int visitado[MAX_NODOS]={0};
    int padre[MAX_NODOS];
    int cola[MAX_NODOS];
    int frente=0, fin=0;

    for (int i=0;i<MAX_NODOS;i++) padre[i]=-1;

    visitado[origen]=1;
    cola[fin++]=origen;

    while (frente<fin) {
        int actual=cola[frente++];
        if (actual==destino) {
            *largo=0;
            int tmp[MAX_NODOS];
            int cur=destino;
            while (cur!=-1) {
                tmp[(*largo)++]=cur;
                cur=padre[cur];
            }
            for (int i=0;i<*largo;i++)
                camino[i]=tmp[*largo - 1 - i];
            return 1;
        }
        for (int k=0; k<g->nodos[actual].n_vecinos; k++) {
            int v=g->nodos[actual].vecinos[k];
            if (!visitado[v]) {
                visitado[v]=1;
                padre[v]=actual;
                cola[fin++]=v;
            }
        }
    }
    return 0;
}

void imprimir_ruta(Grafo *g,Datos *datos,int camino[],int largo,int visitado[]) {
    for (int i=0;i<largo - 1;i++) {
        int u=camino[i];
        int v=camino[i+1];

        // Buscar calle compartida
        int calle_compartida=-1;
        for (int a=0; a<g->nodos[u].n_calles && calle_compartida==-1; a++)
            for (int b=0; b<g->nodos[v].n_calles && calle_compartida==-1; b++)
                if (g->nodos[u].calles[a]==g->nodos[v].calles[b])
                    calle_compartida=g->nodos[u].calles[a];

        float dist=sqrtf(
            (g->nodos[v].x - g->nodos[u].x) * (g->nodos[v].x - g->nodos[u].x) +
            (g->nodos[v].y - g->nodos[u].y) * (g->nodos[v].y - g->nodos[u].y)
        );

        if (calle_compartida!=-1)
            printf("  Siga por %s %.1f metros\n",
                   datos->calles[calle_compartida].nombreCalle, dist);
        else
            printf("  Avance %.1f metros\n", dist);

        if (g->nodos[v].es_turistico != -1) {
            int t = g->nodos[v].es_turistico;
            if (!visitado[t])
                printf("  >>> Ha llegado a %s\n", datos->puntos[t].nombre);
            else
                printf("  (Pasamos de nuevo por %s)\n", datos->puntos[t].nombre);
        }
    }
}

void recorrer_puntos(Grafo *g,Datos *datos) {
    int nodo_punto[50];
    for (int i=0;i<datos->nPuntos;i++) {
        nodo_punto[i]=-1;
        for (int n=0; n<g->n_nodos; n++) {
            if (g->nodos[n].es_turistico==i) {
                nodo_punto[i]=n;
                break;
            }
        }
    }

    int visitado[50]={0};
    int camino[MAX_NODOS];
    int largo;
    int ultimo=nodo_punto[0];
    visitado[0]=1;

    printf("\nRUTA TURISTICA\n");
    printf("Partimos en %s\n", datos->puntos[0].nombre);

    for (int i=1; i<datos->nPuntos;i++) {
        if (visitado[i]) continue;

        printf("\nDe %s a %s:\n",
               datos->puntos[g->nodos[ultimo].es_turistico].nombre,
               datos->puntos[i].nombre);

        // Construir lista de nodos turisticos ya visitados a evitar
        int evitar[50];
        int n_evitar=0;
        for (int k=0; k<datos->nPuntos; k++)
            if (visitado[k] && nodo_punto[k]!=ultimo)
                evitar[n_evitar++]=nodo_punto[k];

        if (bfs(g, ultimo, nodo_punto[i], camino, &largo)) {
            imprimir_ruta(g,datos,camino,largo,visitado);
            for (int k=0; k<largo; k++) {
                int t=g->nodos[camino[k]].es_turistico;
                if (t!=-1) {
                    visitado[t]=1;
                    ultimo=camino[k];
                }
            }
        } else {
            // Si no hay ruta evitando visitados, intentar sin restricciones
            if (bfs(g, ultimo, nodo_punto[i], camino, &largo)) {
                imprimir_ruta(g,datos, camino, largo,visitado);
                for (int k=0; k<largo; k++) {
                    int t=g->nodos[camino[k]].es_turistico;
                    if (t!=-1) {
                        visitado[t]=1;
                        ultimo=camino[k];
                    }
                }
            } else {
                printf("  No hay ruta disponible entre estos puntos.\n");
                visitado[i]=1;
                ultimo=nodo_punto[i];
            }
        }
    }
}