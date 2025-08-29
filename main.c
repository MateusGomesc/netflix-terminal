#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"

void clean_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    int opc, ret;

    // creating data structures
    ListVerbete* l = createListVerbete();
    Stack* s = createStack();

    // loading verbetes file
    loadVerbetes(l);

    do{
        system("cls");
        printf("Menu -----------------------\n\n");
        printf("[1] - Pesquisar significado\n");
        printf("[2] - Pesquisar significado do arquivo frases.txt\n\n");
        printf("Opcao: ");
        scanf("%d", &opc);
        clean_buffer();
        system("cls");

        switch(opc){
            case 1:
                printf("Pesquisar significado -----------------\n\n");

                char word[50];

                printf("Palavra: ");
                scanf(" %49[^\n]", word);
                clean_buffer();

                if(!findVerbete(l, word)){
                    printf("Verbete nao encontrado!\n\n");
                }

                break;
            case 2:
                printf("Significados encontrados para frases.txt -----------------\n\n");
                getMeaning(s, l);
                break;
            default:
                printf("Opcao invalida!\n\n");
        }

        printf("Digite 1 para continuar e 0 para sair: ");
        scanf("%d", &ret);
        clean_buffer();
    }while(ret);

    // free data structures of memory
    freeListVerbete(l);
    freeStack(s);

    return 0;
}
