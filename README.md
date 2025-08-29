# :movie_camera: Netflix no terminal

## Introdução

### Modelagem do Problema

O problema apresentado para ser resolvido era escrever um código em linguagem C que utilize da lista duplamente encadeada para fazer uma lista de usuários, sendo que cada usuário contém uma lista de séries que já assistiu. A solução proposta para esse exercício foi a de transpor a essência da aplicação web da Netflix para o contexto do terminal com o seguinte fluxo:

* Listagem dos usuários
* Escolha do usuário
* Listagem das séries
* Escolha da série
* Assistir série

Desse modo, foi criado um módulo chamado ``list.c`` para realizar a implementação das funções relativas a estrutura de dados juntamente com um arquivo de interface ``list.h`` para compartilhamento das funções, estruturas, constantes e tipos com o arquivo ``main.c``.

### Bibliotecas Utilizadas

* ``stdio.h``: Entrada/saída padrão.
* ``stdlib.h``: funções de alocação dinâmica de memória, controle do sistema operacional e para manipulação de arquivos.
* ``string.h``: funções de manipulação de string.
* ``locale.h``: utilizada para habilitar o padrão UTF-8 para o terminal.
* ``ctype.h``: funções para manipular caracteres, utilizada na função trim.

### Estruturas de Dados Utilizadas

A estrutura de dados utilizada para o projeto foi a ``lista duplamente encadeada`` que foi requisito pedido para a realização desse trabalho acadêmico.
  
## Documentação do código

### Funções

```c
ListUsers* createListUsers()
```

Não recebe nenhum parâmetro e retorna um ponteiro do tipo ListUsers que aponta para NULL. <br/>
Função de criação da lista de usuários inicialmente vazia.

```c
ListSeries* createListSeries()
```

Não recebe nenhum parâmetro e retorna um ponteiro do tipo ListSeries que aponta para NULL. <br/>
Função de criação da lista de séries inicialmente vazia.

```c
void freeListUsers(ListUsers* l)
```

Recebe uma lista de usuários como parâmetro e não tem retorno. <br/>
Função que libera lista de usuários da memória.


```c
void freeListSeries(ListSeries* l)
```
Recebe uma lista de séries como parâmetro e não tem retorno. <br/>
Função que libera lista de séries da memória.

```c
int insertSerie(ListSeries* l, Serie s)
```

Recebe uma lista de séries e uma struct Serie, retorna um inteiro de sinalização, 0 para erro, 1 para sucesso. <br/>
Função para inserir um novo nó na lista de séries ordenadamente, considerando a ordem alfabetica a partir do titulo (campo title da struct Serie).

```c
int insertUser(ListUsers* l, User u);
```

Recebe uma lista de usuários e uma struct User, retorna um inteiro de sinalização, 0 para erro, 1 para sucesso. <br/>
Função para inserir um novo nó na lista de usuários ordenadamente, considerando a ordem alfabetica a partir do nome (campo name da struct Serie).

```c
int removeSerie(ListSeries* l, char* title)
```

Recebe uma lista de séries e uma string com o título da série a ser retirada. <br/>
Função para remover uma série da lista de séries pelo seu título.

```c
int removeUser(ListUsers* l, char* name)
```

Recebe uma lista de usuários e uma string com o nome do usuário a ser retirado. <br/>
Função para remover um usuário da lista de usuários pelo seu nome.

```c
int loadData(ListUsers* l)
```

Recebe uma lista de usuários e retorna um inteiro de sinalização, 0 para erro, 1 para sucesso. <br/>
Função para carregar dados dos arquivos users.txt e series.txt, devolvendo a lista completa de usuários e para cada usuário uma lista de séries.

```c
void printUsers(ListUsers* l)
```

Recebe uma lista de usuários e não tem retorno. <br/>
Função para printar na tela a lista de usuários da seguinte maneira: ``[%d] %s\n``, onde ``%d`` é o indíce do usuário e ``%s`` é o nome do usuário.


```c
void printSeries(ListSeries* l, char* nameUser)
```

Recebe uma lista de séries e não tem retorno. <br/>
Função para printar na tela a lista de séries da seguinte maneira: ``%s:\n%s\n\n``, onde o primeiro ``%s`` é o título da série e o segundo ``%s`` é a descrição da série.

```c
int lengthSerie(ListSeries* l)
```

Recebe uma lista de séries e retorna um inteiro. <br/>
Função para resgatar tamanho da lista de séries.

```c
int lengthUser(ListUsers* l)
```

Recebe uma lista de usuários e retorna um inteiro. <br/>
Função para resgatar tamanho da lista de usuários.

```c
NodeUser* walkNextUser(ListUsers* l, int index)
```

Recebe uma lista de usuários e um inteiro indicando o index. <br/>
Função para retornar o nó que está na posição index recebida como parâmetro (com index >= 0).

```c
int openUrl(ListSeries* l, char* title)
```

Recebe uma lista de séries e uma string indicando o titulo da série. <br/>
Função para abrir no navegador a série indicada no parâmetro title, procurando na lista de séries recebida pelo título, quando encontra, pega a url da série e chama o comando para abrir o link no navegador.

```c
void trim(char *str)
```

Recebe uma string e não tem retorno.
Função para retirar espaços em branco do ínicio e do final da string. Utilizada na função ``loadData`` para retirar os espaços em brancos deixados nas strings quando os valores são pegos dos arquivos.

### Structs

Struct que guarda as informações da série:
```c
struct serie{
    char title[50];
    char description[200];
    char url[100];
};
typedef struct serie Serie;
```

Struct para o nó da lista de séries:
```c
struct nodeSerie{
    struct nodeSerie* before;
    Serie data;
    struct nodeSerie* next;
};
```

Typedefs para a lista de série:
```c
typedef struct nodeSerie NodeSerie;
typedef struct nodeSerie* ListSeries;
```

Struct para guardar informações de usuários:
```c
struct user{
    char name[50];
    ListSeries* series;
};
typedef struct user User;
```

Struct para o nó da lista de usuários:
```c
struct nodeUser{
    struct nodeUser* before;
    User data;
    struct nodeUser* next;
};
```

Typedefs para a lista de usuários:
```c
typedef struct nodeUser NodeUser;
typedef struct nodeUser* ListUsers;
```

### Arquivos de texto

Sobre como os dados estão oranizados nos arquivos de texto.

Arquivo users.txt:
```txt
Nome do usuário\n
```

Arquivo series.txt:
```txt
Nome do usuário | título | descrição | url para trailer no Youtube\n
```

## Exemplos de Uso

### Criação da lista

Para realizar a crição de uma lista de usuários, utilize o seguinte código, o qual cria um ponteiro do tipo ``ListUsers`` e chama a função ``createListUsers`` para criar a lista na memória.

```c
ListUsers* listUsers = createListUsers();
```

### Andando pela lista

Na situação a seguir é feito um tratamento de erro onde a váriavel ``opc`` guarda o número do usuário ao qual devo pegar a lista de séries pra ser exibida. <br/>
Porém, é preciso ter certeza de quantos usuários temos na lista para que não acessemos posições de memória inválidas. <br/>
Para a resolução, foi feita uma condicional verificando o tamanho da lista de usuários (se o tamanho da lista era suficiente), se está suficiente utiliza a função ``walkNextUser`` para receber o usuário desejado, se não retorna a proxima iteração do menu.

```c
switch(opc){
  case 1:
      if(quantUsers >= 1){ // Verificacao de seguranca de acordo com a quantidade de usuarios
          // Recebendo usuario com seguranca
          node = walkNextUser(listUsers, 0);
      }
      else{
          continue;
      }
  
      break;
  case 2:
      if(quantUsers >= 2){
          node = walkNextUser(listUsers, 1);
      }
      else{
          continue;
      }
  
      break;
  case 3:
      if(quantUsers >= 3){
          node = walkNextUser(listUsers, 2);
      }
      else{
          continue;
      }
  
      break;
  case 4:
      if(quantUsers == 4){
          node = walkNextUser(listUsers, 3);
      }
      else{
          continue;
      }
  
      break;
  default:
      printf(COR_VERMELHA "Usuário inválido!\n\n" RESET_COR);
      continue;
}
```

### Liberando a lista da memória

No final do código, lembre-se de eliminar todos os nós da lista para não haver vazamento de memória. Utiliza a função ``freeListUsers`` que faz a liberação de maneira segura como no exemplo abaixo:

```c
freeListUsers(listUsers);
```

## Conclusão

O trabalho foi um excelente meio de fixação do contéudo visto em aula, mostrar a utilização das estruturas de dados no meio comercial de uma maneira interessante e divertida. Foi possível aprender ainda mais sobre a ementa da disciplina e também conceitos que vão além, como por exemplo comandos de terminal para navegação web.

### Melhorias que podem ser implementadas

* Inserção de novas séries por usuário
* Remoção de séries pelo usuário
* Melhoras na interface

