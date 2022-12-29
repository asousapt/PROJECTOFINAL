/*
 * Programa e C para manipular Alunos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Criando estrutura aluno.
typedef struct{
    char numero [10]; //numero mecanografico
    char nome[50]; // nome do aluno
    char curso[10]; /*CONT, EA, EC, EE, EI, EM, GE, GI, MKT, TDM, TDMO, TUR,*/
    char ano_matricula[5]; // 1° 2° ou 3° ano
    char regime[25]; //ID dos regimes = 1 (normal), 2 (trabalhador estudante), 3 (atleta), 4 (dirigente associativo), 5 (Erasmus)
}ALUNO;

//CRUD - Create,Read,Update,Delete

FILE *arquivo_aluno, *fp1;
int contador_de_alunos = 0; //contador de alunos

//Create
void criar_aluno(){
    ALUNO aluno;
    fflush(stdin);
    printf("Nome do aluno:\n");
    gets(aluno.nome); //Registrando nome do aluno
    printf("Numero do aluno:\n");
    scanf("%s", &aluno.numero); //Registrando numerdo do aluno
    printf("Escreva o curso do aluno: [CONT, EA, EC, EE, EI, EM, GE, GI, MKT, TDM, TDMO, TUR]\n");
    scanf("%s", &aluno.curso); //Registrando curso do aluno
    printf("Ano de Matricula (APENAS NUMERO): 1, 2 ou 3?\n");
    scanf("%s", &aluno.ano_matricula); //Registrando matricula do aluno
    //Registrando regime do aluno
    //Apresentando opcoes
    int escolha;
    printf("Qual o regime do aluno?(APENAS NUMEROS)\n1=Normal\n2=Trabalhador Estudante\n3=Atleta\n4=Dirigente Associativo\n5=Erasmus\n");
    scanf("%d", &escolha);
    switch (escolha){
        case 1:    
            strcpy(aluno.regime, "Normal");
            break;
        case 2:
            strcpy(aluno.regime, "Trabalhador-Estudante");
            break;
        case 3:
            strcpy(aluno.regime, "Atleta");
            break;    
        case 4: 
            strcpy(aluno.regime, "Dirigente-Associativo");
            break;
        case 5:
            strcpy(aluno.regime, "Erasmus");
            break;    
        }
        
    contador_de_alunos++;
    //Retornando sucesso ao usuario
    printf("Aluno %s criado com sucesso!", aluno.nome);
    //escrevendo aluno no arquivo
    fprintf(arquivo_aluno, "%s\t", aluno.nome); //escrevendo nome do aluno
    fprintf(arquivo_aluno, "%s\t", aluno.regime); //escrevendo regime do aluno
    fprintf(arquivo_aluno, "%s\t", aluno.ano_matricula);//escrevendo ano de matricula do aluno
    fprintf(arquivo_aluno, "%s\t", aluno.numero); //escrevendo numero do aluno
    fprintf(arquivo_aluno, "%s\t\n", aluno.curso); //escrevendo curso do aluno
    fclose(arquivo_aluno);//fechando arquivo
}

// Buscar Aluno no ficheiro.
void buscar_aluno(char* numero_aluno) {
    char word[100];
    char line[100];

    // Abre o arquivo para leitura
    arquivo_aluno = fopen("alunos.txt", "r");
    if (arquivo_aluno == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }
    // Enquanto não chegar ao fim do arquivo, lê cada linha do arquivo
    while (fgets(line, sizeof(line), arquivo_aluno) != NULL)
    {
        // Se a palavra for encontrada, imprime a linha
        if (strstr(line, numero_aluno) != NULL)
        {
            printf("%s", line);
        }
    }
    // Fecha o arquivo
    fclose(arquivo_aluno);
}

void ler_alunos(){
  // Abre o arquivo para leitura
  FILE *arquivo_aluno = fopen("alunos.txt", "r");
  if (arquivo_aluno == NULL){
    printf("Erro ao abrir o arquivo\n");
    return;
  }
  // Lê e descarta a primeira linha do arquivo
  char linha[100]; // variável para armazenar a linha lida do arquivo
  fgets(linha, sizeof(linha), arquivo_aluno);
  while (fgets(linha, sizeof(linha), arquivo_aluno) != NULL){
    // Extrai os dados da linha lida
    ALUNO aluno;
    sscanf(linha, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]", aluno.nome, aluno.regime, aluno.ano_matricula, aluno.numero, aluno.curso);
  }
  // Fecha o arquivo
  fclose(arquivo_aluno);
}

//funcao principal do programa aluno.c
void menu_alunos(){
    int escolha;
    ler_alunos();//carrega ficheiro alunos.txt
    //Boas vindas ao usuario
    printf("\n===== Bem vindo ao sistema de alunos do Polietecnico de Viseu: =====\n");
    //Criando loop de menu para o usuario
    while (1){
        // apresentando opcoes
        printf("\nSelecione sua opção:\n[1] Criar aluno:\n[2] Buscar Aluno:\n[3] Atualizar alunos do ficheiro:\n[4] Sair\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1://Criar aluno    
            arquivo_aluno = fopen("alunos.txt", "a");//abre o arquivo com "A", cara criar caso necessario e escrever no final caso ja exista.
            criar_aluno();
            break;
        case 2://Buscar Aluno
            char numero[6];
            printf("Digite o numero do Aluno:\n");
            scanf("%s", &numero);
            buscar_aluno(numero);
            break;
        case 3://Ler alunos do ficheiro
            ler_alunos();
            break;     
        case 4: 
            exit(0);
        }
    }
}

