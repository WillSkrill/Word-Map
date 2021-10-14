#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED


// Lê arquivo desejado, considerando apenas palavras com o tamanho minimo escolhido em opcoes()
// Caso opcoes() não tenham sido utilizada, lê todas as palavras
void recebe_texto(Mapa *mp, int min_char, char *arquivo, int tipo);

// Printa termos e contadores em ordem decrescente
// Printa apenas contadores que tenham uma qtd_min e qtd_max de repetição
void exibe_rank (Mapa *mp, int qtd_min, int qtd_max, char *arquivo);

// Serve de apoio para escrever o ranking em ordem decrescente
// É chamada dentro da função exibe_rank()
int retorna_indice(Mapa *mp, int *verif, int x);

// Procura palavra desejada dentro das structs item e printa seu contador
void palavra_procura(Mapa *mp);

// Define quantidade mínima de caracteres que uma palavra deve para ser considerada na função recebe_texto()
int opcoes(Mapa *mp, char *nome_arquivo);

// Chama função exibe_rank(), indicando que ela deve printar apenas as palavras que tem um número entre qtd_min e qtd_max em seu contador
void intervalo_rank(Mapa *mp, char *arquivo);

// Printa menu principal
void print_menu();

// Funções de auxílio
void red();
void green();
void yellow();
void reset();
int filtraInteiro();


#endif // RANKING_H_INCLUDED
