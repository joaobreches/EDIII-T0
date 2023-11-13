#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct _Nodelista Node;
typedef struct _lista Lista;

Node *CriaNode(char* dado);

Lista *CriaLista();
void DestroiLista(Lista **L_ref);
bool ListaEstaVazia(const Lista *L);
size_t TamanhoLista(const Lista *L);
void AddIniLista(Lista *L, char* dado);
void AddFimLista(Lista *L, char* dado);
void PrintLista(const Lista *L);
void PrintListaInvertida(const Lista *L);

void RemoveLista(Lista *L, char* dado);
void RemoveFimLista(Lista *L);

char* ValFimLista(const Lista *L);

#endif