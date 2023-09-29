#include "funcoesFornecidas.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define TAM_REGISTRO_VARIAVEL 55
#define TAM_CABECALHO 13

#define NULO '-1'
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
  // fseek(arquivo, 1, SEEK_SET);
  fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
  fwrite(&cabecalho.proxRRN, sizeof(int), 1, arquivo);
  fwrite(&cabecalho.nroTecnologias, sizeof(int), 1, arquivo);
  fwrite(&cabecalho.nroParesTecnologias, sizeof(int), 1, arquivo);

}

//implementar a contagem de tecnologias e paresdetecnologias

int contaTecnologias(char* novaTecOrigem, char* novaTecDestino){ 
  /*
  retornos:
  
  0: nada novo;
  1: apenas par novo;
  2: apenas destino e par novos;
  3: apenas origem e par novos;
  4: origem, destino e par novos;
  */

  FILE* arquivoBinario = fopen("arquivoBinario.bin", "rb");
  Registro registro;
  int tecRepetidaOrigem = 0;
  int tecRepetidaDestino = 0;
  int parRepetido = 0;

  fseek(arquivoBinario, TAM_CABECALHO, SEEK_SET);
  
  while(1){
    if(fread(&registro.removido, sizeof(char), 1, arquivoBinario) == 0){
      break;
    }
    if(registro.removido == '1'){
      fseek(arquivoBinario, TAM_REGISTRO-1, SEEK_CUR);
      break;
    }

    fseek(arquivoBinario, 12, SEEK_CUR);
    // fread(&registro.grupo, sizeof(int), 1, arquivoBinario);
    
    // fread(&registro.popularidade, sizeof(int), 1, arquivoBinario);
    
    // fread(&registro.peso, sizeof(int), 1, arquivoBinario);

    
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

    // printf("novaorigem: %s, novodestino: %s, origem: %s, destino: %s\n", novaTecOrigem, novaTecDestino, registro.TecnologiaOrigem.string, registro.TecnologiaDestino.string);

    printf("strcmp: %s e %s\n", registro.TecnologiaOrigem.string, novaTecOrigem);
    if(strcmp(registro.TecnologiaOrigem.string, novaTecOrigem) == 0){
      if(strcmp(registro.TecnologiaDestino.string, novaTecDestino) == 0){
        fclose(arquivoBinario);
        return 0;
      }
      tecRepetidaOrigem = 1;
      if(strcmp(registro.TecnologiaOrigem.string, novaTecDestino) == 0)
        tecRepetidaDestino = 1;
    }
    else if(tecRepetidaOrigem == 0 && strcmp(registro.TecnologiaDestino.string, novaTecOrigem) == 0)
      tecRepetidaOrigem = 1;
    
    free(registro.TecnologiaOrigem.string);
    free(registro.TecnologiaDestino.string);
  }

  // while(!feof(arquivoBinario)){
  //   fread(&registro.removido, sizeof(char), 1, arquivoBinario);
  //   if (registro.removido == '0'){
  //     fseek(arquivoBinario, 12, SEEK_CUR);
  //     fread(&registro.TecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBinario);
  //     fread(&registro.TecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBinario);
  //     registro.TecnologiaOrigem.string = malloc((registro.TecnologiaOrigem.tamanho + 1) * sizeof(char));
  //     fread(registro.TecnologiaOrigem.string, sizeof(char), registro.TecnologiaOrigem.tamanho, arquivoBinario);
  //     registro.TecnologiaOrigem.string[registro.TecnologiaOrigem.tamanho] = '\0';
  //     fread(&registro.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);
  //     fread(&registro.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);
  //     registro.TecnologiaDestino.string = malloc((registro.TecnologiaDestino.tamanho + 1) * sizeof(char));
  //     fread(registro.TecnologiaDestino.string, sizeof(char), registro.TecnologiaDestino.tamanho, arquivoBinario);
  //     registro.TecnologiaDestino.string[registro.TecnologiaDestino.tamanho] = '\0';

  //     // printf("novaorigem: %s, novodestino: %s, origem: %s, destino: %s\n", novaTecOrigem, novaTecDestino, registro.TecnologiaOrigem.string, registro.TecnologiaDestino.string);

  //     printf("strc %s e %s\n", registro.TecnologiaOrigem.string, novaTecOrigem);
  //     if(strcmp(registro.TecnologiaOrigem.string, novaTecOrigem) == 0){
  //       if(strcmp(registro.TecnologiaDestino.string, novaTecDestino) == 0)
  //         return 0;
  //       tecRepetidaOrigem = 1;
  //       if(strcmp(registro.TecnologiaOrigem.string, novaTecDestino) == 0)
  //         tecRepetidaDestino = 1;
  //     }
  //     else if(tecRepetidaOrigem == 0 && strcmp(registro.TecnologiaDestino.string, novaTecOrigem) == 0)
  //       tecRepetidaOrigem = 1;
    
  //     free(registro.TecnologiaOrigem.string);
  //     free(registro.TecnologiaDestino.string);
  //   }
  // }
  fclose(arquivoBinario);
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
  
  FILE *arquivoBinario = fopen("arquivoBinario.bin", "wb");

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
  
  Registro registrosAtual;
  
  fgets(linha, TAM_REGISTRO, arquivoEntrada); //le e ignora a primeira linha do csv
  char* campo = strtok(linha, ",");

  for (int i = 0; i < 5; i++){
    colunas[i] = strdup(campo);
    campo = strtok(NULL, ",");
  }  

  while(fgets(linha, TAM_REGISTRO, arquivoEntrada) != NULL){
    registrosAtual.removido = '0';

    char* campo = strtok(linha, ",");

    for(int i = 0; i < 5; i++){
      if(strcmp(colunas[i], "nomeTecnologiaOrigem") == 0){
          registrosAtual.TecnologiaOrigem.tamanho = strlen(campo);
          registrosAtual.TecnologiaOrigem.string = campo;
      }
      else if(strcmp(colunas[i], "nomeTecnologiaDestino") == 0){
          registrosAtual.TecnologiaDestino.tamanho = strlen(campo);
          registrosAtual.TecnologiaDestino.string = campo;
      }
      else if(strcmp(colunas[i], "grupo") == 0)
        registrosAtual.grupo = atoi(campo);
      else if(strcmp(colunas[i], "popularidade") == 0)
        registrosAtual.popularidade = atoi(campo);
      else if(strcmp(colunas[i], "peso") == 0)
        registrosAtual.peso = atoi(campo);

      campo = strtok(NULL, ",");
    }

    // if(registrosAtual.TecnologiaOrigem.tamanho > 0){
    //   if(registrosAtual.TecnologiaDestino.tamanho > 0)
        // contaTecnologias(arquivoBinario, registrosAtual.TecnologiaOrigem.string, NULL);
    //   else
        // int novaTec = contaTecnologias(registrosAtual.TecnologiaOrigem.string, registrosAtual.TecnologiaDestino.string);
    // }
    // else if(registrosAtual.TecnologiaDestino.tamanho > 0)
    //   contaTecnologias(arquivoBinario, NULL, registrosAtual.TecnologiaDestino.string);

      // printf("novatec: %d, origem: %s, destino: %s\n", novaTec, registrosAtual.TecnologiaOrigem.string, registrosAtual.TecnologiaDestino.string);
    // switch(novaTec){
    //   case 0:
    //     break;
    //   case 1:
    //     cabecalho.nroParesTecnologias++;
    //     break;
    //   case 2:
    //     cabecalho.nroParesTecnologias++;
    //     cabecalho.nroTecnologias++;
    //     break;
    //   case 3:
    //     cabecalho.nroParesTecnologias++;
    //     cabecalho.nroTecnologias++;
    //     break;
    //   case 4:
    //     cabecalho.nroParesTecnologias++;
    //     cabecalho.nroTecnologias += 2;
    //     break;
    // }
    
    fwrite(&registrosAtual.removido, sizeof(char), 1, arquivoBinario);
    fwrite(&registrosAtual.grupo, sizeof(int), 1, arquivoBinario);
    fwrite(&registrosAtual.popularidade, sizeof(int), 1, arquivoBinario);
    fwrite(&registrosAtual.peso, sizeof(int), 1, arquivoBinario);
    fwrite(&registrosAtual.TecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBinario);
    fwrite(registrosAtual.TecnologiaOrigem.string, sizeof(char), registrosAtual.TecnologiaOrigem.tamanho, arquivoBinario);
    fwrite(&registrosAtual.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);
    fwrite(registrosAtual.TecnologiaDestino.string, sizeof(char), registrosAtual.TecnologiaDestino.tamanho, arquivoBinario);
    int tam_bytes = sizeof(registrosAtual.grupo)+sizeof(registrosAtual.popularidade)+sizeof(registrosAtual.peso)+sizeof(registrosAtual.TecnologiaOrigem.tamanho)+sizeof(registrosAtual.TecnologiaDestino.tamanho)+sizeof(char)+strlen(registrosAtual.TecnologiaDestino.string)+strlen(registrosAtual.TecnologiaOrigem.string);
    
    for(int i = tam_bytes; i <= TAM_REGISTRO; i++){
      char lixo = '$';
      fwrite(&lixo, sizeof(char), 1, arquivoBinario);
    }
  }
  
  free(linha);

  // cabecalho.status = '1';
  // escreveCabecalho(arquivoBinario, cabecalho);
  // printf("nroTec: %d, nroPares: %d\n", cabecalho.nroTecnologias, cabecalho.nroParesTecnologias);
  
  fclose(arquivoBinario);

  binarioNaTela("arquivoBinario.bin");

  //reescrever cabeçalho com valores atualizados (status vai para 1, contagem de tecnologias, contagem dos pares, contar proxRRN)
}

void imprimeArquivo(){
  //incluir mensagens de erro
  FILE *arquivoBinario = fopen("arquivoBinario.bin", "rb");

  Registro registro;

  //imprimir cbeçlho antes do while
  fseek(arquivoBinario, TAM_CABECALHO, SEEK_SET);
  
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

    registro.TecnologiaOrigem.string = malloc((registro.TecnologiaOrigem.tamanho + 1) * sizeof(char));
    fread(registro.TecnologiaOrigem.string, sizeof(char), registro.TecnologiaOrigem.tamanho, arquivoBinario);
    registro.TecnologiaOrigem.string[registro.TecnologiaOrigem.tamanho] = '\0';

    fread(&registro.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);
    
    registro.TecnologiaDestino.string = malloc((registro.TecnologiaDestino.tamanho + 1) * sizeof(char));
    fread(registro.TecnologiaDestino.string, sizeof(char), registro.TecnologiaDestino.tamanho, arquivoBinario);
    registro.TecnologiaDestino.string[registro.TecnologiaDestino.tamanho] = '\0';

    int tam_bytes = sizeof(registro.grupo)+sizeof(registro.popularidade)+sizeof(registro.peso)+sizeof(registro.TecnologiaOrigem.tamanho)+sizeof(registro.TecnologiaDestino.tamanho)+sizeof(char)+registro.TecnologiaOrigem.tamanho+registro.TecnologiaDestino.tamanho;
    fseek(arquivoBinario, TAM_REGISTRO - tam_bytes + 1, SEEK_CUR);

    printf("%s, %d, %d, %s, %d\n", registro.TecnologiaOrigem.string, registro.grupo, registro.popularidade, registro.TecnologiaDestino.string, registro.peso);
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
  arquivoEntrada = fopen("tecnologia.csv", "r");
  // arquivoEntrada = fopen("dados1.csv", "r");
  // arquivoEntrada = fopen("dados2.csv", "r");
  createTable(arquivoEntrada, colunas);
  fclose(arquivoEntrada);

  imprimeArquivo();
  
  return 0;
}