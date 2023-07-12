#include <stdlib.h>
#include <stdio.h>
#include "arquivo.h"

int main(int argc, char* argv[]){
    // declaracao de variaveis
    char nomeDiretorioEntrada[99] = "";
    char nomeArqIndex[99] = "";
    char nomeArqStopWords[99] = "";
    char nomeArquivoSaida[99] = "";
    FILE *arqIndex;
    FILE *arqStopWords;
    FILE *arqSaida;
    Entrada *entrada;

    // copia o nome dos arquivos de entrada e saida fornecidos como parametros
    // strcat(nomeDiretorioEntrada, argv[1]);
    // strcat(nomeArquivoSaida, argv[2]);

    // strcat(nomeArqIndex, nomeDiretorioEntrada);
    // strcat(nomeArqStopWords, nomeDiretorioEntrada);

    // strcat(nomeArqIndex, "/index.txt");
    // strcat(nomeArqStopWords, "/stopwords.txt");

    // TESTE
    strcat(nomeArquivoSaida, "./saida.txt");
    strcat(nomeArqIndex, "./exemplo/exemplo/index.txt");
    strcat(nomeArqStopWords, "./exemplo/exemplo/stopwords.txt");
    // TESTE

    // realiza abertura dos arquivo para manipulacao
    arqIndex = fopen(nomeDiretorioEntrada, "r");
    arqStopWords = fopen(nomeDiretorioEntrada, "r");
    arqSaida = fopen(nomeArquivoSaida, "w");

    printf("nome arquivo index: %s\n", nomeArqIndex);
    printf("nome arquivo stop words: %s\n", nomeArqStopWords);

    // verifica se o arquivo é válido
    if (arqIndex == NULL)
    {
        printf("nao foi possivel abrir o arquivo de index\n");
        return 0;
    }
    // verifica se o arquivo é válido
    else if (arqStopWords == NULL)
    {
        printf("nao foi possivel abrir o arquivo de stopwords\n");
        return 0;
    }

    // adquire os dados da entrada
    setDados(arqIndex, arqStopWords);
    
    escreveSaida(arqSaida);

    // limpaDadosEntrada(entrada);
    // free(entrada);
    fclose(arqIndex);
    fclose(arqStopWords);
    fclose(arqSaida);
    return 0;
}