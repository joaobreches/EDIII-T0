// #include "funcoesFornecidas.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define TAM_REGISTRO 76
// #define TAM_REGISTRO_FIXO 21
// #define TAM_REGISTRO_VARIAVEL 55
// #define TAM_CABECALHO 13

// #define NULO '-1'
// #define LIXO "$"

// #define REMOVIDO '1'
// #define NAO_REMOVIDO '0'

// int qntRegistros = 0;

// typedef struct {
//   char status; // 0 para arquivo inconsistente e 1 para arquivo consistente
//   int proxRRN;
//   int nroTecnologias;
//   int nroParesTecnologias;
// } Cabecalho;

// typedef struct {
//   int tamanho;
//   char* string; 
// } StringVariavel;

// typedef struct {
//   char removido;

//   int grupo;
//   int popularidade;
//   int peso;

//   StringVariavel TecnologiaOrigem;
//   StringVariavel TecnologiaDestino;
// } Registro;

// void escreveCabecalho(FILE* arquivo, Cabecalho cabecalho){
//   fprintf(arquivo, "%c%d%d%d", cabecalho.status, cabecalho.proxRRN, cabecalho.nroTecnologias, cabecalho.nroParesTecnologias);
// }

// //implementar a contagem de tecnologias e paresdetecnologias

// Registro* leArquivoCSV(FILE *arquivoEntrada, Registro* registros){ 
//   char* linha = malloc(sizeof(char)*TAM_REGISTRO);

  
//   fgets(linha, TAM_REGISTRO, arquivoEntrada); //le e ignora a primeira linha do csv

//   int i = 0;
  
//   while(fgets(linha, TAM_REGISTRO, arquivoEntrada) != NULL){

//     registros = realloc(registros, sizeof(Registro) * ((i+1)));

//     registros[i].removido = '0';

//     char* campo = strtok(linha, ",");

//     registros[i].TecnologiaOrigem.tamanho = strlen(campo);
//     registros[i].TecnologiaOrigem.string = campo;

//     campo = strtok(NULL, ",");
//     registros[i].grupo = atoi(campo);

//     campo = strtok(NULL, ",");
//     registros[i].popularidade = atoi(campo);

//     campo = strtok(NULL, ",");
//     registros[i].TecnologiaDestino.tamanho = strlen(campo);
//     registros[i].TecnologiaDestino.string = campo;

//     campo = strtok(NULL, ",");
//     registros[i].peso = atoi(campo);

//     i++;
//     linha = malloc(sizeof(char)*TAM_REGISTRO);
//   }

//   printf("o arquivo tem %d linhas de registro\n\n", i);

//   // for (int j = 0; j < i; j++) {
//   //   printf("Registro %d:\n", j);
//   //   printf("Removido: %c\n", registros[j].removido);
//   //   printf("Grupo: %d\n", registros[j].grupo);
//   //   printf("Popularidade: %d\n", registros[j].popularidade);
//   //   printf("Peso: %d\n", registros[j].peso);
//   //   printf("TecnologiaOrigem: %s\n", registros[j].TecnologiaOrigem.string);
//   //   printf("TecnologiaDestino: %s\n\n", registros[j].TecnologiaDestino.string);
//   // }

//   // for(int j = 0; j < i; j++)
//   //   printf("%d %d\n", j, registros[j].grupo);

//   // printf("%d\n", registros[0].grupo);

//   qntRegistros = i;
//   return registros;
// }

// void createTable(FILE *arquivoEntrada, int maxTamLinha, int qntRegistros, Registro* registros) {
//   char linha[maxTamLinha];

//   FILE *arquivoSaida1 = fopen("arquivoSaida1.bin", "wb");

//   if (arquivoSaida1 == NULL) {
//     printf("Erro ao abrir o arquivo de saida\n");
//     exit(-2);
//   }

//   Cabecalho cabecalho;
//   cabecalho.status = '0';
//   cabecalho.proxRRN = 0;
//   cabecalho.nroTecnologias = 0;
//   cabecalho.nroParesTecnologias = 0;

//   escreveCabecalho(arquivoSaida1, cabecalho);

//   int qntLixoRegistro;
//   for(int i = 0; i < qntRegistros; i ++){  
//     fprintf(arquivoSaida1, "%c%d%d%d%d", registros[i].removido, registros[i].grupo, registros[i].popularidade, registros[i].peso, registros[i].TecnologiaOrigem.tamanho);
//     fwrite(registros[i].TecnologiaOrigem.string, sizeof(char), registros[i].TecnologiaOrigem.tamanho, arquivoSaida1);
//     fprintf(arquivoSaida1, "%d", registros[i].TecnologiaDestino.tamanho);
//     fwrite(registros[i].TecnologiaDestino.string, sizeof(char), registros[i].TecnologiaDestino.tamanho, arquivoSaida1);

//     for(int j = 0; j < TAM_REGISTRO_VARIAVEL - registros[i].TecnologiaOrigem.tamanho - registros[i].TecnologiaDestino.tamanho; j++)
//       fwrite(LIXO, sizeof(char), 1, arquivoSaida1);
//   }

//   fclose(arquivoSaida1);

//   binarioNaTela("arquivoSaida1.bin");
// }

// // Termina funções ^^^^

// int main() {

//   Registro* registros = malloc(sizeof(Registro));

//   FILE *arquivoEntrada;
//   arquivoEntrada = fopen("tecnologia.csv", "r");

//   registros = leArquivoCSV(arquivoEntrada, registros);


//   // for (int i = 0; i < qntRegistros; i++) {
//   //   printf("Registro %d:\n", i);
//   //   printf("Removido: %c\n", registros[i].removido);
//   //   printf("Grupo: %d\n", registros[i].grupo);
//   //   printf("Popularidade: %d\n", registros[i].popularidade);
//   //   printf("Peso: %d\n", registros[i].peso);
//   //   printf("TecnologiaOrigem: %s\n", registros[i].TecnologiaOrigem.string);
//   //   printf("TecnologiaDestino: %s\n\n", registros[i].TecnologiaDestino.string);
//   // }


//   // printf("registro %s\n", registros[489].TecnologiaOrigem.string);

//   createTable(arquivoEntrada, 500, qntRegistros, registros);
//   fclose(arquivoEntrada);
  
//   return 0;
// }


// ///LEMBRAR DE DAR FREE NAS LINHAS