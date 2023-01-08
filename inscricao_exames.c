#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_ALUNOS 3000
#define MAX_INSCRICOES 3000

//definicao da estrutura de exames
/*
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
*/
/*
//definicao da estrutura salas
typedef struct{
	int id;
	char* codigo;
	char* nome_sala;
	int lotacao;
	int ocupado;
}SALAS;
*/
/*
// Vincula um vetor de alunos a um exame
void vincular_alunos_exame(char* alunos_ID[], int num_alunos, char* exame_ID, EXAMES* exames, int num_exames, SALAS* salas, int num_salas) {
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
*/

void import_txt_inscricoes_exames(INSCRICOESEXAMES* inscricoes_exames, STRING* V) { //, STRING* V

	int i = 0, k, n_campos_lidos; 

	//Abre o ficheiro
	FILE* f = fopen("inscricoes_exames.txt", "r");
	if (f == NULL) {
		printf("Erro ao abrir ficheiro inscricoes_exames.txt\n");
		exit(1);
	}
	
	do {
		V = Read_Split_Line_File(f, &n_campos_lidos);
		if (V != NULL) {// caso consigamos ler alguma informacao			

			inscricoes_exames[i].codigo = atoi(V[0]);

			inscricoes_exames[i].unidade_curricular = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
			strcpy(inscricoes_exames[i].unidade_curricular, V[1]);
			
			inscricoes_exames[i].numero_aluno = atoi(V[2]);
			
			inscricoes_exames[i].ano_matricula = atoi(V[3]);

			inscricoes_exames[i].epoca = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
			strcpy(inscricoes_exames[i].epoca, V[4]);

      inscricoes_exames[i].regime = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
			strcpy(inscricoes_exames[i].regime, V[4]);

			inscricoes_exames[i].ocupado = 1;

			for (k = 0; k < n_campos_lidos; k++)
				free(V[k]);
			free(V);
			i++;
		}
	} while (!feof(f));

	fclose(f);
}

//lista as inscricoes efetuadas
void listar_inscricoes(INSCRICOESEXAMES* inscricoes_exames){
  int i;
	printf("%s %s %s %s %s\n", "ID", "Unidade Curricular","Numero Aluno", "Ano Matricula", "Epoca", "Regime\n");
	for (i = 0; i < MAX_INSCRICOES; i++)
	{
		if (inscricoes_exames[i].ocupado == 1) {
			printf("%d %s %d %d %s %s\n",inscricoes_exames[i].codigo, inscricoes_exames[i].unidade_curricular, inscricoes_exames[i].numero_aluno, 
      inscricoes_exames[i].ano_matricula, inscricoes_exames[i].epoca, inscricoes_exames[i].regime);
		}
	}
}

int valida_aluno_inscrito(INSCRICOESEXAMES* inscricoes_exames, int opcaoAluno) {
	int i = 0;
	for (i = 0; i < MAX_INSCRICOES; i++)
	{
		if (inscricoes_exames[i].ocupado == 1) {

			if (inscricoes_exames[i].numero_aluno == opcaoAluno) {

				return 1;
			}
		}
	}
	return 0;
}

//lista as inscricoes por aluno
void lista_inscricoes_aluno(INSCRICOESEXAMES* inscricoes_exames){
  int opcaoAluno = 0;
  int n[MAX_INSCRICOES];
  
  printf("Insira o numero do aluno: ");
  scanf("%d", opcaoAluno);

  if(valida_aluno_inscrito(inscricoes_exames, opcaoAluno) == 1){
    printf("Teste");
  }
}

int valida_uc_escolhida(EXAMES* exames, int opcao_uc) {
	int i = 0; 
	
	for ( i = 0; i < MAX_EXAMES_FILE; i++)
	{
		if (exames[i].ocupado == 1 && i == opcao_uc) {
			return 1;
		}
	}
	
	return 0;
}

//valida 3 ano e regimes
int valida_epoca_especial(int ano_matricula, REGIMES* opcaoRegime){
    int i;
    if (ano_matricula == 3 && opcaoRegime[i].regime != "Normal" || opcaoRegime[i].regime != "Erasmus");

    return 1;
}

void inscrever_aluno(INSCRICOESEXAMES* inscricoes_exames, EXAMES* exames, ALUNOS* alunos, REGIMES* regimes){
  int opcao_uc;
  int opcaoAluno = 0;
  int ano_matricula = 0;
  char* epoca;
  int opcaoRegime;
  int ocupado;

  do{
    printf("Qual o numero do aluno");
    scanf("%d", &opcaoAluno);
  } while (valida_aluno_existe(alunos, opcaoAluno) == 1);

  do {
    printf("Qual o ano de matricula do aluno");
    scanf("%d", ano_matricula);
  } while(valida_ano_matricula(ano_matricula)==1);

  do{
    printf("Qual o estatuto do aluno");
    scanf("%d", &opcaoRegime);
  }while (valida_regime_escolhido(regimes, opcaoRegime)==1);
   

  if (valida_epoca_especial(ano_matricula, opcaoRegime)){
    listar_exames(exames, 0);
    printf("Qual a Unidade Curricular para a qual pretende inscrever o aluno");
    scanf("%d", &opcao_uc);
  }

  do{
    listar_exames(exames, 0);
    printf("Qual a Unidade Curricular para a qual pretende inscrever o aluno");
    scanf("%d", &opcao_uc);
  }while (valida_uc_escolhida(exames, opcao_uc) == 1);

}

void menu_inscricao_exames(INSCRICOESEXAMES* inscricoes_exames, EXAMES* exames, ALUNOS* alunos, REGIMES* regimes){
  STRING* V;
	int opcao = -1;

	while(opcao != 0){
		printf("\n");
		printf("Bem-vindo ao menu de inscrição de exames!\n");
		printf("Escolha uma das opções:\n");
		printf("1 - Inscrever aluno\n");
		printf("2 - Consultar Inscrições\n");
		printf("3 - Lista por aluno \n");
		printf("4 - Apagar \n");
		printf("0 - Sair\n");
		printf("Introduza a Opcao: ");
		scanf("%d", &opcao);
		
		switch (opcao) {
			case 1: //inscreve um novo aluno
				inscrever_aluno(inscricoes_exames, exames, alunos, regimes);
				break;
			case 2: //lista as inscricoes
				listar_inscricoes(inscricoes_exames);
				break;
			case 3: // 
			 	lista_inscricoes_aluno(inscricoes_exames);
				break; 
			case 4: //
				
				break;
		}
	}
}
