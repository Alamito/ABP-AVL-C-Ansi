#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABELA_ALIMENTOS "1000Shuffled.csv"
#define TABELA_NUTRI "day1.csv"

//----------------- VARIAVEIS GLOBAIS ---------------------//
int totalCalorias = 0;
int comp = 1; // inicia com 1 por causa do while que na comparacao final nao soma 1 na variavel
//---------------------------------------------------------//

// estrutura do alimento que sera inserido na arvore
typedef struct { 
  char nome[50];
  int caloria;
} Alimento;

// estrutura da arvore ABP
typedef struct no { 
  Alimento alimento;
  struct no *dir;
  struct no *esq;
} noABP;

// leitura do alimento colocando na struct
Alimento ler_alimento(char *nomeAlimento, int calAlimento) {
  Alimento alimento;
  strcpy(alimento.nome, nomeAlimento);
  alimento.caloria = calAlimento;
  return alimento;
}

// imprime a arvore
void imprimir_alimento(Alimento alimento) {
  printf("\tAlimento: %s\tcaloria: %d\n", alimento.nome, alimento.caloria);
}

// insere de acordo com a menor caloria para a maior (nao utilizado)
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

// insere de acordo com o alfabeto em ordem crescente (A - Z)
noABP *inserir_versao_2(noABP *raiz, Alimento a) { 
  if (raiz == NULL) {
    noABP *aux = malloc(sizeof(noABP));
    aux->alimento = a;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
  } else {
    if (strcmp(a.nome, raiz->alimento.nome) < 0) { // se o novo alimento comecar com uma letra menor... insere a esquerda
      raiz->esq = inserir_versao_2(raiz->esq, a);
    } else if (strcmp(a.nome, raiz->alimento.nome) == 0) { // se os nomes forem iguais... insere a direita
      raiz->esq = inserir_versao_2(raiz->dir, a);
    } else { // se o novo alimento comecar com uma letra maior... insere a direita
      raiz->dir = inserir_versao_2(raiz->dir, a);
    }
    return raiz;
  }
}

// calcula altura da arvore
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

// calcula a quantidade de nos
int quantidade_nos(noABP *raiz) {
  if (raiz == NULL)
    return 0;
  else
    return 1 + quantidade_nos(raiz->esq) + quantidade_nos(raiz->dir);
}

// calcula a quantidade de nos folhas
int quantidade_folhas(noABP *raiz) {
  if (raiz == NULL)
    return 0;
  else if (raiz->esq == NULL && raiz->dir == NULL)
    return 1;
  else
    return quantidade_folhas(raiz->esq) + quantidade_folhas(raiz->dir);
}

// imprime a arvore no terminal
void imprimir_versao_1(noABP *raiz) { // 50 25 30 100
  if (raiz) {
    imprimir_alimento(raiz->alimento);
    imprimir_versao_1(raiz->esq);
    imprimir_versao_1(raiz->dir);
  }
}

// imprime a arvore indicando o nivel
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

// realiza a leitura do arquivo com os alimentos e quantidade de calorias
noABP *leituraArqCalorias(noABP *raiz, char nomeArquivo[]) {
  char *texto[50], nomeAlimento[50], *arq;
  int iteracao = 0, caloria;
  FILE *open_arq;                                      // ponteiro para file

  open_arq = fopen(nomeArquivo, "r");                  // abre o arquivo

  while (EOF != fscanf(open_arq, "%[^\n]\n", texto)) { // enquanto nao chegar no final do arquivo faz a leitura ate a quebra de texto
    arq = strtok(texto, ";");                          // divide a string pelo delimitador ";"
    while (arq != NULL) {                              // quando iteracao = 0 le o nome do alimento... iteracao = 1 le a caloria do alimento
      if (iteracao == 0) {                             // leitura do nome do alimento
        strcpy(nomeAlimento, arq);                     // copia o nome do alimento do arquivo para a variavel nomeAlimento
        iteracao = 1;
      } else {                                        // leitura da caloria
        caloria = atoi(arq);                          // transforma em inteiro a quantidade de caloria do alimento
        raiz = inserir_versao_2(raiz, ler_alimento(nomeAlimento, caloria)); // insere na arvore
        iteracao = 0;
      }
      arq = strtok(NULL, ";"); // necessario para obter os proximos tokens do arquivo
    }
  }
  fclose(open_arq);
  return raiz;
}

// leitura do arquivo com o alimento e a quantidade de gramas ingeridas
void leituraArqNutri(noABP *raiz, char nomeArqIngerido[], char nomeSaida[]) {
  char *texto[50], nomeAlimento[50], *arq;
  short iteracao = 0;
  int porcao;
  FILE *open_arq, *arq_exit;                              // ponteiro para file

  open_arq = fopen(nomeArqIngerido, "r");                 // abre o arquivo
  arq_exit = fopen(nomeSaida, "w");

  informacoesTXT(raiz, arq_exit, 1);                      // chama funcao com parametro 1 para escrever o texto do titulo do arquivo

  while (EOF != fscanf(open_arq, "%[^\n]\n", texto)) {    // enquanto nao chegar no final do arquivo faz a leitura ate a quebra de texto
    arq = strtok(texto, ";");                             // divide a string pelo delimitador ";"
    while (arq != NULL) {                                 // quando iteracao = 0 le o nome do alimento... iteracao = 1 le a caloria do alimento
      if (iteracao == 0) {                                // leitura do nome do alimento
        strcpy(nomeAlimento, arq);                        // copia o nome do alimento do arquivo para a variavel nomeAlimento
        iteracao = 1;
      } else {                                            // leitura da porcao ingerida
        porcao = atoi(arq);                               // transforma em inteiro
        iteracao = 0;
        if (!(procuraABP(raiz, nomeAlimento, porcao, arq_exit))) { // procura na ABP o nome do alimento... se achar retorna true... se nao achar retorna false
          printf("Alimento %s nao encontrado!\n", nomeAlimento);
        }
      }
      arq = strtok(NULL, ";");                             // necessario para obter os proximos tokens do arquivo
    }
  }
  informacoesTXT(raiz, arq_exit, 2);                       // funcao com parametro 2 para escrever as estatisticas no arquivo de saida
  fclose(open_arq);
  fclose(arq_exit);
}

// procura na arvore o alimento encontrado na funcao leituraArqNutri
int procuraABP(noABP *raiz, char *nomeAlimento, int porcao, FILE *arq_exit) {
  while (raiz != NULL) {
    comp++;
    if (strcmp(nomeAlimento, raiz->alimento.nome) == 0) {           // se o nome do alimento for igual ao nome do alimento do nodo
      exitAlimentoCaloria(nomeAlimento, raiz->alimento.caloria, porcao, arq_exit); // escreve no arquivo de saida a estatistica do alimento encontrado
      return 1;                                                     // se achou vai retornar verdadeiro
      comp++;
    } else if (strcmp(nomeAlimento, raiz->alimento.nome) > 0) {     // se a letra do nome do alimento for maior q a letra do alimento do nodo vai para a direita
      raiz = raiz->dir;
      comp++;
    } else {                                                        // se a letra do nome do alimento for menor q a letra do alimento do nodo vai para a esquerda
      raiz = raiz->esq;
    }
  }
  return 0; // se nao achou vai retornar falso
}

// escreve no arquivo de saida as informacoes do alimento encontrado
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

// escreve informacoes de titulo e de estatisticas de comparacoes, altura, nos folhas, etc
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

  clock_t timeExecution = clock();  // inicia a contagem de tempo
  noABP *raiz = NULL;

  if (argc != 4) {  // sao necessarios 4 parametros para o programa funcionar como deveria
    printf("Numero incorreto de parametros!\n");
    printf("Insira: <programa> <arq_entrada_caloria> <arq_entrada_ingerido> <arq_saida>");
  } else {
    raiz = leituraArqCalorias(raiz, nomeArqCaloria);
    printf("%.1f ms - Tempo de armazenar na arvore \n", (double)(clock() - timeExecution));
    leituraArqNutri(raiz, nomeArqIngerido, nomeOutput);

    // Desenha(raiz, 1);
    printf("%.1f ms - Tempo de armazenar, procurar e escrever no arquivo \n", (double)(clock() - timeExecution)); // printa o tempo de execucao do programa
    system("pause");
    system("cls");
  }
  return 0;
}