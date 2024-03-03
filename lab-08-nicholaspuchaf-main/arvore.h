#define ARVORE_H

typedef struct no no;
// VAMO VER SE VAI
struct no
{

    char dado;
    int tipo_dado;

    no *filho_esq;
    no *filho_dir;
};

no *cria_arvore(char dado, int tipo_dado, no *filho_esq, no *filho_dir);

void destruir_raiz(no *raiz);