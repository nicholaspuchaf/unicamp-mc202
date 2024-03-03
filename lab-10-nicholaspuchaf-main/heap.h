
#define MAX 30
#define HEAP_H 1

typedef struct
{

    char prato[MAX];
    char nome[MAX];
    int chave;
    int id;

} Item;

typedef struct
{

    int endereco_heap;
    int chave;
    char nome[MAX];
} Id;

typedef struct
{

    Item *v;     // vetor do heap
    int n;       // indice do ultimo item
    int tamanho; // tamanho do heap
    Id *ids;     // lista dos ids;

} Heap;

Heap *cria_heap(int tam);
/*
Está é a função que cria a fila de prioridade heap, recebe int tam como parametro que define o tamanho da fila heap!
Retorna um ponteiro da heap
*/
void destroi_heap(Heap *h);
/*
Desaloca toda as memorias alocadas da fila heap
*/
void troca(Heap *h, int ind1, int ind2);
/*
Esta função troca dois itens da fila de prioridades, recebe "h" a fila heap, e ind1 e ind2 os indices dos itens a serem trocados
*/
void insere(Heap *h, Item item);
/*
Esta função insere um item na fila de prioridades heap
*/
Item extrai_maximo(Heap *h);
/*
Esta funcao retira o item de maior prioridade do heap
*/
void muda_prioridade(Heap *h, int indice, int valor);
/*
Esta funcao muda a prioridade do item do heap e atualiza a posicao dele no heap
*/
