#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


typedef struct _lista{
    Node *ini;
    Node *fim;
    size_t size;
} Lista;


typedef struct _Nodelista{
    char* dado;
    struct _Nodelista *prev;
    struct _Nodelista *next;
} Node;


Node *CriaNode(char* dado){
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->dado = dado;
    
    return node;
}

Lista *CriaLista(){
    Lista *L = (Lista*) calloc(1, sizeof(Lista));
    L->ini = NULL;
    L->fim = NULL;
    L-> size = 0;
    
    return L;
}



void DestroiLista(Lista **L_ref){
    Lista *L = *L_ref;
    
    Node *n = L->ini;
    Node *aux = NULL;
    
    while (n != NULL){
        aux = n;
        n = n->next;
        free(aux);
    }
    free(L);
    
    *L_ref = NULL;
}

bool ListaEstaVazia(const Lista *L){
    return L->size == 0;   
}

size_t TamanhoLista(const Lista *L){
    return L->size;
}




void AddIniLista(Lista *L, char* dado){
    Node *n = CriaNode(dado);
    n->next = L->ini;
    
    if(ListaEstaVazia(L)){
        L->fim = n;
    } 
    else{
        L->ini->prev = n;
    }
    
    L->ini = n;
    L->size++;
}

void AddFimLista(Lista *L, char* dado){
    Node *n = CriaNode(dado);
    n->prev = L->fim;
    
    if(ListaEstaVazia(L)){
        L->ini = n;
    } 
    else{
        L->fim->next = n;
    }
    
    L->fim = n;
    L->size++;
}



void PrintLista(const Lista *L){
    Node *n = L->ini;
    
    while(n){
        printf("%s\n", n->dado);
        n = n->next;
    }
}

void PrintListaInvertida(const Lista *L){
    Node *n = L->fim;
    
    while(n != NULL){
        printf("%s\n", n->dado);
        n = n->prev;
    }
}



void RemoveLista(Lista *L, char* dado){
    if(!ListaEstaVazia(L)){
        Node *n = L->ini;
        
        if(strcmp(L->ini->dado, dado) == 0){
            L->ini = n->next;
            
            if(L->fim == n){
                L->fim = NULL;
            } 
            else {
                L->ini->prev = NULL;
            }
            
            free(n);
            L->size--;
        }
        
        else {
            n = n->next;
            
            while(n != NULL){
                if(strcmp(n->dado, dado) == 0){
                    n->prev->next = n->next;
                    
                    if(L->fim == n){
                        L->fim = n->prev;
                    }
                    else {
                        n->next->prev = n->prev;
                    }
                    
                    free(n);
                    n = NULL;
                    L->size--;
                }
                else {
                    n = n->next;
                }
            }
        }
    }
}

void RemoveFimLista(Lista *L){
    if(!ListaEstaVazia(L)){
        Node *n = L->fim;
        
        if(L->ini == L->fim){
            L->ini = NULL;            
            L->fim = NULL;
        }
        else {
            L->fim = L->fim->prev;
            L->fim->next = NULL;
        }
        
        free(n);
        L->size--;
    }
}



char* ValFimLista(const Lista *L){
    if(ListaEstaVazia(L)){
        fprintf(stderr, "ERROR em 'ValFimLista'\n");
        fprintf(stderr, "A lista esta vazia\n");
        exit(EXIT_FAILURE);
    }
    
    return L->fim->dado;
}