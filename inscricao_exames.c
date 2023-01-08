#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IES 100

typedef struct {
  char ID[10];
  char disciplina[50];
  char codigo[10];
  char ano[5];
  char periodo[5];
} IE;

IE ies[MAX_IES];
int num_ies = 0;

// Função para criar uma nova IE
void create_ie(IE ie) {
  if (num_ies == MAX_IES) {
    printf("Não é possível adicionar mais IEs, pois o limite máximo foi atingido.\n");
    return;
  }
  ies[num_ies] = ie;
  num_ies++;
}

// Função para ler todas as IEs do arquivo "inscricoes_exames.txt"
void read_ies_from_file() {
  char line[150];
  char *token;
  FILE *file = fopen("inscricoes_exames.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo inscricoes_exames.txt\n");
    return;
  }
  while (fgets(line, 150, file) != NULL) {
    IE ie;
    token = strtok(line, "|");
    strcpy(ie.ID, token);
    token = strtok(NULL, "|");
    strcpy(ie.disciplina, token);
    token = strtok(NULL, "|");
    strcpy(ie.codigo, token);
    token = strtok(NULL, "|");
    strcpy(ie.ano, token);
    token = strtok(NULL, "|");
    strcpy(ie.periodo, token);
    create_ie(ie);
  }
  fclose(file);
}

// Função para atualizar uma IE existente
void update_ie(char *ID, IE new_ie) {
  for (int i = 0; i < num_ies; i++) {
    if (strcmp(ies[i].ID, ID) == 0) {
      ies[i] = new_ie;
      return;
    }
  }
  printf("Não foi encontrada nenhuma IE com o ID especificado.\n");
}

// Função para excluir uma IE
void delete_ie(char *ID) {
  for (int i = 0; i < num_ies; i++) {
    if (strcmp(ies[i].ID, ID) == 0) {
      for (int j = i; j < num_ies - 1; j++) {
        ies[j] = ies[j+1];
      }
      num_ies--;
      printf("IE excluída com sucesso.\n");
      return;
    }
  }
  printf("Não foi encontrada nenhuma IE com o ID especificado.\n");
}

// Função para ler uma IE pelo ID
void read_ie(char *ID) {
for (int i = 0; i < num_ies; i++) {
if (strcmp(ies[i].ID, ID) == 0) {
printf("ID: %s\n", ies[i].ID);
printf("Disciplina: %s\n", ies[i].disciplina);
printf("Código: %s\n", ies[i].codigo);
printf("Ano: %s\n", ies[i].ano);
printf("Período: %s\n", ies[i].periodo);
return;
}
}
printf("Não foi encontrada nenhuma IE com o ID especificado.\n");
}

int main() {
read_ies_from_file();

// Código para testar as funções aqui
return 0;
}