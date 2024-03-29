#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "feriados.c"
#include "UnidadesCurriculares.c"
#include "exames.c"
#include "salas.c"
#include "alunos.c"
#include "epocas.c"
#include "exames_salas.c"
#include"inscricao_exames.c"


#define MAX_EXAMES_FILE 100
#define STRING char *
#define MAX_FERIADOS 20 
#define MAX_UNIDADES_CURRICULARES 100
#define MAX_CURSOS 20
#define MAX_ALUNOS 3000
#define MAX_SALAS 100
#define MAX_REGIMES 5
#define MAX_EPOCAS 10
#define MAX_INSCRICOES 3000
#define MAX_EXAMES_SALAS 100

//Função Principal do programa
void main(int argc, char** argv) {
    STRING* V;
    char escolha;
    /* Carregamento em memoria de todos os ficheiros txt do projecto*/

     //carrega os dados das epocas
    EPOCAS* epocas = (EPOCAS*)malloc(MAX_SALAS * sizeof(EPOCAS));
    import_txt_epocas(epocas, V);

    //carrega o ficheiro dos feriados em memoria
    FERIADOS* feriado = (FERIADOS*)malloc(MAX_FERIADOS * sizeof(FERIADOS));
    import_feriados(feriado, V);

    //carrega o ficheiro das UC em memoria
    UNIDADECURRICULAR* uc = (UNIDADECURRICULAR*)malloc(MAX_UNIDADES_CURRICULARES * sizeof(UNIDADECURRICULAR));
    import_txt_uc(uc, V);

    //carrega o ficheiro dos cursos em memoria
    CURSO* cursos = (CURSO*)malloc(MAX_CURSOS * sizeof(CURSO));
    import_txt_cursos(cursos, V);

    //carrega os dados dos exames em memoria
    EXAMES* exames = (EXAMES*)malloc(MAX_EXAMES_FILE * sizeof(EXAMES));
    import_txt_exames(exames, V, uc);
    
    //carrega os dados das inscricoes dos exames em memoria
    INSCRICOESEXAMES* inscricoes_exames = (INSCRICOESEXAMES*)malloc(MAX_INSCRICOES * sizeof(INSCRICOESEXAMES));
    import_txt_inscricoes_exames(inscricoes_exames, V);

    //carrega os dados dos regimes em memoria
    REGIMES* regimes = (REGIMES*)malloc(MAX_REGIMES * sizeof(REGIMES));
    import_txt_regimes(regimes, V);

    //carrega os dados dos alunos em memoria
    ALUNOS* alunos = (ALUNOS*)malloc(MAX_ALUNOS * sizeof(ALUNOS));
    import_txt_alunos(alunos, V);

    //carrega os dados das salas
    SALAS* salas = (SALAS*)malloc(MAX_SALAS * sizeof(SALAS));
    import_txt_salas(salas, V);

    EXAMESSALAS* exames_salas = (EXAMESSALAS*)malloc(MAX_EXAMES_SALAS * sizeof(EXAMESSALAS));
    import_txt_exames_salas(exames_salas, V);

    /* Termina o carregamento de variaveis em memoria */
    while (1) {
        printf("\n\n");
        printf("*** MENU PRINCIPAL ***\n");
        printf("A: Alunos\n");
        printf("B: Unidades Curriculares\n");
        printf("C: Exames\n");
        printf("D: Salas\n");
        printf("F: Exames e inscricoes\n");
        printf("S - Guardar dados e sair\n");
        printf("Opcao: ");
        scanf("%c", &escolha);
        system("cls");
        switch (escolha)
        {
        case 'A': // ALUNOS 
            menu_alunos(alunos, regimes, cursos, inscricoes_exames);
            break;

        case 'B': // menu das unidades curriculares
            menu_uc(uc, cursos, exames);
            break;

        case 'C': // menu de exames
            menu_exames(exames, inscricoes_exames, alunos, salas, epocas, uc, cursos, feriado,exames_salas);
            break;
        case 'D': // menu salas
            menu_salas(salas, exames);
            break;
        case 'F': // menu inscricoes
             menu_inscricao_exames( inscricoes_exames, exames, alunos, regimes);
            break;
        case 'S': //grava tudo nos ficheiros 
            export_Salas(salas);
            export_exames(exames);
            export_UC(uc);
            export_feriados(feriado);
            export_alunos(alunos);
            export_exames_salas( exames_salas);
            break;
        }
    }


    // Limpeza da memoria 
    free(uc);
    free(cursos);
    free(feriado);
    free(exames);
    free(alunos);
    free(salas);
    free(epocas);
    free(exames_salas);
}