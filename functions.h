#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define STRING char *

#include <locale.h>

/**INICIO Da declaracao de estruturas**/
//Definicao de estrutura de feriados 
typedef struct
{
	int dia;
	int mes;
}FERIADOS;

typedef struct
{
	int codigo;
	char* epoca;
	char* dataInicio;
	char* dataFim;
	int semestre;
	int ocupado;
}EPOCAS;

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
	char* curso;
	char* docente;
	int ano;
	int semestre;
	int ocupado;
}UNIDADECURRICULAR;

//definicao da estrutura de exames
typedef struct
{
	int codigo;
	char* unidade_curricular;
	int ano; 
	char* curso;
	char* epoca;
	char* data;
	char* hora;
	int duracao;
	char* sala;
	int alunos_inscritos;
	int realizado;
	int ocupado;
} EXAMES;

//definicao da estrutura regimes
typedef struct {
	int codigo;
	char* regime;
	int ocupado;
}REGIMES;

//definicao da estrutura alunos
typedef struct {
	char* nome; 
	char* regime; //ID dos regimes = 1 (normal), 2 (trabalhador estudante), 3 (atleta), 4 (dirigente associativo), 5 (Erasmus)
	int ano_matricula; 
	int numero; 
	char* curso;
	int ocupado;
}ALUNOS;

//definicao da estrutura salas
typedef struct{
	int id;
	char* codigo;
	char* nome_sala;
	int lotacao;
	int ocupado;
}SALAS;

//definicao da estrutura inscricoes exames
typedef struct{
	int codigo;
	char* unidade_curricular;
	int numero_aluno;
	int ano_matricula;
	char* epoca;
	char* regime;
	int ocupado;
}INSCRICOESEXAMES;

typedef struct{
	int dia; 
	int mes; 
	int ano;
}DATA;

typedef struct 
{
	int exameid; 
	char* sala; 
	char* data; 
	char* hora;
	int realizado; 
}EXAMESSALAS;



/*FIM da definicao de estruturas*/
void menu_inscricao_exames(INSCRICOESEXAMES* inscricoes_exames, EXAMES* exames, ALUNOS* alunos, REGIMES* regimes);
void export_exames_salas(EXAMESSALAS* exames_salas);
void consulta_Salas_exame(EXAMES* exames_bv, EXAMESSALAS* exames_salas, SALAS* salas);
void listar_exames(EXAMES* exames_bv, int jarealizados);
void atribuir_salas(EXAMES* exames_bv, SALAS* salas, EXAMESSALAS* exames_salas);
STRING* Read_Split_Line_File(FILE* f, int* n_campos_lidos);
void import_feriados(FERIADOS* feriado, STRING* V);
void lista_feriados(FERIADOS* feriado);
void import_txt_cursos(CURSO* curso, STRING* V);
void import_txt_uc(UNIDADECURRICULAR* uc, STRING* V);
void export_UC(UNIDADECURRICULAR* uc);
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
void menu_uc(UNIDADECURRICULAR* uc, CURSO* cursos, EXAMES* exames_bv);
void import_txt_exames(EXAMES* exames, STRING* V, UNIDADECURRICULAR* uc);
void import_txt_inscricoes_exames(INSCRICOESEXAMES* inscricoes_exames, STRING* V);
void menu_exames(EXAMES* exames_bv, INSCRICOESEXAMES* inscricoes_exames, ALUNOS* alunos, SALAS* salas, EPOCAS* epocas, UNIDADECURRICULAR* uc, CURSO* cursos, FERIADOS* feriados_datas, EXAMESSALAS* exames_salas);
void listar_exames(EXAMES* exames, int jarealizados);
void import_txt_alunos(ALUNOS* alunos, STRING* V);
void import_txt_regimes(REGIMES* regimes, STRING* V);
void listar_regimes(REGIMES* regimes);
void listar_alunos(ALUNOS* alunos);
int valida_regime_escolhido(REGIMES* regimes, int posicaoRegime);
int valida_ano_matricula(int ano_matricula);
int valida_aluno_existe(ALUNOS* alunos, int numero);
int get_posicao_vect_alunos(ALUNOS* alunos);
int insere_aluno(ALUNOS* alunos, char* nome, char* regime, int ano_matricula, int numero, char* curso);
void criar_aluno(ALUNOS* alunos, REGIMES* regimes, CURSO* cursos);
int valida_delete_aluno(INSCRICOESEXAMES* inscricoes_exames, ALUNOS* alunos, int numero_aluno, int opcao_aluno);
void apagar_aluno(ALUNOS* alunos, INSCRICOESEXAMES* inscricoes_exames);
void editar_aluno(ALUNOS* alunos, INSCRICOESEXAMES* inscricoes_exames, REGIMES* regimes, CURSO* cursos);
void export_alunos(ALUNOS* alunos);
void menu_alunos(ALUNOS* alunos, REGIMES* regimes, CURSO* cursos, INSCRICOESEXAMES* inscricoes_exames);
void import_txt_salas(SALAS* salas, STRING* V);
void listar_salas(SALAS* salas);
int valida_sala_existe_vector(SALAS* salas, char* nome_sala);
int get_newID_sala(SALAS* salas);
int get_posicao_vect_salas(SALAS* salas);
int insere_sala(SALAS* salas, char* codigo, char* nome_sala, int lotacao);
void criar_sala(SALAS* salas);
int valida_cod_sala(SALAS* salas, int opcaoSala);
int valida_delete_sala(EXAMES* exames, char* codigo);
void apagar_salas(SALAS* salas, EXAMES* exames_bv);
void export_Salas(SALAS* salas);
void menu_salas(SALAS* salas, EXAMES* exames_bv);
void export_feriados(FERIADOS* feriado);
void export_alunos(ALUNOS* alunos);
void import_txt_epocas(EPOCAS* epocas, STRING* V);
char *trim(char *str);
DATA* data_actual(DATA* DataActual);
DATA* coloca_data_em_struct(char* datastr, DATA* data_exame);
int exame_ja_realizado(DATA* data_actual, DATA* data_exame);
void lista_epocas(EPOCAS* epocas);
void listar_UC_curso_semestre(UNIDADECURRICULAR* uc, char* curso, int semestre);
int valida_UC_curso_semestre(UNIDADECURRICULAR* uc, char* curso, int semestre, int opcao);
void export_inscricoes(INSCRICOESEXAMES* inscricoes_exames);

#endif 