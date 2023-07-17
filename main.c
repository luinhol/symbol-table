// Lucas Pereira Taborda

#include <stdlib.h>
#include <stdio.h>
#include "arquivo.h"

int main(int argc, char* argv[]){
    // declaracao de variaveis
    char nomeDiretorioEntrada[99] = "";
    char nomeArqIndex[99] = "";
    char nomeArqStopWords[99] = "";
    char nomeArqGrafo[99] = "";
    char nomeDirPages[99] = "";

    FILE *arqIndex;
    FILE *arqStopWords;
    FILE *arqGrafo;
    Entrada *entrada;

    size_t len = 0;
    char *line = NULL;
    char *pt;
    char* palavras;

    // copia o nome do diretorio de entrada fornecido como parametro
    // strcat(nomeDiretorioEntrada, "/mnt/c/Users/lucas/Desktop/codes/UFES/4periodo/tbo/c/trabalho3/exemplo/exemplo/");
    // strcat(nomeDiretorioEntrada, "/mnt/c/Users/lucas/Desktop/codes/UFES/4periodo/tbo/c/trabalho3/exemploPDF/");
    strcat(nomeDiretorioEntrada, argv[1]);

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

    while (!feof_unlocked(stdin))
    {
        ssize_t n = getline(&line, &len, stdin);

        palavras = strdup(line);

        realizaPesquisa(entrada, palavras);
        free(palavras);
    }

    limpaDadosEntrada(entrada);
    free(line);
    free(entrada);
    fclose(arqIndex);
    fclose(arqStopWords);
    fclose(arqGrafo);
    return 0;
}