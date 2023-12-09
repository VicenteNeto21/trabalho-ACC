#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"

processo* criarProcesso(int id, const char* desc, int prioridade) {
    processo* novoProcesso = (processo*)malloc(sizeof(processo));
    if (novoProcesso != NULL) {
        novoProcesso->id = id;
        strncpy(novoProcesso->desc, desc, sizeof(novoProcesso->desc) - 1);
        novoProcesso->desc[sizeof(novoProcesso->desc) - 1] = '\0'; // Garante que a string esteja terminada
        novoProcesso->prioridade = prioridade;
        novoProcesso->status = aberto;
    }
    return novoProcesso;
}

void mudancaStatus(processo* p) {
    if (p->status == aberto) {
        p->status = concluido;
    } else {
        p->status = aberto;
    }
}

