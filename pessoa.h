#ifndef PESSOA_H
#define PESSOA_H

#include "avp.h" // Suponho que Tno é definido em avp.h
#include "processo.h" // Suponho que processo seja definido em processo.h

typedef struct pessoa {
    int id;
    char nome[50];
    struct Tno* arvore; // Suponho que Tno é definido como struct Tno em avp.h
    struct pessoa* prox;
} Pessoa;

Pessoa criarPessoa(int id, const char* nome);

Pessoa* inserirNoInicio(Pessoa* lista, int id, const char* nome);

void imprimirPessoa(Pessoa* lista);

void addProcesso(Pessoa* lista, int id, processo b);

#endif /* PESSOA_H */

