#include "mapa.h"
#include "ranking.h"
#include <ctype.h>

//////////////////////////////////////
//////////////L� ARQUIVO//////////////
//////////////////////////////////////

void recebe_texto(Mapa *mp, int min_char, char *arquivo, int tipo)
{
    // Reseta mapa caso j� tenha lido um arquivo anteriormente
    libera_mapa(mp);

    // Cria mapa zerado
    inicia_mapa(mp);

    int total_palavras = 0; // Cria vari�vel que ir� guardar total de palavras presente no arquivo
    char letra;  // Char que ler� letra por letra do arquivo txt
    int verif = 0;  // Verificador, caso '1' cria novo termo, caso '0' encrementa em termo existente


    // Cria buffer palavra com todos os espa�os com '\0'
    char palavra[64]; // Palavras de no m�ximo 64 caracteres
    memset(palavra, '\0', sizeof palavra);

    // Caso fun��o recebe_texto() tenha sido chamada na primeira op��o do menu
    if (tipo == 1)
    {
        yellow();
        printf("Digite o nome do arquivo (mais a extens�o .txt) que deseja ler:\n\n");
        reset();

        // Recebe nome do arquivo que deve ser lido e retira '\n' da string
        fgets(arquivo, 129 * sizeof(char), stdin); // Tamanho m�ximo do nome do arquivo de 128 caracteres
        arquivo[strcspn(arquivo, "\n")] = 0;

        system("cls");
    }


    // Abre arquivo txt em modo "read"
    FILE *txt;
    txt = fopen(arquivo, "r");

    // Caso arquivo n�o tenha sido encontrado
    if (txt == NULL)
    {
        if (tipo==1)
        {
            // Mensagem de erro
            red();
            printf("Arquivo n�o encontrado!\n\n");
            reset();
            system("pause");
            system("cls");
        }

        // Caso fun��o recebe_texto() tenha sido chamada em op��es() ou em "Atualizar arquivo" no menu
        else
        {
            system("pause");
            system("cls");
        }

        // Sai da fun��o
        return;
    }

    // Roda loop enquanto n�o encontra final do arquivo e envia palavra por palavras para as fun��es incrementa() ou insere_termo()
    for (int loop = 0; loop == 0;)
    {
        // Recebe proximo 'char' do arquivo .txt
        letra = fgetc(txt);
        // Se letra for mai�scula, coloca como min�scula
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

        // Caso encontre um espa�o vazio
        else if ((letra == ' ') || (letra == EOF) || (letra == '\n'))
        {
            // Verifica se palavra possui tamanho estipulado em "opcoes()"
            if (strlen(palavra) >= min_char)
            {
                // Caso j� exista uma 'Struct Item' desta palavra, acrescenta +1 no contador e retorna 0
                // Caso ainda n�o exista uma 'Struct Item' desta palavra retorna 1
                verif = incrementa(mp, palavra);

                // Caso 'verif==1' (indicando que palavra ainda n�o possui uma 'Struct Item')
                if (verif)
                {
                    // Cria uma nova 'Struct Item' para a palavra em espec�fico
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
            // Loop = 1, indicando que j� leu todas as palavras e deve parar a repeti��o (for)
            loop = 1;
        }
    }

    // Fecha arquivo
    fclose(txt);

    // // Caso fun��o recebe_texto() tenha sido chamada em "Ler arquivo" no menu
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

    // Pausa e limpa tela antes de sair da fun��o
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
    int verif[mp->total]; // Cria vetor para guardar os maiores �ndices em ordem decrescente (indicando que n�o devem ser lidos novamente)

    // Preenche struct verif com '-1'
    for (int t = 0; t < mp->total; t++)
    {
        verif[t] = -1;
    }

    // Repete at� printar todos os termos e contadores em ordem decrescente
    for (int x=0; x < mp->total; x++)
    {
        // Chama fun��o que retorna o maior �ndice atual e guarda maior indice anterior para n�o ser lido anteriormente
        maior_indice = retorna_indice(mp, verif, x);

        // Caso termo esteja entre a quantidade m�nima e m�xima de repeti��es definida
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

    // Pausa e limpa a tela antes de sair da fun��o
    system("pause");
    system("cls");
}


//////////////////////////////////////
/////////RETORNA MAIOR INDICE/////////
//////////////////////////////////////

// Esta fun��o serve de apoio para escrever o ranking em ordem decrescente
// Ela verifica qual o �ndice que possui maior contador
// E certifica de que o �ndice anterior n�o seja lido novamente (o colocando dentro do vetor verif[] recebido)
// O vetor verif anteriormente � preenchido apenas com '-1'

int retorna_indice(Mapa *mp, int *verif, int x)
{
    int maior_indice = 0;
    int maior_num = 0;
    int teste;

    // Repete at� ler todas as structs 'Item'
    for (int z=0 ; z < mp->total; z++)
    {
        // reseta vari�vel teste
        teste = 0;

        // Testa para ver se mp->lista[z] j� foi usado (L� todas as posi��es de (verif[])
        for (int cont = 0, finaliza =0; cont < mp->total && teste != 1 && finaliza == 0; cont++)
        {
            // Se verif = -1, finaliza repeti��o
            if (verif[cont] == -1)
            {
                finaliza = 1; // Caso verif[] j� esteja lendo uma posi��o n�o utilizada, finaliza = 1
            }

            // Se verif = n�mero do contador, teste = 1, definindo que palavra j� foi utilizada anteriormente
            if (verif[cont] == z)
            {
                teste = 1; // Indica que �ndice 'z' j� foi utilizado antes
            }
        }

        // Se o �ndice atual 'z' � maior que o maior_num anterior e se teste for diferente de 1 (indicando que incide 'z' n�o foi usado anteriormente
        if ((mp->lista[z]->conta > maior_num) && (teste != 1))
        {
            maior_indice = z; // Recebe o �ndice de maior n�mero (caso o contador seja o maior lido at� agora)
            maior_num = mp->lista[z]->conta; // Recebe o n�mero do contador do �ndice 'z'
        }
    }
    // Guarda o maior �ndice lido no vetor verif[x] para n�o l�-lo novamente depois
    verif[x] = maior_indice;
    // Retorna o maior �ndice
    return(maior_indice);
}


//////////////////////////////////////
///////////PROCURA PALAVRA////////////
//////////////////////////////////////

void palavra_procura(Mapa *mp)
{
    int cont; // �ndice da palavra buscada
    char palavra[32]; // Buffer para palavra

    green();
    printf("Digite a palavra que deseja buscar:\n");
    reset();
    red();
    printf("   Use '-1' para voltar ao menu.\n\n");
    reset();

    // Roda infinito, mas para quando usu�rio digitar "-1"
    for (;;)
    {
        // Recebe palavra que deve ser buscada
        fgets(palavra, sizeof palavra, stdin);
        // Apaga o '\n' da string palavra (por causa do fgets)
        palavra[strcspn(palavra, "\n")] = 0;

        // Deixa palavra apenas com caracteres min�sculos
        for (int ler = 0; ler < strlen(palavra); ler++)
        {
            palavra[ler] = tolower(palavra[ler]);
        }

        // Verifica se palara = '-1', para finalizar opera��o
        if (strcmp(palavra, "-1") == 0)
        {
            // Limpa tela
            system("cls");

            green();
            printf("Opera��o finalizada com sucesso!\n\n");
            reset();

            // Pausa e limpa tela
            system("pause");
            system("cls");

            // Volta para menu principal
            return;
        }

        // Recebe �ndice de palavra desejada, caso palavra n�o seja encontrada, cont = -1
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

        // Caso n�o tenha encontrado a palavra
        else
        {
            // Limpa tela
            system("cls");

            // Mensagem de erro
            red();
            printf("Palavra digitada n�o encontrada!\n");
            printf("   Por favor, tente novamente.\n\n");
            reset();

            // Pausa e limpa a tela
            system("pause");
            system("cls");

            // Printa mensagem inicial da fun��o
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
///////////////OP��ES/////////////////
//////////////////////////////////////

int opcoes(Mapa *mp, char *nome_arquivo)
{
    yellow();
    printf("Digite o n�mero m�nimo de caracteres a considerar:\n\n");
    reset();

    // Recebe o m�nimo de caracteres a se considerar para ler o txt
    int min_char = filtraInteiro();

    // Limpa tela
    system("cls");

    // Caso usu�rio digite um n�mero v�lido
    if (min_char > 0)
    {
        green();
        printf("     Opera��o finalizada com sucesso!\n");
        reset();

        // Chama fun��o recebe_texto() para atualizar as palavras lidas
        recebe_texto(mp, min_char, nome_arquivo, 0);
    }

    // Casou o usu�rio digite algo inv�lido
    else
    {
        // Mensagem de erro
        red();
        printf("         N�mero inserido inv�lido!\n");
        reset();

        yellow();
        printf("N�mero m�nimo de caracteres definido para 1.\n\n");
        reset();

        // Define m�nimo de caracteres para 1
        min_char = 1;

        system("pause");
        system("cls");

        // Chama fun��o recebe testo, lendo todas as palavras
        recebe_texto(mp, min_char, nome_arquivo, 0);
    }

    // Retorna o n�mero m�nimo de caracters
    return (min_char);

}


//////////////////////////////////////
//////INTERVALO ENTRA RANKING/////////
//////////////////////////////////////

void intervalo_rank(Mapa *mp, char *nome_arquivo)
{
    yellow();
    printf("Digite quantidade m�nima de palavras:\n");
    reset();

    // Recebe quantidade m�nima de palavras
    int qtd_min = filtraInteiro();

    printf("\n");
    yellow();
    printf("Digite quantidade m�xima de palavras:\n");
    reset();

    // Recebe quantidade m�xima de palavras
    int qtd_max = filtraInteiro();
    system("cls");

    // Caso quantidade m�nima ou m�ximas sejam inv�lidas
    if ((qtd_min <= 0) || (qtd_max <= 0))
    {
        // Mensagem de erro
        red();
        printf("Quantidade m�nima ou m�xima inv�lidas!\n\n");
        reset();

        // Pausa e limpa tela
        system("pause");
        system("cls");

        // Retorna para menu
        return;
    }

    // Caso quantidade m�nima seja definida como maior que quantidade m�xima
    else if (qtd_min > qtd_max)
    {
        // Mensagem de erro
        red();
        printf("            N�meros inv�lidos!\n\n");
        reset();

        yellow();
        printf("Quantidade m�nima maior que quantidade m�xima!\n\n");
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
    printf("  Escolha uma das op��es abaixo\n");
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

    printf(" Op��es                      ");

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

