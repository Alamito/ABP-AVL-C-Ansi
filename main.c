#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char *palavra[50];
  char *arq;

  FILE *farq;

  farq = fopen("arquivoTeste.csv", "r");

  while (EOF != fscanf(farq, "%[^\n]\n", palavra)) {
    arq = strtok(palavra, ";");
    while (arq != NULL) {
      printf("'%s' ", arq);
      arq = strtok(NULL, ";");
      system("pause");
    }
    printf("%s\n", "");
  }
  fclose(farq);

  system("pause");
  system("cls");
  return 0;
}