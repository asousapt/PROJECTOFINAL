/*
 * Programa e C para manipular a estrutura UNIDADECURRICULAR
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR 300
#define STRING char *
#define N_CAMPOS_MAX 100
#define MAX_LINHA_FICHEIRO 300

//definicao da estrutura de unidade curricular
typedef struct {
char* codigo;//ID da UC
char* nome;//Nome da UC
char* docente;//Nome do docente Responsavel
char* ano;//Ano da materia
char* semestre;//Semestre da materia
} UNIDADECURRICULAR;

//CRUD

//CREATE
UNIDADECURRICULAR* criarUC(char* codigo, char* nome, char* docente, char* ano, char* semestre) {
UNIDADECURRICULAR* uc = (UNIDADECURRICULAR*) malloc(sizeof(UNIDADECURRICULAR));
uc->codigo = codigo;
uc->nome = nome;
uc->docente = docente;
uc->ano = ano;
uc->semestre = semestre;
return uc;
}

//READ
void readUC(UNIDADECURRICULAR* uc) {
printf("Código da UC: %s\n", uc->codigo);
printf("Nome da UC: %s\n", uc->nome);
printf("Docente responsável: %s\n", uc->docente);
printf("Ano: %s\n", uc->ano);
printf("Semestre: %s\n", uc->semestre);
}

//UPDATE
void updateUC(UNIDADECURRICULAR* uc) {
char* codigo = (char*) malloc(sizeof(char) * MAX_CAR);
char* nome = (char*) malloc(sizeof(char) * MAX_CAR);
char* docente = (char*) malloc(sizeof(char) * MAX_CAR);
char* ano = (char*) malloc(sizeof(char) * MAX_CAR);
char* semestre = (char*) malloc(sizeof(char) * MAX_CAR);
printf("Insira o novo código da UC (atual: %s): ", uc->codigo);
scanf("%s", codigo);
printf("Insira o novo nome da UC (atual: %s): ", uc->nome);
scanf("%s", nome);
printf("Insira o novo nome do docente responsável (atual: %s): ", uc->docente);
scanf("%s", docente);
printf("Insira o novo ano da UC (atual: %s): ", uc->ano);
scanf("%s", ano);
printf("Insira o novo semestre da UC (atual: %s): ", uc->semestre);
scanf("%s", semestre);
free(uc->codigo);
free(uc->nome);
free(uc->docente);
free(uc->ano);
free(uc->semestre);
uc->codigo = codigo;
uc->nome = nome;
uc->docente = docente;
uc->ano = ano;
uc->semestre = semestre;
}

//DELETE
void deleteUC(UNIDADECURRICULAR* uc) {
free(uc->codigo);
free(uc->nome);
free(uc->docente);
free(uc->ano);
free(uc->semestre);
free(uc);
}

//Ler UC do arquivo
void ImportUnidadesCurriculares(){
    FILE* arq = fopen("UnidadesCurriculares.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de unidades curriculares.\n");
    }
    char linha[MAX_LINHA_FICHEIRO];
    fgets(linha, MAX_LINHA_FICHEIRO, arq); // ignorar a primeira linha (cabeçalho)
    while (fgets(linha, MAX_LINHA_FICHEIRO, arq) != NULL) {
        char* codigo = strtok(linha, "|");
        char* nome = strtok(NULL, "|");
        char* docente = strtok(NULL, "|");
        char* ano = strtok(NULL, "|");
        char* semestre = strtok(NULL, "|");
        UNIDADECURRICULAR* uc = criarUC(codigo, nome, docente, ano, semestre);
        readUC(uc);
    }
fclose(arq);
}

void MenuUC(){
    while (1){//Loop de menu
        int escolha;//opção do usuario
        printf("========== Bem vindo a Unidades Curriculares ==========\n");
        printf("Selecione sua opção:\n[1] Criar Unidade Curricular\n[2] Exibir Unidades Curriculares\n[3] Atualizar Unidades Curriculares\n[4] Deletar Unidades Curriculares\n[0] SAIR\n");
        scanf("%d", &escolha);//registrando escolha do usuario
        switch (escolha){
            case 0:
                exit(0);
            case 1://Criar UC
                char* codigo = (char*) malloc(sizeof(char) * MAX_CAR);
                char* nome = (char*) malloc(sizeof(char) * MAX_CAR);
                char* docente = (char*) malloc(sizeof(char) * MAX_CAR);
                char* ano = (char*) malloc(sizeof(char) * MAX_CAR);
                char* semestre = (char*) malloc(sizeof(char) * MAX_CAR);
                printf("Insira o código da UC:\n");
                scanf("%s", codigo);
                printf("Insira o código da UC:\n");
                scanf("%s", nome);
                printf("Insira o nome do docente responsável:\n");
                scanf("%s", docente);
                printf("Insira o ano da UC:\n");
                scanf("%s", ano);
                printf("Insira o semestre da UC:\n");
                scanf("%s", semestre);
                criarUC(codigo, nome, docente, ano, semestre);
                break;
            case 2://Exibir UC
                ImportUnidadesCurriculares();    
            default:
                break;
    }
    }
}