/** --------------------------------------------------- INCLUDES --------------------------------------------------- **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProjetoPrincipal_header.h"


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
        if (c!='\a' && c!='\b' && c!='\f' && c!='\r' && c!='\t' && c!='\v' && c!='\0') linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = (char) fgetc(ficheiro);
    return c;
}


// Função que permite verificar se a extensão do ficheiro é correta
// Os parâmetros da função são o array de caracteres que se pretende veerificar, o tamanho maximo do array e a extensão
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


// Função que permite inicializar a lista como NULL
// A função não tem parâmetros
void inicializar_lista(void) {
    tab_classificacao = NULL;
}


// Função que permite criar um novo nó na lista
// O parâmetro da função é a struct onde são armazenados a equipa e respetivos pontos que se pretende colocar no novo nó
struct LDL *criar_novo_no(struct equipa_pontos e_p_novos) {
    struct LDL *novo_no = (struct LDL *)malloc(sizeof(struct LDL));
    novo_no->e_p = e_p_novos;
    novo_no->e_p_seguinte = NULL;
    novo_no->e_p_anterior = NULL;
    return novo_no;
}


// Função que permite colocar um elemento na lista (na frente da lista)
// O parâmetro da função é a struct onde são armazenados a equipa e respetivos pontos que se pretende colocar no novo
// nó que vai ser inserido na lista
void colocar_lista(struct equipa_pontos e_p_novos) {
    struct LDL *novo_no = criar_novo_no(e_p_novos);
    if(tab_classificacao == NULL) {
        tab_classificacao = novo_no;
        return;
    }
    tab_classificacao->e_p_anterior = novo_no;
    novo_no->e_p_seguinte = tab_classificacao;
    tab_classificacao = novo_no;
}


// Função que permite colocar na lista todas as equipas com 0 pontos
// O parâmetro da função é o array de caracteres que contém o nome do ficheiro de entrada binário que contém as equipas
void colocar_equipas(char input_file1[MAXLETRASFICHEIRO]) {
    // array de caracteres onde vai ser armazenado o nome da equipa lida
    char equipa[MAXLETRASEQUIPA];
    // struct temporaria onde vai ser armazenada a equipa e respetivos pontos que vai ser colocada na lista
    struct equipa_pontos temp;

    // abrir o ficheiro
    FILE *input1;
    input1 = fopen(input_file1, "rb");
    if (input1 == NULL)
        printf("Erro ao abrir o ficheiro\n");

    //colocar na lista a equipa com 0 pontos
    while (fread(temp.equipa, sizeof(equipa), 1, input1) == 1) {
        temp.pontos = 0;
        colocar_lista(temp);
    }

    // fechar o ficheiro
    fclose(input1);
}


// Função que permite atualizar os pontos de cada equipa consoante os resultados
// O parâmetro da função é o array de caracteres que contém o nome do ficheiro de entrada binário que contém os
// resultados
void atualizar_pontos(char input_file2[MAXLETRASFICHEIRO]) {
    // struct onde vão ser armazenados os valores lidos do ficheiro binário
    struct resultado_jogos {
        char equipa1[MAXLETRASEQUIPA];
        char equipa2[MAXLETRASEQUIPA];
        int pontos1;
        int pontos2;
    } resultado;

    // abrir o ficheiro
    FILE *input2;
    input2 = fopen(input_file2, "rb");
    if (input2 == NULL)
        printf("Erro ao abrir o ficheiro\n");

    // atualizar os pontos de cada equipa consoante os resultados
    while (fread(&resultado, sizeof(resultado), 1, input2) == 1) {
        // estrutura auxiliar que permite percorrer a lista
        struct LDL *aux = tab_classificacao;

        // verificar se as equipas estão presentes na lista
        int encontrado = -2;
        while (aux != NULL) {
            if (strcmp(aux->e_p.equipa, resultado.equipa1) == 0)
                encontrado++;
            if (strcmp(aux->e_p.equipa, resultado.equipa2) == 0)
                encontrado++;
            aux = aux->e_p_seguinte;
        }
        if (encontrado == 0) {
            aux = tab_classificacao;
            // caso a equipa 1 ganhe
            if (resultado.pontos1 > resultado.pontos2) {
                while (aux != NULL) {
                    if (strcmp(aux->e_p.equipa, resultado.equipa1) == 0)
                        aux->e_p.pontos += 2;
                    else if (strcmp(aux->e_p.equipa, resultado.equipa2) == 0)
                        aux->e_p.pontos += 1;
                    aux = aux->e_p_seguinte;
                }
            }
            // caso a equipa 2 ganhe
            if (resultado.pontos1 < resultado.pontos2) {
                while (aux != NULL) {
                    if (strcmp(aux->e_p.equipa, resultado.equipa1) == 0)
                        aux->e_p.pontos += 1;
                    else if (strcmp(aux->e_p.equipa, resultado.equipa2) == 0)
                        aux->e_p.pontos += 2;
                    aux = aux->e_p_seguinte;
                }
            }
        }
        else {
            // como a equipa que não está presente na lista pode não estar incrita na competição, é emitida uma mensagem
            // de aviso, e o resultado não conta para a classificação
            printf("Erro - equipa não está presente na lista: %s %d - %d %s\n", resultado.equipa1, resultado.pontos1,
                   resultado.pontos2, resultado.equipa2);
        }
    }

    // fechar o ficheiro
    fclose(input2);
}


// Função que permite imprimir a classificação final e o campeão, promoções e despromoções nos ficheiros de output
// Os parâmetros da função são os arrays de caracteres que contêm os nomes dos ficheiros de output
void imprimir_lista_ficheiros(char output_file1[MAXLETRASFICHEIRO], char output_file2[MAXLETRASFICHEIRO]) {
    // abrir os ficheiros
    FILE *output1;
    output1 = fopen(output_file1, "wb");
    if (output1 == NULL)
        printf("Erro ao abrir o ficheiro\n");
    FILE *output2;
    output2 = fopen(output_file2, "wb");
    if (output2 == NULL)
        printf("Erro ao abrir o ficheiro\n");

    // estrutura auxiliar que permite percorrer a lista
    struct LDL *aux = tab_classificacao;

    // contar quantas equipas existem
    int num_equipas = 0;
    while (aux != NULL) {
        num_equipas += 1;
        aux = aux->e_p_seguinte;
    }

    // escrever no ficheiro a classificação final e o campeão, promoções e despromoções
    struct equipa_pontos temp;
    for (int i=1; i<=num_equipas; i++) {
        temp.pontos = -1;

        // procurar a equipa com mais pontos e guardar os valores
        aux = tab_classificacao;
        while (aux != NULL) {
            if (aux->e_p.pontos > temp.pontos)
                temp = aux->e_p;
            aux = aux->e_p_seguinte;
        }

        // colocar a equipa com mais pontos com -1 pontos
        aux = tab_classificacao;
        while (aux != NULL) {
            if (strcmp(aux->e_p.equipa, temp.equipa) == 0)
                aux->e_p.pontos = -1;
            aux = aux->e_p_seguinte;
        }

        // escrever no ficheiro da classificação final
        if (i==1)
            fprintf(output1, "Classificação final\n\n%s#%d\n", temp.equipa, temp.pontos);
        else
            fprintf(output1, "%s#%d\n", temp.equipa, temp.pontos);


        // escrever no ficheiro do campeão, das promoções e das despromoções
        if (i==1)
            fprintf(output2, "Campeão:\n   %s\n\nPromovidos:\n   %s\n", temp.equipa, temp.equipa);
        if (i==2)
            fprintf(output2, "   %s\n\n", temp.equipa);
        if (i == (num_equipas-1))
            fprintf(output2, "Despromovidos:\n   %s\n", temp.equipa);
        if (i==num_equipas)
            fprintf(output2, "   %s\n\n", temp.equipa);
    }

    // fechar os ficheiros
    fclose(output1);
    fclose(output2);
}


// Função que permite limpar a lista
// A função não tem parâmetros
void limpar_lista(void) {
    while (tab_classificacao != NULL) {
        struct LDL *aux = tab_classificacao->e_p_seguinte;
        free(tab_classificacao);
        tab_classificacao = aux;
    }
}