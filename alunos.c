/*
 * Programa e C para manipular Alunos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Criando estrutura aluno.
typedef struct{
    int numero; //numero mecanografico
    char nome[50]; // nome do aluno
    char curso[6]; /*CONT, EA, EC, EE, EI, EM, GE, GI, MKT, TDM, TDMO, TUR,*/
    int ano_matricula; // 1° 2° ou 3° ano
    int regime; //ID dos regimes = 1 (normal), 2 (trabalhador estudante), 3 (atleta), 4 (dirigente associativo), 5 (Erasmus)
}ALUNO;

//CRUD - Create,Read,Update,Delete

FILE *arquivo_aluno, *fp1;
int contador_de_alunos = 0; //contador de alunos

//Create
void criar_aluno(){
    ALUNO aluno;
    printf("Nome do aluno:\n");
    scanf("%s", &aluno.nome); //Registrando nome do aluno
    printf("Numero do aluno:\n");
    scanf("%d", &aluno.numero); //Registrando numerdo do aluno
    printf("Escreva o curso do aluno: [CONT, EA, EC, EE, EI, EM, GE, GI, MKT, TDM, TDMO, TUR]\n");
    scanf("%c", &aluno.curso); //Registrando curso do aluno
    printf("Ano de Matricula (APENAS NUMERO): 1, 2 ou 3?\n");
    scanf("%d", &aluno.ano_matricula); //Registrando matricula do aluno
    printf("Por ultimo qual o regime do aluno?(APENAS NUMEROS)\n1=Normal\n2=Trabalhador Estudante\n3=Atleta\n4=Dirigente Associativo\n5= Erasmus\n");
    scanf("%d", &aluno.regime); //Registrando regime do aluno
    contador_de_alunos++;
    //Retornando sucesso ao usuario
    printf("Aluno %s criado com sucesso!", aluno.nome);
    //escrevendo aluno no arquivo
    fwrite(&aluno.nome, sizeof(char),sizeof(aluno.nome), arquivo_aluno); //escrevendo nome do aluno
    fwrite(&aluno.regime, sizeof(char),sizeof(aluno.regime), arquivo_aluno); //escrevendo regime do aluno
    fwrite(&aluno.ano_matricula, sizeof(int),sizeof(aluno.ano_matricula), arquivo_aluno);//escrevendo ano de matricula do aluno
    fwrite(&aluno.numero, sizeof(int),sizeof(aluno.numero), arquivo_aluno); //escrevendo numero do aluno
    fwrite(&aluno.curso, sizeof(char),sizeof(aluno.curso), arquivo_aluno); //escrevendo curso do aluno
    fclose(arquivo_aluno);//fechando arquivo
}

// Mostrar aluno
void mostrar_aluno(ALUNO aluno) {
  printf("Nome: %s\n", aluno.nome);
  printf("Regime: %d\n", aluno.regime);
  printf("Ano: %d\n", aluno.ano_matricula);
  printf("Numero: %d\n", aluno.numero);
  printf("Curso: %s\n", aluno.curso);
}

//funcao principal do programa aluno.c
void main(int argc, char **argv)
{
    int escolha;
    //Boas vindas ao usuario
    printf("Bem vindo ao sistema de alunos do Polietecnico de Viseu:\n");
    //Criando loop de menu para o usuario
    while (1){
        // apresentando opcoes
        printf("\nSelecione sua opção:\n[1] Criar aluno:\n[2] Mostrar aluno:\n[3] Atualizar aluno:\n[4] Sair\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1://Criar aluno    
            arquivo_aluno = fopen("alunos.txt", "a");
            criar_aluno();
            break;
        case 2:
            break;
        case 3:
            break;     
        case 4: 
            exit(0);
        }
    }
}