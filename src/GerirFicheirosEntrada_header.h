/** --------------------------------------------------- DEFINES ---------------------------------------------------- **/
#define MAXLETRASFICHEIRO 40
#define MAXLETRASEQUIPA 50
#define MAXDIGPONTOS 5


/** --------------------------------------------------- FUNÇÕES ---------------------------------------------------- **/
int ler_linha(FILE *ficheiro, char *linha, int lim);
int str_para_int(const char *string);
int verificar_extensao(const char file[MAXLETRASFICHEIRO], int lim, char extensao[4]);
int nomes_ficheiros(char input_file1[MAXLETRASFICHEIRO], char input_file2[MAXLETRASFICHEIRO],
                     char output_file1[MAXLETRASFICHEIRO], char output_file2[MAXLETRASFICHEIRO]);
void introduzir_equipa(char input_file1[MAXLETRASFICHEIRO]);
void introduzir_resultado(char input_file2[MAXLETRASFICHEIRO]);
void gerir_ficheiros_entrada(char input_file1[MAXLETRASFICHEIRO], char input_file2[MAXLETRASFICHEIRO]);