#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "functions.h"
#include "feriados.c"
#include "UnidadesCurriculares.c"
#include "Exames.c"
#include "alunos.c"
#include "salas.c"

#define MAX_EXAMES_FILE 100
#define STRING char *
#define MAX_FERIADOS 20 
#define MAX_UNIDADES_CURRICULARES 100
#define MAX_CURSOS 20
#define MAX_ALUNOS 3000
#define MAX_SALAS 100
#define MAX_REGIMES 5

//Função Principal do programa
void main(int argc, char** argv) {
    STRING* V;
    char escolha;
    /* Carregamento em memoria de todos os ficheiros txt do projecto*/
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
    import_txt_exames(exames, V);
    //import_txt_exames(exames_bv, V);
    
    //carrega os dados dos regimes em memoria
    REGIMES* regimes = (REGIMES*)malloc(MAX_REGIMES * sizeof(REGIMES));
    import_txt_regimes(regimes, V);

    //carrega os dados dos alunos em memoria
    ALUNOS* alunos = (ALUNOS*)malloc(MAX_ALUNOS * sizeof(ALUNOS));
    import_txt_alunos(alunos, V);

    //carrega os dados das salas
    SALAS* salas = (SALAS*)malloc(MAX_SALAS * sizeof(SALAS));
    import_txt_salas(salas, V);

    

    /* Termina o carregamento de variaveis em memoria */
    while (1) {
        printf("\n\n");
        printf("*** MENU PRINCIPAL ***\n");
        printf("A: Alunos\n");
        printf("B: Unidades Curriculares\n");
        printf("C: Exames\n");
        printf("D: Salas\n");
        printf("Opcao: ");
        scanf("%c", &escolha);
        system("cls");
        switch (escolha)
        {
        case 'A': // ALUNOS 
            menu_alunos(alunos, regimes, cursos);
            break;

        case 'B': // menu das unidades curriculares
            menu_uc(uc, cursos);
            break;

        case 'C': // menu de exames
            menu_exames(exames);
            break;
        case 'D': // menu salas
            menu_salas(salas);
            break;
        default:
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
}