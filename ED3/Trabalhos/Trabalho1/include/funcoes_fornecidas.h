#ifndef __FUNCOES_FORNECIDAS__
#define __FUNCOES_FORNECIDAS__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void readline(char *string);

/**
 * Use essa função para comparação no run.codes.
 * Lembre-se de ter fechado (fclose) o arquivo anteriormente.
 *
 * Ela vai abrir de novo para leitura e depois fechar
 * (você não vai perder pontos por isso se usar ela).
 */
void binarioNaTela(char *nomeArquivoBinario);

void scan_quote_string(char *str);

#endif // __FUNCOES_FORNECIDAS__
