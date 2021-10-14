#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED


// L� arquivo desejado, considerando apenas palavras com o tamanho minimo escolhido em opcoes()
// Caso opcoes() n�o tenham sido utilizada, l� todas as palavras
void recebe_texto(Mapa *mp, int min_char, char *arquivo, int tipo);

// Printa termos e contadores em ordem decrescente
// Printa apenas contadores que tenham uma qtd_min e qtd_max de repeti��o
void exibe_rank (Mapa *mp, int qtd_min, int qtd_max, char *arquivo);

// Serve de apoio para escrever o ranking em ordem decrescente
// � chamada dentro da fun��o exibe_rank()
int retorna_indice(Mapa *mp, int *verif, int x);

// Procura palavra desejada dentro das structs item e printa seu contador
void palavra_procura(Mapa *mp);

// Define quantidade m�nima de caracteres que uma palavra deve para ser considerada na fun��o recebe_texto()
int opcoes(Mapa *mp, char *nome_arquivo);

// Chama fun��o exibe_rank(), indicando que ela deve printar apenas as palavras que tem um n�mero entre qtd_min e qtd_max em seu contador
void intervalo_rank(Mapa *mp, char *arquivo);

// Printa menu principal
void print_menu();

// Fun��es de aux�lio
void red();
void green();
void yellow();
void reset();
int filtraInteiro();


#endif // RANKING_H_INCLUDED
