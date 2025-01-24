#ifndef LP_G14_FILES_H
#define LP_G14_FILES_H

#include "stdlib.h"
#include "stdio.h"

#define TABELA_FICHA_TECNICA "../csv/Tabela_Ficha_Tecnica.csv"

/**
 * Abre o ficheiro que é passado como parâmetro.
 * @param filename
 * @param mode
 * @return ficheiro.
 */
FILE *abrirFicheiro(char *filename, char *mode);

/**
 * A função obtem o tamanho do fichiero em linhas.
 * @param file
 * @return número de linhas.
 */
int obterTamanhoFicheiro(FILE *file);

#endif //LP_G14_FILES_H
