#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "processo.h"

heap* criar(int nmax) {
    heap *h = (heap *)malloc(sizeof(heap));
    h->n = 0;
    h->nmax = nmax;
    h->v = (processo *)malloc(h->nmax * sizeof(processo));
    return h;
}

void heap_libera(heap *h) {
    free(h->v);
    free(h);
}

int heap_vazia(heap *h) {
    return (h->n == 0);
}

void troca(heap *h, int i, int j) {
    processo temp = h->v[i];
    h->v[i] = h->v[j];
    h->v[j] = temp;
}

void sobe(heap *h, int i) {
    int pai;
    while (i > 0) {
        pai = pai(i);
        if ((h->v[pai].id) > (h->v[i].id))
            break;
        troca(h, pai, i);
        i = pai;
    }
}

void desce(heap *h, int i) {
    int aux = esq(i);
    int filho_dir;
    while (aux < h->n) {
        filho_dir = dir(i);
        if ((filho_dir < h->n) && (h->v[filho_dir].id > h->v[aux].id))
            aux = filho_dir;
        if (h->v[aux].id < h->v[i].id)
            break;
        troca(h, i, aux);
        i = aux;
        aux = esq(i);
    }
}

void heap_insere(heap *h, processo valor) {
    h->v[h->n++] = valor;
    sobe(h, h->n - 1);
}

int heap_retira(heap *h) {
    int topo = h->v[0].id;
    h->v[0] = h->v[--(h->n)];
    desce(h, 0);
    return topo;
}

void mostrar(heap *h) {
    int i;
    puts("-----------ELEMENTOS-----------");
    for (i = 0; i < h->n; i++)
        printf("ID=%d, Desc=%s, Prioridade=%d, Status=%d\n",
               h->v[i].id, h->v[i].desc, h->v[i].prioridade, h->v[i].status);
}

int esq(int i) {
    return 2 * i + 1;
}

int dir(int i) {
    return 2 * i + 2;
}
