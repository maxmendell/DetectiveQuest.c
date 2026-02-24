#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Estrutura que representa uma Sala da mansão.
 * Contém o nome do cômodo e ponteiros para as salas à esquerda e à direita.
 */
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;
/**
 * Cria uma nova sala de forma dinâmica.
 * @param nome O nome da sala a ser criada.
 * @return Um ponteiro para a nova Sala criada.
 */
Sala* criarSala(char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}
/**
 * Permite a navegação do jogador pela árvore binária (mapa da mansão).
 * @param atual Ponteiro para a sala onde o jogador se encontra no momento.
 */
void explorarSalas(Sala* atual) {
    char escolha;
    
    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);
        // Verifica se é uma sala sem saídas (nó-folha)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim do caminho. Exploração concluída!\n");
            break;
        }
        printf("Escolha uma direção: (e) para esquerda, (d) para direita, (s) para sair: ");
        scanf(" %c", &escolha);
        if (escolha == 's') {
            printf("Saindo da exploração...\n");
            break;
        } else if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há caminho para a esquerda nesta sala.\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há caminho para a direita nesta sala.\n");
            }
        } else {
            printf("Escolha inválida! Use 'e', 'd' ou 's'.\n");
        }
    }
}
int main() {
    // Configura a codificação de saída para suportar caracteres especiais no console (Windows)
    // No Windows, costuma-se usar system("chcp 65001 > nul") para UTF-8, mas manteremos o padrão ANSI para simplicidade.
    
    // Montagem do mapa da mansão (Árvore Binária)
    Sala* hallInput = criarSala("Hall de entrada");
    Sala* salaEstar = criarSala("Sala de estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jardim = criarSala("Jardim");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* escritorio = criarSala("Escritório");
    Sala* despensa = criarSala("Despensa");
    // Definindo as conexões do mapa
    hallInput->esquerda = salaEstar;
    hallInput->direita = cozinha;
    salaEstar->esquerda = jardim;
    salaEstar->direita = biblioteca;
    cozinha->esquerda = despensa;
    // Cozinha não tem saída à direita neste exemplo
    biblioteca->esquerda = escritorio;
    // Início da exploração
    printf("--- Bem-vindo ao Detective Quest! ---\n");
    explorarSalas(hallInput);
    // Nota: Em um programa real, deveríamos liberar a memória alocada dinamicamente
    // percorrendo a árvore, mas conforme as simplificações, focaremos na lógica de navegação.
    return 0;
}
