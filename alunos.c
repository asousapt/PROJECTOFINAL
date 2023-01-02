/*
 * Programa e C para manipular Alunos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_CAR 300 
#define STRING char *
#define N_CAMPOS_MAX 100 
#define MAX_ALUNOS 3000
#define MAX_REGIMES 10

 //CRUD - Create,Read,Update,Delete

//int contador_de_alunos = 0; //contador de alunos

void import_txt_alunos(ALUNOS* alunos, STRING* V) {
    int i = 0, k, n_campos_lidos;

    FILE* f = fopen("alunos.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro alunos.txt");
    }
    do {
        V = Read_Split_Line_File(f, &n_campos_lidos);
        if (V != NULL) {

            alunos[i].nome = (char*)malloc(sizeof(char) * (strlen(V[0]) + 1));
            strcpy(alunos[i].nome, V[0]);

            alunos[i].regime = (char*)malloc(sizeof(char) * (strlen(V[1]) + 1));
            strcpy(alunos[i].regime, V[1]);

            alunos[i].ano_matricula = atoi(V[2]);

            alunos[i].numero = atoi(V[3]);

            alunos[i].curso = (char*)malloc(sizeof(char) * (strlen(V[4]) + 1));
            strcpy(alunos[i].nome, V[4]);

            //alunos[i].ocupado = 1;
        }
    } while (!feof(f));

    fclose(f);

}

void import_txt_regimes(REGIMES* regimes, STRING* V) {
    int i = 0, k, n_campos_lidos;

    //Abre o ficheiro
    FILE* f = fopen("regimes.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir ficheiro regimes.txt\n");
        exit(1);
    }

    do {
        V = Read_Split_Line_File(f, &n_campos_lidos);
        if (V != NULL) {// caso consigamos ler alguma informacao			

            regimes[i].codigo = atoi(V[0]);

            regimes[i].regime = (char*)malloc(sizeof(char) * (strlen(V[1]) + 5));
            strcpy(regimes[i].regime, V[1]);

            regimes[i].ocupado = 1;

            for (k = 0; k < n_campos_lidos; k++)
                free(V[k]);
            free(V);
            i++;
        }
    } while (!feof(f));

    fclose(f);

}

void listar_alunos(ALUNOS* alunos) {
    int i;
    printf("Nome|Regime|Ano Matricula|Numero|Curso\n");
    for (i = 0; i < MAX_UNIDADES_CURRICULARES; i++)
    {
        if (alunos[i].ocupado == 1) {
            printf("%s %s %d %d %s\n", alunos[i].nome, alunos[i].regime, alunos[i].ano_matricula, alunos[i].numero, alunos[i].curso);
      }
   }
}

void listar_regimes(REGIMES* regimes) {
    int i = 0;

    printf("%s %s\n", "Codigo", "Regime");
    for (i = 0; i < MAX_REGIMES; i++)
    {
        if (regimes[i].ocupado == 1) {
            printf("%-3d %s\n", i, regimes[i].regime);
        }
    }
}

int valida_regime_escolhido(REGIMES* regimes, int regime) {
    int i = 0;

    for (i = 0; i < MAX_REGIMES; i++)
    {
        if (regimes[i].ocupado == 1 && i == regime) {
            return 1;
        }
    }

    return 0;
}

int valida_numero_aluno(ALUNOS* alunos, int numero_aluno) {
    int i = 0;

    for (i = 0; i < MAX_ALUNOS; i++)
    {
        if (alunos[i].numero == 1 && i == numero_aluno) {
            return 0;
        }
    }

    return 1;
}

int valida_ano(int ano_matricula) {
    if (ano_matricula < 1 || ano_matricula > 3) {
        return 0;
    }
    return 1;
}

int get_posicao_vect_alunos(ALUNOS* alunos) {
    int i;
    for (i = 0; i < MAX_ALUNOS; i++)
    {
        if ((alunos[i].ocupado == 0) && (i < MAX_ALUNOS)) {
            return i;
        }
    }
    return -1;
}

int insere_aluno(ALUNOS* alunos, char* nome, char* regime, int ano_matricula, int numero, char* curso) {
    int posicaoVazia = 0;
    posicaoVazia = get_posicao_vect_alunos(alunos);
    if (posicaoVazia == -1) {
        return -1;
    }

    //insere a nova unidade curricular no vector 
    alunos[posicaoVazia].nome = nome;
    alunos[posicaoVazia].regime = regime;
    alunos[posicaoVazia].ano_matricula = ano_matricula;
    alunos[posicaoVazia].numero = numero;
    alunos[posicaoVazia].curso = curso;
    alunos[posicaoVazia].ocupado = 1;

    return 1;
}

//Create
void criar_aluno(ALUNOS* alunos, REGIMES* regimes, CURSO* cursos) {
    //vamos pedir ao utilizador os dados para criar a nova unidade curricular
                //declarecao de variaveis necessarias
    char* nome;
    char* regime;
    int ano_matricula;
    int numero_aluno;
    int posicaoRegime;
    char posicaoCurso;

    //vamos pedir o nome do aluno 
    do{
        printf("Qual o nome do aluno?\n");
        scanf("%s", &nome);
   } while (strlen(nome) == 1);

    //vamos pedir o regime 
    do{
        listar_regimes(regimes);
        printf("Indique o regime da lista acima\n");
        scanf("%d", &posicaoRegime);
    } while (valida_regime_escolhido(regimes, posicaoRegime) == 0);

    // introducao do ano de matricula
    do {
        printf("Indique o ano de matricula do aluno (1,2,3)\n");
        scanf("%d", &ano_matricula);
    } while (valida_ano(ano_matricula) == 0);

    //introducao do numero do aluno
    do {
        printf("Indique o numero do aluno\n");
        scanf("%d", &numero_aluno);
    } while (valida_numero_aluno(alunos, numero_aluno) == 0);

    // introducao do curso
    do {
        listar_cursos(cursos);
        printf("Indique o curso do aluno de acordo com a lista acima\n");
        scanf("%d", &posicaoCurso);
    } while (valida_curso_escolhido(cursos, posicaoCurso));

    //valida se a unidade curricular já existe no nosso vector
    //No caso de retornar 1 a UC ja existe, caso contrario podemos inserir 
    insere_aluno(alunos, nome, regimes[posicaoRegime].regime, ano_matricula, numero_aluno, cursos[posicaoCurso].codcurso); // == 1);
    printf("Aluno inserido com sucesso!\n");
    printf("\n");
    }
/*
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

void ler_alunos() {
    // Abre o arquivo para leitura
    FILE* arquivo_aluno = fopen("alunos.txt", "r");
    if (arquivo_aluno == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Lê os dados do arquivo e armazena na estrutura "aluno"
    ALUNOS aluno;
    while (fscanf(arquivo_aluno, "%d %s %s %d %s", &aluno.numero, aluno.nome, aluno.curso, &aluno.ano_matricula, aluno.regime) == 5) {
        // Aqui você pode fazer alguma coisa com os dados lidos, como adicionar a um vetor de alunos, por exemplo
        printf("Aluno: %s %s %s %d %s\n", aluno.nome, aluno.curso, aluno.regime, aluno.ano_matricula, aluno.numero);
    }

    // Fecha o arquivo
    fclose(arquivo_aluno);
}
*/

//funcao principal do programa aluno.c
void menu_alunos(ALUNOS* alunos, REGIMES* regimes, CURSO* cursos){
    int escolha;
    //Boas vindas ao usuario
    printf("Bem vindo ao sistema de alunos do Politecnico de Viseu:\n");
    //Criando loop de menu para o usuario
    while (1) {
        // apresentando opcoes
        printf("\nSelecione sua opção:\n[1] Criar aluno:\n[2] Buscar Aluno:\n[3] Listar Alunos:\n[4] Sair\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1://Criar aluno    
            //alunos = fopen("alunos.txt", "a");//abre o arquivo com "A", cara criar caso necessario e escrever no final caso ja exista.
            criar_aluno(alunos, regimes, cursos);
            break;
        case 2://Buscar Aluno
            char numero[6];
            printf("Digite o numero do Aluno:\n");
            scanf("%s", &numero);
            //buscar_aluno(numero);
            break;
        case 3: 
            listar_alunos(alunos);
            break;
        case 4:
            exit(0);
        }
    }
}
