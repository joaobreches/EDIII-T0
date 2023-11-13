#include "funcionalidades.h"
#include "funcoesFornecidas.h"
#include "funcoesBasicas.h"

void funcionalidade1(char* nomeArquivoCSV, char* nomeArquivoBinario){
  FILE* arquivoCSV = fopen(nomeArquivoCSV, "r");
  if (arquivoCSV == NULL) {
    printf("Falha no processamento do arquivo.\n");
    exit(-2);
  }
  
  criaTabela(arquivoCSV, nomeArquivoBinario);
  fclose(arquivoCSV);

  binarioNaTela(nomeArquivoBinario);
}

void funcionalidade2(char* nomeArquivoBinario){
  imprimeArquivo(nomeArquivoBinario);  
}

void funcionalidade3(){
  
}

void funcionalidade4();