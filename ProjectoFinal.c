#include<stdio.h>
#include<string.h>
#define STRING char *

//Função Principal do programa
void main(int argc, char** argv) { 
    STRING *V;
    char escolha;
    printf("*** Inscricao em Exames - MENU ***\n");
    printf("A: Alunos\n");
    printf("B: Unidades Curriculares\n");
    scanf("%c", &escolha);
    switch (escolha)
    {
    case 'A': // ALUNOS 
        
        break;
    
     case 'B':
       menu_uc();
        break;
    }

}