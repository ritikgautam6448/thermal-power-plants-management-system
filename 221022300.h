//definindo o arquivo como um c header;
#ifndef biblioteca
#define biblioteca

//importação de bibliotecas;
#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//alguns #define necessarios para as funcoes;
#define MAX_ID 22
#define MAX_NOME 50

//criacao de um registro para agrupar os dados de uma data;
typedef struct data DATA;
struct data
{
    int dia;
    int mes;
    int ano;
};

//criacao de um registro para agrupar os dados de uma usina;
typedef struct usina USINA;
struct usina
{
    char cnpj[MAX_ID];
    char nome[MAX_NOME];
    int potencia_estimada;
    DATA data_inicio_operacao;
};

//criacao de um registro para agrupar os dados de um consumidor;
typedef struct consumidor CONSUMIDOR;
struct consumidor
{
    char id[MAX_ID];
    char nomeCon[MAX_NOME];
};

//criacao de um registro para agrupar os dados de um contrato;
typedef struct contrato CONTRATO;
struct contrato
{
    char cnpj[MAX_ID];
    char id[MAX_ID];
    int potencia_contratada;
    DATA data_inicio_contrato;
};

//prototipos das 7 funcoes basicas (retorno direto do menu);
void cadastroU();
void cadastroCs();
void cadastroCt();

void pesquisarU();
void pesquisarCs();

void excluirU();
void excluirCs();

//prototipo das funcoes auxiliares;
void limpaTela();
void header();
void instrucoes();
void finalizador();

//prototipo das funcoes verificadoras;
int verificadorCpf();
int verificadorCnpj();
int verificarData();

//funcao que faz o cadastro de uma usina;
//1) Cadastrar Usina;
void cadastroU()
{
    FILE *arquivo;
    FILE *arquivo2;
    FILE *arquivo3;

    USINA usn, usnLer;

    do
    {
        arquivo = fopen("usina.txt", "a+b");
        rewind(arquivo);
        if(arquivo == NULL)
        {
            limpaTela();
            printf("\n Não foi possível abrir o arquivo.\n");
        }
        else
        {
            limpaTela();
            fflush(stdin);
            printf(" 1. CADASTRO DE USINA \n");

            fflush(stdin);
            printf(" Digite o nome da usina: ");
            gets(usn.nome);

            arquivo2 = fopen("usina.txt", "rb");
            if(arquivo2 == NULL)
            {
                limpaTela();
                printf("\n Não foi possível abrir o arquivo.\n");
            }
            else
            {
                while(fread(&usnLer, sizeof(USINA), 1, arquivo2) == 1)
                {
                    if(strcmp(usn.nome, usnLer.nome) == 0)
                    {
                        printf("\n A USINA INFORMADA JÁ SE ENCONTRA CADASTRADA! ");

                        fclose(arquivo);
                        fclose(arquivo2);

                        getch();
                        return;
                    }
                }
            }
            fclose(arquivo2);

            fflush(stdin);
            printf(" Digite o CNPJ da usina: ");
            gets(usn.cnpj);

            char *pChecker = usn.cnpj;
            if(verificadorCnpj(pChecker) == 0)
            {
                arquivo3 = fopen("usina.txt", "rb");
                if(arquivo3 == NULL)
                {
                    printf("Não foi possível abrir o arquivo.\n");
                }
                else
                {
                    while(fread(&usnLer, sizeof(USINA), 1, arquivo3) == 1)
                    {
                        if(strcmp(usn.cnpj, usnLer.cnpj) == 0)
                        {
                            printf("\n A USINA INFORMADA JÁ SE ENCONTRA CADASTRADA! ");

                            fclose(arquivo);
                            fclose(arquivo3);

                            getch();
                            return;
                        }
                    }
                }
                fclose(arquivo3);

                fflush(stdin);
                printf(" Digite a potência estimada da usina (MW): ");
                scanf("%d", &usn.potencia_estimada);

                if(usn.potencia_estimada > 0)
                {
                    fflush(stdin);
                    printf(" Digite a data de início de operação da usina (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &usn.data_inicio_operacao.dia, &usn.data_inicio_operacao.mes, &usn.data_inicio_operacao.ano);

                    int *pDia = &usn.data_inicio_operacao.dia;
                    int *pMes = &usn.data_inicio_operacao.mes;
                    int *pAno = &usn.data_inicio_operacao.ano;

                    if(verificarData(pDia, pMes, pAno) == 0)
                    {
                        fwrite(&usn, sizeof(USINA), 1, arquivo);

                        printf("\n Deseja cadastrar outra usina? (s/n) ");
                        fclose(arquivo);
                    }
                    else
                    {
                        printf("\n A DATA INSERIDA É INVÁLIDA! ");
                        printf("\n Deseja tentar novamente? (s/n) ");

                        fclose(arquivo);
                    }
                }
                else
                {
                    printf("\n UMA USINA NÃO PODE TER POTÊNCIA MENOR OU IGUAL A ZERO! ");
                    printf("\n Deseja tentar novamente? (s/n) ");

                    fclose(arquivo);
                }

            }
            if(verificadorCnpj(pChecker) == 1)
            {
                printf("\n O CNPJ DE USINA INSERIDO É INVÁLIDO! ");
                printf("\n Deseja tentar novamente? (s/n) ");

                fclose(arquivo);
            }
        }
    }
    while(getche() == 's');
}

//funcao que faz o cadastro de um consumidor;
//2) Cadastrar Consumidor;
void cadastroCs()
{
    FILE* arquivo4;
    FILE* arquivo5;
    FILE* arquivo6;

    CONSUMIDOR csm, csmLer;

    int pessoa;
    limpaTela();

    printf(" 2. CADASTRO DE CONSUMIDOR \n");
    printf(" 1) Cadastrar Pessoa Física (PF) ");
    printf("\n 2) Cadastrar Pessoa Jurídica (PJ)\n ");

    printf("\n Digite uma opção: ");
    scanf("%d", &pessoa);

    switch (pessoa)
    {
    case 1:

        arquivo4 = fopen("consumidor.txt", "a+b");
        rewind(arquivo4);
        if(arquivo4 == NULL)
        {
            limpaTela();
            printf("\n Não foi possível abrir o arquivo.\n");
        }
        else
        {
            fflush(stdin);
            limpaTela();

            printf(" 2. CADASTRO DE CONSUMIDOR \n");
            printf(" Digite o nome do consumidor: ");
            gets(csm.nomeCon);

            arquivo5 = fopen("consumidor.txt", "rb");
            if(arquivo5 == NULL)
            {
                limpaTela();
                printf("\n Não foi possível abrir o arquivo.\n");
            }
            else
            {
                while(fread(&csmLer, sizeof(CONSUMIDOR), 1, arquivo5) == 1)
                {
                    if(strcmp(csm.nomeCon, csmLer.nomeCon) == 0)
                    {
                        printf("\n O CONSUMIDOR INFORMADO JÁ SE ENCONTRA CADASTRADO! ");

                        fclose(arquivo4);
                        fclose(arquivo5);

                        getch();
                        return;
                    }
                }
            }
            fclose(arquivo5);

            fflush(stdin);
            printf(" Digite o CPF do consumidor: ");
            gets(csm.id);

            char *pChecker = csm.id;
            if(verificadorCpf(pChecker) == 0)
            {
                arquivo6 = fopen("consumidor.txt", "rb");
                if(arquivo6 == NULL)
                {
                    printf("\n Não foi possível abrir o arquivo.\n");
                }
                else
                {
                    while(fread(&csmLer, sizeof(CONSUMIDOR), 1, arquivo6) == 1)
                    {
                        if(strcmp(csm.id, csmLer.id) == 0)
                        {
                            printf("\n O CONSUMIDOR INFORMADO JÁ SE ENCONTRA CADASTRADO! ");

                            fclose(arquivo4);
                            fclose(arquivo6);

                            getch();
                            return;
                        }
                    }
                }
                fclose(arquivo6);

                fwrite(&csm, sizeof(CONSUMIDOR), 1, arquivo4);

                printf("\n Deseja cadastrar outro Consumidor? (s/n) ");
                fclose(arquivo4);

                if(getche() == 's')
                {
                    cadastroCs();
                    return;
                }
                else
                {
                    return;
                }
            }
            if(verificadorCpf(pChecker) == 1)
            {
                printf("\n O CNPJ DE CONSUMIDOR INSERIDO É INVÁLIDO! ");
                printf("\n Deseja tentar novamente? (s/n) ");

                fclose(arquivo4);
                fclose(arquivo6);
            }
        }
        break;

    case 2:

        arquivo4 = fopen("consumidor.txt", "a+b");
        rewind(arquivo4);
        if(arquivo4 == NULL)
        {
            limpaTela();
            printf("\n Não foi possível abrir o arquivo.\n");
        }
        else
        {
            fflush(stdin);
            limpaTela();

            printf(" 2. CADASTRO DE CONSUMIDOR \n");
            printf(" Digite o nome do consumidor: ");
            gets(csm.nomeCon);

            arquivo5 = fopen("consumidor.txt", "rb");
            if(arquivo5 == NULL)
            {
                limpaTela();
                printf("\n Não foi possível abrir o arquivo.\n");
            }
            else
            {
                while(fread(&csmLer, sizeof(CONSUMIDOR), 1, arquivo5) == 1)
                {
                    if(strcmp(csm.nomeCon, csmLer.nomeCon) == 0)
                    {
                        printf("\n O CONSUMIDOR INFORMADO JÁ SE ENCONTRA CADASTRADO! ");

                        fclose(arquivo4);
                        fclose(arquivo5);

                        getch();
                        return;
                    }
                }
            }
            fclose(arquivo5);

            fflush(stdin);
            printf(" Digite o CNPJ do consumidor: ");
            gets(csm.id);

            char *pChecker = csm.id;
            if(verificadorCnpj(pChecker) == 0)
            {
                arquivo6 = fopen("consumidor.txt", "rb");
                if(arquivo6 == NULL)
                {
                    printf("\n Não foi possível abrir o arquivo.\n");
                }
                else
                {
                    while(fread(&csmLer, sizeof(CONSUMIDOR), 1, arquivo6) == 1)
                    {
                        if(strcmp(csm.id, csmLer.id) == 0)
                        {
                            printf("\n O CONSUMIDOR INFORMADO JÁ SE ENCONTRA CADASTRADO! ");

                            fclose(arquivo4);
                            fclose(arquivo6);

                            getch();
                            return;
                        }
                    }
                }
                fclose(arquivo6);

                fwrite(&csm, sizeof(CONSUMIDOR), 1, arquivo4);

                printf("\n Deseja cadastrar outro Consumidor? (s/n) ");
                fclose(arquivo4);

                if(getche() == 's')
                {
                    cadastroCs();
                    return;
                }
                else
                {
                    return;
                }
            }
            if(verificadorCnpj(pChecker) == 1)
            {
                printf("\n O CPF DE CONSUMIDOR INSERIDO É INVÁLIDO! ");
                printf("\n Deseja tentar novamente? (s/n) ");

                fclose(arquivo4);
                fclose(arquivo6);
            }
        }

        break;

    default:
        printf(" Opção inválida! \n");
        getch();
        break;
    };
}

//funcao que faz o cadastro de um contrato entre usina e consumidor;
//3) Cadastrar Contrato entre Consumidor e Usina;
void cadastroCt()
{
    FILE *arquivo7;
    FILE *arquivo8;
    FILE *arquivo9;
    FILE *arquivoX;
    FILE *arquivoXI;

    CONTRATO ctt, cttAux;
    CONSUMIDOR csm, cttLerCs;
    USINA cttLerU;

    int cont;
    cont = 0;

    arquivo7 = fopen("contrato.txt", "a+b");
    if(arquivo7 == NULL)
    {
        limpaTela();
        printf(" Não foi possível abrir o arquivo. ");
        fclose(arquivo7);
        getch();
        return;
    }
    else
    {
        limpaTela();
        fflush(stdin);
        printf(" 3. CADASTRO DE CONTRATO \n");

        printf(" Digite o CNPJ da Usina: ");
        gets(ctt.cnpj);

        arquivo8 = fopen("usina.txt", "rb");
        if(arquivo8 == NULL)
        {
            printf("\n AINDA NÃO HÁ NENHUMA USINA CADASTRADA! \n");
            printf(" Deseja cadastrar uma nova Usina? (s/n) ");

            if(getche() == 's')
            {
                fclose(arquivo7);
                fclose(arquivo8);

                cadastroU();

                return;
            }
        }
        else
        {
            arquivo9 = fopen("consumidor.txt", "rb");
            if(arquivo9 == NULL)
            {
                printf("\n AINDA NÃO HÁ NENHUM CONSUMIDOR CADASTRADO! \n");
                printf(" Deseja cadastrar um novo Consumidor? (s/n) ");

                if(getche() == 's')
                {
                    fclose(arquivo7);
                    fclose(arquivo8);
                    fclose(arquivo9);

                    cadastroCs();

                    return;
                }
                else
                {
                    fclose(arquivo7);
                    fclose(arquivo8);
                    fclose(arquivo9);

                    return;
                }
            }
            else
            {
                while(fread(&cttLerU, sizeof(USINA), 1, arquivo8) == 1)
                {
                    if(strcmp(ctt.cnpj, cttLerU.cnpj) == 0)
                    {
                        printf(" Digite o CPF/CNPJ do Consumidor: ");
                        gets(ctt.id);

                        arquivoX = fopen("consumidor.txt", "rb");
                        arquivoXI = fopen("contrato.txt", "rb");

                        while(fread(&ctt, sizeof(CONTRATO), 1, arquivoXI) == 1)
                        {
                            if(strcmp(cttLerU.cnpj, ctt.cnpj) == 0)
                            {

                                while(fread(&cttLerCs, sizeof(CONSUMIDOR), 1, arquivoX) == 1);
                                {
                                    if(strcmp(ctt.id, cttLerCs.id) == 0)
                                    {
                                        cont = cont + ctt.potencia_contratada;
                                    }
                                }
                            }
                        }
                        fclose(arquivoX);
                        fclose(arquivoXI);

                        cont = cttLerU.potencia_estimada - cont;

                        while(fread(&cttLerCs, sizeof(CONSUMIDOR), 1, arquivo9) == 1)
                        {
                            if(strcmp(ctt.id, cttLerCs.id) == 0)
                            {
                                fflush(stdin);
                                printf(" Digite a potência a ser contratada (total disponível: %d MW): ", cont);
                                scanf("%d", &ctt.potencia_contratada);

                                if(ctt.potencia_contratada > 0 && ctt.potencia_contratada <= cont)
                                {
                                    fflush(stdin);
                                    printf(" Digite a data de início do contrato entre a usina e o consumidor (DD/MM/AAAA): ");
                                    scanf("%d/%d/%d", &ctt.data_inicio_contrato.dia, &ctt.data_inicio_contrato.mes, &ctt.data_inicio_contrato.ano);

                                    int *pDi = &ctt.data_inicio_contrato.dia;
                                    int *pMe = &ctt.data_inicio_contrato.mes;
                                    int *pAn = &ctt.data_inicio_contrato.ano;

                                    if(verificarData(pDi, pMe, pAn) == 0)
                                    {
                                        fwrite(&ctt, sizeof(CONTRATO), 1, arquivo7);

                                        printf("\n Deseja cadastrar outro contrato? (s/n) ");
                                    }
                                    else
                                    {
                                        printf("\n A DATA INSERIDA É INVÁLIDA! ");
                                        printf("\n Deseja tentar novamente? (s/n) ");
                                    }

                                    if(getche() == 's')
                                    {
                                        fclose(arquivo7);
                                        fclose(arquivo8);
                                        fclose(arquivo9);

                                        cadastroCt();
                                        return;
                                    }
                                    else
                                    {
                                        fclose(arquivo7);
                                        fclose(arquivo8);
                                        fclose(arquivo9);

                                        return;
                                    }
                                }
                                else
                                {
                                    printf("\n A POTÊNCIA CONTRATADA DEVE SER MAIOR QUE ZERO E MENOR QUE A POTÊNCIA RESTANTE DA USINA ");
                                    printf("\n Deseja tentar efetuar o cadastro novamente? (s/n) ");

                                    fclose(arquivo7);
                                    fclose(arquivo8);
                                    fclose(arquivo9);

                                    if(getche() == 's')
                                    {
                                        cadastroCt();
                                        return;
                                    }
                                    else
                                    {
                                        return;
                                    }
                                }
                            }
                        }
                        if(strcmp(ctt.id, cttLerCs.id)!= 0)
                        {
                            printf("\n O CONSUMIDOR INFORMADO NÃO SE ENCONTRA CADASTRADO! ");
                            printf("\n Deseja fazer o cadastro de um novo Consumidor? (s/n) ");

                            if(getche() == 's')
                            {
                                fclose(arquivo7);
                                fclose(arquivo8);
                                fclose(arquivo9);

                                cadastroCs();

                                return;
                            }
                            else
                            {
                                fclose(arquivo7);
                                fclose(arquivo8);
                                fclose(arquivo9);

                                return;
                            }
                        }
                    }
                }
                if(strcmp(ctt.cnpj, cttLerU.cnpj) != 0)
                {
                    printf("\n A USINA INFORMADA NÃO SE ENCONTRA CADASTRADA! ");
                    printf("\n Deseja fazer o cadastro de uma nova Usina? (s/n) ");

                    if(getche() == 's')
                    {
                        fclose(arquivo7);
                        fclose(arquivo8);

                        cadastroU();

                        return;
                    }
                    else
                    {
                        fclose(arquivo7);
                        fclose(arquivo8);

                        return;
                    }
                }
            }
            fclose(arquivo9);
        }
        fclose(arquivo8);
    }
    fclose(arquivo7);
}

//funcao que faz a pesquisa de uma usina;
//4) Consultar Usina Cadastrada;
void pesquisarU()
{
    FILE *arquivo4;
    FILE *arquivo5;
    FILE *arquivo6;
    FILE *arquivo7;

    CONSUMIDOR csm;
    CONTRATO ctt;
    USINA usn;

    int cont = 0;
    char cnpj[MAX_ID];

    arquivo4 = fopen("usina.txt", "rb");
    arquivo5 = fopen("contrato.txt", "rb");
    arquivo6 = fopen("consumidor.txt", "rb");

    arquivo7 = fopen("contrato.txt", "rb");

    rewind(arquivo4);
    rewind(arquivo5);
    rewind(arquivo6);

    if(arquivo4 == NULL)
    {
        limpaTela();
        printf(" AINDA NÃO HÁ NENHUMA USINA CADASTRADA! \n");
        printf(" Deseja cadastrar uma nova Usina? (s/n) ");
        if(getche() == 's')
        {
            fclose(arquivo4);
            cadastroU();

            return;
        }
    }
    else
    {
        limpaTela();
        fflush(stdin);
        printf(" 4. CONSULTAR USINA CADASTRADA \n");
        printf(" Digite o CNPJ da usina que deseja consultar: ");
        gets(cnpj);

        while(fread(&usn, sizeof(USINA), 1, arquivo4) == 1)
        {
            if(strcmp(cnpj, usn.cnpj) != 0)
            {
                printf("\n A USINA INFORMADA NÃO SE ENCONTRA CADASTRADA! ");
                printf("\n Deseja fazer o cadastro de uma nova Usina? (s/n) ");

                if(getche() == 's')
                {
                    rewind(arquivo4);
                    fclose(arquivo4);

                    rewind(arquivo5);
                    fclose(arquivo5);

                    rewind(arquivo6);
                    fclose(arquivo6);

                    fclose(arquivo7);

                    pesquisarU();

                    return;
                }
                else
                {
                    rewind(arquivo4);
                    fclose(arquivo4);

                    rewind(arquivo5);
                    fclose(arquivo5);

                    rewind(arquivo6);
                    fclose(arquivo6);

                    fclose(arquivo7);

                    return;
                }
            }
            else
            {
                while(fread(&ctt, sizeof(CONTRATO), 1, arquivo7) == 1)
                {
                    if(strcmp(cnpj, ctt.cnpj) == 0)
                    {
                        while(fread(&csm, sizeof(CONSUMIDOR), 1, arquivo6) == 1);
                        {
                            if(strcmp(ctt.id, csm.id) == 0)
                            {
                                cont = cont + ctt.potencia_contratada;
                            }
                        }
                    }
                }

                cont = usn.potencia_estimada - cont;

                printf("\n Nome da Usina: %s\n", usn.nome);
                printf(" CNPJ de %s: %s\n", usn.nome, usn.cnpj);
                printf(" Potência restante de %s: %d MW\n", usn.nome, cont);
                printf(" Data de início da operação de %s: %d/%d/%d\n", usn.nome, usn.data_inicio_operacao.dia, usn.data_inicio_operacao.mes, usn.data_inicio_operacao.ano);

                while(fread(&ctt, sizeof(CONTRATO), 1, arquivo5) == 1)
                {
                    if(strcmp(usn.cnpj, ctt.cnpj) == 0)
                    {
                        while(fread(&csm, sizeof(CONSUMIDOR), 1, arquivo6) == 1);
                        {
                            if(strcmp(ctt.id, csm.id) == 0)
                            {
                                printf("\n CONTRATO COM %s\n", csm.nomeCon);
                                printf(" Potência contratada: %d MW\n", ctt.potencia_contratada);
                                printf(" Contrato iniciado em %d/%d/%d\n", ctt.data_inicio_contrato.dia, ctt.data_inicio_contrato.mes, ctt.data_inicio_contrato.ano);
                            }
                        }
                    }
                }
                printf("\n Deseja fazer uma nova consulta? (s/n) ");

                rewind(arquivo4);
                fclose(arquivo4);

                rewind(arquivo5);
                fclose(arquivo5);

                rewind(arquivo6);
                fclose(arquivo6);

                fclose(arquivo7);

                if(getche() == 's')
                {
                    pesquisarU();
                }
                return;

            }
        }
    }
    rewind(arquivo4);
    fclose(arquivo4);

    rewind(arquivo5);
    fclose(arquivo5);

    rewind(arquivo6);
    fclose(arquivo6);

    fclose(arquivo7);

    if(getche() == 's')
    {
        pesquisarU();
    }
    return;
}

//funcao que faz a pesquisa de um consumidor;
//5) Consultar Consumidor Cadastrado;
void pesquisarCs()
{
    FILE *arquivo4;
    FILE *arquivo5;
    FILE *arquivo6;

    CONSUMIDOR csm;
    CONTRATO ctt;
    USINA usn;

    char id[MAX_ID];

    arquivo4 = fopen("consumidor.txt", "rb");
    arquivo5 = fopen("contrato.txt", "rb");
    arquivo6 = fopen("usina.txt", "rb");

    if(arquivo4 == NULL)
    {
        limpaTela();
        printf(" AINDA NÃO HÁ NENHUM CONSUMIDOR CADASTRADO! \n");
        printf(" Deseja cadastrar um novo Consumidor? (s/n) ");
        if(getche() == 's')
        {
            fclose(arquivo4);
            cadastroCs();

            return;
        }
    }
    else
    {
        limpaTela();
        fflush(stdin);
        printf(" 5. CONSULTAR CONSUMIDOR CADASTRADO \n");
        printf(" Digite a identificação do consumidor que deseja consultar: ");
        gets(id);

        while(fread(&csm, sizeof(CONSUMIDOR), 1, arquivo4) == 1)
        {
            if(strcmp(id, csm.id) == 0)
            {
                printf("\n Nome do Consumidor: %s\n", csm.nomeCon);
                printf(" Identificação de %s: %s\n", csm.nomeCon, csm.id);

                while(fread(&ctt, sizeof(CONTRATO), 1, arquivo5) == 1)
                {
                    if(strcmp(id, ctt.id) == 0)
                    {
                        while(fread(&usn, sizeof(USINA), 1, arquivo6) == 1);
                        {
                            if(strcmp(ctt.cnpj, usn.cnpj) == 0)
                            {
                                printf("\n CONTRATO COM %s\n", usn.nome);
                                printf(" Potência contratada: %d MW\n", ctt.potencia_contratada);
                                printf(" Contrato iniciado em %d/%d/%d\n", ctt.data_inicio_contrato.dia, ctt.data_inicio_contrato.mes, ctt.data_inicio_contrato.ano);
                            }
                        }
                    }
                }
                printf("\n Deseja fazer uma nova consulta? (s/n) ");

                rewind(arquivo4);
                fclose(arquivo4);

                rewind(arquivo5);
                fclose(arquivo5);

                rewind(arquivo6);
                fclose(arquivo6);

                if(getche() == 's')
                {
                    pesquisarCs();
                }
                return;
            }
            else
            {
                printf("\n O CONSUMIDOR INFORMADO NÃO SE ENCONTRA CADASTRADO! ");
                printf("\n Deseja fazer o cadastro de um novo Consumidor? (s/n) ");
            }
        }
    }
    rewind(arquivo4);
    fclose(arquivo4);

    rewind(arquivo5);
    fclose(arquivo5);

    rewind(arquivo6);
    fclose(arquivo6);

    if(getche() == 's')
    {
        pesquisarCs();
    }
    return;
}

//funcao que exclui o cadastro de uma usina;
//6) Excluir Usina;
void excluirU()
{
    FILE *arquivoVan;
    FILE *arquivoMod;

    FILE *arquivoV;
    FILE *arquivoM;

    USINA usn;
    CONTRATO ctt;
    char cnpj[MAX_ID];

    limpaTela();
    arquivoVan = fopen("usina.txt", "rb");
    arquivoMod = fopen("usinaTemp.txt", "a+b");

    rewind(arquivoVan);
    rewind(arquivoMod);

    arquivoV = fopen("contrato.txt", "rb");
    arquivoM = fopen("contratoTemp.txt", "a+b");

    rewind(arquivoV);
    rewind(arquivoM);

    if(arquivoVan == NULL || arquivoMod == NULL || arquivoV == NULL || arquivoM == NULL)
    {
        limpaTela();
        printf(" Não foi possível abrir o arquivo.\n");
    }
    else
    {
        limpaTela();
        fflush(stdin);
        printf(" 6. EXCLUIR USINA \n");

        printf(" Digite o CNPJ da usina a ser excluída do cadastro: ");
        gets(cnpj);

        while(fread(&usn, sizeof(USINA), 1, arquivoVan) == 1)
        {
            if(strcmp(cnpj, usn.cnpj) != 0)
            {
                fwrite(&usn, sizeof(USINA), 1, arquivoMod);
            }
        }

        while(fread(&ctt, sizeof(CONTRATO), 1, arquivoV) == 1)
        {
            if(strcmp(cnpj, ctt.cnpj) != 0)
            {
                fwrite(&ctt, sizeof(CONTRATO), 1, arquivoM);
            }
        }
    }
    fclose(arquivoV);
    fclose(arquivoM);

    fclose(arquivoVan);
    fclose(arquivoMod);

    remove("contrato.txt");
    rename("contratoTemp.txt", "contrato.txt");

    remove("usina.txt");
    rename("usinaTemp.txt", "usina.txt");

    printf("\n EXCLUSÃO SOLICITADA COM SUCESSO, CASO O DADO EXISTA SERÁ DELETADO DO SISTEMA. \n");

    printf(" Deseja excluir outra Usina? (s/n) ");
    if(getche() == 's')
    {
        excluirU();
        return;
    }
    else
    {
        return;
    }
}

//funcao que exclui o cadastro de um consumidor;
//7) Excluir Consumidor;
void excluirCs()
{
    FILE *arquivoVani;
    FILE *arquivoModi;

    FILE *arquivoV;
    FILE *arquivoM;

    CONTRATO ctt;
    CONSUMIDOR csm;
    char id[MAX_ID];

    limpaTela();
    arquivoVani = fopen("consumidor.txt", "rb");
    arquivoModi = fopen("consumidorTemp.txt", "a+b");

    rewind(arquivoVani);
    rewind(arquivoModi);

    arquivoV = fopen("contrato.txt", "rb");
    arquivoM = fopen("contratoTemp.txt", "a+b");

    rewind(arquivoV);
    rewind(arquivoM);

    if(arquivoVani == NULL || arquivoModi == NULL || arquivoV == NULL || arquivoM == NULL)
    {
        limpaTela();
        printf(" Não foi possível abrir o arquivo.\n");
    }
    else
    {
        limpaTela();
        fflush(stdin);
        printf(" 7. EXCLUIR CONSUMIDOR \n");

        printf(" Digite a identificação do Consumidor a ser excluído do cadastro: ");
        gets(id);

        while(fread(&csm, sizeof(CONSUMIDOR), 1, arquivoVani) == 1)
        {
            if(strcmp(id, csm.id) != 0)
            {
                fwrite(&csm, sizeof(CONSUMIDOR), 1, arquivoModi);
            }
        }

        while(fread(&ctt, sizeof(CONTRATO), 1, arquivoV) == 1)
        {
            if(strcmp(id, ctt.id) != 0)
            {
                fwrite(&ctt, sizeof(CONTRATO), 1, arquivoM);
            }
        }
    }
    fclose(arquivoV);
    fclose(arquivoM);

    fclose(arquivoVani);
    fclose(arquivoModi);

    remove("consumidor.txt");
    rename("consumidorTemp.txt", "consumidor.txt");

    remove("contrato.txt");
    rename("contratoTemp.txt", "contrato.txt");

    printf("\n EXCLUSÃO SOLICITADA COM SUCESSO, CASO O DADO EXISTA SERÁ DELETADO DO SISTEMA. \n");

    printf(" Deseja excluir outro Consumidor? (s/n) ");

    if(getche() == 's')
    {
        excluirU();
        return;
    }
    else
    {
        return;
    }
}

//=====================================================================================================================================================
//funcoes auxiliares;
//criacao da funcao para limpar a tela;
void limpaTela()
{
#if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

//criacao da funcao de um cabecalho visual com nome do programa + relogio;
void header()
{
    time_t dataHora;
    dataHora = time(NULL);
    struct tm tm = *localtime(&dataHora);

    printf(" SISTEMA DE GERAÇÃO COMPARTILHADA \n");
    printf(" Acesso dia %d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf(", às %d:%d.\n\n", tm.tm_hour, tm.tm_min);
}

//criacao da funcao que cria um relogio atualizado + intrucoes de bom uso do programa;
void instrucoes()
{
    header();

    printf(" INSTRUÇÕES DE BOM USO DO SISTEMA DE GERAÇÃO COMPARTILHADA:\n");

    printf(" - Ao digitar nomes, inserir apenas letras, exceto caso o número componha o nome fantasia de uma empresa;\n");
    printf(" - Ao digitar o valor de uma potência energética, insira apenas números positivos maiores que zero;\n");
    printf(" - Ao digitar uma identificação como CPF ou CNPJ, inclua os pontos(.), traços(-), e barras(/);\n");
    printf(" - Ao digitar uma data, use barras, formato: DD/MM/AAAA.\n\n");

    printf(" Pressione qualquer tecla para iniciar a utilização ");
    getch();
    return;
}

void finalizador()
{
    time_t dataHora;
    dataHora = time(NULL);
    struct tm tm = *localtime(&dataHora);

    limpaTela();
    printf(" OBRIGADO POR UTILIZAR O SISTEMA DE GERAÇÃO COMPARTILHADA \n");
    printf(" Uma realização, GDF - Governo do Distrito Federal.\n\n");

    printf(" Seção encerrada às %d:%d", tm.tm_hour, tm.tm_min);
    printf(" do dia %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

//=====================================================================================================================================================
//verificadores
//criacao da funcao que verifica se um cpf eh valido;
int verificadorCpf(char *cpf)
{
    int dgt1, dgt2;

    if((strcmp(cpf,"000.000.000-00") == 0) || (strcmp(cpf,"111.111.111-11") == 0) || (strcmp(cpf,"222.222.222-22") == 0) ||
            (strcmp(cpf,"333.333.333-33") == 0) || (strcmp(cpf,"444.444.444-44") == 0) || (strcmp(cpf,"555.555.555-55") == 0) ||
            (strcmp(cpf,"666.666.666-66") == 0) || (strcmp(cpf,"777.777.777-77") == 0) || (strcmp(cpf,"888.888.888-88") == 0) ||
            (strcmp(cpf,"999.999.999-99") == 0))
    {
        return 1;
    }

    dgt1 = (((((cpf[0] - '0') * 10) + ((cpf[1] - '0') * 9) + ((cpf[2] - '0') * 8) + ((cpf[4] - '0') * 7) + ((cpf[5] - '0') * 6) + ((cpf[6] - '0') * 5) + ((cpf[8] - '0') * 4) + ((cpf[9] - '0') * 3) + ((cpf[10] - '0') * 2)) *10) % 11);

    dgt2 = (((((cpf[0] - '0') * 11) + ((cpf[1] - '0') * 10) + ((cpf[2] - '0') * 9) + ((cpf[4] - '0') * 8) + ((cpf[5] - '0') * 7) + ((cpf[6] - '0') * 6) + ((cpf[8] - '0') * 5) + ((cpf[9] - '0') * 4) + ((cpf[10] - '0') * 3) + ((cpf[12] - '0') * 2)) *10) % 11);

    if(dgt1 != (cpf[12] - '0') || dgt2 != (cpf[13] - '0'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//criacao da funcao que verifica se um cnpj eh valido;
int verificadorCnpj(char *cnpj)
{
    int dgt1, dgt2, dt1, dt2, d1, d2;

    if((strcmp(cnpj,"00.000.000/0000-00") == 0) || (strcmp(cnpj,"11.111.111/1111-11") == 0) || (strcmp(cnpj,"22.222.222/2222-22") == 0) ||
            (strcmp(cnpj,"33.333.333/3333-33") == 0) || (strcmp(cnpj,"44.444.444/4444-44") == 0) || (strcmp(cnpj,"55.555.555/5555-55") == 0) ||
            (strcmp(cnpj,"66.666.666/6666-66") == 0) || (strcmp(cnpj,"77.777.777/7777-77") == 0) || (strcmp(cnpj,"88.888.888/8888-88") == 0) ||
            (strcmp(cnpj,"99.999.999/9999-99") == 0))
    {
        return 1;
    }
    else
    {
        dgt1 = (((cnpj[0] - '0') * 5) + ((cnpj[1] - '0') * 4) + ((cnpj[3] - '0') * 3) + ((cnpj[4] - '0') * 2) + ((cnpj[5] - '0') * 9) + ((cnpj[7] - '0') * 8) + ((cnpj[8] - '0') * 7) + ((cnpj[9] - '0') * 6) + ((cnpj[11] - '0') * 5) + ((cnpj[12] - '0') * 4) + ((cnpj[13] - '0') * 3) + ((cnpj[14] - '0') * 2));
        dt1 = dgt1 % 11;

        if(dt1 >= 2)
        {
            d1 = 11 - dt1;
        }

        if(dt1 < 2)
        {
            d1 = 0;
        }

        dgt2 = ((((cnpj[0] - '0') * 6) + ((cnpj[1] - '0') * 5) + ((cnpj[3] - '0') * 4) + ((cnpj[4] - '0') * 3) + ((cnpj[5] - '0') * 2) + ((cnpj[7] - '0') * 9) + ((cnpj[8] - '0') * 8) + ((cnpj[9] - '0') * 7) + ((cnpj[11] - '0') * 6) + ((cnpj[12] - '0') * 5) + ((cnpj[13] - '0') * 4) + ((cnpj[14] - '0') * 3) + ((cnpj[16] - '0') * 2)) % 11);
        dt2 = dgt2 % 11;

        if(dt2 >= 2)
        {
            d2 = 11 - dt2;
        }

        if(dt2 < 2)
        {
            d2 = 0;
        }

        if(d1 != (cnpj[16] - '0') || d2 != (cnpj[17] - '0'))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

//verificador de data;
int verificarData(int *dia, int *mes, int *ano)
{
    int dd = *dia;
    int mm = *mes;
    int aa = *ano;

    if (aa >= 1900 && aa <= 2022)
    {
        if (mm >= 1 && mm <= 12)
        {
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
            {
                return 0;
            }
            else
            {
                if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
                {
                    return 0;
                }
                else
                {
                    if ((dd >= 1 && dd <= 28) && (mm == 2))
                    {
                        return 0;
                    }
                    else
                    {
                        if (dd == 29 && mm == 2 && (aa % 400 == 0 || (aa % 4 == 0 && aa % 100 != 0)))
                        {
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

#endif
