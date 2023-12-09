#ifndef HEAP_H
#define HEAP_H

#include "processo.h"

#define pai(i) (((i)-1)/2)


typedef struct {
    int n;
    int nmax;
    processo *v;
} heap;

heap* criar(int nmax);
void heap_libera(heap *h);
int heap_vazia (heap *h);

void troca (heap *h, int i, int j);
void sobe (heap *h, int i);
void desce (heap *h, int i);

void heap_insere(heap *h, processo valor);
int heap_retira(heap *h);
void mostrar(heap *h);

#endif /* HEAP_H */

