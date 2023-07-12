/** Define um tad Arquivo.
 * @file arquivo.c
 * @author Lucas Pereira Taborda
 */

#include "arquivo.h"

// estrutura de dados que armazena informacoes da entrada
struct entrada
{
    int numPags;
    int numStopWords;
    // hash das paginas
    Hash* index;
    // arvore rubro negra das stopwords
    char** stopWords;
};

// funcao que inicializara a estrutura que armazena os dados, alocando vetor para a mesma
Entrada* inicializaEntrada(int numPags, int numStopWords, Hash* index, char** stopWords){
    Entrada* entrada = (Entrada*)malloc(sizeof(Entrada));

    entrada->numPags = numPags;
    entrada->numStopWords = numStopWords;

    entrada->index = index;
    entrada->stopWords = stopWords;

    return entrada;
}

Hash* getIndex(Entrada* entrada){
    return entrada->index;
}

char* getStopWord(Entrada* entrada, int indice){
    return entrada->stopWords[indice];
}

// funcao que adquire os dados a partir de um arquivo
Entrada* setDados(FILE *indexFile, FILE *stopWordsFile)
{
    // declara variaveis
    Entrada* entrada;
    int numPags = 0, numStopWords = 0, numLinks = 0;

    // realiza leitura do arquivo de index
    numPags = getNumLines(indexFile);
    printf("num pags: %d\n", numPags);
    // Hash* index = getIndexFile(indexFile, numPags);

    // realiza leitura do arquivo de stopWords
    numStopWords = getNumLines(stopWordsFile);
    printf("num StopWords: %d\n", numStopWords);
    // char** stopWords = getStopWordsFile(stopWordsFile, numStopWords);

    // inicializa a entrada
    // entrada = inicializaEntrada(numPags, numStopWords, index, stopWords);

    return entrada;
}

// funcao que adquire os index a partir do arquivo de index
Hash* getIndexFile(FILE *indexFile, int numPags)
{
    // declara variaveis
    Hash* h = inicializaHash((numPags * 2) - 1);
    
    fseek(indexFile, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int i = 0;
    fpos_t pos;
    ssize_t n;

    for (i = 0; i < numPags; i++)
    {
        n = getline(&line, &len, indexFile);
        Pagina* p = inicializaPagina(line);

        insereHash(h, line, p);
    }

    // libera a variavel linha
    free(line);
    return h;
}

// funcao que adquire os index a partir do arquivo de index
char** getStopWordsFile(FILE *stopWordsFile, int numStopWords)
{
    // declara variaveis
    char** index = (char**)malloc(sizeof(char*)*numStopWords);
    fseek(stopWordsFile, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int i = 0;
    fpos_t pos;
    ssize_t n;

    for (i = 0; i < numStopWords; i++)
    {
        n = getline(&line, &len, stopWordsFile);

        index[i] = line;
    }

    // libera a variavel linha
    free(line);
    return index;
}

// funcao para contar a quantidade de linhas do arquivo
int getNumLines(FILE *arquivo){
    fseek(arquivo, 0, SEEK_SET);
    // inicializa variaveis
    size_t len = 0, n = 0;
    char *line = NULL;
    int numLines = 0;

    // conta as atualizacoes
    // while (!feof_unlocked(arquivo))
    // {
    //     n = getline(&line, &len, arquivo);
    //     if (n <= 0)
    //     {
    //         // linha vazia ou final do arquivo
    //         break;
    //     }
    //     if (n > 1)
    //     {
    //         printf("%s\n", line);
    //         ++numLines;
    //     }
    // }

    n = getline(&line, &len, arquivo);
    if (n > 1)
    {
        printf("%s\n", line);
        ++numLines;
    }

    // libera a variavel linha
    free(line);
    return numLines;
}

void limpaDadosEntrada(Entrada* entrada){
    int i;

    for(i = 0; i < entrada->numPags; i++){
        liberaHash(entrada->index);
    }

    for(i = 0; i < entrada->numStopWords; i++){
        free(entrada->stopWords[i]);
    }

    free(entrada->index);
    free(entrada->stopWords);
}

void escreveSaida(FILE* saida){
    fprintf(saida, "testando escrita arquivo saida\n");
}