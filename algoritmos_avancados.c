// BLI, STRUCTS, e CONSTANTES

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

// SUSPEITO
typedef struct Suspeito {
    char nome[50];
    int contadorPistas;
    struct Suspeito* proxima;
} Suspeito;

// TABELA HASH
#define TAM_HASH 10
Suspeito* hashTable[TAM_HASH];

int hashFunction(char* pista) {
    int hash = 0;
    int i = 0;
    while (i < 5 && pista[i] != '\0') {
        hash += (int)pista[i];
        i++;
    }
    return hash % TAM_HASH;
}

Suspeito* criarSuspeito(char* nome) {
    Suspeito* novo = (Suspeito*)malloc(sizeof(Suspeito));
    strcpy(novo->nome, nome);
    novo->contadorPistas = 1;
    novo->proxima = NULL;
    return novo;
}

void inserirNaHash(char* pista, char* suspeito) {
    int indice = hashFunction(pista);
    
    Suspeito* atual = hashTable[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->nome, suspeito) == 0) {
            atual->contadorPistas++;
            return;
        }
        atual = atual->proxima;
    }

    Suspeito* novo = criarSuspeito(suspeito);
    novo->proxima = hashTable[indice];
    hashTable[indice] = novo;
}

void listarAssociacoes() {
    printf("\n=== ASSOCIAÇÕES PISTA -> SUSPEITO ===\n");
    int totalAssociacoes = 0;
    
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* atual = hashTable[i];
        while (atual != NULL) {
            printf("Suspeito '%s': %d pista(s)\n", atual->nome, atual->contadorPistas);
            totalAssociacoes += atual->contadorPistas;
            atual = atual->proxima;
        }
    }
    
    if (totalAssociacoes == 0) {
        printf("Nenhuma associação encontrada.\n");
    }
}

void suspeitoMaisCitado() {
    int maxPistas = 0;
    char suspeitoVencedor[50] = "Nenhum";
    
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* atual = hashTable[i];
        while (atual != NULL) {
            if (atual->contadorPistas > maxPistas) {
                maxPistas = atual->contadorPistas;
                strcpy(suspeitoVencedor, atual->nome);
            }
            atual = atual->proxima;
        }
    }
    
    printf("\n=== SUSPEITO MAIS CITADO ===\n");
    printf("CULPADO: %s (%d pista(s))\n", suspeitoVencedor, maxPistas);
}

void inicializarHash() {
    for (int i = 0; i < TAM_HASH; i++) {
        hashTable[i] = NULL;
    }
}

void liberarHash() {
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* atual = hashTable[i];
        while (atual != NULL) {
            Suspeito* temp = atual;
            atual = atual->proxima;
            free(temp);
        }
    }
}

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
    printf("  - %s\n", raiz->pista);
    listarPistas(raiz->direita);
}

// FUNÇÕES SALAS
void explorarSalas(No* salaAtual, Pista** raizPistas) {
    char opcao;
    
    while (1) {
        printf("\nVoce esta na sala: %s\n", salaAtual->nome);
        
        if (strcmp(salaAtual->nome, "Cozinha") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Chave perdida");
            inserirNaHash("Chave perdida", "João");
            printf("Pista encontrada: Chave perdida! (Suspeito: João)\n");
        }
        else if (strcmp(salaAtual->nome, "Quarto Principal") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Lencol manchado");
            inserirNaHash("Lencol manchado", "Maria");
            printf("Pista encontrada: Lencol manchado! (Suspeito: Maria)\n");
        }
        else if (strcmp(salaAtual->nome, "Biblioteca") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Livro com pagina faltando");
            inserirNaHash("Livro com pagina faltando", "João");
            printf("Pista encontrada: Livro com pagina faltando! (Suspeito: João)\n");
        }
        
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Fim do caminho! Voce explorou esta ala da mansao.\n");
            break;
        }
        
        printf("Opcoes:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  e → %s (esquerda)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  d → %s (direita)\n", salaAtual->direita->nome);
        }
        printf("  p → listar pistas\n");
        printf("  a → ver associacoes pista-suspeito\n");
        printf("  c → suspeito mais citado\n");
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
        else if (opcao == 'a') {
            listarAssociacoes();
        }
        else if (opcao == 'c') {
            suspeitoMaisCitado();
        }
        else if (opcao == 's') {
            printf("Saindo da exploracao...\n");
            break;
        }
        else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

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
    
    // Inicializar tabela hash
    inicializarHash();
    
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
    
    printf("NIVEL MESTRE - DETECTIVE QUEST COM TABELA HASH!\n");
    printf("Explore os comodos: 'e'(esquerda), 'd'(direita)\n");
    printf("'p'(pistas), 'a'(associacoes), 'c'(culpado), 's'(sair)\n\n");
    
    explorarSalas(hallEntrada, &raizPistas);
    
    // Resultado final
    printf("\n=== INVESTIGACAO FINALIZADA ===\n");
    listarAssociacoes();
    suspeitoMaisCitado();
    
    // Limpeza de memoria
    free(hallEntrada); free(salaEstar); free(cozinha);
    free(quarto); free(banheiro); free(biblioteca); free(jardim);
    liberarHash();
    
    printf("\nParabens, Detective! Missao concluida.\n");
    return 0;
}