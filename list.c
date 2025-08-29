#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "list.h"



void trim(char *str){
    char *start, *end;

    start = str;
    while(*start && isspace((unsigned char) *start)){
        start++;
    }

    if(*start == 0){
        *str = '\0';
        return;
    }

    end = start + strlen(str) - 1;
    while(end > start && isspace((unsigned char)*end)){
        end--;
    }
    *(end+1) = '\0';

    if(start != end){
        memmove(str, start, end-start+2);
    }
}

ListUsers* createListUsers(){
    ListUsers* l = (ListUsers*) malloc(sizeof(ListUsers));
    if(l != NULL)
        *l = NULL;
    return l;
}

ListSeries* createListSeries(){
    ListSeries* l = (ListSeries*) malloc(sizeof(ListSeries));
    if(l != NULL)
        *l = NULL;
    return l;
}

void freeListSeries(ListSeries* l){
    if(l != NULL){
        NodeSerie* node;
        while((*l) != NULL){
            node = *l;
            *l = (*l)->next;
            free(node);
        }
        free(l);
    }
}

void freeListUsers(ListUsers* l){
    if(l != NULL){
        NodeUser* node;
        while((*l) != NULL){
            node = *l;
            *l = (*l)->next;
            freeListSeries(node->data.series);
            free(node);
        }
        free(l);
    }
}

int insertSerie(ListSeries* l, Serie s){
    if(l == NULL){
        printf("Lista invalida!\n");
        return 0;
    }

    // Criando novo no de serie
    NodeSerie* node = (NodeSerie*) malloc(sizeof(NodeSerie));
    if(node == NULL){
        printf("Erro ao alocar memória para nova série!\n");
        return 0;
    }
    node->data = s;

    // Se a lista estiver vazia
    if(*l == NULL){
        node->next = NULL;
        node->before = NULL;
        *l = node;
    }
    else{
        NodeSerie *aux = *l;
        NodeSerie *before = NULL;

        // Percorrendo lista para encontrar posicao alfabeticamente correta
        while(aux != NULL && strcmp(aux->data.title, node->data.title) < 0){
            before = aux;
            aux = aux->next;
        }

        // Se a palavra for a primeira
        if(before == NULL){
            node->before = NULL;
            node->next = *l;
            (*l)->before = node;
            *l = node;
        }
        else if(aux == NULL){ // Se a palavra for a ultima
            before->next = node;
            node->next = NULL;
            node->before = before;
        }
        else{ // Se for no meio
            before->next = node;
            node->before = before;
            node->next = aux;
            aux->before = node;
        }
    }

    return 1;
}

int insertUser(ListUsers* l, User u){
    if(l == NULL){
        printf("Lista inválida!\n");
        return 0;
    }

    if(lengthUser(l) >= 4){
        printf("Quantidade máxima de usuários antigida para seu plano!\n");
        return 0;
    }

    // Criando novo no de serie
    NodeUser* node = (NodeUser*) malloc(sizeof(NodeUser));
    if(node == NULL){
        printf("Erro ao alocar memória para nova série!\n");
        return 0;
    }
    node->data = u;

    // Se a lista estiver vazia
    if(*l == NULL){
        node->next = NULL;
        node->before = NULL;
        *l = node;
    }
    else{
        NodeUser *aux = *l;
        NodeUser *before = NULL;

        // Percorrendo lista para encontrar posicao alfabeticamente correta
        while(aux != NULL && strcmp(aux->data.name, node->data.name) < 0){
            aux = aux->next;
        }

        // Se a palavra for a primeira
        if(before == NULL){
            node->before = NULL;
            node->next = *l;
            (*l)->before = node;
            *l = node;
        }
        else if(aux == NULL){ // Se a palavra for a ultima
            before->next = node;
            node->next = NULL;
            node->before = before;
        }
        else{ // Se for no meio
            before->next = node;
            node->before = before;
            node->next = aux;
            aux->before = node;
        }
    }

    return 1;
}

int removeSerie(ListSeries* l, char* title){
    if(l == NULL){
        printf("Lista inválida!\n");
        return 0;
    }

    NodeSerie* node = *l;

    // Procurando elemento na lista
    while(node != NULL && strcmp(node->data.title, title) != 0){
        node = node->next;
    }

    // Se nao for encontrado
    if(node == NULL){
        printf("Elemento não encontrado!\n");
        return 0;
    }

    // Se for o primeiro
    if(node->before == NULL)
        *l = node->next;
    else
        node->before->next = node->next;

    // Se nao for o ultimo
    if(node->next != NULL)
        node->next->before = node->before;

    free(node);
    return 1;
}

int removeUser(ListUsers* l, char* name){
    if(l == NULL){
        printf("Lista inválida!\n");
        return 0;
    }

    NodeUser* node = *l;

    // Procurando elemento na lista
    while(node != NULL && strcmp(node->data.name, name) != 0){
        node = node->next;
    }

    // Se nao for encontrado
    if(node == NULL){
        printf("Elemento não encontrado!\n");
        return 0;
    }

    // Se for o primeiro
    if(node->before == NULL)
        *l = node->next;
    else
        node->before->next = node->next;

    // Se nao for o ultimo
    if(node->next != NULL)
        node->next->before = node->before;

    free(node);
    return 1;
}

int loadData(ListUsers* l){
    if(l == NULL){
        printf("Lista inválida!\n");
        return 0;
    }

    FILE *fu = fopen("users.txt", "r");
    FILE *fs = fopen("series.txt", "r");
    if(fu == NULL || fs == NULL){
        printf("Erro ao carregar os arquivos de dados!\n");
        return 0;
    }

    // Lendo cada linha do arquivo de usuarios
    User u;
    char nameUser[50];
    while(fgets(nameUser, sizeof(nameUser), fu)){
        nameUser[strcspn(nameUser, "\n")] = '\0';
        trim(nameUser);

        // Populando struct de usuario
        strcpy(u.name, nameUser);
        u.series = createListSeries();

        // Lendo cada linha do arquivo de series e procurando por serie do usuario
        char lineSerie[250];
        char* serieUser;
        Serie s;
        while(fgets(lineSerie, sizeof(lineSerie), fs)){
            lineSerie[strcspn(lineSerie, "\n")] = '\0';

            // Recebendo nome do usuario dono da serie
            serieUser = strtok(lineSerie, "|");
            trim(serieUser);

            // Se o nome do dono da serie for igual ao nome do usuario que estamos inserindo na lista
            if(strcmp(nameUser, serieUser) == 0){
                strcpy(s.title, strtok(NULL, "|"));
                trim(s.title);
                strcpy(s.description, strtok(NULL, "|"));
                strcpy(s.url, strtok(NULL, "|"));

                trim(s.title);
                trim(s.description);
                trim(s.url);

                if(!insertSerie(u.series, s)){ // Se a insercao falhar
                    printf("Erro ao inserir série: %s - %s\n", nameUser, s.title);
                }
            }
        }

        // Inserindo Usuario populado na lista
        if(!insertUser(l, u)){
            printf("Erro ao inserir usuário: %s\n", nameUser);
        }

        // Retorna cursor do arquivo de series para o inicio do arquivo
        rewind(fs);
    }

    fclose(fs);
    fclose(fu);
    return 1;
}

int lengthUser(ListUsers* l){
    if(l == NULL || *l == NULL) return 0;

    int cont=0;
    NodeUser* aux = *l;
    while(aux != NULL){
        cont++;
        aux = aux->next;
    }
    return cont;
}

int lengthSerie(ListSeries* l){
    if(l == NULL || *l == NULL) return 0;

    int cont=0;
    NodeSerie* aux = *l;
    while(aux != NULL){
        cont++;
        aux = aux->next;
    }
    return cont;
}

NodeUser* walkNextUser(ListUsers* l, int index){
    if(l == NULL || *l == NULL || index >= lengthUser(l) || index < 0) return NULL;

    int i;
    NodeUser* node = *l;
    for(i=0; i<index; i++){
        node = node->next;
    }
    return node;
}

int openUrl(ListSeries* l, char* title){
    if(l == NULL){
        printf("Lista inválida!\n");
        return 0;
    }

    // Procurando url da serie
    NodeSerie* node = *l;
    while(node != NULL && strcasecmp(node->data.title, title) != 0){
        node = node->next;
    }

    // Se a lista for ate o final
    if(node == NULL){
        printf(COR_VERMELHA "Série não encontrada em sua lista!\n\n" RESET_COR);
        return 0;
    }

    // MOnta string de comando de acordo com sistema operacional
    char command[256];
    #ifdef _WIN32
        sprintf(command, "start %s", node->data.url);
    #elif __APPLE__
        sprintf(command, "open %s", node->data.url);
    #elif __linux__
        sprintf(command, "xdg-open %s", node->data.url);
    #else
        printf("Sistema operacional não reconhecido!\n\n");
        return 0;
    #endif

    printf("Abrindo %s, Boa Série!\n", title);
    system(command);
    return 1;
}

void printUsers(ListUsers* l){
    if(l == NULL){
        printf("Lista inválida!\n");
        return;
    }

    NodeUser* node = *l;
    int i = 1;
    printf("Quem está assistindo?\n\n");
    while(node != NULL){
        printf("[%d] %s\n", i, node->data.name);
        node = node->next;
        i++;
    }
    printf("\n");
}

void printSeries(ListSeries* l, char* nameUser){
    if(l == NULL){
        printf("Lista inválida!\n");
        return;
    }

    NodeSerie* node = *l;
    printf("Continuar assistindo como %s\n\n", nameUser);
    while(node != NULL){
        printf("%s:\n", node->data.title);
        printf("%s\n\n", node->data.description);
        node = node->next;
    }
}
