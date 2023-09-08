/** --------------------------------------------------- INCLUDES --------------------------------------------------- **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GerirFicheirosEntrada_header.h"


/** --------------------------------------------------- FUNÇÕES ---------------------------------------------------- **/
// Função que permite ler uma linha
// Os parâmetros da função são o ponteiro para o objeto FILE de onde se pretende ler, o array de caracteres onde se
// escreve o que se leu e o inteiro com o tamanho máximo de caracteres que se pode ler
int ler_linha(FILE *ficheiro, char *linha, int lim) {
    int i;
    char c;
    i = 0;
    while ((c = (char) fgetc(ficheiro)) == ' ');
    if (c != EOF) {
        if (c!='\n' && c!='\a' && c!='\b' && c!='\f' && c!='\r' && c!='\t' && c!='\v' && c!='\0')
            linha[i++] = c;
    } else
        return c;
    for (; i < lim - 1;) {
        c = (char) fgetc(ficheiro);
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (c!='\a' && c!='\b' && c!='\f' && c!='\r' && c!='\t' && c!='\v' && c!='\0')
            linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = (char) fgetc(ficheiro);
    return c;
}


// Função que permite transformar um array de caracteres num inteiro
// O parâmetro da função é o array de caracteres que se pretende transformar
int str_para_int(const char *string) {
    int res=0;
    int i;
    for (i=0; string[i] != '\0'; ++i) {
        if ((string[i])<'0' || (string[i])>'9')
            return -1;
        res = res * 10 + string[i] - '0';
    }

    return res;
}


// Função que permite verificar se a extensão do ficheiro é correta
// Os parâmetros da função são o array de caracteres que se pretende veerificar, o tamanho máximo do array e a extensão
// correta
int verificar_extensao(const char file[MAXLETRASFICHEIRO], int lim, char extensao[4]) {
    char temp_extensao[MAXLETRASFICHEIRO];
    for (int i=0; i<lim; i++) {
        if (file[i] == '.') {
            int j=0;
            for (int l=i+1; l<lim; l++) {
                temp_extensao[j] = (char) file[l];
                j++;
            }
            break;
        }
    }

    if (strcmp(temp_extensao, extensao) == 0)
        return 0;
    else
        return 1;
}


// Função que permite retirar os nomes dos ficheiros de entrada e de saída do ficheiro de texto "config.txt"
// Os parâmetros da função são os arrays de caracteres onde se pretende guardar os nomes dos ficheiros
int nomes_ficheiros(char input_file1[MAXLETRASFICHEIRO], char input_file2[MAXLETRASFICHEIRO],
                     char output_file1[MAXLETRASFICHEIRO], char output_file2[MAXLETRASFICHEIRO]) {
    // variável que vai permitir detetar erros na extensão
    int erro=0;

    // abrir o ficheiro
    FILE *config;
    config = fopen("config.txt", "r");
    if (config == NULL)
        printf("Erro ao abrir o ficheiro\n");

    // retirar nomes dos ficheiros e verificar as extensões do ficheiro
    ler_linha(config, input_file1, MAXLETRASFICHEIRO);
    erro += verificar_extensao(input_file1, MAXLETRASFICHEIRO, "bin");
    ler_linha(config, input_file2, MAXLETRASFICHEIRO);
    erro += verificar_extensao(input_file2, MAXLETRASFICHEIRO, "bin");
    ler_linha(config, output_file1, MAXLETRASFICHEIRO);
    erro += verificar_extensao(output_file1, MAXLETRASFICHEIRO, "txt");
    ler_linha(config, output_file2, MAXLETRASFICHEIRO);
    erro += verificar_extensao(output_file2, MAXLETRASFICHEIRO, "txt");

    // fechar o ficheiro
    fclose(config);

    return erro;
}


// Função que permite ao utilizador introduzir introduzir/escrever uma equipa num dos ficheiros de entrada binário
// O parâmetro da função é o array de caracteres que contém o nome do ficheiro de entrada onde se pretende escrever as
// equipas
void introduzir_equipa(char input_file1[MAXLETRASFICHEIRO]) {
    // array de caracteres onde vai ser armazenado o nome da equipa lida
    char equipa[MAXLETRASEQUIPA];
    // variáveis que vão permitir saber se o utilizador pretende inserir mais equipas
    char repetir;
    int int_repetir = 1;

    // introduzir equipa
    while (int_repetir == 1) {
        // como o nome das equipas podem conter qualquer tipo de caracter, não é necessario verificar a existência de
        // algum caracter específico

        // inserir o nome da equipa no array de caracteres
        printf("Insira a equipa: ");
        ler_linha(stdin, equipa, MAXLETRASEQUIPA);

        // abrir o ficheiro
        FILE *input1;
        input1 = fopen(input_file1, "ab");
        if (input1 == NULL)
            printf("Erro ao abrir o ficheiro\n");
        // escrever equipa no ficheiro
        fwrite(&equipa, sizeof(equipa), 1, input1);
        // fechar o ficheiro
        fclose(input1);

        // verificar se pretende introduzir mais equipas e se está a inserir uma das opções
        printf("Deseja inserir uma nova equipa? (1-sim ; 0-não)\n");
        scanf("%s", &repetir);
        int_repetir = str_para_int(&repetir);
        while (int_repetir != 1 && int_repetir!=0) {
            printf("Erro - introduza novamente: ");
            scanf("%s", &repetir);
            int_repetir = str_para_int(&repetir);
        }
    }
}


// Função que permite ao utilizador introduzir/escrever um resultado num dos ficheiros de entrada binário
// O parâmetro da função é o array de caracteres que contém o nome do ficheiro de entrada onde se pretende escrever os
// resultados
void introduzir_resultado(char input_file2[MAXLETRASFICHEIRO]) {
    // struct onde vão ser armazenados os valores lidos do ficheiro binário
    struct resultado_jogos {
        char equipa1[MAXLETRASEQUIPA];
        char equipa2[MAXLETRASEQUIPA];
        int pontos1;
        int pontos2;
    } resultado;
    // variáveis que vão permitir saber se o utilizador pretende inserir mais resultados
    char repetir;
    int int_repetir = 1;

    // introduzir resultado
    while (int_repetir == 1) {
        // inserir equipas na struct
        printf("Insira a primeira equipa: ");
        ler_linha(stdin, resultado.equipa1, MAXLETRASEQUIPA);
        printf("Insira a segunda equipa: ");
        ler_linha(stdin, resultado.equipa2, MAXLETRASEQUIPA);
        // como o nome das equipas podem conter qualquer tipo de caracter, não é necessario verificar a existência de
        // algum caracter específico

        // inserir pontos na struct
        // variáveis que vão permitir saber se os caracteres que o utilizador inseriu são números
        char pontos_lidos[MAXDIGPONTOS];
        int temp_pontos;
        printf("Insira os pontos da primeira equipa: ");
        ler_linha(stdin, pontos_lidos, MAXDIGPONTOS);
        while ((temp_pontos = str_para_int(pontos_lidos)) < 0) {
            printf("Pontos inválidos - introduza novamente: ");
            ler_linha(stdin, pontos_lidos, MAXDIGPONTOS);
        }
        resultado.pontos1 = temp_pontos;
        printf("Insira os pontos da segunda equipa: ");
        ler_linha(stdin, pontos_lidos, MAXDIGPONTOS);
        while ((temp_pontos = str_para_int(pontos_lidos)) < 0) {
            printf("Pontos inválidos - introduza novamente: ");
            ler_linha(stdin, pontos_lidos, MAXDIGPONTOS);
        }
        resultado.pontos2 = temp_pontos;

        // verificar se as equipas são diferentes e não há empates
        if ((strcmp(resultado.equipa1, resultado.equipa2) != 0) && (resultado.pontos1 != resultado.pontos2)) {
            // abrir o ficheiro
            FILE *input2;
            input2 = fopen(input_file2, "ab");
            if (input2 == NULL)
                printf("Erro ao abrir o ficheiro\n");
            // escrever resultado no ficheiro
            fwrite(&resultado, sizeof(resultado), 1, input2);
            // fechar o ficheiro
            fclose(input2);
        }
        else {
            printf("Erro - resultado inválido\n");
        }

        // verificar se pretende introduzir mais equipas e se está a inserir uma das opções
        printf("Deseja inserir um novo resultado? (1-sim ; 0-não)\n");
        scanf("%s", &repetir);
        int_repetir = str_para_int(&repetir);
        while (int_repetir != 1 && int_repetir!=0) {
            printf("Erro - introduza novamente: ");
            scanf("%s", &repetir);
            int_repetir = str_para_int(&repetir);
        }
    }
}


// Função que permite ao utilizador escolher se pretende inserir uma equipa ou um resultado nos ficheiros de entrada
// binários
// Os parâmetros da função são os arrays de caracteres que contêm os nomes dos ficheiros de entrada
void gerir_ficheiros_entrada(char input_file1[MAXLETRASFICHEIRO], char input_file2[MAXLETRASFICHEIRO]) {
    // perguntar ao utilizador o que desja inseir
    printf("Deseja \n  (1) introduzir uma equipa\n  (2) introduzir um resultado\n");
    char opcao;
    scanf("%s", &opcao);
    int int_opcao = str_para_int(&opcao);

    // verificar se o utilizador está a escrever uma das opções dadas
    while (int_opcao != 1 && int_opcao != 2) {
        printf("Erro - introduza novamente: ");
        scanf("%s", &opcao);
        int_opcao = str_para_int(&opcao);
    }

    // introduzir equipa
    if (int_opcao == 1) {
        introduzir_equipa(input_file1);
    }
    // introduzir resultado
    if (int_opcao == 2) {
        introduzir_resultado(input_file2);
    }
}