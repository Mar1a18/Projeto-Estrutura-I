#include <stdio.h>
#include "farmacia.h"

int main() {
    int opcao, logado = 0;

    carregarUsuariosDeArquivo();
    carregarItensDeArquivo();

    // Boas-vindas e login
    printf("Bem-vindo à Farmácia Virtual!\n");

    do {
        printf("\n1. Login\n2. Cadastrar Usuário\n3. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                logado = login();
                break;
            case 2:
                cadastrarUsuario();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (!logado && opcao != 3);

    if (!logado) {
        return 0;
    }

    // Menu de operações da farmácia
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarItem();
                break;
            case 2:
                listarItens();
                break;
            case 3:
                editarItem();
                break;
            case 4:
                excluirItem();
                break;
            case 5:
                exibirPromocoes();
                break;
            case 6:
                buscarPorCategoria();
                break;
            case 7: {
                // Adiciona ao carrinho com busca binária
                char nomeBusca[50];
                printf("Digite o nome do medicamento que deseja buscar: ");
                scanf(" %[^\n]", nomeBusca);
                mergeSort(itens, 0, totalItens - 1);  // Ordena os itens por nome antes da busca
                int indice = buscaBinariaPorNome(itens, totalItens, nomeBusca);
                if (indice != -1) {
                    printf("Medicamento encontrado: %s - Preço: R$%.2f\n", itens[indice].nome, itens[indice].preco);
                } else {
                    printf("Medicamento não encontrado.\n");
                }
                break;
            }
            case 8:
                printf("Opção de pagamento ainda não implementada.\n");
                break;
            case 9:
                printf("Saindo do sistema...\n");
                salvarItensEmArquivo();  // Salvando as alterações
                salvarUsuariosEmArquivo();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 9);

    return 0;
}
