#ifndef AVP_H
#define AVP_H

#include "processo.h"

typedef enum cor { vermelho, preto } Cor;

typedef struct Tno {
    processo elemento;
    struct Tno* esq;
    struct Tno* dir;
    Cor cor;
} Tno;

Tno *rotacao_simples_esquerda(Tno *a);

Tno *rotacao_simples_direita(Tno *a);

Tno *criarTno(processo elemento);

Tno *inserir(Tno *a, processo valor);

Tno *incluir_no(Tno *a, Tno *dado);

int cor(Tno *a);

void trocaCor(Tno *a);

void imprime(Tno *a);

Tno* procurar(Tno* raiz, int id);

void imprimirProcesso(processo p);

#endif /* AVP_H */

