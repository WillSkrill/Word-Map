#include "mapa.h"

//////////////////////////////////////
//////////INICIA MAPA COM 0///////////
//////////////////////////////////////

void inicia_mapa (Mapa *mp)
{
    mp->lista = (Item**) malloc(BLOCOS * sizeof(Item*));

    if(mp->lista == NULL){
        printf("Espaço na memória é insuficiente.\n");
        system("pause");
        exit(1);
    }

    mp->total = 0;
    mp->blocos = 1;
}


//////////////////////////////////////
/////////INSERE PALAVRA NOVA//////////
//////////////////////////////////////

void insere_termo (Mapa *mp, char *s)
{
    // Recebe palavra
    int tam = strlen(s) + 1; // Tamanho da palavra + \0
    char palavra[tam];
    strcpy(palavra, s);

    // Contador recebe número de structfs "Item" existentes
    int cont = mp->total;

    // Aloca mais 10 espaços na memória do tamanho da struct "Item" em mp->lista, caso o total de itens ultrapasse o tamanho alocado anteriormente
    if ((mp->total != 0) && (mp->total % 10 == 0))
    {
        // Atualiza contador de blocos em struct mp
        mp->blocos++;
        // Aloca mais 10 espaços
        mp->lista = (Item**) realloc(mp->lista, mp->blocos * BLOCOS * sizeof(Item*));
    }

    // Aloca novo item e atualiza total de "Itens" no mapa
    mp->lista[cont] = (Item*) malloc(sizeof(Item));
    mp->total++;

    // Atualiza contador de item para 1
    mp->lista[cont]->conta = 1;

    // Aloca palavra de tamanho tam e insere palavra em termo
    mp->lista[cont]->termo = (char *) malloc(tam * sizeof(char));
    strcpy(mp->lista[cont]->termo, palavra);
}


//////////////////////////////////////
/////INCREMENTA PALAVRA JÁ USADA//////
//////////////////////////////////////

int incrementa (Mapa *mp, char *s)
{
    int cont = busca_palavra(mp, s);

    // Caso termo tenha sido encontrado
    if (cont != -1)
    {
        // Incrementa +1 no contador do termo
        mp->lista[cont]->conta++;
        return (0);
    }

    // Caso termo ainda não exista
    return (1);
}


//////////////////////////////////////
//////ATUALIZA CONTADOR DE TERMO//////
//////////////////////////////////////

int escreve_cont (Mapa *mp, char *s, int c)
{
    int cont = busca_palavra(mp, s);

    // Caso termo tenha sido encontrado
    if (cont != -1)
    {
        // Escreve 'c' no contador do termo atual
        mp->lista[cont]->conta = c;
        return (0);
    }

    // Caso termo ainda não exista
    return (1);
}


//////////////////////////////////////
///////RETORNA CONTADOR DE TERMO//////
//////////////////////////////////////

int le_contador (Mapa *mp, char *s)
{
    // Verifica se termo já existe
    int cont = busca_palavra(mp, s);

    // Caso termo tenha sido encontrado
    if (cont != -1)
    {
        return (mp->lista[cont]->conta);
    }

    // Caso termo ainda não exista
    return (1);
}


//////////////////////////////////////
/////////////REMOVE ITEM//////////////
//////////////////////////////////////

void remove_termo (Mapa *mp, char *s)
{
    // Verifica se termo já existe
    int cont = busca_palavra(mp, s);

    // Caso termo tenha sido encontrado
    if (cont != -1)
    {
        // Libera memória de struct item com termo 's'
        free(mp->lista[cont]);
        // Diminui -1 no contador de itens na struct mapa
        mp->total--;
    }
    return;
}


//////////////////////////////////////
/////////////LIBERA MAPA//////////////
//////////////////////////////////////

void libera_mapa (Mapa *mp)
{
    // Libera toda a memória alocada para "Itens", caso exista algum
    if (mp->total > 0)
    {
        free(mp->lista);
    }

    // Zera completamente o mapa
    mp->total = 0;
    mp->blocos = 0;
}


//////////////////////////////////////
////RETORNA NÚMERO DE STRUCTS ITEM////
//////////////////////////////////////

int tamanho_mapa (Mapa *mp)
{
    return mp->total;
}


//////////////////////////////////////
///////RETORNA TERMO E CONTADOR///////
//////////////////////////////////////
void le_termo (Mapa *mp, int i, char *t, int *c)
{
    strcpy(t, mp->lista[i]->termo);
    *c = mp->lista[i]->conta;
    return;
}


//////////////////////////////////////
////////////BUSCA PALAVRA/////////////
//////////////////////////////////////

int busca_palavra (Mapa *mp, char *s)
{
    // Recebe palavra
    int tam = strlen(s) + 1;
    char palavra[tam];
    strcpy(palavra, s);

    // Repete até rodar todas os itens alocados
    for (int cont = 0; cont < mp->total; cont++)
    {
        // Caso palavra tenha sido encontrada
        if (strcmp(palavra, mp->lista[cont]->termo) == 0)
        {
            return (cont);
        }
    }

    // Retorna -1 caso palavra não tenha sido encontrada
    return (-1);
}





