//incluindo outros arquivos
#include "alunos.c"
#include "salas.c"
#include "UnidadesCurriculares.c"

//Menu para execução dos outros sistemas
void main(int argc, char const *argv[]){
    while (1){//Loop de menu
        int escolha;//opção do usuario
        printf("========== Bem vindo a gestão de exames ==========\n");
        printf("Selecione sua opção:\n[1] Menu Alunos\n[2] Menu Salas\n[3] Menu Unidades Curriculares\n[0] SAIR\n");
        scanf("%d", &escolha);//registrando escolha do usuario
        switch (escolha){
            case 0:
                exit(0);
            case 1:
                menu_alunos();
                break;
            case 2:
                MenuSalas();
            case 3:
                MenuUC();    
            default:
                break;
    }
    }
}
