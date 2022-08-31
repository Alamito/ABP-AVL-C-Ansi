#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- VARIAVEIS GLOBAIS ---------------------
int totalCalorias = 0;                                   //
// --------------------------------------------------------

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
  strcpy(alimento.nome, nomeAlimento);
  alimento.caloria = calAlimento;
  return alimento;
}

void imprimir_alimento(Alimento alimento) {
  printf("\tAlimento: %s\tcaloria: %d\n", alimento.nome, alimento.caloria);
}

noABP *inserir_versao_1(
    noABP *raiz,
    Alimento a) { // insere de acordo com a menor caloria para a maior
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

noABP *inserir_versao_2(noABP *raiz,
                        Alimento a) { // insere de acordo com o alfabeto
  if (raiz == NULL) {
    noABP *aux = malloc(sizeof(noABP));
    aux->alimento = a;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
  } else {
    if (strcmp(a.nome, raiz->alimento.nome) <
        0) { // se o novo no comecar com uma letra menor
      raiz->esq = inserir_versao_2(raiz->esq, a);
    } else if (strcmp(a.nome, raiz->alimento.nome) == 0) { // se forem iguais
      raiz->esq = inserir_versao_2(raiz->dir, a);
    } else { // se o novo no comecar com uma letra maior
      raiz->dir = inserir_versao_2(raiz->dir, a);
    }
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
    for (x = 1; x <= nivel; x++) {
      printf("=");
    }
    printf("%s\n", a->alimento.nome);
    printf("%d\n", a->alimento.caloria);
    if (a->esq != NULL)
      Desenha(a->esq, (nivel + 1));
    if (a->dir != NULL)
      Desenha(a->dir, (nivel + 1));
  }
}

noABP *leituraArqCalorias(noABP *raiz) {
  char *texto[50], nomeAlimento[50], *arq;
  int iteracao = 0, caloria;
  FILE *open_arq; // ponteiro para file

  open_arq = fopen("1000Shuffled.csv", "r"); // abre o arquivo

  while (EOF != fscanf(open_arq, "%[^\n]\n", texto)) {
    arq = strtok(texto, ";");
    while (arq != NULL) {
      if (iteracao == 0) { // leitura do nome do alimento;
        strcpy(nomeAlimento, arq);
        iteracao = 1;
      } else { // leitura da caloria
        caloria = atoi(arq);
        raiz = inserir_versao_2(raiz, ler_alimento(nomeAlimento, caloria));
        iteracao = 0;
      }
      arq = strtok(NULL, ";");
    }
  }
  fclose(open_arq);
  return raiz;
}

void leituraArqNutri(noABP *raiz) {
  char *texto[50], nomeAlimento[50], *arq;
  int iteracao = 0, porcao;
  FILE *open_arq; // ponteiro para file

  open_arq = fopen("day1.csv", "r"); // abre o arquivo

  while (EOF != fscanf(open_arq, "%[^\n]\n", texto)) {
    arq = strtok(texto, ";");
    while (arq != NULL) {
      if (iteracao == 0) { // leitura do nome do alimento;
        strcpy(nomeAlimento, arq);
        iteracao = 1;
      } else { // leitura da porcao
        porcao = atoi(arq);
        iteracao = 0;
        if (!(procuraABP(raiz, nomeAlimento, porcao))) {  // procura na ABP o nome do alimento
          printf("Alimento %s nao encontrado!\n", nomeAlimento);
        }
      }
      arq = strtok(NULL, ";");
    }
  }
  fclose(open_arq);
}

int procuraABP(noABP *raiz, char *nomeAlimento, int porcao) {
  while (raiz != NULL) {
    if (strcmp(nomeAlimento, raiz->alimento.nome) == 0) { // se o nome do alimento for igual ao nome do alimento do nodo
      exitAlimentoCaloria(nomeAlimento, raiz->alimento.caloria, porcao);
      return 1; // se achou vai retornar verdadeiro
    } else if (strcmp(nomeAlimento, raiz->alimento.nome) > 0) { // se a letra do nome do alimento for maior q a letra do alimento do nodo vai para a direita
      raiz = raiz->dir;
    } else {  // se a letra do nome do alimento for menor q a letra do alimento do nodo vai para a esquerda
      raiz = raiz->esq;
    }
  }
  return 0; // se nao achou vai retornar falso
}

void exitAlimentoCaloria(char *nomeAlimento, int porcaoNutri, int caloriaAlimento) {
  int quantidadeCalorias;

  quantidadeCalorias = (caloriaAlimento * porcaoNutri) / 100; //regra de 3 para calculo das calorias ingeridas
  totalCalorias += quantidadeCalorias;

  printf("quantidade de calorias ingeridas no alimento %s = %d\n", nomeAlimento, quantidadeCalorias);
  //printf("total calorias = %d\n", totalCalorias); // totalCalorias eh uma variavel global
}

int main() {
  noABP *raiz = NULL;

  raiz = leituraArqCalorias(raiz);
  leituraArqNutri(raiz);


  /*raiz = leituraArqCalorias(raiz);
  // imprimir_versao_1(raiz);
  //Desenha(raiz, 1);
  //printf("%d", raiz->alimento.caloria);
  printf("\n");
  printf("folhas = %d | nos = %d | altura = %d", quantidade_folhas(raiz),
         quantidade_nos(raiz), altura(raiz));
  printf("\n");*/

  system("pause");
  system("cls");
  return 0;
}