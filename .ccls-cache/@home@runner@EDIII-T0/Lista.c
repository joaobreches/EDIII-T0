#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


typedef struct _Nodelista{
    char* val;
    struct _Nodelista *prev;
    struct _Nodelista *next;
} Node;

typedef struct _lista{
    Node *ini;
    Node *fim;
    int size;
} Lista;


Node *CriaNode(char* val){
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node-> val = val;

    printf("node: %s\n", node->val);
    
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

int TamanhoLista(const Lista *L){
    return L->size;
}


void AddIniLista(Lista *L, char* val){
    Node *n = CriaNode(val);
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


void AddFimLista(Lista *L, char* val){
  // printf("adicionou %s no fim\n", val);
    Node *n = CriaNode(val);
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
  if(ListaEstaVazia(L)){
    printf("A lista esta vazia\n\n");
    return;
  }

  Node *n = L->ini;

  printf("Lista: ");
  
  while(n != NULL){
      printf("%s ", n->val);
      n = n->next;
  }
  printf("\n\n");
}

void PrintListaInvertida(const Lista *L){
    Node *n = L->fim;
    
    while(n != NULL){
        printf("%s ", n->val);
        n = n->prev;
    }
  printf("\n");
}


void RemoveLista(Lista *L, char* val){
    if(!ListaEstaVazia(L)){
        Node *n = L->ini;
        
        if(L->ini->val == val){
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
                if(n->val == val){
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
    
    return L->fim->val;
}


bool BuscaLista(const Lista *L, char* val){
  Node* n = L->ini;
  for(int i = 0; i < L->size; i++){
    if(n->val == val){
      return true;
    }
    n = n->next;
  }
  return false;
}