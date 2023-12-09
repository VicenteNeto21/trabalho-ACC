#include <stdio.h>
#include <stdlib.h>
#include "avp.h"
#include "processo.h"

Tno *rotacao_simples_esquerda(Tno *a) {
    Tno *aux = a->dir;
    a->dir = aux->esq;
    aux->esq = a;
    a = aux;
    return a;
}

Tno *rotacao_simples_direita(Tno *a) {
    Tno *aux = a->esq;
    a->esq = aux->dir;
    aux->dir = a;
    a = aux;
    return a;
}

Tno *criarTno(processo elemento) {
    Tno *dado = (Tno *)malloc(sizeof(Tno));
    if (dado == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    dado->elemento = elemento;
    dado->esq = NULL;
    dado->dir = NULL;
    dado->cor = vermelho;
    return dado;
}

Tno *inserir(Tno *a, processo valor) {
    Tno *dado = criarTno(valor);
    a = incluir_no(a, dado);
    if (a != NULL) {
        a->cor = preto;
    }
    return a;
}

Tno *incluir_no(Tno *a, Tno *dado) {
    if (a == NULL) {
        return dado;
    } else {
        if (a->elemento.id > dado->elemento.id) {
            a->esq = incluir_no(a->esq, dado);
        } else {
            a->dir = incluir_no(a->dir, dado);
        }
        if (cor(a->esq) == vermelho && cor(a->dir) == vermelho) {
            trocaCor(a);
        }
    }
    return a;
}

int cor(Tno *a) {
    return (a == NULL) ? preto : a->cor;
}

void trocaCor(Tno *a) {
    if (a == NULL)
        return;

    a->cor = !a->cor;
    if (a->esq != NULL) {
        a->esq->cor = !a->esq->cor;
    }
    if (a->dir != NULL) {
        a->dir->cor = !a->dir->cor;
    }
}

void imprime(Tno *a) {
    if (a == NULL) {
        return;
    }
    imprimirProcesso(a->elemento);
    printf("\ncor: %d", a->cor);

    if (a->esq != NULL) {
        printf("(E:%d [cor: %d])", a->esq->elemento.id, a->esq->cor);
    }
    if (a->dir != NULL) {
        printf("(D:%d [cor: %d])", a->dir->elemento.id, a->dir->cor);
    }
    printf("\n");

    imprime(a->esq);
    imprime(a->dir);
}

Tno* procurar(Tno* raiz, int id) {
    if (raiz == NULL || raiz->elemento.id == id) {
        return raiz;
    }
    if (id < raiz->elemento.id) {
        return procurar(raiz->esq, id);
    } else if (id > raiz->elemento.id) {
        return procurar(raiz->dir, id);
    }
    return NULL;
}

void imprimirProcesso(processo p) {
    printf("ID: %d\n", p.id);
    printf("Descrição: %s\n", p.desc);
    printf("Prioridade: %d\n", p.prioridade);
    printf("Status: %d\n", p.status);
    printf("\n");
}
