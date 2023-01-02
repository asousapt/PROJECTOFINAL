#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define STRING char *

/**INICIO Da declaracao de estruturas**/
//Definicao de estrutura de feriados 
typedef struct 
{
   int dia; 
   int mes;
}FERIADOS;

typedef struct {
	char* codcurso; 
	char* descricao;
	int ocupado;
} CURSO; 

//definicao da estrutura de unidade curricular 
typedef struct
{
	int codigo;
	char* descricao;
	char* docente;
	int ano;
	int semestre;
	char* curso;
	int ocupado;
}UNIDADECURRICULAR;

//definicao da estrutura de exames
typedef struct
{
	int codigo;
    char* curso;
	char* unidade_curricular;
	char* epoca;
	char* data;
	char* hora;
	int duracao;
	char* sala;
	int alunos_inscritos;
	int realizado;
	int ocupado;
} EXAMES;

/*FIM da definicao de estruturas*/

STRING* Read_Split_Line_File(FILE* f, int* n_campos_lidos);
void import_feriados(FERIADOS* feriado, STRING* V);
void lista_feriados(FERIADOS* feriado);
void import_txt_cursos(CURSO* curso, STRING* V);
void import_txt_uc(UNIDADECURRICULAR* uc, STRING* V);
void listar_UC(UNIDADECURRICULAR* uc);
void listar_cursos(CURSO* cursos);
int valida_curso_escolhido(CURSO* cursos, int escolhido);
int valida_ano_semestre(int ano, int semestre);
int valida_UC_existe_vector(UNIDADECURRICULAR* uc, char* descricao, char* curso);
void criar_UC(UNIDADECURRICULAR* uc, CURSO* cursos);
int insere_uc(UNIDADECURRICULAR* uc, char* descricao, char* docente, char* curso, int ano, int semestre);
int get_posicao_vect_UC(UNIDADECURRICULAR* uc);
int get_newID_UC(UNIDADECURRICULAR* uc);
int valida_UC_existe_vector(UNIDADECURRICULAR* uc, char* descricao, char* curso);
void menu_uc(UNIDADECURRICULAR* uc, CURSO* cursos);
void import_txt_exames(EXAMES* exames_bv, STRING* V);
void menu_exames(EXAMES* exames_bv);
void listar_exames(EXAMES* exames_bv);


#endif 