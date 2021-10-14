#include "mapa.h"
#include "ranking.h"
#include <ctype.h>

//////////////////////////////////////
//////////////LÊ ARQUIVO//////////////
//////////////////////////////////////

void recebe_texto(Mapa *mp, int min_char, char *arquivo, int tipo)
{
    // Reseta mapa caso já tenha lido um arquivo anteriormente
    libera_mapa(mp);

    // Cria mapa zerado
    inicia_mapa(mp);

    int total_palavras = 0; // Cria variável que irá guardar total de palavras presente no arquivo
    char letra;  // Char que lerá letra por letra do arquivo txt
    int verif = 0;  // Verificador, caso '1' cria novo termo, caso '0' encrementa em termo existente


    // Cria buffer palavra com todos os espaços com '\0'
    char palavra[64]; // Palavras de no máximo 64 caracteres
    memset(palavra, '\0', sizeof palavra);

    // Caso função recebe_texto() tenha sido chamada na primeira opção do menu
    if (tipo == 1)
    {
        yellow();
        printf("Digite o nome do arquivo (mais a extensão .txt) que deseja ler:\n\n");
        reset();

        // Recebe nome do arquivo que deve ser lido e retira '\n' da string
        fgets(arquivo, 129 * sizeof(char), stdin); // Tamanho máximo do nome do arquivo de 128 caracteres
        arquivo[strcspn(arquivo, "\n")] = 0;

        system("cls");
    }


    // Abre arquivo txt em modo "read"
    FILE *txt;
    txt = fopen(arquivo, "r");

    // Caso arquivo não tenha sido encontrado
    if (txt == NULL)
    {
        if (tipo==1)
        {
            // Mensagem de erro
            red();
            printf("Arquivo não encontrado!\n\n");
            reset();
            system("pause");
            system("cls");
        }

        // Caso função recebe_texto() tenha sido chamada em opções() ou em "Atualizar arquivo" no menu
        else
        {
            system("pause");
            system("cls");
        }

        // Sai da função
        return;
    }

    // Roda loop enquanto não encontra final do arquivo e envia palavra por palavras para as funções incrementa() ou insere_termo()
    for (int loop = 0; loop == 0;)
    {
        // Recebe proximo 'char' do arquivo .txt
        letra = fgetc(txt);
        // Se letra for maiúscula, coloca como minúscula
        letra = tolower(letra);

        // Caso 'letra' seja literalmente uma letra
        if (
              (letra != ' ') && (letra != '\n') && (letra != ',') && (letra != '.') && (letra != ';') &&
              (letra != ':') && (letra != '?') && (letra != '!') && (letra != '"') && (letra != '#') &&
              (letra != '(') && (letra != ')') && (letra != '{') && (letra != '}') && (letra != '[') &&
              (letra != ']') &&(letra != EOF)
           )
        {
            // Concatena 'letra' em 'palavra'
            strncat(palavra, &letra, 1);
        }

        // Caso encontre um espaço vazio
        else if ((letra == ' ') || (letra == EOF) || (letra == '\n'))
        {
            // Verifica se palavra possui tamanho estipulado em "opcoes()"
            if (strlen(palavra) >= min_char)
            {
                // Caso já exista uma 'Struct Item' desta palavra, acrescenta +1 no contador e retorna 0
                // Caso ainda não exista uma 'Struct Item' desta palavra retorna 1
                verif = incrementa(mp, palavra);

                // Caso 'verif==1' (indicando que palavra ainda não possui uma 'Struct Item')
                if (verif)
                {
                    // Cria uma nova 'Struct Item' para a palavra em específico
                    insere_termo(mp, palavra);
                }

                // Acrescenta + 1 no total de palavras
                total_palavras++;
            }

            // Reseta o buffer 'palavra'
            memset(palavra, '\0', sizeof palavra);
        }

        // Caso 'letra' encontre final do arquivo
        if (letra == EOF)
        {
            // Loop = 1, indicando que já leu todas as palavras e deve parar a repetição (for)
            loop = 1;
        }
    }

    // Fecha arquivo
    fclose(txt);

    // // Caso função recebe_texto() tenha sido chamada em "Ler arquivo" no menu
    if (tipo == 1)
    {
        // Mensagem de sucesso
        green();
        printf("       Arquivo lido com sucesso!\n");
        reset();
    }

    // Printa total de palavras lidas
    yellow();
    printf("Foram computadas um total de %i palavras.\n\n", total_palavras);
    reset();

    // Pausa e limpa tela antes de sair da função
    system("pause");
    system("cls");

}


//////////////////////////////////////
////////////EXIBE RANKING/////////////
//////////////////////////////////////

void exibe_rank (Mapa *mp, int qtd_min, int qtd_max, char *nome_arquivo)
{
    int total_palavras = 0;

    ///////////////Printa parte inicial do menu///////////////
    red();
    printf(" ARQUIVO: ");
    reset();
    printf("%s\n", nome_arquivo);

    yellow();
    printf(" ____________________________________\n");
    reset();

    yellow();
    printf("|                       |            |\n");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf("        PALAVRA        ");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf(" QUANTIDADE ");
    reset();

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|_______________________|____________|\n");
    reset();
    ///////////////////////////////////////////////////////////


    int maior_indice = 0;
    int verif[mp->total]; // Cria vetor para guardar os maiores índices em ordem decrescente (indicando que não devem ser lidos novamente)

    // Preenche struct verif com '-1'
    for (int t = 0; t < mp->total; t++)
    {
        verif[t] = -1;
    }

    // Repete até printar todos os termos e contadores em ordem decrescente
    for (int x=0; x < mp->total; x++)
    {
        // Chama função que retorna o maior índice atual e guarda maior indice anterior para não ser lido anteriormente
        maior_indice = retorna_indice(mp, verif, x);

        // Caso termo esteja entre a quantidade mínima e máxima de repetições definida
        if ((mp->lista[maior_indice]->conta >= qtd_min) && (mp->lista[maior_indice]->conta <= qtd_max))
        {
            yellow();
            printf("|");
            reset();

            // Printa termo
            printf("%-23s", mp->lista[maior_indice]->termo);

            yellow();
            printf("|");
            reset();

            // Printa contador
            printf("     %-6i ", mp->lista[maior_indice]->conta);

            yellow();
            printf("|\n");
            reset();

            // Guarda total de palavras dos contadores (somando todos)
            total_palavras = total_palavras + mp->lista[maior_indice]->conta;
        }
    }

    yellow();
    printf("|_______________________|____________|\n\n");
    reset();

    red();
    printf("        TOTAL DE PALAVRAS: ");
    reset();

    // Printa total de palavras lidas
    printf("%i\n\n", total_palavras);

    // Pausa e limpa a tela antes de sair da função
    system("pause");
    system("cls");
}


//////////////////////////////////////
/////////RETORNA MAIOR INDICE/////////
//////////////////////////////////////

// Esta função serve de apoio para escrever o ranking em ordem decrescente
// Ela verifica qual o índice que possui maior contador
// E certifica de que o índice anterior não seja lido novamente (o colocando dentro do vetor verif[] recebido)
// O vetor verif anteriormente é preenchido apenas com '-1'

int retorna_indice(Mapa *mp, int *verif, int x)
{
    int maior_indice = 0;
    int maior_num = 0;
    int teste;

    // Repete até ler todas as structs 'Item'
    for (int z=0 ; z < mp->total; z++)
    {
        // reseta variável teste
        teste = 0;

        // Testa para ver se mp->lista[z] já foi usado (Lê todas as posições de (verif[])
        for (int cont = 0, finaliza =0; cont < mp->total && teste != 1 && finaliza == 0; cont++)
        {
            // Se verif = -1, finaliza repetição
            if (verif[cont] == -1)
            {
                finaliza = 1; // Caso verif[] já esteja lendo uma posição não utilizada, finaliza = 1
            }

            // Se verif = número do contador, teste = 1, definindo que palavra já foi utilizada anteriormente
            if (verif[cont] == z)
            {
                teste = 1; // Indica que índice 'z' já foi utilizado antes
            }
        }

        // Se o índice atual 'z' é maior que o maior_num anterior e se teste for diferente de 1 (indicando que incide 'z' não foi usado anteriormente
        if ((mp->lista[z]->conta > maior_num) && (teste != 1))
        {
            maior_indice = z; // Recebe o índice de maior número (caso o contador seja o maior lido até agora)
            maior_num = mp->lista[z]->conta; // Recebe o número do contador do índice 'z'
        }
    }
    // Guarda o maior índice lido no vetor verif[x] para não lê-lo novamente depois
    verif[x] = maior_indice;
    // Retorna o maior índice
    return(maior_indice);
}


//////////////////////////////////////
///////////PROCURA PALAVRA////////////
//////////////////////////////////////

void palavra_procura(Mapa *mp)
{
    int cont; // Índice da palavra buscada
    char palavra[32]; // Buffer para palavra

    green();
    printf("Digite a palavra que deseja buscar:\n");
    reset();
    red();
    printf("   Use '-1' para voltar ao menu.\n\n");
    reset();

    // Roda infinito, mas para quando usuário digitar "-1"
    for (;;)
    {
        // Recebe palavra que deve ser buscada
        fgets(palavra, sizeof palavra, stdin);
        // Apaga o '\n' da string palavra (por causa do fgets)
        palavra[strcspn(palavra, "\n")] = 0;

        // Deixa palavra apenas com caracteres minúsculos
        for (int ler = 0; ler < strlen(palavra); ler++)
        {
            palavra[ler] = tolower(palavra[ler]);
        }

        // Verifica se palara = '-1', para finalizar operação
        if (strcmp(palavra, "-1") == 0)
        {
            // Limpa tela
            system("cls");

            green();
            printf("Operação finalizada com sucesso!\n\n");
            reset();

            // Pausa e limpa tela
            system("pause");
            system("cls");

            // Volta para menu principal
            return;
        }

        // Recebe índice de palavra desejada, caso palavra não seja encontrada, cont = -1
        cont = busca_palavra (mp, palavra);

        // Se encontrou a palavra
        if (cont != -1)
        {
            yellow();
            printf("QUANTIDADE: ");
            reset();

            // Printa palavra
            printf("%i\n\n", mp->lista[cont]->conta);

            // Reseta palavra completamente
            memset(palavra, '\0', sizeof palavra);
        }

        // Caso não tenha encontrado a palavra
        else
        {
            // Limpa tela
            system("cls");

            // Mensagem de erro
            red();
            printf("Palavra digitada não encontrada!\n");
            printf("   Por favor, tente novamente.\n\n");
            reset();

            // Pausa e limpa a tela
            system("pause");
            system("cls");

            // Printa mensagem inicial da função
            green();
            printf("Digite a palavra que deseja buscar:\n");
            reset();
            red();
            printf("   Use '-1' para voltar ao menu.\n\n");
            reset();
        }
    }
}


//////////////////////////////////////
///////////////OPÇÕES/////////////////
//////////////////////////////////////

int opcoes(Mapa *mp, char *nome_arquivo)
{
    yellow();
    printf("Digite o número mínimo de caracteres a considerar:\n\n");
    reset();

    // Recebe o mínimo de caracteres a se considerar para ler o txt
    int min_char = filtraInteiro();

    // Limpa tela
    system("cls");

    // Caso usuário digite um número válido
    if (min_char > 0)
    {
        green();
        printf("     Operação finalizada com sucesso!\n");
        reset();

        // Chama função recebe_texto() para atualizar as palavras lidas
        recebe_texto(mp, min_char, nome_arquivo, 0);
    }

    // Casou o usuário digite algo inválido
    else
    {
        // Mensagem de erro
        red();
        printf("         Número inserido inválido!\n");
        reset();

        yellow();
        printf("Número mínimo de caracteres definido para 1.\n\n");
        reset();

        // Define mínimo de caracteres para 1
        min_char = 1;

        system("pause");
        system("cls");

        // Chama função recebe testo, lendo todas as palavras
        recebe_texto(mp, min_char, nome_arquivo, 0);
    }

    // Retorna o número mínimo de caracters
    return (min_char);

}


//////////////////////////////////////
//////INTERVALO ENTRA RANKING/////////
//////////////////////////////////////

void intervalo_rank(Mapa *mp, char *nome_arquivo)
{
    yellow();
    printf("Digite quantidade mínima de palavras:\n");
    reset();

    // Recebe quantidade mínima de palavras
    int qtd_min = filtraInteiro();

    printf("\n");
    yellow();
    printf("Digite quantidade máxima de palavras:\n");
    reset();

    // Recebe quantidade máxima de palavras
    int qtd_max = filtraInteiro();
    system("cls");

    // Caso quantidade mínima ou máximas sejam inválidas
    if ((qtd_min <= 0) || (qtd_max <= 0))
    {
        // Mensagem de erro
        red();
        printf("Quantidade mínima ou máxima inválidas!\n\n");
        reset();

        // Pausa e limpa tela
        system("pause");
        system("cls");

        // Retorna para menu
        return;
    }

    // Caso quantidade mínima seja definida como maior que quantidade máxima
    else if (qtd_min > qtd_max)
    {
        // Mensagem de erro
        red();
        printf("            Números inválidos!\n\n");
        reset();

        yellow();
        printf("Quantidade mínima maior que quantidade máxima!\n\n");
        reset();

        // Pausa e limpa tela
        system("pause");
        system("cls");

        // Retorna para menu
        return;
    }

    // Exibe rank, com um intervalo entre qtd_min e qtd_max
    exibe_rank(mp, qtd_min, qtd_max, nome_arquivo);
}


//////////////////////////////////////
//////////////PRINTA MENU/////////////
//////////////////////////////////////

void print_menu()
{
    yellow();
    printf("  Escolha uma das opções abaixo\n");
    reset();

    yellow();
    printf(" _______________________________\n");
    reset();

    yellow();
    printf("| |                             |\n");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf("1");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Ler arquivo txt             ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf("2");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Exibir ranking completo     ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf("3");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Exibir intervalo de ranking ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf("4");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Buscar palavra              ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf("5");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Opções                      ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    green();
    printf("6");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Atualizar arquivo           ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    red();
    printf("7");
    reset();

    yellow();
    printf("|");
    reset();

    red();
    printf(" Sair                        ");
    reset();

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|_|_____________________________|\n\n");
    reset();
}

