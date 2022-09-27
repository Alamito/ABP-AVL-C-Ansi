#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABELA_ALIMENTOS "1000Shuffled.csv"
#define TABELA_NUTRI "day1.csv"

//----------------- VARIAVEIS GLOBAIS ---------------------
int totalCalorias = 0;
int comp = 1; // inicia com 1 por causa do while que na comparacao final nao soma 1 na variavel
//---------------------------------------------------------

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

noABP *inserir_versao_1(noABP *raiz, Alimento a) { // insere de acordo com a menor caloria para a maior
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

noABP *inserir_versao_2(noABP *raiz, Alimento a) { // insere de acordo com o alfabeto
  if (raiz == NULL) {
    noABP *aux = malloc(sizeof(noABP));
    aux->alimento = a;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
  } else {
    if (strcmp(a.nome, raiz->alimento.nome) < 0) { // se o novo no comecar com uma letra menor
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

noABP *leituraArqCalorias(noABP *raiz, char nomeArquivo[]) {
  char *texto[50], nomeAlimento[50], *arq;
  int iteracao = 0, caloria;
  FILE *open_arq; // ponteiro para file

  open_arq = fopen(nomeArquivo, "r"); // abre o arquivo

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

void leituraArqNutri(noABP *raiz, char nomeArqIngerido[], char nomeSaida[]) {
  char *texto[50], nomeAlimento[50], *arq;
  short iteracao = 0;
  int porcao;
  FILE *open_arq, *arq_exit; // ponteiro para file

  open_arq = fopen(TABELA_NUTRI, "r"); // abre o arquivo
  arq_exit = fopen(nomeSaida, "w");

  informacoesTXT(raiz, arq_exit, 1);

  while (EOF != fscanf(open_arq, "%[^\n]\n", texto)) {
    arq = strtok(texto, ";");
    while (arq != NULL) {
      if (iteracao == 0) { // leitura do nome do alimento;
        strcpy(nomeAlimento, arq);
        iteracao = 1;
      } else { // leitura da porcao
        porcao = atoi(arq);
        iteracao = 0;
        if (!(procuraABP(raiz, nomeAlimento, porcao, arq_exit))) { // procura na ABP o nome do alimento
          printf("Alimento %s nao encontrado!\n", nomeAlimento);
        }
      }
      arq = strtok(NULL, ";");
    }
  }
  informacoesTXT(raiz, arq_exit, 2);
  fclose(open_arq);
  fclose(arq_exit);
}

int procuraABP(noABP *raiz, char *nomeAlimento, int porcao, FILE *arq_exit) {
  while (raiz != NULL) {
    comp++;
    if (strcmp(nomeAlimento, raiz->alimento.nome) == 0) { // se o nome do alimento for igual ao nome do alimento do nodo
      exitAlimentoCaloria(nomeAlimento, raiz->alimento.caloria, porcao, arq_exit);
      return 1; // se achou vai retornar verdadeiro
      comp++;
    } else if (strcmp(nomeAlimento, raiz->alimento.nome) > 0) { // se a letra do nome do alimento for maior q a letra do alimento do nodo vai para a direita
      raiz = raiz->dir;
      comp++;
    } else { // se a letra do nome do alimento for menor q a letra do alimento do nodo vai para a esquerda
      raiz = raiz->esq;
    }
  }
  return 0; // se nao achou vai retornar falso
}

void exitAlimentoCaloria(char *nomeAlimento, int porcaoNutri, int caloriaAlimento, FILE *arq_exit) {
  int quantidadeCalorias;
  FILE *open_arq;

  quantidadeCalorias = (caloriaAlimento * porcaoNutri) / 100; // regra de 3 para calculo das calorias ingeridas
  totalCalorias += quantidadeCalorias;

  fprintf(arq_exit, "%dg de ", caloriaAlimento);
  fputs(nomeAlimento, arq_exit);
  fprintf(arq_exit, " (%d calorias por 100g)", porcaoNutri);
  fputs(" = ", arq_exit);
  fprintf(arq_exit, "%d calorias", caloriaAlimento, quantidadeCalorias);
  fputs("\n", arq_exit);

}

void informacoesTXT(noABP *raiz, FILE *arq_exit, short flag) {
  if (flag == 1) {
    fputs("Calorias calculada para ", arq_exit);
    fputs(TABELA_NUTRI, arq_exit);
    fputs(" usando a tabela ", arq_exit);
    fputs(TABELA_ALIMENTOS, arq_exit);
    fputs("\n\n", arq_exit);
  } else if (flag == 2) {
    fputs("\n", arq_exit);
    fputs("Total de ", arq_exit);
    fprintf(arq_exit, "%d calorias consumidas no dia.\n\n", totalCalorias); // totalCalorias eh uma variavel global
    fputs("======== ESTATÍSTICAS ABP ============\n", arq_exit);
    fprintf(arq_exit, "Numero de Nodos: %d\n", quantidade_nos(raiz));
    fprintf(arq_exit, "Numero de Nodos folhas: %d\n", quantidade_folhas(raiz));
    fprintf(arq_exit, "Altura: %d\n", altura(raiz));
    fprintf(arq_exit, "Rotações: 0\n");
    fprintf(arq_exit, "Comparações: %d\n\n", comp);
  }
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
//----- PASSAGEM DE PARAMETROS PELA main -----//  
  char nomeArqCaloria[50];
  char nomeArqIngerido[50];
  char nomeOutput[50];
  strcpy(nomeArqCaloria, argv[1]);
  strcpy (nomeArqIngerido, argv[2]);
  strcpy (nomeOutput, argv[3]);
//--------------------------------------------//

  clock_t timeExecution = clock();
  noABP *raiz = NULL;

  if (argc != 4) {
    printf("Numero incorreto de parametros!\n");
    printf("Insira: <.exe> <arq_entrada_caloria> <arq_entrada_ingerido> <arq_saida>");
  }

  raiz = leituraArqCalorias(raiz, nomeArqCaloria);
  leituraArqNutri(raiz, nomeArqIngerido, nomeOutput);

  //Desenha(raiz, 1);
  printf("%.3f seg\n", (double)(clock() - timeExecution) / CLOCKS_PER_SEC);
  system("pause");
  system("cls");
  return 0;
}