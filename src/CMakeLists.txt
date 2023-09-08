cmake_minimum_required(VERSION 3.16)
project(Projeto_Miguel_Faria C)

set(CMAKE_C_STANDARD 11)


add_executable(GerirFicheirosEntrada GerirFicheirosEntrada_main.c GerirFicheirosEntrada_header.h GerirFicheirosEntrada_funcoes.c)

add_executable(ProjetoPrincipal ProjetoPrincipal_main.c ProjetoPrincipal_header.h ProjetoPrincipal_funcoes.c)