#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct _Nodelista Node;
typedef struct _lista Lista;

Node *CriaNode(char* val);

Lista *CriaLista();
void DestroiLista(Lista **L_ref);
bool ListaEstaVazia(const Lista *L);
int TamanhoLista(const Lista *L);
void AddIniLista(Lista *L, char* val);
void AddFimLista(Lista *L, char* val);
void PrintLista(const Lista *L);
void PrintListaInvertida(const Lista *L);

void RemoveLista(Lista *L, char* val);
void RemoveFimLista(Lista *L);

char* ValFimLista(const Lista *L);
bool BuscaLista(const Lista *L, char* val);

#endif