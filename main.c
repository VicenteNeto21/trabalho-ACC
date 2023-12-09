#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "processo.h"
#include "pessoa.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    Pessoa* listaUsuarios = NULL;
    int proximoID = 1;

    int opcao = 0;
    while (opcao != 7) {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar usuário\n");
        printf("2. Cadastrar pedido de serviço\n");
        printf("3. Listar todos os usuários e seus serviços\n");
        printf("4. Listar serviços de um usuário\n");
        printf("5. Alterar informações de um usuário\n");
        printf("6. Alterar informações de um pedido\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                char nome[100];

                printf("Digite o nome completo do usuário: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                listaUsuarios = inserirNoInicio(listaUsuarios, proximoID, nome);
                printf("Usuário cadastrado com sucesso com o ID %d!\n", proximoID);

                proximoID++; // Incrementa para o próximo ID único
                break;
            }
            case 2: {
                int idUsuario;
                int prioridade;
                char descricao[100];

                printf("Digite o ID do usuário: ");
                scanf("%d", &idUsuario);
                getchar();

                Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
                if (usuario == NULL) {
                    printf("Usuário não encontrado.\n");
                    break;
                }

                printf("Digite a descrição do serviço: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0';

                printf("Digite a prioridade do serviço (0 - Baixo, 1 - Médio, 2 - Alto): ");
                scanf("%d", &prioridade);
                getchar();

                if (prioridade < 0 || prioridade > 2) {
                    printf("Prioridade inválida. Por favor, escolha entre 0, 1 ou 2.\n");
                    break;
                }

                processo* novoServico = criarProcesso(idUsuario, descricao, prioridade);
                addProcesso(usuario, idUsuario, *novoServico);
                printf("Pedido de serviço cadastrado com sucesso!\n");
                break;
            }
            case 3: {
                printf("=== LISTA DE USUÁRIOS E SEUS SERVIÇOS ===\n");
                if (listaUsuarios == NULL) {
                    printf("Nenhum usuário cadastrado.\n");
                } else {
                    Pessoa* usuarioAtual = listaUsuarios;
                    while (usuarioAtual != NULL) {
                        printf("\nUsuário: %s (ID: %d)\n", usuarioAtual->nome, usuarioAtual->id);
                        if (usuarioAtual->arvore == NULL) {
                            printf("Nenhum serviço cadastrado para este usuário.\n");
                        } else {
                            printf("Serviços cadastrados:\n");
                            imprime(usuarioAtual->arvore);
                        }
                        usuarioAtual = usuarioAtual->prox;
                    }
                }
                break;
            }
            case 4: {
                int idUsuario;
                printf("Digite o ID do usuário para listar os serviços: ");
                scanf("%d", &idUsuario);
                getchar();

                Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
                if (usuario == NULL) {
                    printf("Usuário não encontrado.\n");
                    break;
                }

                printf("=== SERVIÇOS DO USUÁRIO ===\n");
                if (usuario->arvore == NULL) {
                    printf("Nenhum serviço cadastrado para este usuário.\n");
                } else {
                    printf("Serviços cadastrados:\n");
                    imprime(usuario->arvore);
                }
                break;
            }
            case 5: {
                int idUsuario;
                char novoNome[100];

                printf("Digite o ID do usuário que deseja alterar: ");
                scanf("%d", &idUsuario);
                getchar();

                Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
                if (usuario == NULL) {
                    printf("Usuário não encontrado.\n");
                    break;
                }

                printf("Digite o novo nome para o usuário: ");
                fgets(novoNome, sizeof(novoNome), stdin);
                novoNome[strcspn(novoNome, "\n")] = '\0';

                strncpy(usuario->nome, novoNome, sizeof(usuario->nome));
                printf("Informações do usuário alteradas com sucesso!\n");
                break;
            }
            case 6: {
    int idUsuario;
    int idPedido;
    int opcaoUsuario;

    printf("Digite o ID do usuário do pedido que deseja alterar: ");
    scanf("%d", &idUsuario);
    getchar();

    Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
    if (usuario == NULL) {
        printf("Usuário não encontrado.\n");
        break;
    }

    printf("Digite o ID do pedido que deseja alterar: ");
    scanf("%d", &idPedido);
    getchar();

    Tno* pedido = procurar(usuario->arvore, idPedido);
    if (pedido == NULL) {
        printf("Pedido não encontrado para este usuário.\n");
        break;
    }

    printf("1. Alterar prioridade do pedido\n");
    printf("2. Encerrar o pedido\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoUsuario);
    getchar();

    switch (opcaoUsuario) {
        case 1:
            printf("Digite a nova prioridade para o pedido (baixo = 0, médio = 1, alto = 2): ");
            int novaPrioridade;
            scanf("%d", &novaPrioridade);
            getchar();
            pedido->elemento.prioridade = novaPrioridade;
            printf("Informações do pedido alteradas com sucesso!\n");
            break;
        case 2:
            pedido->elemento.status = concluido;
            printf("Pedido encerrado com sucesso!\n");
            break;
        default:
            printf("Opção inválida.\n");
    }
    break;
}
            case 7:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida. Escolha novamente.\n");
        }
    }

    return 0;
}

