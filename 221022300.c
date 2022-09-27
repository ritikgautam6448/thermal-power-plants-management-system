//importacao de bibliotecas padrao + biblioteca propria (221022300.h);
#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "221022300.h"

//metodo main, contendo o menu de escolha, que chama uma das 7 funcoes basicas da biblioteca;
int main()
{
    //funcao da biblioteca padrao locale.h para inclusao dos caracteres especiais da lingua portuguesa;
    setlocale(LC_ALL, "Portuguese");

    int opc;

    instrucoes();

    do
    {
        //fazer funcao de abertura do programa (cabecalho de introducao);

        limpaTela();
        header();

        printf(" MENU DE OPÇÕES: ");

        printf("\n 1) Cadastrar Usina ");
        printf("\n 2) Cadastrar Consumidor ");
        printf("\n 3) Cadastrar Contrato entre Consumidor e Usina ");
        printf("\n 4) Consultar Usina Cadastrada ");
        printf("\n 5) Consultar Consumidor Cadastrado ");
        printf("\n 6) Excluir Usina ");
        printf("\n 7) Excluir Consumidor ");
        printf("\n 8) Encerrar Programa \n ");

        printf("\n Digite uma opção: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            cadastroU();
            break;

        case 2:
            cadastroCs();
            break;

        case 3:
            cadastroCt();
            break;

        case 4:
            pesquisarU();
            break;

        case 5:
            pesquisarCs();
            break;

        case 6:
            excluirU();
            break;

        case 7:
            excluirCs();
            break;

        case 8:
            finalizador();
            break;

        default:
            printf(" Opção inválida! \n");
            getch();
            break;
        };
    }
    while(opc != 8);
}
