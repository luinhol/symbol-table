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
    // arvore rubro negra das palavras que nao sao stopwords
    RBT* palavras;
};

// funcao que inicializara a estrutura que armazena os dados, alocando vetor para a mesma
Entrada* inicializaEntrada(int numPags, int numStopWords, Hash* index, char** stopWords, RBT* palavras){
    Entrada* entrada = (Entrada*)malloc(sizeof(Entrada));

    entrada->numPags = numPags;
    entrada->numStopWords = numStopWords;

    entrada->index = index;
    entrada->stopWords = stopWords;
    entrada->palavras = palavras;

    return entrada;
}

static char* limpaBarraN(char* str){
    int i = 0;
    for(i = 0;; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            return str;
        }
    }
}

Hash* getIndex(Entrada* entrada){
    return entrada->index;
}

char* getStopWord(Entrada* entrada, int indice){
    return entrada->stopWords[indice];
}

// funcao que adquire os dados a partir de um arquivo
Entrada* setDados(FILE *indexFile, FILE *stopWordsFile, FILE *grafoFile, char* nomeDirPages)
{
    // declara variaveis
    Entrada* entrada;
    int numPags = 0, numStopWords = 0, numLinks = 0;

    // realiza leitura do arquivo de index
    numPags = getNumLines(indexFile);
    // printf("num pags: %d\n", numPags);
    Hash* index = getIndexFile(indexFile, numPags);

    // realiza leitura do arquivo de stopWords
    numStopWords = getNumLines(stopWordsFile);
    char** stopWords = getStopWordsFile(stopWordsFile, numStopWords);

    // realiza leitura do arquivo de grafo
    numLinks = getNumLines(grafoFile);
    getGraphFile(index, grafoFile, numLinks);

    calculaPageRank(index, numPags);

    // imprimeHash(index);

    // imprimeHash(index);
    RBT* palavras = setTermos(numPags, index, nomeDirPages);

    // inicializa a entrada
    entrada = inicializaEntrada(numPags, numStopWords, index, stopWords, palavras);

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
    char *nome;
    int i = 0;
    fpos_t pos;
    ssize_t n;

    for (i = 0; i < numPags; i++)
    {
        n = getline(&line, &len, indexFile);
        pt = strtok(line, "\n");
        strcat(pt, "\0");
        nome = strdup(pt);

        Pagina* p = inicializaPagina(nome);

        insereHash(h, getNomePagina(p), p);
    }

    // libera a variavel linha
    free(line);
    return h;
}

// funcao que adquire os index a partir do arquivo de index
char** getStopWordsFile(FILE *stopWordsFile, int numStopWords)
{
    // declara variaveis
    char** stopWords = (char**)malloc(sizeof(char*)*numStopWords);
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
        pt = strtok(line, "\n");
        strcat(pt, "\0");
        stopWords[i] = strdup(pt);
    }

    // libera a variavel linha
    free(line);
    return stopWords;
}

void getGraphFile(Hash* hashTable, FILE *graphFile, int numLines)
{
    // declara variaveis
    fseek(graphFile, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int i = 0, j = 0;
    fpos_t pos;
    ssize_t n;
    Pagina* paginaOrigem = NULL;
    Pagina* paginaDestino = NULL;

    for (i = 0; i < numLines; i++)
    {
        n = getline(&line, &len, graphFile);
        pt = strtok(line, " ");

        // pagina de origem
        paginaOrigem = procuraHash(hashTable, pt);

        // numero de paginas destino
        pt = strtok(NULL, " ");

        int numeroPaginas = atoi(pt);
        
        for (j = 0; j < numeroPaginas; j++)
        {
            pt = strtok(NULL, " \n");
            // limpaBarraN(pt);
            paginaDestino = procuraHash(hashTable, pt);
            adcionaLink(paginaOrigem, paginaDestino);
        }
    }

    // libera a variavel linha
    free(line);
}

RBT* setTermos(int numPags, Hash* hash, char* dir){
    int i = 0;
    FILE* arqPagina;
    Lista* lista;
    Pagina* pagina;
    char* nomePagina;
    char* nomeArqPagina;
    int tamNomeArquivo = 0;

    RBT* rbt = NULL;

    for (i = 0; i < getTamanhoHash(hash); i++)
    {
        lista = getListaHash(hash, i);
        if(lista != NULL){
            pagina = getPrim(lista);

            while (pagina != NULL)
            {
                nomeArqPagina = strdup(dir);

                nomePagina = getNomePagina(pagina);
                tamNomeArquivo = strlen(nomeArqPagina) + strlen(nomePagina) + 2;
                nomeArqPagina = (char*)realloc(nomeArqPagina, sizeof(char*)* tamNomeArquivo);
                strcat(nomeArqPagina, nomePagina);
                strcat(nomeArqPagina, "\0");
                arqPagina = fopen(nomeArqPagina, "r");

                rbt = leituraPagina(rbt, numPags, arqPagina, pagina);

                free(nomeArqPagina);
                fclose(arqPagina);
                pagina = proxPagina(lista);
            }
        }
    }
    return rbt;
}

// funcao para contar a quantidade de linhas do arquivo
int getNumLines(FILE *arquivo){
    // fseek(arquivo, 0, SEEK_SET);
    // inicializa variaveis
    ssize_t len = 0, n = 0;
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

RBT* leituraPagina(RBT* rbt, int numPags, FILE* arqPagina, Pagina* pagina){
    fseek(arqPagina, 0, SEEK_SET);

    size_t len = 0;
    char *line = NULL;
    char *pt;
    Termo* termo;
    char* palavra;

    while (!feof_unlocked(arqPagina))
    {
        ssize_t n = getline(&line, &len, arqPagina);

        char *token = strtok(line, " \t\n");  // divide o buffer com os delimitadores

        while (token != NULL) {
            palavra = strdup(token);
            // printf("palavra: %s\n", palavra);
            termo = search(rbt, palavra);
            if(termo == NULL){ // se o termo ainda nao foi incluido na arvore
                termo = inicializaTermo(palavra, numPags);   // deve ser inicializado
                // liberaTermo(termo);
                rbt = RBT_insert(rbt, palavra, termo); // e inserido no arvore
            }
            else{
                free(palavra);
            }
            adcionaPagina(termo, pagina);   // adciona pagina na hash de paginas que o termo esta

            token = strtok(NULL, " \t\n");  // vai para o proximo token
        }
    }
    // printf("paginas de cada termo:\n");
    // printRBT(rbt);
    free(line);
    return rbt;
}

void limpaDadosEntrada(Entrada* entrada){
    int i;

    for(i = 0; i < entrada->numStopWords; i++){
        free(entrada->stopWords[i]);
    }
    free(entrada->stopWords);
    liberaHash(entrada->index, true);
    deleteRBT(entrada->palavras);
}

void escreveSaida(Entrada* entrada, FILE* saida){
    fprintf(saida, "stopwords:\n");
    for (int i = 0; i < entrada->numStopWords; i++)
    {
        fprintf(saida, "%s\n", entrada->stopWords[i]);
    }
}

void realizaPesquisa(Entrada* entrada, char* palavras){
    printf("search:%s", palavras);

    Pagina** pages;
    Lista* paginasComuns;

    int tamHashs = 5, qtdHashs = 0;
    Hash** hashs = (Hash**)calloc(tamHashs, sizeof(Hash*));

    Termo* termo = NULL;
    char *palavra;
    char *token = strtok(palavras, " ");

    int i = 0;

    // realiza leitura dos tokens e armazena o vetor dos termos
    while (token != NULL) {
        palavra = strdup(token);
        termo = search(entrada->palavras, palavra);
        free(palavra);

        // se um dos termos nao existir na arvore ja retorna 
        if(termo == NULL){
            break;
        }

        hashs[i] = getHash(termo);
        qtdHashs++;

        i++;
        if(tamHashs - i <= 0){
            i += tamHashs;
            tamHashs = tamHashs*2;
            hashs = (Hash**)realloc(hashs, sizeof(Hash*)*tamHashs);
        }
        token = strtok(NULL, " \n");  // vai para o proximo token
    }

    // for(i = 0; i < numTermos; i++){
    //     printf("\ntermo: %s", getNomeTermo(termos[i]));
    // }

    if(hashs != NULL){
        paginasComuns = getPaginasComuns(hashs, qtdHashs);
    }

    if(paginasComuns != NULL){
        selectionSort(paginasComuns);
    }

    printf("pages:");
    if(paginasComuns != NULL){
        imprimeLista(paginasComuns);
    }
    printf("\n");

    printf("pr:");
    if(paginasComuns != NULL){
        imprimePRLista(paginasComuns);
    }
    printf("\n");

    if(paginasComuns != NULL){
        liberaLista(paginasComuns);
    }
    free(hashs);
}