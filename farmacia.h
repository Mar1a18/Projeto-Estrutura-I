#ifndef FARMACIA_H
#define FARMACIA_H

// Definições de estrutura para o sistema de farmácia
typedef struct {
    char nome[50];
    char email[80];
    char senha[20];
} Usuario;

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
    char categoria[30];
} Item;

// Funções para manipulação de usuários
void cadastrarUsuario();
int login();

// Funções para manipulação de itens
void cadastrarItem();
void listarItens();
void editarItem();
void excluirItem();
void buscarPorCategoria();
void exibirPromocoes();

// Funções de manipulação de arquivos
void salvarItensEmArquivo();
void carregarItensDeArquivo();
void salvarUsuariosEmArquivo();
void carregarUsuariosDeArquivo();

// Algoritmos de busca e ordenação
int buscaBinariaPorNome(Item itens[], int n, char nome[]);
void mergeSort(Item arr[], int l, int r);
void merge(Item arr[], int l, int m, int r);

#endif
