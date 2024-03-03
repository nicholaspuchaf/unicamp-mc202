typedef struct node no;

struct node
{

    char *livro;
    no *proximo;
};

no *cria_lista_vazia();
// CRIA LISTA VAZIA = NULA

void destruir_lista(no *lista);
/*
   Destroi a lista recursivamente. Nao tem retorno e recebe a lista como primeiro elemento.

*/

no *adiciona_elemento_final(no *lista, char *dado);
/*
    Adiciona um elemento no final da lista, recebe a lista e o dado a ser adicionado como parametros.
    Retorna uma nova lista ligada porque pode-ser que a lista passada seja nula!
*/

no *junta_lista(no *listaOriginal, no *listaExtra);
/*
    Junta duas lista ligadas, sendo que essa junta a listaExtra no final da listaOriginal
    retorna o ponteiro para a nova lista ligada combinada!

*/
void imprimir_lista(no *lista, no *lista2);
/*
    Imprime a lista, recebe duas listas, a lista original e a auxiliar, verifica se ambas forem diferentes de NULL imprime as duas, caso contrário
    imprime apenas uma!
*/
no *remover_elemento(no *lista, char *dado);
/*
    Função remove o elemento da lista ligada, recebe como parâmetro a lista e o dado a ser retirado
    Retorna um ponteiro da lista, porque pode-ser que tenha que retirar o primeiro elemento!
*/
