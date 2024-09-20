#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "farmacia.h"

#define MAX_USERS 100
#define MAX_ITEMS 100

Usuario usuarios[MAX_USERS];
Item itens[MAX_ITEMS];
int totalUsuarios = 0;
int totalItens = 0;

// Funções para manipulação de arquivos
void salvarItensEmArquivo() {
    FILE *arquivo = fopen("itens.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar itens.\n");
        return;
    }
    fwrite(itens, sizeof(Item), totalItens, arquivo);
    fclose(arquivo);
}

void carregarItensDeArquivo() {
    FILE *arquivo = fopen("itens.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de itens encontrado.\n");
        return;
    }
    totalItens = fread(itens, sizeof(Item), MAX_ITEMS, arquivo);
    fclose(arquivo);
}

void salvarUsuariosEmArquivo() {
    FILE *arquivo = fopen("usuarios.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar usuários.\n");
        return;
    }
    fwrite(usuarios, sizeof(Usuario), totalUsuarios, arquivo);
    fclose(arquivo);
}

void carregarUsuariosDeArquivo() {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de usuários encontrado.\n");
        return;
    }
    totalUsuarios = fread(usuarios, sizeof(Usuario), MAX_USERS, arquivo);
    fclose(arquivo);
}

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
    if (totalUsuarios >= MAX_USERS) {
        printf("Limite máximo de usuários atingido!\n");
        return;
    }

    Usuario novoUsuario;
    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", novoUsuario.nome);

    do {
        printf("Digite o email do usuário: ");
        scanf(" %[^\n]", novoUsuario.email);

        if (strchr(novoUsuario.email, '@') == NULL || strlen(novoUsuario.email) >= 80) {
            printf("Email inválido. Deve conter '@' e ser menor que 80 caracteres.\n");
            continue;
        }

        int emailExistente = 0;
        for (int i = 0; i < totalUsuarios; i++) {
            if (strcmp(usuarios[i].email, novoUsuario.email) == 0) {
                emailExistente = 1;
                break;
            }
        }

        if (emailExistente) {
            printf("Email já cadastrado. Por favor, insira um email diferente.\n");
        } else {
            break;
        }

    } while (1);

    printf("Digite a senha do usuário: ");
    scanf(" %[^\n]", novoUsuario.senha);

    usuarios[totalUsuarios++] = novoUsuario;
    salvarUsuariosEmArquivo();
    printf("Usuário cadastrado com sucesso!\n");
}

// Função para realizar o login
int login() {
    char nome[50];
    char senha[20];

    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", nome);

    printf("Digite a senha: ");
    scanf(" %[^\n]", senha);

    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            printf("Login realizado com sucesso! Bem-vindo, %s!\n", usuarios[i].nome);
            return 1;
        }
    }

    printf("Nome de usuário ou senha incorretos.\n");
    return 0;
}

// Função para cadastrar um novo item
void cadastrarItem() {
    if (totalItens >= MAX_ITEMS) {
        printf("Limite máximo de itens atingido!\n");
        return;
    }

    Item novoItem;
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", novoItem.nome);
    printf("Digite o preço do produto: ");
    scanf("%f", &novoItem.preco);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoItem.quantidade);
    printf("Digite a categoria do produto: ");
    scanf(" %[^\n]", novoItem.categoria);

    itens[totalItens++] = novoItem;
    salvarItensEmArquivo();
    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar todos os itens
void listarItens() {
    if (totalItens == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nLista de Produtos:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Produto %d: %s\n", i + 1, itens[i].nome);
        printf("Preço: R$%.2f\n", itens[i].preco);
        printf("Quantidade: %d\n", itens[i].quantidade);
        printf("Categoria: %s\n\n", itens[i].categoria);
    }
}

// Função para editar um item
void editarItem() {
    int indice;
    listarItens();

    printf("Digite o número do item que deseja editar: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > totalItens) {
        printf("Item inválido.\n");
        return;
    }

    Item *item = &itens[indice - 1];
    printf("Editando item: %s\n", item->nome);

    printf("Digite o novo nome (ou pressione Enter para manter): ");
    char novoNome[50];
    scanf(" %[^\n]", novoNome);
    if (strlen(novoNome) > 0) {
        strcpy(item->nome, novoNome);
    }

    printf("Digite o novo preço (ou 0 para manter): ");
    float novoPreco;
    scanf("%f", &novoPreco);
    if (novoPreco > 0) {
        item->preco = novoPreco;
    }

    printf("Digite a nova quantidade (ou 0 para manter): ");
    int novaQuantidade;
    scanf("%d", &novaQuantidade);
    if (novaQuantidade > 0) {
        item->quantidade = novaQuantidade;
    }

    printf("Digite a nova categoria (ou pressione Enter para manter): ");
    char novaCategoria[30];
    scanf(" %[^\n]", novaCategoria);
    if (strlen(novaCategoria) > 0) {
        strcpy(item->categoria, novaCategoria);
    }

    salvarItensEmArquivo();
    printf("Item editado com sucesso!\n");
}

// Função para excluir um item
void excluirItem() {
    int indice;
    listarItens();

    printf("Digite o número do item que deseja excluir: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > totalItens) {
        printf("Item inválido.\n");
        return;
    }

    for (int i = indice - 1; i < totalItens - 1; i++) {
        itens[i] = itens[i + 1];
    }

    totalItens--;
    salvarItensEmArquivo();
    printf("Item excluído com sucesso!\n");
}

// Função de busca binária para encontrar um item pelo nome
int buscaBinariaPorNome(Item itens[], int n, char nome[]) {
    int esquerda = 0, direita = n - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(itens[meio].nome, nome);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

// Algoritmo mergesort para ordenar itens por nome
void mergeSort(Item arr[], int l, int r) {
    if (l < r) {
