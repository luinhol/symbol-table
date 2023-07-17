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
    RBT* stopWords;
    // arvore rubro negra das palavras que nao sao stopwords
    RBT* palavras;
};

// funcao que inicializara a estrutura que armazena os dados, alocando espaco para a mesma
Entrada* inicializaEntrada(int numPags, int numStopWords, Hash* index, RBT* stopWords, RBT* palavras){
    Entrada* entrada = (Entrada*)malloc(sizeof(Entrada));

    entrada->numPags = numPags;
    entrada->numStopWords = numStopWords;

    entrada->index = index;
    entrada->stopWords = stopWords;
    entrada->palavras = palavras;

    return entrada;
}

Hash* getIndex(Entrada* entrada){
    return entrada->index;
}

RBT* getStopWord(Entrada* entrada, int indice){
    return entrada->stopWords;
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
    RBT* stopWords = getStopWordsFile(stopWordsFile, numStopWords);

    // realiza leitura do arquivo de grafo
    numLinks = getNumLines(grafoFile);
    getGraphFile(index, grafoFile, numLinks);

    // realiza todo o calculo do PR
    calculaPageRank(index, numPags);

    // funcao que adquire os termos e os coloca na arvore de termos
    RBT* palavras = setTermos(stopWords, numPags, index, nomeDirPages);

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
RBT* getStopWordsFile(FILE *stopWordsFile, int numStopWords)
{
    // declara variaveis
    fseek(stopWordsFile, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    char *pt;
    int i = 0;
    ssize_t n;
    RBT* rbt = NULL;
    Termo* termo;
    char* palavra;

    for (i = 0; i < numStopWords; i++)
    {
        n = getline(&line, &len, stopWordsFile);
        pt = strtok(line, "\n");
        strcat(pt, "\0");

        palavra = strdup(pt);

        if(search(rbt, palavra)){ // se o termo ainda nao foi incluido na arvore
            rbt = RBT_insert(rbt, palavra, NULL); // insere palavra na arvore com termo NULO, pois é uma arvore de stop word
        }
        else{
            free(palavra);
        }
    }

    // libera a variavel linha
    free(line);
    return rbt;
}

// funcao que realiza a leitura de um arquivo e salva seus termos em uma arvore rubro negra
RBT* leituraPagina(RBT* rbt, int numPags, FILE* arqPagina, RBT* stopWords, Pagina* pagina){
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

            termo = search(rbt, palavra);
            if(termo == NULL && search(stopWords, palavra) == NULL){ // se o termo ainda nao foi incluido na arvore
                termo = inicializaTermo(palavra, numPags);   // deve ser inicializado
                rbt = RBT_insert(rbt, palavra, termo); // e inserido no arvore
            }
            else{
                free(palavra);
            }
            adcionaPagina(termo, pagina);   // adciona pagina na hash de paginas que o termo esta

            token = strtok(NULL, " \t\n");  // vai para o proximo token
        }
    }
    free(line);
    return rbt;
}

// funcao que realiza a leitura do arquivo
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
        
        // itera sobre as paginas de destino, inserindo o link entre ela e a pagina origem
        for (j = 0; j < numeroPaginas; j++)
        {
            pt = strtok(NULL, " \n");
            paginaDestino = procuraHash(hashTable, pt);
            adcionaLink(paginaOrigem, paginaDestino);
        }
    }

    // libera a variavel linha
    free(line);
}

// funcao que realiza a leitura de todos os arquivos dentro da pasta pages
RBT* setTermos(RBT* stopWords, int numPags, Hash* hash, char* dir){
    int i = 0;
    FILE* arqPagina;
    Lista* lista;
    Pagina* pagina;
    char* nomePagina;
    char* nomeArqPagina;
    int tamNomeArquivo = 0;

    RBT* rbt = NULL;

    // vai iterar na hash de index, abrindo os arquivos referentes a cada index
    for (i = 0; i < getTamanhoHash(hash); i++)
    {
        lista = getListaHash(hash, i);
        if(lista != NULL){
            pagina = getPrim(lista);

            // para cada pagina dentro da lista de paginas de uma celula da hash
            while (pagina != NULL)
            {
                nomeArqPagina = strdup(dir);
                nomePagina = getNomePagina(pagina);
                tamNomeArquivo = strlen(nomeArqPagina) + strlen(nomePagina) + 2;
                nomeArqPagina = (char*)realloc(nomeArqPagina, sizeof(char*)* tamNomeArquivo);
                strcat(nomeArqPagina, nomePagina);
                strcat(nomeArqPagina, "\0");
                arqPagina = fopen(nomeArqPagina, "r");

                // realiza leitura da pagina e salva os termos na arvore de termos
                rbt = leituraPagina(rbt, numPags, arqPagina, stopWords, pagina);

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

// funcao de limpeza da estrutura de entrada
void limpaDadosEntrada(Entrada* entrada){
    liberaHash(entrada->index, true);
    deleteRBT(entrada->palavras);
    deleteRBT(entrada->stopWords);
}

// funcao que realiza a pesquisa de uma sequencia de palavras informada
void realizaPesquisa(Entrada* entrada, char* palavras){
    // inicializa variaveis
    Lista* paginasComuns;
    int qtdMaxTermos = 5, qtdTermos = 0;
    Hash** hashs = (Hash**)calloc(qtdMaxTermos, sizeof(Hash*));
    Termo** termos = (Termo**)calloc(qtdMaxTermos, sizeof(Termo*));
    Termo* termo = NULL;
    char *palavra;
    char *token = strtok(palavras, " \n");

    int i = 0, j = 0;

    // realiza leitura dos tokens e armazena
    while (token != NULL) {
        palavra = strdup(token);
        termo = search(entrada->palavras, palavra); // procura o token na arvore de termos
        free(palavra);

        // se um dos termos nao existir na arvore ja retorna 
        if(termo == NULL){
            break;
        }

        // insere o termo em um vetor de termos
        termos[i] = termo;
        qtdTermos++;

        // armazena a hash de um termo (paginas em que esse termo aparece)
        hashs[i] = getHash(termo);

        i++;
        // verifica se a quantidade de termos informados excedeu o limite dos vetore e aloca mais caso necessário
        if(qtdMaxTermos - qtdTermos < 0){
            i += qtdTermos;
            qtdMaxTermos = qtdMaxTermos*2;
            hashs = (Hash**)realloc(hashs, sizeof(Hash*)*qtdMaxTermos);
            termos = (Termo**)realloc(termos, sizeof(Termo*)*qtdMaxTermos);
        }
        token = strtok(NULL, " \n");  // vai para o proximo token
    }

    // se os termos existirem em algum arquivo, computa as paginas em que aparecem de forma mutua
    if(hashs != NULL){
        paginasComuns = getPaginasComuns(hashs, qtdTermos);
    }

    // reordena as paginas comuns por ordem de PR
    if(paginasComuns != NULL){
        selectionSort(paginasComuns);
    }

    // print pesquisa
    printf("search:", palavras);
    for(j = 0; j < qtdTermos; j++){
        printf("%s ", getNomeTermo(termos[j]));
    }

    // print paginas comuns
    printf("\npages:");
    if(paginasComuns != NULL){
        imprimeLista(paginasComuns);
    }
    printf("\n");

    // print PR das paginas comuns
    printf("pr:");
    if(paginasComuns != NULL){
        imprimePRLista(paginasComuns);
    }
    printf("\n");

    // libera espaco alocado
    if(paginasComuns != NULL){
        liberaLista(paginasComuns);
    }
    
    free(termos);
    free(hashs);
}