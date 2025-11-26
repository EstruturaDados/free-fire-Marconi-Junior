#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa cada item do inventário
typedef struct {
    char nome[30];
    char tipo[20]; // Ex.: arma, munição, cura, ferramenta
    int quantidade;
} Item;

// Prototipação das funções
void inserirItem(Item inventario[], int *total);
void removerItem(Item inventario[], int *total);
void listarItens(Item inventario[], int total);
int buscarItem(Item inventario[], int total, char nomeBuscado[]);

// Função principal
int main() {
    Item inventario[MAX_ITENS];  
    int totalItens = 0;
    int opcao;

    do {
        // Menu principal
        printf("\n=========================================\n");
        printf("MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");
        printf("=========================================\n");
        printf("1. Adcionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Item\n");
        printf("4. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                inserirItem(inventario, &totalItens);
                listarItens(inventario, totalItens);
                break;
            case 2:
                removerItem(inventario, &totalItens);
                listarItens(inventario, totalItens);
                break;
            case 3: {
                char nomeBusca[30];
                printf("Digite o nome do item para buscar: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                int pos = buscarItem(inventario, totalItens, nomeBusca);
                if (pos != -1) {
                    printf("\nItem encontrado:\n");
                    printf("Nome: %s\n", inventario[pos].nome);
                    printf("Tipo: %s\n", inventario[pos].tipo);
                    printf("Quantidade: %d\n", inventario[pos].quantidade);
                } else {
                    printf("Item nao encontrado na mochila.\n");
                }
                break;
            }
            case 4:
                listarItens(inventario, totalItens);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para inserir um item no inventário
void inserirItem(Item inventario[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Inventario cheio! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\n--- Adicionar Novo Item ---\n");

    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar buffer

    inventario[*total] = novo;
    (*total)++;

    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem(Item inventario[], int *total) {
    if (*total == 0) {
        printf("Inventario vazio! Nada para remover.\n");
        return;
    }

    char nomeRemover[30];

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

    int pos = buscarItem(inventario, *total, nomeRemover);

    if (pos == -1) {
        printf("Item nao encontrado!\n");
        return;
    }

    // Deslocamento dos itens
    for (int i = pos; i < *total - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    (*total)--;

    printf("\nItem removido com sucesso!\n");
}

// Função de listagem dos itens
void listarItens(Item inventario[], int total) {
    printf("\n--- ITENS NA MOCHILA ---\n");

    if (total == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("Item %d:\n", i + 1);
        printf(" Nome: %s\n", inventario[i].nome);
        printf(" Tipo: %s\n", inventario[i].tipo);
        printf(" Quantidade: %d\n", inventario[i].quantidade);
        printf("---------------------------\n");
    }
}

// Busca sequencial por nome
int buscarItem(Item inventario[], int total, char nomeBuscado[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(inventario[i].nome, nomeBuscado) == 0) {
            return i; // encontrado
        }
    }
    return -1; // não encontrado
}