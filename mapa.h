#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define BLOCOS 10

typedef struct _item
{
int conta; // contador
char *termo; // palavra
} Item;

typedef struct _mapa
{
int total; // n�mero de itens no mapa
int blocos; // n�mero de blocos de itens alocados
Item **lista; // vetor de ponteiros para itens
} Mapa;

// inicia um mapa vazio
void inicia_mapa (Mapa *mp);

// insere um item com termo s e conta=1
void insere_termo (Mapa *mp, char *s);

// incrementa contador do termo s, retorna 1 se n�o encontrou o termo
int incrementa (Mapa *mp, char *s);

// escreve 'c' no contador do termo s, retorna 1 se n�o encontrou o termo
int escreve_cont (Mapa *mp, char *s, int c);

// retorna contador do termo s
int le_contador (Mapa *mp, char *s);

// remove o item com termo s
void remove_termo (Mapa *mp, char *s);

// libera o espa�o ocupado pelo mapa
void libera_mapa (Mapa * mp);

// retorna n�mero de itens no mapa
int tamanho_mapa (Mapa * mp);

// retorna em 't' o termo no �ndice e em 'c' o seu contador
void le_termo (Mapa * mp, int i, char *t, int *c);

// verifica se termo existe em algum item, se existir retorna seu indice, retorna -1 caso n�o exista
int busca_palavra (Mapa *mp, char *s);



#endif // MAPA_H_INCLUDED
