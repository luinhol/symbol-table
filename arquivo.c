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
    // lista do nome das paginas consideradas
    char** index;
    // stop words
    char** stopWords;
    // links entre as páginas (index de cada pagina no index)
    Lista** graph;
};

// funcao que inicializara a estrutura que armazena os dados, alocando vetor para a mesma
Entrada* inicializaEntrada(int numPags, int numStopWords, char** index, char** stopWords, Lista** graph){
    Entrada* entrada = (Entrada*)malloc(sizeof(Entrada));

    entrada->numPags = numPags;
    entrada->numStopWords = numStopWords;

    entrada->index = index;
    entrada->stopWords = stopWords;
    entrada->graph = graph;

    return entrada;
}

char* getIndex(Entrada* entrada, int indice){
    return entrada->index[indice];
}

char* getStopWord(Entrada* entrada, int indice){
    return entrada->stopWords[indice];
}

Lista* getLinks(Entrada* entrada, int indice){
    return entrada->graph[indice];
}

// funcao que adquire os dados a partir de um arquivo
Entrada* setDados(FILE *indexFile, FILE *stopWordsFile, FILE *graphFile)
{
    // declara variaveis
    Entrada* entrada;
    int numPags = 0, numStopWords = 0, numLinks = 0;

    // realiza leitura do arquivo de index
    numPags = getNumLines(FILE *indexFile);
    char** index = getIndexFile(FILE *indexFile, numPags);

    // realiza leitura do arquivo de stopWords
    numStopWords = getNumLines(FILE *stopWordsFile);
    char** stopWords = getStopWordsFile(FILE *stopWordsFile, numStopWords);

    // realiza leitura do arquivo de graph
    Lista** graph = getGraphFile(FILE *graphFile, numPags);

    // inicializa a entrada
    entrada = inicializaEntrada(index, stopWords, graph);

    return entrada;
}

// funcao que adquire os index a partir do arquivo de index
char** getIndexFile(FILE *indexFile, int numIndex)
{
    // declara variaveis
    char** index = (char**)malloc(sizeof(char*)*numIndex);
    fseek(indexFile, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int i = 0;
    fpos_t pos;
    ssize_t n;


    for (i = 0; i < numIndex; i++)
    {
        n = getline(&line, &len, indexFile);

        index[i] = line;
    }

    // libera a variavel linha
    free(line);
    return index;
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
        n = getline(&line, &len, numStopWords);

        index[i] = line;
    }

    // libera a variavel linha
    free(line);
    return index;
}

// funcao que adquire os index a partir do arquivo de index
Lista** getGraphFile(FILE *indexFile, int numIndex)
{
    // declara variaveis
    char** index = (char**)malloc(sizeof(char*)*numIndex);
    fseek(indexFile, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int i = 0;
    fpos_t pos;
    ssize_t n;


    for (i = 0; i < numIndex; i++)
    {
        n = getline(&line, &len, indexFile);

        pt = strtok(line, ";");
        vOrigem = atoi(pt);
        
        index[i] = line;
    }

    // libera a variavel linha
    free(line);
    return index;
}

// funcao para contar a quantidade de atualizacoes do arquivo
int getNumLines(FILE *arquivo){
    // inicializa variaveis
    size_t len = 0, n = 0;
    char *line = NULL;
    int numLines = 0;

    // conta as atualizacoes
    while (!feof_unlocked(arquivo))
    {
        n = getline(&line, &len, arquivo);
        if (n <= 0)
        {
            // linha vazia ou final do arquivo
            break;
        }
        if (n > 1)
        {
            ++numLines;
        }
    }

    // libera a variavel linha
    free(line);
    return numLines;
}

void limpaDadosEntrada(Entrada* entrada){
    int i;

    for(i = 0; i < entrada->numPags; i++){
        free(entrada->index[i]);
    }

    for(i = 0; i < entrada->numStopWords; i++){
        liberaLista(entrada->stopWords[i]);
    }

    for(i = 0; i < entrada->graph; i++){
        liberaLista(entrada->graph[i]);
    }

    free(entrada->index);
    free(entrada->stopWords);
    free(entrada->graph);
}

void escreveSaida(FILE* saida, int tamCaminho, int* caminhoPercorrido, double distanciaTotal, double tempo){
    int i;
    for (i = 0; i < tamCaminho; i++)
    {
        fprintf(saida, "%d;",caminhoPercorrido[i]);
    }
    fprintf(saida, "%d\n", caminhoPercorrido[i]);

    fprintf(saida, "%.14f\n", distanciaTotal/1000);

    int tmpH, tmpM;
    double tmpS;
    tmpH = tempo/3600;
    tmpM = (tempo -(3600*tmpH))/60;
    tmpS = (tempo -(3600*tmpH)-(tmpM*60));
    fprintf(saida, "%02d:%02d:%.14f", tmpH, tmpM, tmpS);
}