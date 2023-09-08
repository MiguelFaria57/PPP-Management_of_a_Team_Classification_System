/** --------------------------------------------------- DEFINES ---------------------------------------------------- **/
#define MAXLETRASFICHEIRO 40
#define MAXLETRASEQUIPA 50
#define MAXDIGPONTOS 5


/** ------------------------------------------- LISTA DUPLAMENTE LIGADA -------------------------------------------- **/
// Struct onde são armazenados a equipa e respetivos pontos
struct equipa_pontos {
    char equipa[MAXLETRASEQUIPA];
    int pontos;
};

// Struct da lista duplamente ligada
struct LDL  {
    struct equipa_pontos e_p;
    struct LDL *e_p_seguinte;
    __unused struct LDL *e_p_anterior;
    // o "__unused" serve para retirar um warning que refere que "struct LDL *e_p_anterior" não é acessada, apesar de,
    // por exemplo, ser alterada numa struct do tipo LDL ("tab_classificacao") na função "colocar_lista"
};

// Struct da tabela de classificação
static struct LDL *tab_classificacao;


/** --------------------------------------------------- FUNÇÕES ---------------------------------------------------- **/
int ler_linha(FILE *ficheiro, char *linha, int lim);
int str_para_int(const char *string);
int verificar_extensao(const char file[MAXLETRASFICHEIRO], int lim, char extensao[4]);
int nomes_ficheiros(char input_file1[MAXLETRASFICHEIRO], char input_file2[MAXLETRASFICHEIRO],
                     char output_file1[MAXLETRASFICHEIRO], char output_file2[MAXLETRASFICHEIRO]);
void inicializar_lista(void);
struct LDL *criar_novo_no(struct equipa_pontos e_p_novos);
void colocar_lista(struct equipa_pontos e_p_novos);
void colocar_equipas(char input_file1[MAXLETRASFICHEIRO]);
void atualizar_pontos(char input_file2[MAXLETRASFICHEIRO]);
void imprimir_lista_ficheiros(char output_file1[MAXLETRASFICHEIRO], char output_file2[MAXLETRASFICHEIRO]);
void limpar_lista();