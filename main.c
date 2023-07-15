#include <stdlib.h>
#include <stdio.h>
#include "arquivo.h"

int main(int argc, char* argv[]){
    // declaracao de variaveis
    char nomeDiretorioEntrada[99] = "";
    char nomeArqIndex[99] = "";
    char nomeArqStopWords[99] = "";
    char nomeArqGrafo[99] = "";
    char nomeArquivoSaida[99] = "";
    char nomeDirPages[99] = "";

    FILE *arqIndex;
    FILE *arqStopWords;
    FILE *arqGrafo;
    FILE *arqSaida;
    Entrada *entrada;

    // copia o nome dos arquivos de entrada e saida fornecidos como parametros
    strcat(nomeDiretorioEntrada, "/mnt/c/Users/lucas/Desktop/codes/UFES/4 periodo/tbo/c/trabalho3/exemplo/exemplo/");
    strcat(nomeArquivoSaida, "saida.txt");

    strcat(nomeArqIndex, nomeDiretorioEntrada);
    strcat(nomeArqStopWords, nomeDiretorioEntrada);
    strcat(nomeArqGrafo, nomeDiretorioEntrada);
    strcat(nomeDirPages, nomeDiretorioEntrada);

    strcat(nomeArqIndex, "index.txt");
    strcat(nomeArqStopWords, "stopwords.txt");
    strcat(nomeArqGrafo, "graph.txt");
    strcat(nomeDirPages, "pages/");

    // realiza abertura dos arquivo para manipulacao
    arqIndex = fopen(nomeArqIndex, "r");
    arqStopWords = fopen(nomeArqStopWords, "r");
    arqGrafo = fopen(nomeArqGrafo, "r");
    arqSaida = fopen(nomeArquivoSaida, "w");

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
    entrada = setDados(arqIndex, arqStopWords, arqGrafo, nomeDirPages);
    
    escreveSaida(entrada, arqSaida);

    limpaDadosEntrada(entrada);
    free(entrada);
    fclose(arqIndex);
    fclose(arqStopWords);
    fclose(arqGrafo);
    fclose(arqSaida);
    return 0;
}