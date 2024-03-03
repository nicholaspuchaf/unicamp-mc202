
enum cor
{
    VERMELHO,
    PRETO
};

enum tipo
{
    INT,
    DOUBLE,
    CHAR
};

typedef struct no no;

typedef struct chave tipo_chave;

struct chave
{
    /*
        Tipos:
        0 : Int
        1 : Double
        2 : Char
    */

    enum tipo tipo;
    char *nome_var;
    // int valor_int;
    // double valor_double;
    // char *valor_char;
};

struct no
{

    tipo_chave *chave;
    enum cor cor;

    no *esq;
    no *dir;
};

no *cria_arvore(tipo_chave *chave);

int eh_preto(no *raiz);

int eh_vermelho(no *raiz);

no *rotacao_para_esquerda(no *raiz);

no *rotacao_para_direita(no *raiz);

void sobe_vermelho(no *raiz);

int comparar_chaves(tipo_chave *chave1, tipo_chave *chave2);

no *inserir_rec(no *raiz, tipo_chave *chave);

no *inserir(no *raiz, tipo_chave *chave);

int mesmo_nome_chave(tipo_chave *chave1, tipo_chave *chave2);

no *buscar_nome(no *raiz, char *nome);

no *buscar(no *raiz, tipo_chave *chave);

void imprimir_arvore(no *raiz);

void destruir_chave(tipo_chave *chave);

void destruir_arvore(no *raiz);

char *extrai_tipo(no *raiz);

void imprimir_esq_dir(no *raiz);

int contagem_numero_nos(no *raiz);

int altura_da_arvore(no *raiz);