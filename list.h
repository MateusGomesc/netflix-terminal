#ifndef LIST_H
#define LIST_H
#include "list.h"

// Paleta de cores padrão ASCII
#define RESET_COR    "\x1b[0m"
#define COR_VERMELHA "\x1b[31m"

struct serie{
    char title[50];
    char description[200];
    char url[100];
};
typedef struct serie Serie;

struct nodeSerie{
    struct nodeSerie* before;
    Serie data;
    struct nodeSerie* next;
};
typedef struct nodeSerie NodeSerie;
typedef struct nodeSerie* ListSeries;

struct user{
    char name[50];
    ListSeries* series;
};
typedef struct user User;

struct nodeUser{
    struct nodeUser* before;
    User data;
    struct nodeUser* next;
};
typedef struct nodeUser NodeUser;
typedef struct nodeUser* ListUsers;

ListUsers* createListUsers();
ListSeries* createListSeries();
void freeListUsers(ListUsers* l);
void freeListSeries(ListSeries* l);
int insertSerie(ListSeries* l, Serie s);
int insertUser(ListUsers* l, User u);
int removeSerie(ListSeries* l, char* title);
int removeUser(ListUsers* l, char* name);
int loadData(ListUsers* l);
void printUsers(ListUsers* l);
void printSeries(ListSeries* l, char* nameUser);
int lengthSerie(ListSeries* l);
int lengthUser(ListUsers* l);
NodeUser* walkNextUser(ListUsers* l, int index);
int openUrl(ListSeries* l, char* title);
#endif
