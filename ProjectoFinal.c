#include<stdio.h>


//Função Principal do programa
void main(int argc, char** argv) { 
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
        UNIDADE* UC;
        lista_UC("teste.txt", uc );
        break;
    }

}