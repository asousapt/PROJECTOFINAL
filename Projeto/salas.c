/*
 * Programa e C para manipular a estrutura SALA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR 300
#define STRING char *
#define N_CAMPOS_MAX 100
#define MAX_LINHA_FICHEIRO 300

typedef struct {
   char* ID;
   char* nome;
   char* lotacao;
}SALA;

//CRUD

//CREATE
void criarSala(char* ID, char* nome, char* lotacao){
// Alocação dinâmica da estrutura
SALA* nova_sala = (SALA*) malloc(sizeof(SALA));
// Atribuição dos valores aos campos da estrutura
nova_sala->ID = ID;
nova_sala->nome = nome;
nova_sala->lotacao = lotacao;
// Abrir o arquivo em modo de escrita
FILE* arquivo_salas = fopen("salas.txt", "a");
// Escrever os dados da nova sala no arquivo, separando cada campo com um tab
fprintf(arquivo_salas, "%s\t%s\t%s\n", nova_sala->ID, nova_sala->nome, nova_sala->lotacao);
// Fechar o arquivo
fclose(arquivo_salas);
}

//READ
void ImportSalas() {
  // Abrir o arquivo em modo de leitura
  FILE* arquivo_salas = fopen("salas.txt", "r");

  // Verificar se o arquivo foi aberto com sucesso
  if (arquivo_salas == NULL) {
    printf("Erro ao abrir o arquivo salas.txt\n");
    return;
  }

  // Lê a primeira linha do arquivo (cabeçalho) e descarta
  char linha[MAX_LINHA_FICHEIRO];
  fgets(linha, MAX_LINHA_FICHEIRO, arquivo_salas);

  // Lê cada linha do arquivo até chegar ao fim
  while (!feof(arquivo_salas)) {
    // Lê uma linha do arquivo e separa os campos por tabs
    fgets(linha, MAX_LINHA_FICHEIRO, arquivo_salas);
    char* ID = strtok(linha, "\t");
    char* nome = strtok(NULL, "\t");
    char* lotacao = strtok(NULL, "\t");

    // Verifica se a linha lida não está vazia (é possível que a última linha do arquivo esteja vazia)
    if (ID == NULL || nome == NULL || lotacao == NULL) {
      continue;
    }

    // Imprime os campos da sala lida
    printf("ID: %s\n", ID);
    printf("Nome: %s\n", nome);
    printf("Lotação: %s\n", lotacao);
  }

  // Fecha o arquivo
  fclose(arquivo_salas);
}

void MenuSalas(){
    while (1){//Loop de menu
        int escolha;//opção do usuario
        printf("========== Bem vindo a controle de Salas ==========\n");
        printf("Selecione sua opção:\n[1] Criar nova Sala\n[2] Exibir Salas existentes\n[3] Atualizar Sala\n[4] Deletar Sala\n[0] SAIR\n");
        scanf("%d", &escolha);//registrando escolha do usuario
        switch (escolha){
            case 0:
                exit(0);
            case 1://Criar UC
                char* ID = (char*) malloc(sizeof(char) * MAX_CAR);
                char* nome = (char*) malloc(sizeof(char) * MAX_CAR);
                char* lotacao = (char*) malloc(sizeof(char) * MAX_CAR);
                printf("Insira o ID da sala:\n");
                scanf("%s", ID);
                printf("Insira o nome da sala:\n");
                scanf("%s", nome);
                printf("Insira a lotação da nova sala:\n");
                scanf("%s", lotacao);
                criarSala(ID, nome, lotacao);
                break;
            case 2://Exibir UC
                ImportSalas();    
            default:
                break;
        }
    }
}