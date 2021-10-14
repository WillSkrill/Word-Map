#include "mapa.h"
#include "ranking.h"

int main()
{
    int min_char = 1; // Caracter que recebe o tamanho mínimo das palavras

    // Nome do arquivo com no máximo 128 caracteres
    char nome_arquivo[129];
    memset(nome_arquivo, '\0', sizeof(nome_arquivo));

    setlocale(LC_ALL, "Portuguese");
    int menu; // Variável para receber opção desejada do usuário

    // Cria mapa
    Mapa mp;

    // Inicia mapa com 0 e aloca 10 "itens"
    inicia_mapa(&mp);

    // Menu principal
    for (;;)
    {
        // Limpa tela
        system("cls");

        // Printa menu principal
        print_menu();

        // Recebe intput do usuário e filtra (caso o usuário digite algo que não seja um inteiro)
        menu = filtraInteiro();

        // Limpa tela
        system("cls");

        switch (menu)
        {
            // Lê arquivo txt
            case 1:
                recebe_texto(&mp, min_char, nome_arquivo, 1);
            break;

            // Exibe ranking completo
            case 2:
                exibe_rank(&mp, 1, 10000000, nome_arquivo);
             break;

            // Intervalo de ranking
            case 3:
                intervalo_rank(&mp, nome_arquivo);
             break;

            // Procura palavra e printa quantidade
            case 4:
                palavra_procura(&mp);
             break;

            // Defini mínimo de caracteres para palavras na hora de ler .txt
            case 5:
                min_char = opcoes(&mp, nome_arquivo);
             break;

            // Fecha programa
            case 6:
                green();
                printf("     Arquivo atualizado com sucesso!\n");
                reset();

                // Atualiza arquivo
                recebe_texto(&mp, min_char, nome_arquivo, 0);
             break;

            // Fecha programa
            case 7:
                return 0;
             break;

            // Caso o usuário digite um número/input inexistente no menu
            default:
               // Printa menu principal
               print_menu();

               // Mensagem de erro
               red();
               printf("Digite algo que corresponda a uma opção existente!\n\n");
               reset();

               // Pausa e limpa a tela
               system("pause");
               system("cls");
            break;
        }
    }
}
