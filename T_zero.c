#include "funcoesFornecidas.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define TAM_REGISTRO_VARIAVEL 55
#define TAM_CABECALHO 13

#define NULO "-1"
#define LIXO "$"

#define REMOVIDO '1'
#define NAO_REMOVIDO '0'

typedef struct {
  char status; // 0 para arquivo inconsistente e 1 para arquivo consistente
  int proxRRN;
  int nroTecnologias;
  int nroParesTecnologias;
} Cabecalho;

typedef struct {
  int tamanho;
  char* string; 
} StringVariavel;

typedef struct {
  char removido;

  int grupo;
  int popularidade;
  int peso;

  StringVariavel TecnologiaOrigem;
  StringVariavel TecnologiaDestino;
} Registro;

void escreveCabecalho(FILE* arquivo, Cabecalho cabecalho){
  fseek(arquivo, 0, SEEK_SET);
  fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
  fwrite(&cabecalho.proxRRN, sizeof(int), 1, arquivo);
  fwrite(&cabecalho.nroTecnologias, sizeof(int), 1, arquivo);
  fwrite(&cabecalho.nroParesTecnologias, sizeof(int), 1, arquivo);
}

void printCabecalho(FILE* arquivo){
  fseek(arquivo, 0, SEEK_SET);
  Cabecalho cabecalho;
  fread(&cabecalho.status, sizeof(char), 1, arquivo);
  fread(&cabecalho.proxRRN, sizeof(int), 1, arquivo);
  fread(&cabecalho.nroTecnologias, sizeof(int), 1, arquivo);
  fread(&cabecalho.nroParesTecnologias, sizeof(int), 1, arquivo);
  printf("%c %d %d %d\n", cabecalho.status, cabecalho.proxRRN, cabecalho.nroTecnologias, cabecalho.nroParesTecnologias);
}


int contaTecnologias(FILE* arquivoBinario, char* novaTecOrigem, char* novaTecDestino){ 
  /*
  retornos:
  
  0: nada novo;
  1: apenas par novo;
  2: apenas destino e par novos;
  3: apenas origem e par novos;
  4: origem, destino e par novos;
  */

  Registro registro;
  int tecRepetidaOrigem = 0;
  int tecRepetidaDestino = 0;
  int parRepetido = 0;

  if (fseek(arquivoBinario, TAM_CABECALHO, SEEK_SET) != 0) {
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoBinario);
        return -1;
    }
  
  while(1){
    if(fread(&registro.removido, sizeof(char), 1, arquivoBinario) == 0){
      break;
    }
    if(registro.removido == '1'){
      fseek(arquivoBinario, TAM_REGISTRO-1, SEEK_CUR);
      break;
    }

    fseek(arquivoBinario, 12, SEEK_CUR);
    
    fread(&registro.TecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBinario);

    registro.TecnologiaOrigem.string = malloc((registro.TecnologiaOrigem.tamanho + 1) * sizeof(char));
    fread(registro.TecnologiaOrigem.string, sizeof(char), registro.TecnologiaOrigem.tamanho, arquivoBinario);
    registro.TecnologiaOrigem.string[registro.TecnologiaOrigem.tamanho] = '\0';

    fread(&registro.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);
    
    registro.TecnologiaDestino.string = malloc((registro.TecnologiaDestino.tamanho + 1) * sizeof(char));
    fread(registro.TecnologiaDestino.string, sizeof(char), registro.TecnologiaDestino.tamanho, arquivoBinario);
    registro.TecnologiaDestino.string[registro.TecnologiaDestino.tamanho] = '\0';

    int TAM_BITES = sizeof(registro.grupo)+sizeof(registro.popularidade)+sizeof(registro.peso)+sizeof(registro.TecnologiaOrigem.tamanho)+sizeof(registro.TecnologiaDestino.tamanho)+sizeof(char)+registro.TecnologiaOrigem.tamanho+registro.TecnologiaDestino.tamanho;
    fseek(arquivoBinario, TAM_REGISTRO - TAM_BITES + 1, SEEK_CUR);

    if(strcmp(registro.TecnologiaOrigem.string, novaTecOrigem) == 0){
      if(strcmp(registro.TecnologiaDestino.string, novaTecDestino) == 0){
        return 0;
      }
      tecRepetidaOrigem = 1;
    }
    if(tecRepetidaDestino == 0 && strcmp(registro.TecnologiaDestino.string, novaTecDestino) == 0){
      tecRepetidaDestino = 1;
    }
    if(tecRepetidaDestino == 0 && strcmp(registro.TecnologiaOrigem.string, novaTecDestino) == 0){
      tecRepetidaDestino = 1;
    }
    if(tecRepetidaOrigem == 0 && strcmp(registro.TecnologiaDestino.string, novaTecOrigem) == 0){
      tecRepetidaOrigem = 1;
    }
    
    free(registro.TecnologiaOrigem.string);
    free(registro.TecnologiaDestino.string);
  }

  if(tecRepetidaOrigem == 1){
    if(tecRepetidaDestino == 1){
      return 1;
    }
    else
      return 2;
  }
  if(tecRepetidaDestino == 1){
    return 3;
  }
  return 4;
}

void createTable(FILE *arquivoEntrada, char** colunas) {
  //ler casos nulos
  
  FILE *arquivoBinario = fopen("arquivoBinario.bin", "wb+");

  if (arquivoBinario == NULL) {
    printf("Falha no processamento do arquivo.\n");
    exit(-2);
  }

  Cabecalho cabecalho;
  cabecalho.status = '0';
  cabecalho.proxRRN = 0;
  cabecalho.nroTecnologias = 0;
  cabecalho.nroParesTecnologias = 0;

  escreveCabecalho(arquivoBinario, cabecalho);

  char* linha = malloc(sizeof(char)*TAM_REGISTRO);
  if (linha == NULL){
    printf("Falha no processamento do arquivo.\n");
    exit(-3);
  }
  
  Registro registroAtual;
  
  fgets(linha, TAM_REGISTRO, arquivoEntrada); //le e ignora a primeira linha do csv
  char* campo = strtok(linha, ",");

  for (int i = 0; i < 5; i++){
    if(i == 4)
      campo[strlen(campo) - 2] = '\0'; 
    colunas[i] = strdup(campo);
    campo = strtok(NULL, ",");
  }  

  while(fgets(linha, TAM_REGISTRO, arquivoEntrada) != NULL){
    registroAtual.removido = '0';

    char* campo = strtok(linha, ",");
    char c;
    
    for(int i = 0; i < 5; i++){
      // printf("campo %s\n", campo);
      if(strcmp(colunas[i], "nomeTecnologiaOrigem") == 0){
          registroAtual.TecnologiaOrigem.tamanho = strlen(campo);
          registroAtual.TecnologiaOrigem.string = campo;
      }
      else if(strcmp(colunas[i], "nomeTecnologiaDestino") == 0){
          registroAtual.TecnologiaDestino.tamanho = strlen(campo);
          registroAtual.TecnologiaDestino.string = campo;
      }
      else if(strcmp(colunas[i], "grupo") == 0)
        registroAtual.grupo = atoi(campo);
      else if(strcmp(colunas[i], "popularidade") == 0)
        registroAtual.popularidade = atoi(campo);
      else if(strcmp(colunas[i], "peso") == 0){
        registroAtual.peso = atoi(campo);
      }

      campo = strtok(NULL, ",");
      // printf("%s\n", campo);
    }

    // if(registroAtual.TecnologiaOrigem.tamanho > 0){
    //   if(registroAtual.TecnologiaDestino.tamanho > 0)
        // contaTecnologias(arquivoBinario, registroAtual.TecnologiaOrigem.string, NULL);
    //   else
        int novaTec = contaTecnologias(arquivoBinario, registroAtual.TecnologiaOrigem.string, registroAtual.TecnologiaDestino.string);
    // }
    // else if(registroAtual.TecnologiaDestino.tamanho > 0)
    //   contaTecnologias(arquivoBinario, NULL, registroAtual.TecnologiaDestino.string);

    // printf("novatec: %d, %s\n", novaTec, registroAtual.TecnologiaOrigem.string);
    switch(novaTec){
      case 0:
        break;
      case 1:
        cabecalho.nroParesTecnologias++;
        break;
      case 2:
        cabecalho.nroParesTecnologias++;
        cabecalho.nroTecnologias++;
        break;
      case 3:
        cabecalho.nroParesTecnologias++;
        cabecalho.nroTecnologias++;
        break;
      case 4:
        cabecalho.nroParesTecnologias++;
        cabecalho.nroTecnologias += 2;
        break;
    }
    
    fwrite(&registroAtual.removido, sizeof(char), 1, arquivoBinario);
    fwrite(&registroAtual.grupo, sizeof(int), 1, arquivoBinario);
    fwrite(&registroAtual.popularidade, sizeof(int), 1, arquivoBinario);
    fwrite(&registroAtual.peso, sizeof(int), 1, arquivoBinario);
    fwrite(&registroAtual.TecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBinario);
    fwrite(registroAtual.TecnologiaOrigem.string, sizeof(char), registroAtual.TecnologiaOrigem.tamanho, arquivoBinario);
    fwrite(&registroAtual.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);
    fwrite(registroAtual.TecnologiaDestino.string, sizeof(char), registroAtual.TecnologiaDestino.tamanho, arquivoBinario);
    int tam_bytes = sizeof(registroAtual.grupo)+sizeof(registroAtual.popularidade)+sizeof(registroAtual.peso)+sizeof(registroAtual.TecnologiaOrigem.tamanho)+sizeof(registroAtual.TecnologiaDestino.tamanho)+sizeof(char)+strlen(registroAtual.TecnologiaDestino.string)+strlen(registroAtual.TecnologiaOrigem.string);
    
    for(int i = tam_bytes; i <= TAM_REGISTRO; i++){
      char lixo = '$';
      fwrite(&lixo, sizeof(char), 1, arquivoBinario);
    }
    cabecalho.proxRRN++;
  }
  
  free(linha);

  cabecalho.status = '1';
  escreveCabecalho(arquivoBinario, cabecalho);  
  fclose(arquivoBinario);

  binarioNaTela("arquivoBinario.bin");
}

void imprimeArquivo(){
  //incluir mensagens de erro - erro de nao registros ja incluido
  FILE *arquivoBinario = fopen("arquivoBinario.bin", "rb");

  Registro registro;

  //imprimir cbeçlho antes do while
  fseek(arquivoBinario, 1, SEEK_SET);
  int proxRRN;
  fread(&proxRRN, sizeof(int), 1, arquivoBinario);
  if(proxRRN < 1){
    printf("Registro inexistente.\n");
    return;
  }
  fseek(arquivoBinario, 8, SEEK_CUR);
  
  while(1){
    if(fread(&registro.removido, sizeof(char), 1, arquivoBinario) == 0){
      break;
    }
    if(registro.removido == '1'){
      fseek(arquivoBinario, TAM_REGISTRO-1, SEEK_CUR);
      break;
    }
    
    fread(&registro.grupo, sizeof(int), 1, arquivoBinario);
    
    fread(&registro.popularidade, sizeof(int), 1, arquivoBinario);
    
    fread(&registro.peso, sizeof(int), 1, arquivoBinario);

    
    fread(&registro.TecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBinario);

    if(registro.TecnologiaOrigem.tamanho != 0){
      registro.TecnologiaOrigem.string = malloc((registro.TecnologiaOrigem.tamanho + 1) * sizeof(char));
      fread(registro.TecnologiaOrigem.string, sizeof(char), registro.TecnologiaOrigem.tamanho, arquivoBinario);
      registro.TecnologiaOrigem.string[registro.TecnologiaOrigem.tamanho] = '\0';
    }
    else {
      registro.TecnologiaOrigem.string = "NULO";
    }

    fread(&registro.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);

    if(registro.TecnologiaDestino.tamanho != 0){
      registro.TecnologiaDestino.string = malloc((registro.TecnologiaDestino.tamanho + 1) * sizeof(char));
      fread(registro.TecnologiaDestino.string, sizeof(char), registro.TecnologiaDestino.tamanho, arquivoBinario);
      registro.TecnologiaDestino.string[registro.TecnologiaDestino.tamanho] = '\0';
    }
    else {
      registro.TecnologiaDestino.string = "NULO";
    }
      
    int tam_bytes = sizeof(registro.grupo)+sizeof(registro.popularidade)+sizeof(registro.peso)+sizeof(registro.TecnologiaOrigem.tamanho)+sizeof(registro.TecnologiaDestino.tamanho)+sizeof(char)+registro.TecnologiaOrigem.tamanho+registro.TecnologiaDestino.tamanho;
    fseek(arquivoBinario, TAM_REGISTRO - tam_bytes + 1, SEEK_CUR);

    printf("%s, %d, %d, %s, %d\n", registro.TecnologiaOrigem.string, registro.grupo, registro.popularidade, registro.TecnologiaDestino.string, registro.peso);
    // printf("%c, %d, %d, %d, %d, %s, %d, %s\n", registro.removido, registro.grupo, registro.popularidade, registro. peso, registro.TecnologiaOrigem.tamanho, registro.TecnologiaOrigem.string, registro.TecnologiaDestino.tamanho, registro.TecnologiaDestino.string);
      free(registro.TecnologiaOrigem.string);
      free(registro.TecnologiaDestino.string);
  }

  fclose(arquivoBinario);
  
  //checar casos nulos (quando for nulo imprimir nulo)
}

// Termina funções ^^^^

int main() {

  char* colunas[5];
  FILE *arquivoEntrada;
  // arquivoEntrada = fopen("tecnologia.csv", "r");
  arquivoEntrada = fopen("dados1.csv", "r");
  // arquivoEntrada = fopen("dados2.csv", "r");
  createTable(arquivoEntrada, colunas);
  fclose(arquivoEntrada);

  imprimeArquivo();
  
  return 0;
}