#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "list.h"

void logo(){
    printf("======================================\n");
    printf("|                                    |\n");
    printf("|              %sNETFLIX%s               |\n", COR_VERMELHA, RESET_COR);
    printf("|                                    |\n");
    printf("======================================\n\n\n");
}

int main()
{
    // Configurando terminal para UTF-8
    setlocale(LC_ALL, "Portuguese");
    system("chcp 65001 > nul");

    int ret, opc;
    char title[50];

    ListUsers* listUsers = createListUsers();

    // Carregando dados dos arquivos para a lista
    loadData(listUsers);

    do{
        system("cls");
        logo();
        printUsers(listUsers);
        printf("Escolha do usuário: ");
        scanf("%d", &opc);
        system("cls");
        logo();

        int quantUsers = lengthUser(listUsers);
        NodeUser* node;

        switch(opc){
            case 1:
                if(quantUsers >= 1){ // Verificacao de seguranca de acordo com a quantidade de usuarios
                    // Recebendo usuario com seguranca
                    node = walkNextUser(listUsers, 0);
                }

                break;
            case 2:
                if(quantUsers >= 2){
                    node = walkNextUser(listUsers, 1);
                }

                break;
            case 3:
                if(quantUsers >= 3){
                    node = walkNextUser(listUsers, 2);
                }

                break;
            case 4:
                if(quantUsers == 4){
                    node = walkNextUser(listUsers, 3);
                }

                break;
            default:
                printf(COR_VERMELHA "Usuário inválido!\n\n" RESET_COR);
                continue;
        }

        // Printa com seguranca todas as series do usuario
        printSeries(node->data.series, node->data.name);

        printf("Nome da série que deseja assistir: ");
        scanf(" %49[^\n]", title);

        // Abre url
        openUrl(node->data.series, title);

        printf("Digite 1 para continuar e 0 para sair: ");
        scanf("%d", &ret);
    }while(ret);

    system("cls");
    logo();
    printf("Volte sempre! Suas séries estarão sempre aqui na %sNETFLIX%s!\n", COR_VERMELHA, RESET_COR);

    freeListUsers(listUsers);

    return 0;
}
