#include <stdio.h>
#include <math.h>

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
            int aux[MAX_NODOS];
            int final=destino;
            while (final!=-1) {
                aux[(*largo)++]=final;
                final=padre[final];
            }
            for (int i=0;i<*largo;i++)
                camino[i]=aux[*largo - 1 - i];
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

        float dx = g->nodos[v].x - g->nodos[u].x;
        float dy = g->nodos[v].y - g->nodos[u].y;
        char *direccion;

        if      (dx > 0 && dy == 0) direccion = "Este";
        else if (dx < 0 && dy == 0) direccion = "Oeste";
        else if (dy > 0 && dx == 0) direccion = "Norte";
        else if (dy < 0 && dx == 0) direccion = "Sur";
        // direcciones diagonales
        else if (dx > 0 && dy > 0)  direccion = "Noreste";
        else if (dx > 0 && dy < 0)  direccion = "Sureste";
        else if (dx < 0 && dy > 0)  direccion = "Noroeste";
        else                         direccion = "Suroeste";

        if (calle_compartida != -1)
            printf("  Siga por %s %s %.1f metros\n",
                   datos->calles[calle_compartida].nombreCalle, direccion, dist);
        else
            printf("  Avance %s %.1f metros\n", direccion, dist);

        if (g->nodos[v].es_turistico != -1) {
            int t = g->nodos[v].es_turistico;
            if (!visitado[t])
                printf("  >>> Ha llegado a %s\n", datos->puntos[t].nombre);
            else
                printf("  (Pasamos de nuevo por %s)\n", datos->puntos[t].nombre);
        }
    }
}

void recorrer_puntos(Grafo *g, Datos *datos, int caminos[][MAX_NODOS]) {
    int nodo_punto[50];
    for (int i = 0; i < datos->nPuntos; i++) {
        nodo_punto[i] = -1;
        for (int n = 0; n < g->n_nodos; n++) {
            if (g->nodos[n].es_turistico == i) {
                nodo_punto[i] = n;
                break;
            }
        }
    }

    // verificar si hay ruta factible entre puntos turisticos
    int largos[50];
    int visitado_sim[50] = {0};
    int ultimo_sim = nodo_punto[0];
    visitado_sim[0] = 1;

    for (int i = 1; i < datos->nPuntos; i++) {
        if (visitado_sim[i]) continue;
        if (!bfs(g, ultimo_sim, nodo_punto[i], caminos[i], &largos[i])) {
            printf("Error: no existe ruta entre %s y %s. Ruta turistica no factible.\n",
                   datos->puntos[g->nodos[ultimo_sim].es_turistico].nombre,
                   datos->puntos[i].nombre);
            return;
        }
        // marcar visitados los que se pasan por el camino
        for (int k = 0; k < largos[i]; k++) {
            int t = g->nodos[caminos[i][k]].es_turistico;
            if (t != -1) visitado_sim[t] = 1;
        }
        // ultimo_sim siempre es el destino del tramo
        ultimo_sim = nodo_punto[i];
        visitado_sim[i] = 1;
    }

    // mostrar instrucciones si es que hay
    int visitado[50] = {0};
    int ultimo = nodo_punto[0];
    visitado[0] = 1;

    printf("\nRUTA TURISTICA\n");
    printf("Partimos en %s\n", datos->puntos[0].nombre);

    for (int i = 1; i < datos->nPuntos; i++) {
        if (visitado[i]) continue;

        printf("\nDe %s a %s:\n",
               datos->puntos[g->nodos[ultimo].es_turistico].nombre,
               datos->puntos[i].nombre);

        imprimir_ruta(g, datos, caminos[i], largos[i], visitado);

        for (int k = 0; k < largos[i]; k++) {
            int t = g->nodos[caminos[i][k]].es_turistico;
            if (t != -1) {
                visitado[t] = 1;
                ultimo = caminos[i][k];
            }
        }
    }
}