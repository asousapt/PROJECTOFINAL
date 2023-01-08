#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IES 100

typedef struct {
  char ID[5];
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
void update_ie(char *ID, IE nova_IE) {
  for (int i = 0; i < num_ies; i++) {
    if (strcmp(ies[i].ID, ID) == 0) {
      ies[i] = nova_IE;
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

//funcao principal do programa Inscrição_exames.c
void menu_IE(){
    int escolha;
    ler_alunos();//carrega ficheiro inscricao_exames.txt
    //Boas vindas ao usuario
    printf("\n===== Bem vindo ao sistema de Inscrição de Exames do Polietecnico de Viseu: =====\n");
    //Criando loop de menu para o usuario
    while (1){
        // apresentando opcoes
        printf("\nSelecione sua opção:\n[1] Criar Exame:\n[2] Buscar Exame:\n[3] Atualizar Exames do ficheiro:\n[4] Deletar Exames:\n[5] Sair\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1://Criar nova IE
            IE nova_IE;
            printf("Insira os dados da nova inscrição em exame:\n");
            printf("ID: ");
            scanf("%s", nova_IE.ID);
            printf("Disciplina: ");
            scanf("%s", nova_IE.disciplina);
            printf("Código: ");
            scanf("%s", nova_IE.codigo);
            printf("Ano: ");
            scanf("%s", nova_IE.ano);
            printf("Período: ");
            scanf("%s", nova_IE.periodo);
            create_ie(nova_IE);
            break;
        case 2://Buscar IE existente
            char ID[5];
            printf("Insira o ID da inscrição em exame a ser lida: ");
            scanf("%s", ID);
            read_ie(ID);
            break;
        case 3:
            IE Temp_IE;
            printf("Insira o ID da inscrição em exame a ser atualizada: ");
            scanf("%s", ID);
            printf("Insira os novos dados da inscrição em exame:\n");
            printf("ID: ");
            scanf("%s", Temp_IE.ID);
            printf("Disciplina: ");
            scanf("%s", Temp_IE.disciplina);
            printf("Código: ");
            scanf("%s", Temp_IE.codigo);
            printf("Ano: ");
            scanf("%s", Temp_IE.ano);
            printf("Período: ");
            scanf("%s", Temp_IE.periodo);
            update_ie(ID, Temp_IE);
            break;    
        case 4:
            printf("Insira o ID da inscrição em exame a ser excluída: ");
            scanf("%s", ID);
            delete_ie(ID);
            break;
        case 5: 
            exit(0);
        }
    }
}
