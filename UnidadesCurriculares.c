#include<stdio.h>

//definicao da estrutura de unidade curricular 
typedef struct 
{
    int codigo;
    char descricao [60];
    char curso [6]; 
    int ano; 
    int semestre; 
    char docente [30];
} UNIDADECURRICULAR;

typedef struct 
{
    UNIDADECURRICULAR unic;
} UNIDADE;


// faz a listagem das unidades curriculares 
void lista_UC(char* ficheiro_uc,UNIDADE* uc ){
    
}
//cria uma nova unidade curricular
void criar_UC(){
    int codigo; 
    char descricao [60];
    do
    {
       printf("Insercao de Unidade Curricular\n");
    scanf("%d", &codigo);
    } while (valida_UC_existe() == 0);
    
    
    printf("introduza o codigo da unidade curricular\n");
}

//função que escreve as unidades curriculares no ficheiro
void escreve_UCs_ficheiro(char* ficheiro_uc, UNIDADE* uc){
    
}

int valida_UC_existe(int codigo, UNIDADE* uc) {
    // falta iterar sobre a estrutura de dados para comparar todos os valores 

    UNIDADECURRICULAR* unidadecur; 
    if (unidadecur->codigo == codigo) {
        return 0;
    }
    else {
        return 1; 
    }
}