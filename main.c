#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *texto[50];
  char *arq;
  int iteracao = 0;
  int caloria;

  FILE *open_arq;

  open_arq = fopen("arquivoTeste.csv", "r");

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
  fclose(open_arq);

  system("pause");
  system("cls");
  return 0;
}