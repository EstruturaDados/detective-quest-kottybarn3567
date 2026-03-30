// ===================================================================================
// BLI, CONST, e STRUCT

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct No {
        char nome[50];
        struct No* esquerda;
        struct No* direita;
    } No;

    No* criarSala(char* nome) {
        No* novaSala = (No*)malloc(sizeof(No));
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
        return novaSala;
    }

// ===================================================================================
// FUNÇÕES

    void explorarSalas(No* salaAtual) {
        char opcao;
        
        while (1) {
            printf("\n🚪 Você está na sala: %s\n", salaAtual->nome);
            
            if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
                printf("🎉 Fim do caminho! Você explorou esta ala da mansão.\n");
                break;
            }
            
            printf("Opções:\n");
            if (salaAtual->esquerda != NULL) {
                printf("  e → %s (esquerda)\n", salaAtual->esquerda->nome);
            }
            if (salaAtual->direita != NULL) {
                printf("  d → %s (direita)\n", salaAtual->direita->nome);
            }
            printf("  s → sair\n");
            printf("Escolha: ");
            
            scanf(" %c", &opcao);
            
            if (opcao == 'e' && salaAtual->esquerda != NULL) {
                explorarSalas(salaAtual->esquerda);
            }
            else if (opcao == 'd' && salaAtual->direita != NULL) {
                explorarSalas(salaAtual->direita);
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
        
        cozinha->esquerda = NULL;    
        quarto->direita = banheiro;  
        
        biblioteca->direita = jardim;
        
        printf("BEM-VINDO À MANSÃO ASSOMBRADA!\n");
        printf("Explore os cômodos usando 'e' (esquerda) ou 'd' (direita)\n\n");
        
        explorarSalas(hallEntrada);
        
        free(hallEntrada);
        free(salaEstar);
        free(cozinha);
        free(quarto);
        free(banheiro);
        free(biblioteca);
        free(jardim);
        
        printf("\nfim do jogo! obrigado por explorar a mansão!\n");
        return 0;
    }
    
// ===================================================================================