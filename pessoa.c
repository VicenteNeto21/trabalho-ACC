#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

Pessoa criarPessoa(int id, const char* nome) {
    Pessoa novaPessoa;
    novaPessoa.id = id;
    strncpy(novaPessoa.nome, nome, sizeof(novaPessoa.nome));
    novaPessoa.arvore = NULL;
    novaPessoa.prox = NULL;
    return novaPessoa;
}

Pessoa* inserirNoInicio(Pessoa* lista, int id, const char* nome) {
    Pessoa* novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if (novaPessoa == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(EXIT_FAILURE);
    }
    *novaPessoa = criarPessoa(id, nome);
    novaPessoa->prox = lista;
    return novaPessoa;
}

void imprimirPessoa(Pessoa* lista) {
    while (lista != NULL) {
        printf("Nome: %s, ID: %d\n", lista->nome, lista->id);
        lista = lista->prox;
    }
}

Pessoa* encontrarUsuario(Pessoa* lista, int id) {
    while (lista != NULL) {
        if (lista->id == id) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

void addProcesso(Pessoa* pessoa, int id, processo p) {
    // Encontrar a pessoa na lista
    Pessoa* alvo = encontrarUsuario(pessoa, id);

    if (alvo != NULL) {
        // Criar um novo n� na �rvore de processos
        Tno* novo = criarTno(p);

        // Verificar se a �rvore da pessoa est� vazia
        if (alvo->arvore == NULL) {
            alvo->arvore = novo;
        } else {
            // Caso contr�rio, inserir o novo processo na �rvore
            alvo->arvore = incluir_no(alvo->arvore, novo);
        }
    } else {
        printf("Pessoa n�o encontrada.\n");
    }
}
