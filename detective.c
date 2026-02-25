#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Estrutura que representa um nó da Árvore Binária de Busca (BST) de pistas.
 */
typedef struct PistaNode {
  char conteudo[100];
  struct PistaNode *esquerda;
  struct PistaNode *direita;
} PistaNode;
/**
 * Estrutura que representa uma Sala da mansão.
 * Cada sala pode conter uma pista opcional.
 */
typedef struct Sala {
  char nome[50];
  char pista[100];
  struct Sala *esquerda;
  struct Sala *direita;
} Sala;
/**
 * Cria uma nova sala de forma dinâmica com uma pista opcional.
 * @param nome O nome da sala.
 * @param pista O conteúdo da pista (pode ser vazio "").
 * @return Um ponteiro para a nova Sala criada.
 */
Sala *criarSala(char *nome, char *pista) {
  Sala *novaSala = (Sala *)malloc(sizeof(Sala));
  if (novaSala != NULL) {
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
  }
  return novaSala;
}
/**
 * Insere uma nova pista na árvore BST de forma alfabética.
 * @param raiz Ponteiro para o ponteiro da raiz da árvore de pistas.
 * @param conteudo O texto da pista a ser inserido.
 */
void inserirPista(PistaNode **raiz, char *conteudo) {
  if (*raiz == NULL) {
    *raiz = (PistaNode *)malloc(sizeof(PistaNode));
    if (*raiz != NULL) {
      strcpy((*raiz)->conteudo, conteudo);
      (*raiz)->esquerda = NULL;
      (*raiz)->direita = NULL;
    }
    return;
  }
  if (strcmp(conteudo, (*raiz)->conteudo) < 0) {
    inserirPista(&((*raiz)->esquerda), conteudo);
  } else {
    inserirPista(&((*raiz)->direita), conteudo);
  }
}
/**
 * Exibe as pistas coletadas em ordem alfabética (Percorrimento In-Order).
 * @param raiz Raiz da árvore de pistas.
 */
void exibirPistas(PistaNode *raiz) {
  if (raiz != NULL) {
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->conteudo);
    exibirPistas(raiz->direita);
  }
}
/**
 * Controla a navegação entre salas e coleta automática de pistas.
 * @param raizMapa Ponteiro para a sala inicial.
 * @param pistasColetadas Ponteiro para a raiz da BST de pistas.
 */
void explorarSalasComPistas(Sala *raizMapa, PistaNode **pistasColetadas) {
  Sala *atual = raizMapa;
  char escolha;
  while (atual != NULL) {
    printf("\n--- Você está no(a): %s ---\n", atual->nome);
    // Se houver uma pista na sala, ela é coletada automaticamente
    if (strlen(atual->pista) > 0) {
      printf("[PISTA ENCONTRADA]: %s\n", atual->pista);
      inserirPista(pistasColetadas, atual->pista);
      // Limpa a pista para não coletar novamente se voltar à mesma sala
      // logicamente Embora neste modelo fixo apenas avancemos, é uma boa
      // prática.
      strcpy(atual->pista, "");
    }
    printf("Para onde deseja ir? (e) Esquerda, (d) Direita, (s) Sair: ");
    scanf(" %c", &escolha);
    if (escolha == 's') {
      printf("Encerrando investigação...\n");
      break;
    } else if (escolha == 'e') {
      if (atual->esquerda != NULL) {
        atual = atual->esquerda;
      } else {
        printf("Não há saída pela esquerda nesta sala!\n");
      }
    } else if (escolha == 'd') {
      if (atual->direita != NULL) {
        atual = atual->direita;
      } else {
        printf("Não há saída pela direita nesta sala!\n");
      }
    } else {
      printf("Comando inválido. Use 'e', 'd' ou 's'.\n");
    }
  }
}
int main() {
  // Inicialização da árvore de pistas vazia
  PistaNode *pistasColetadas = NULL;
  // Montagem do mapa da mansão com pistas
  Sala *hall = criarSala("Hall de Entrada", "");
  Sala *salaEstar =
      criarSala("Sala de Estar", "Um lenço com as iniciais 'E.S.'");
  Sala *cozinha = criarSala("Cozinha", "Manchas de café recentes no balcão");
  Sala *jardim = criarSala("Jardim", "Pegadas de sapatos tamanho 42");
  Sala *biblioteca = criarSala("Biblioteca", "Um livro de mistério caído");
  Sala *escritorio = criarSala("Escritório", "Documentos triturados no lixo");
  Sala *despensa =
      criarSala("Despensa", "Chave dourada escondida atrás dos sacos");
  // Conexões do mapa (Árvore Binária)
  hall->esquerda = salaEstar;
  hall->direita = cozinha;
  salaEstar->esquerda = jardim;
  salaEstar->direita = biblioteca;
  cozinha->esquerda = despensa;
  biblioteca->esquerda = escritorio;
  // Início do jogo
  printf("--- Bem-vindo ao Detective Quest: A Busca pelas Pistas ---\n");
  explorarSalasComPistas(hall, &pistasColetadas);
  // Finalização e exibição das pistas coletadas
  printf("\n========================================\n");
  printf("RELATÓRIO FINAL DO DETETIVE\n");
  printf("========================================\n");
  if (pistasColetadas == NULL) {
    printf("Nenhuma pista foi coletada durante a investigação.\n");
  } else {
    printf("Pistas organizadas alfabeticamente:\n");
    exibirPistas(pistasColetadas);
  }
  printf("========================================\n");
  return 0;
}
