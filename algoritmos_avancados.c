// ===================================================================================
// BLI, CONST, e STRUCT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SALAS
typedef struct No {
    char nome[50];
    struct No* esquerda;
    struct No* direita;
} No;

// PISTAS
typedef struct Pista {
    char pista[50];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

No* criarSala(char* nome) {
    No* novaSala = (No*)malloc(sizeof(No));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

Pista* criarPista(char* pista) {
    Pista* novaPista = (Pista*)malloc(sizeof(Pista));
    strcpy(novaPista->pista, pista);
    novaPista->esquerda = NULL;
    novaPista->direita = NULL;
    return novaPista;
}

// ===================================================================================
// FUNÇÕES PISTAS (BST)
Pista* inserirPista(Pista* raiz, char* pista) {
    if (raiz == NULL) {
        return criarPista(pista);
    }
    
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    return raiz;
}

void listarPistas(Pista* raiz) {
    if (raiz == NULL) return;
    listarPistas(raiz->esquerda);
    printf("%s\n", raiz->pista);
    listarPistas(raiz->direita);
}

// ===================================================================================
// FUNÇÕES SALAS
void explorarSalas(No* salaAtual, Pista** raizPistas) {
    char opcao;
    
    while (1) {
        printf("\nVocê está na sala: %s\n", salaAtual->nome);
        
        if (strcmp(salaAtual->nome, "Cozinha") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Chave perdida");
            printf("Pista encontrada: Chave perdida!\n");
        }
        else if (strcmp(salaAtual->nome, "Quarto Principal") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Lençol manchado");
            printf("Pista encontrada: Lençol manchado!\n");
        }
        else if (strcmp(salaAtual->nome, "Biblioteca") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Livro com página faltando");
            printf("Pista encontrada: Livro com página faltando!\n");
        }
        
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Fim do caminho! Você explorou esta ala da mansão.\n");
            break;
        }
        
        printf("Opções:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  e → %s (esquerda)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  d → %s (direita)\n", salaAtual->direita->nome);
        }
        printf("  p → listar pistas\n");
        printf("  s → sair\n");
        printf("Escolha: ");
        
        scanf(" %c", &opcao);
        
        if (opcao == 'e' && salaAtual->esquerda != NULL) {
            explorarSalas(salaAtual->esquerda, raizPistas);
        }
        else if (opcao == 'd' && salaAtual->direita != NULL) {
            explorarSalas(salaAtual->direita, raizPistas);
        }
        else if (opcao == 'p') {
            printf("\nSuas pistas (ordenadas):\n");
            if (*raizPistas == NULL) {
                printf("Nenhuma pista encontrada ainda.\n");
            } else {
                listarPistas(*raizPistas);
            }
            printf("\n");
        }
        else if (opcao == 's') {
            printf("Saindo da exploração...\n");
            break;
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// ===================================================================================
// MAIN
int main() {
    No* hallEntrada;
    No* salaEstar;
    No* cozinha;
    No* quarto;
    No* banheiro;
    No* biblioteca;
    No* jardim;
    Pista* raizPistas = NULL;
    
    hallEntrada = criarSala("Hall de Entrada");
    salaEstar = criarSala("Sala de Estar");
    cozinha = criarSala("Cozinha");
    quarto = criarSala("Quarto Principal");
    banheiro = criarSala("Banheiro");
    biblioteca = criarSala("Biblioteca");
    jardim = criarSala("Jardim Secreto");
    
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = biblioteca;
    
    salaEstar->esquerda = cozinha;
    salaEstar->direita = quarto;
    
    quarto->direita = banheiro;
    
    biblioteca->direita = jardim;
    
    printf("BEM-VINDO À MANSÃO ASSOMBRADA!\n");
    printf("Explore os cômodos: 'e'(esquerda), 'd'(direita), 'p'(pistas)\n\n");
    
    explorarSalas(hallEntrada, &raizPistas);
    
    // Limpeza de memória
    free(hallEntrada); free(salaEstar); free(cozinha);
    free(quarto); free(banheiro); free(biblioteca); free(jardim);
    
    printf("\nFim do jogo! Obrigado por explorar a mansão!\n");
    return 0;
}