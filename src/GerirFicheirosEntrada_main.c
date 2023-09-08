/** ---------------------------------------------------- RESUMO ---------------------------------------------------- **/
// Neste programa começa-se por retirar os nomes dos ficheiros contidos em "config.txt" e armazená-los em arrays de
// caracteres diferentes. De seguida, é perguntado ao utilizador se pretende inserir uma equipa ou um resultado. Após o
// utilizador inserir todos os dados necessários, eles são escritos nos ficheiros de entrada binários, e verifica-se
// se o utilizador pretende inserir mais ou não.

// Para correr este programa, selecionar a opção "GerirFicheirosEntrada" na caixa de diálogo "Edit Run/Debug
// configurations".


/** ------------------------------------------------ ESCOLHAS FEITAS ----------------------------------------------- **/
// Foi tomado como convenção que o ficheiro "config.txt" contém os nomes de dois ficheiros de entrada e dois ficheiros
// de saída:
//   - a primeiras linha é o ficheiro binário de entrada que contém as equipas ("equipas.bin");
//   - a segunda linha é o ficheiro binário de entrada que contém os resultados ("resultados.bin");
//   - a terceira linha é o ficheiro de texto de output que contém a classificação final ("classificacao_final.txt");
//   - a quarta linha é o ficheirode texto de output que contém o campeão, promovidos e despromovidos
//   ("campeao_promocoes_despromocoes.txt").
// Os tamanhos máximos de caracteres do nome dos ficheiros, de caracteres do nome da equipa e de caracteres do número de
// pontos estão establecidos no respetivo header usando "#define" e podem ser alterados.
// Para escrever e ler os resultados existentes no ficheiro binário foi usado uma "struct".


/** ---------------------------------------------------- INCLUDE --------------------------------------------------- **/
#include <stdio.h>
#include "GerirFicheirosEntrada_header.h"


/** ----------------------------------------------------- MAIN ----------------------------------------------------- **/
int main() {
    // Variáveis onde vão ser armazenados os nomes dos ficheiros
    char input_file1[MAXLETRASFICHEIRO], input_file2[MAXLETRASFICHEIRO],
            output_file1[MAXLETRASFICHEIRO], output_file2[MAXLETRASFICHEIRO];

    // Retirar os nomes dos ficheiros de entrada e de saída do ficheiro de texto "config.txt" e verificar se têm as
    // extensões corretas
    if (nomes_ficheiros(input_file1, input_file2, output_file1, output_file2) != 0) {
        printf("Erro - extensões incorretas, corrija no ficheiro 'config.txt'\n");
        return 1;
    }

    // Escolher se pretende inserir uma equipa ou um resultado nos ficheiros de entrada binários
    gerir_ficheiros_entrada(input_file1, input_file2);

    return 0;
}