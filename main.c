#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[50];
  int caloria;
} Alimento;

typedef struct no { // estrutura da arvore
  Alimento alimento;
  struct no *dir;
  struct no *esq;
} noABP;

Alimento ler_alimento(char *nomeAlimento, int calAlimento) {
  Alimento alimento;
  //printf("%s", nomeAlimento);
  strcpy(alimento.nome, nomeAlimento);
  //alimento.caloria = calAlimento;
  //fgets(alimento.nome, 49, stdin);
  alimento.caloria = calAlimento;
  //scanf("%d", &alimento.caloria);
  return alimento;
}

void imprimir_alimento(Alimento alimento) {
  printf("\tAlimento: %s\tcaloria: %d\n", alimento.nome, alimento.caloria);
}

noABP *inserir_versao_1(noABP *raiz, Alimento a) {
  if (raiz == NULL) {
    noABP *aux = malloc(sizeof(noABP));
    aux->alimento = a;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
  } else {
    if (a.caloria < raiz->alimento.caloria)
      raiz->esq = inserir_versao_1(raiz->esq, a);
    else
      raiz->dir = inserir_versao_1(raiz->dir, a);
    return raiz;
  }
}

noABP *inserir_versao_2(noABP *raiz, Alimento a) {
  if (raiz == NULL) {
    noABP *aux = malloc(sizeof(noABP));
    aux->alimento = a;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
  } else {
    if (strcmp(a.nome, raiz->alimento.nome) < 0) {
      //printf("antes");
      raiz->esq = inserir_versao_1(raiz->esq, a);
    } else if (strcmp(a.nome, raiz->alimento.nome) == 0) {
      //printf("igual");
      raiz->esq = inserir_versao_1(raiz->esq, a);
    } else {
      //printf("depois");
      raiz->dir = inserir_versao_1(raiz->dir, a);
    }
      /*if (a.caloria < raiz->alimento.caloria)
        raiz->esq = inserir_versao_1(raiz->esq, a);
      else
        raiz->dir = inserir_versao_1(raiz->dir, a);*/
      return raiz;
  }
}

int altura(noABP *raiz) {
  if (raiz == NULL) {
    return -1;
  } else {
    int esq = altura(raiz->esq);
    int dir = altura(raiz->dir);
    if (esq > dir)
      return esq + 1;
    else
      return dir + 1;
  }
}

int quantidade_nos(noABP *raiz) {
  if (raiz == NULL)
    return 0;
  else
    return 1 + quantidade_nos(raiz->esq) + quantidade_nos(raiz->dir);

  // operador ternário
  // return (raiz == NULL)? 0: 1 + quantidade_nos(raiz->esquerda) +
  // quantidade_nos(raiz->direita);
}

int quantidade_folhas(noABP *raiz) {
  if (raiz == NULL)
    return 0;
  else if (raiz->esq == NULL && raiz->dir == NULL)
    return 1;
  else
    return quantidade_folhas(raiz->esq) + quantidade_folhas(raiz->dir);
}

void imprimir_versao_1(noABP *raiz) { // 50 25 30 100
  if (raiz) {
    imprimir_alimento(raiz->alimento);
    imprimir_versao_1(raiz->esq);
    imprimir_versao_1(raiz->dir);
  }
}

void Desenha(noABP *a, int nivel) { // funcao que imprime a arvore de um modo mais intuitivo
  int x;
  if (a != NULL) {
    for (x = 1; x <= nivel; x++)
      printf("=");
    printf("%s\n", a->alimento.nome);
    printf("%d\n", a->alimento.caloria);
    if (a->esq != NULL)
      Desenha(a->esq, (nivel + 1));
    if (a->dir != NULL)
      Desenha(a->dir, (nivel + 1));
  }
}

int main() {
  noABP *raiz = NULL;
  int opcao = 1;

  /*char *texto[50];
  char *arq;
  int iteracao = 0;
  int caloria;

  FILE *open_arq; //ponteiro para file*/

  raiz = inserir_versao_2(raiz, ler_alimento("cebola", 100));
  raiz = inserir_versao_2(raiz, ler_alimento("melao", 30));
  raiz = inserir_versao_2(raiz, ler_alimento("goiaba", 70));
  raiz = inserir_versao_2(raiz, ler_alimento("abacate", 10));
  raiz = inserir_versao_2(raiz, ler_alimento("beterrava", 80));

  /*while (opcao != 0) {
    raiz = inserir_versao_1(raiz, ler_alimento("banana", 50));
    scanf("%d", &opcao);
    fflush(stdin);
  }*/

  // imprimir_versao_1(raiz);
  Desenha(raiz, 1);
  printf("\n");
  printf("folhas = %d | nos = %d | altura = %d", quantidade_folhas(raiz), quantidade_nos(raiz), altura(raiz));

  /*open_arq = fopen("arquivoTeste.csv", "r"); //abre o arquivo

  while (EOF != fscanf(open_arq, "%[^\n]\n", texto)) {
    arq = strtok(texto, ";");
    while (arq != NULL) {
      //printf("'%s' ", arq);
      if (iteracao == 0) {
        // leitura do nome do alimento;
        iteracao = 1;
      } else { // leitura da caloria
        caloria = atoi(arq);
        printf("/ %d /\n", caloria);
        iteracao = 0;
      }
      arq = strtok(NULL, ";");
    }
    printf("\n");
  }
  fclose(open_arq);*/
  printf("\n");

  system("pause");
  system("cls");
  return 0;
}