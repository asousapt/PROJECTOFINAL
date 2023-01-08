#include <functions.h>
#define MAX_ALUNOS 150

//definicao da estrutura de exames
typedef struct
{
	int codigo;
	char* unidade_curricular;
	int ano; 
	char* curso;
	char* epoca;
	char* data;
	char* hora;
	int duracao;
	char* sala;
	char alunos_inscritos[150][6];
	int realizado;
	int ocupado;
	int num_alunos;
} EXAMES;

//definicao da estrutura salas
typedef struct{
	int id;
	char* codigo;
	char* nome_sala;
	int lotacao;
	int ocupado;
}SALAS;

// Vincula um vetor de alunos a um exame
void vincular_alunos_exame(char *alunos_ID[], int num_alunos, char *exame_ID, EXAMES *exames, int num_exames, SALAS *salas, int num_salas) {
  // Procure o exame pelo ID
  for (int i = 0; i < num_exames; i++) {
    if (strcmp(exames[i].codigo, exame_ID) == 0) {
      // Verifique se a sala do exame possui lotação suficiente
      int lotacao_disponivel = 0;
      for (int j = 0; j < num_salas; j++) {
        if (strcmp(exames[i].sala->codigo, salas[j].codigo) == 0) {
        lotacao_disponivel = salas[j].lotacao - salas[j].ocupado;
        break;
        }
      }
      if (exames[i].num_alunos + num_alunos > lotacao_disponivel) {
        printf("Não é possível vincular mais alunos ao exame, pois a sala não possui lotação suficiente.\n");
        return;
      }
      // Adicione os alunos ao vetor de alunos do exame
      for (int j = 0; j < num_alunos; j++) {
        strcpy(exames[i].alunos_inscritos[exames[i].num_alunos], alunos_ID[j]);
        exames[i].num_alunos++;
        exames[i].sala->ocupado++;
      }
      printf("Alunos vinculados ao exame com sucesso.\n");
      return;
    }
  }
  printf("Não foi encontrado nenhum exame com o ID especificado.\n");
}

void desvincular_alunos_exame(char *alunos_ID[], int num_alunos, char *exame_ID, EXAMES *exames, int num_exames) {
  for (int i = 0; i < num_exames; i++) {
    if (strcmp(exames[i].codigo, exame_ID) == 0) {
      for (int j = 0; j < num_alunos; j++) {
        for (int k = 0; k < exames[i].num_alunos; k++) {
          if (strcmp(exames[i].alunos_inscritos[k], alunos_ID[j]) == 0) {
            // Remove o aluno do vetor de alunos do exame
            for (int l = k; l < exames[i].num_alunos - 1; l++) {
              exames[i].alunos_inscritos[l] = exames[i].alunos_inscritos[l+1];
            }
          exames[i].num_alunos--;
          }
        }
      }
    return;
    }
  }
  printf("Não foi encontrado nenhum exame com o ID especificado.\n");
}