#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "functions.h"
#include "feriados.c"
#include "UnidadesCurriculares.c"
#include "exames.c"
#define MAX_EXAMES_FILE 100
#define STRING char *
#define MAX_FERIADOS 20 
#define MAX_UNIDADES_CURRICULARES 100
#define MAX_CURSOS 20

//Função Principal do programa
void main(int argc, char** argv) { 
    STRING *V;
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
    EXAMES *exames_bv = (EXAMES *)malloc(MAX_EXAMES_FILE * sizeof(EXAMES));
	//import_txt_exames(exames_bv, V);


    
    /* Termina o carregamento de variaveis em memoria */
    while(1) {
        printf("\n\n");
        printf("*** MENU PRINCIPAL ***\n");
        printf("A: Alunos\n");
        printf("B: Unidades Curriculares\n");
        printf("C: Exames\n");
        scanf("%c", &escolha);
        switch (escolha)
        {
        case 'A': // ALUNOS 
            
            break;
        
        case 'B': // menu das unidades curriculares
        menu_uc(uc, cursos);
            break;
        case 'C': // menu de exames
        menu_exames(exames_bv);
            break;
        }
    }
    

    // Limpeza da memoria 
    free(uc); 
    free(cursos);
    free(feriado);
    free(exames_bv);
}