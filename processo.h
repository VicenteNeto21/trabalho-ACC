#ifndef PROCESSO_H
#define PROCESSO_H

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef enum prioridade { baixo, medio, alto } Prioridade;
typedef enum status { aberto, concluido } Status;

typedef struct processo {
    int id;
    char desc[250];
    int prioridade;
    int status;
} processo;

void mudancaStatus(processo* p);
processo* criarProcesso(int id, const char* desc, int prioridade);


#endif /* PROCESSO_H */

