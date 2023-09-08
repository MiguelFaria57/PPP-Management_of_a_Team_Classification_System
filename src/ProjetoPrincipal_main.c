/** ---------------------------------------------------- RESUMO ---------------------------------------------------- **/
// Neste programa começa-se por retirar os nomes dos ficheiros contidos em "config.txt" e armazená-los em arrays de
// caracteres diferentes. De seguida, a lista é inicializada e as equipas presentes no ficheiro binário de entrada que
// as contém são colocadas na lista duplamente ligada, todas com 0 pontos. Posteriormente, os pontos vão sendo
// atualizados à medida que os resultados presentes no ficheiro binário de entrada que os contém vão sendo lidos. Quando
// não existir mais nenhum resultado, a lista é escrita por ordem decrescente de pontos no ficheiro de texto de output
// que é suposto conter a classificação final. Além disto, é também escrito a equipa campeã, as equipas promovidas e as
// equipas despromovidas no outro ficheiro de texto de output. Para finalizar, a lista é limpa.

// Para correr este programa, selecionar a opção "ProjetoPrincipal" na caixa de diálogo "Edit Run/Debug configurations"


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
#include "ProjetoPrincipal_header.h"


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

    // Inicializar a lista
    inicializar_lista();

    // Colocar na lista todas as equipas com 0 pontos
    colocar_equipas(input_file1);

    // Atualizar os pontos de cada equipa consoante os resultados
    atualizar_pontos(input_file2);

    // Imprimir nos ficheiros de output a classificação final e o campeão, promovidos e despromovidos
    imprimir_lista_ficheiros(output_file1, output_file2);

    // Limpar a lista
    limpar_lista();

    return 0;
}