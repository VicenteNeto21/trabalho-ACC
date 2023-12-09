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
        printf("1. Cadastrar usu�rio\n");
        printf("2. Cadastrar pedido de servi�o\n");
        printf("3. Listar todos os usu�rios e seus servi�os\n");
        printf("4. Listar servi�os de um usu�rio\n");
        printf("5. Alterar informa��es de um usu�rio\n");
        printf("6. Alterar informa��es de um pedido\n");
        printf("7. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                char nome[100];

                printf("Digite o nome completo do usu�rio: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                listaUsuarios = inserirNoInicio(listaUsuarios, proximoID, nome);
                printf("Usu�rio cadastrado com sucesso com o ID %d!\n", proximoID);

                proximoID++; // Incrementa para o pr�ximo ID �nico
                break;
            }
            case 2: {
                int idUsuario;
                int prioridade;
                char descricao[100];

                printf("Digite o ID do usu�rio: ");
                scanf("%d", &idUsuario);
                getchar();

                Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
                if (usuario == NULL) {
                    printf("Usu�rio n�o encontrado.\n");
                    break;
                }

                printf("Digite a descri��o do servi�o: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0';

                printf("Digite a prioridade do servi�o (0 - Baixo, 1 - M�dio, 2 - Alto): ");
                scanf("%d", &prioridade);
                getchar();

                if (prioridade < 0 || prioridade > 2) {
                    printf("Prioridade inv�lida. Por favor, escolha entre 0, 1 ou 2.\n");
                    break;
                }

                processo* novoServico = criarProcesso(idUsuario, descricao, prioridade);
                addProcesso(usuario, idUsuario, *novoServico);
                printf("Pedido de servi�o cadastrado com sucesso!\n");
                break;
            }
            case 3: {
                printf("=== LISTA DE USU�RIOS E SEUS SERVI�OS ===\n");
                if (listaUsuarios == NULL) {
                    printf("Nenhum usu�rio cadastrado.\n");
                } else {
                    Pessoa* usuarioAtual = listaUsuarios;
                    while (usuarioAtual != NULL) {
                        printf("\nUsu�rio: %s (ID: %d)\n", usuarioAtual->nome, usuarioAtual->id);
                        if (usuarioAtual->arvore == NULL) {
                            printf("Nenhum servi�o cadastrado para este usu�rio.\n");
                        } else {
                            printf("Servi�os cadastrados:\n");
                            imprime(usuarioAtual->arvore);
                        }
                        usuarioAtual = usuarioAtual->prox;
                    }
                }
                break;
            }
            case 4: {
                int idUsuario;
                printf("Digite o ID do usu�rio para listar os servi�os: ");
                scanf("%d", &idUsuario);
                getchar();

                Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
                if (usuario == NULL) {
                    printf("Usu�rio n�o encontrado.\n");
                    break;
                }

                printf("=== SERVI�OS DO USU�RIO ===\n");
                if (usuario->arvore == NULL) {
                    printf("Nenhum servi�o cadastrado para este usu�rio.\n");
                } else {
                    printf("Servi�os cadastrados:\n");
                    imprime(usuario->arvore);
                }
                break;
            }
            case 5: {
                int idUsuario;
                char novoNome[100];

                printf("Digite o ID do usu�rio que deseja alterar: ");
                scanf("%d", &idUsuario);
                getchar();

                Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
                if (usuario == NULL) {
                    printf("Usu�rio n�o encontrado.\n");
                    break;
                }

                printf("Digite o novo nome para o usu�rio: ");
                fgets(novoNome, sizeof(novoNome), stdin);
                novoNome[strcspn(novoNome, "\n")] = '\0';

                strncpy(usuario->nome, novoNome, sizeof(usuario->nome));
                printf("Informa��es do usu�rio alteradas com sucesso!\n");
                break;
            }
            case 6: {
    int idUsuario;
    int idPedido;
    int opcaoUsuario;

    printf("Digite o ID do usu�rio do pedido que deseja alterar: ");
    scanf("%d", &idUsuario);
    getchar();

    Pessoa* usuario = encontrarUsuario(listaUsuarios, idUsuario);
    if (usuario == NULL) {
        printf("Usu�rio n�o encontrado.\n");
        break;
    }

    printf("Digite o ID do pedido que deseja alterar: ");
    scanf("%d", &idPedido);
    getchar();

    Tno* pedido = procurar(usuario->arvore, idPedido);
    if (pedido == NULL) {
        printf("Pedido n�o encontrado para este usu�rio.\n");
        break;
    }

    printf("1. Alterar prioridade do pedido\n");
    printf("2. Encerrar o pedido\n");
    printf("Escolha uma op��o: ");
    scanf("%d", &opcaoUsuario);
    getchar();

    switch (opcaoUsuario) {
        case 1:
            printf("Digite a nova prioridade para o pedido (baixo = 0, m�dio = 1, alto = 2): ");
            int novaPrioridade;
            scanf("%d", &novaPrioridade);
            getchar();
            pedido->elemento.prioridade = novaPrioridade;
            printf("Informa��es do pedido alteradas com sucesso!\n");
            break;
        case 2:
            pedido->elemento.status = concluido;
            printf("Pedido encerrado com sucesso!\n");
            break;
        default:
            printf("Op��o inv�lida.\n");
    }
    break;
}
            case 7:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Op��o inv�lida. Escolha novamente.\n");
        }
    }

    return 0;
}

