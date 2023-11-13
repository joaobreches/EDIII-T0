// void createTableFormatado(FILE *arquivoEntrada, int maxLinhas) {
//   char linha[maxLinhas];

//   FILE *arquivoSaida1 = fopen("arquivoSaida1.bin", "wb");

//   if (arquivoSaida1 == NULL) {
//     printf("Erro ao abrir o arquivo de saida\n");
//     exit(-1);
//   }
  
//   int i = 1;
  
//   while(fgets(linha, sizeof(linha), arquivoEntrada) != NULL){

//     char* campo = strtok(linha, ",");

//     while(campo != NULL){
//       fwrite("tabela linha ", sizeof(char), strlen("tabela linha "), arquivoSaida1);
//       fprintf(arquivoSaida1, "%d", i);
      
//       fwrite(" {\n\t coluna 1: ", sizeof(char), strlen(" {\n\t coluna 1: "), arquivoSaida1);
//       fwrite(campo, sizeof(char), strlen(campo), arquivoSaida1);
//       campo = strtok(NULL, ",");
      
//       fwrite("\n\t coluna 2: ", sizeof(char), strlen("\n\t coluna 2: "), arquivoSaida1);
//       fwrite(campo, sizeof(char), strlen(campo), arquivoSaida1);
//       campo = strtok(NULL, ",");
      
//       fwrite("\n\t coluna 3: ", sizeof(char), strlen("\n\t coluna 3: "), arquivoSaida1);
//       fwrite(campo, sizeof(char), strlen(campo), arquivoSaida1);
//       campo = strtok(NULL, ",");
      
//       fwrite("\n\t coluna 4: ", sizeof(char), strlen("\n\t coluna 4: "), arquivoSaida1);
//       fwrite(campo, sizeof(char), strlen(campo), arquivoSaida1);
//       campo = strtok(NULL, ",");
      
//       fwrite("\n\t coluna 5: ", sizeof(char), strlen("\n\t coluna 5: "), arquivoSaida1);
//       fwrite(campo, sizeof(char), strlen(campo), arquivoSaida1);
//       campo = strtok(NULL, ",");
      
//       fwrite("}\n\n", sizeof(char), strlen("}\n\n"), arquivoSaida1);
//       i++;
//     }
//   }

//   fclose(arquivoSaida1);

//   binarioNaTela("arquivoSaida1.bin");
// }


// void createTableAntiga(FILE *arquivoEntrada) {
//   //ler casos nulos
  
//   FILE *arquivoBinario = fopen("arquivoBinario.bin", "wb");

//   if (arquivoBinario == NULL) {
//     printf("Falha no processamento do arquivo.\n");
//     exit(-2);
//   }

//   Cabecalho cabecalho;
//   cabecalho.status = '0';
//   cabecalho.proxRRN = 0;
//   cabecalho.nroTecnologias = 0;
//   cabecalho.nroParesTecnologias = 0;

//   escreveCabecalho(arquivoBinario, cabecalho);

//   char* linha = malloc(sizeof(char)*TAM_REGISTRO);
//   Registro registrosAtual;
//   Lista* listaTecnologias = CriaLista();
//   char* colunas[5];
  
//   fgets(linha, TAM_REGISTRO, arquivoEntrada); //le e ignora a primeira linha do csv
//   char* campo = strtok(linha, ",");

//   for (int i = 0; i < 5; i++){
//     colunas[i] = campo;
//     campo = strtok(NULL, ",");
//     printf("%s ", colunas[i]);
//   }  

//   while(fgets(linha, TAM_REGISTRO, arquivoEntrada) != NULL){
//     registrosAtual.removido = '0';

//     char* campo = strtok(linha, ",");

//     registrosAtual.TecnologiaOrigem.tamanho = strlen(campo);
//     registrosAtual.TecnologiaOrigem.string = campo;

//     campo = strtok(NULL, ",");
//     registrosAtual.grupo = atoi(campo);

//     campo = strtok(NULL, ",");
//     registrosAtual.popularidade = atoi(campo);

//     campo = strtok(NULL, ",");
//     registrosAtual.TecnologiaDestino.tamanho = strlen(campo);
//     registrosAtual.TecnologiaDestino.string = campo;

//     campo = strtok(NULL, ",");
//     registrosAtual.peso = atoi(campo);


//     fwrite(&registrosAtual.removido, sizeof(char), 1, arquivoBinario);
//     fwrite(&registrosAtual.grupo, sizeof(int), 1, arquivoBinario);
//     fwrite(&registrosAtual.popularidade, sizeof(int), 1, arquivoBinario);
//     fwrite(&registrosAtual.peso, sizeof(int), 1, arquivoBinario);
//     fwrite(&registrosAtual.TecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBinario);
//     fwrite(registrosAtual.TecnologiaOrigem.string, sizeof(char), registrosAtual.TecnologiaOrigem.tamanho, arquivoBinario);
//     fwrite(&registrosAtual.TecnologiaDestino.tamanho, sizeof(int), 1, arquivoBinario);
//     fwrite(registrosAtual.TecnologiaDestino.string, sizeof(char), registrosAtual.TecnologiaDestino.tamanho, arquivoBinario);
//     int TAM_BITES = sizeof(registrosAtual.grupo)+sizeof(registrosAtual.popularidade)+sizeof(registrosAtual.peso)+sizeof(registrosAtual.TecnologiaOrigem.tamanho)+sizeof(registrosAtual.TecnologiaDestino.tamanho)+sizeof(char)+strlen(registrosAtual.TecnologiaDestino.string)+strlen(registrosAtual.TecnologiaOrigem.string);
    
//     for(int i = TAM_BITES; i <= TAM_REGISTRO; i++){
//       char lixo = '$';
//       fwrite(&lixo, sizeof(char), 1, arquivoBinario);
//     }
  
//     contaTecnologias(listaTecnologias, registrosAtual.TecnologiaOrigem.string);
//     contaTecnologias(listaTecnologias, registrosAtual.TecnologiaDestino.string);

//   }
  
//   free(linha);  
//   fclose(arquivoBinario);

//   binarioNaTela("arquivoBinario.bin");

//   //reescrever cabeçalho com valores atalizados (status vai para 1, contagem de tecnologias, contagem dos pares, contar proxRRN)
// }