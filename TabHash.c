#include <stdio.h>
#include <stdlib.h>

#define TAM_HASH 10

struct est_no_hash
{
    int chave;
    char valor;
    struct est_no_hash *prox;
};
typedef struct est_no_hash tipo_no_hash;

struct est_tab_hash
{
    tipo_no_hash *TabelaHash [TAM_HASH];
};
typedef struct est_tab_hash tipo_tab_hash;



//prototipação

void InicializaTabhash(tipo_tab_hash*);
tipo_no_hash *AlocaNohash(int , int );
int FuncaoHash(int );
tipo_no_hash * BuscaTabHash(tipo_tab_hash *, int );
void InsereTabHash(tipo_tab_hash *, int, char);
char RemoveTabahsh(tipo_tab_hash*, int);

//implementação das funções da Tabela hash

//função responsável por inicilaizar a Tabela Hash, definindo todas posições do vetor (TabelaHash) como NULL
void InicializaTabhash(tipo_tab_hash * tbh){
    int i;

    for (i = 0; i < TAM_HASH; i++){
        tbh -> TabelaHash [i] = NULL;
    }
}

//Função responsavel para alocar dinamicamente na memória um novo_no
tipo_no_hash *AlocaNohash(int chave, int dado ){
    tipo_no_hash * novo_no;
    novo_no = (tipo_no_hash*)malloc(sizeof(tipo_no_hash));
    novo_no -> chave = chave;
    novo_no -> valor = dado;
    novo_no -> prox = NULL;
    return novo_no;
}

//função responsavel por calcular o índice onde o dado com uma determinada chace deve ser armanzada na TabelaHash
int FuncaoHash(int chave){
    return chave %TAM_HASH;
}

//função responsável por procurar na tabela hash uma chave especificada e retorna-la se encontrada 
tipo_no_hash * BuscaTabHash(tipo_tab_hash *tbh , int chave){//a função é declarada com um ponteiro tipo_tb_hash e uma chave como parãmetro 
    tipo_no_hash *aux;
    int pos;

    //calcular a posição na tabela hash usando a "Funcaohash" 
    pos = FuncaoHash(chave);

    if (tbh -> TabelaHash[pos] == NULL){
        return NULL;  // se não houver nenhum nó na posição caculada, rertonar NULL. indicando que o ó com a chave não foi encontrado 

    }else{// se não for NULL
        aux = tbh -> TabelaHash [pos]; // inicializa o ponteiro auxiliar com a posição adquirida, para percorrer a lista encadeada nessa posição da tabela hash

        while (aux != NULL) // enquanto auxiliar for diferente de nulo fça
        {
            if (aux -> chave == chave){ //se ao percorrer a lista encadeada for encontrada a chave correspondente, retornar ponteiro auxiliar 
                return aux; 
            }
        }
        return NULL;
    }

}


void InsereTabHash(tipo_tab_hash * tbh , int chave, char valor){
    
    int pos;
    tipo_no_hash * novo_no;

    //verificar se já existe um nó com a mesma chave na tabela hash
    if(BuscaTabHash(tbh, chave)== NULL){

        //calcular a posição na TabelaHash usando a "FuncaoHash"
        pos = FuncaoHash(chave);

        novo_no = AlocaNohash(chave, valor);//aloca memória para um novo_no com a chave e o valor especificado

        if (tbh -> TabelaHash [pos] == NULL){
            tbh -> TabelaHash[pos] = novo_no; // novo nó é atribuido diretamente na posição existente nesta posição 


        }else{//se não for igual a NULL, o novo nó é encadeado na lista 

        
            novo_no -> prox = tbh -> TabelaHash [pos];
            tbh -> TabelaHash [pos] = novo_no;
        }
    }
}


char RemoveTabahsh(tipo_tab_hash *tbh, int chave){
    tipo_no_hash *aux, *ant;
    int pos;
    char dado;

    //verificar se o nó com a chave especificadaestá presente na tabela hash

    aux = BuscaTabHash(tbh, chave);

    if (aux != NULL){
        pos = (FuncaoHash(chave));

        //verficar se o nó a ser removido é o primeiro nó na posição da tabela hash

        if( tbh -> TabelaHash[pos] == NULL){
            dado = aux-> valor;//salva o valor do nó que vai ser removido 
            free(aux);

            tbh-> TabelaHash[pos] = NULL;

        }else{
            ant = tbh -> TabelaHash[pos];
            while (ant -> prox != aux){
                ant = ant -> prox;
            }
            ant -> prox = aux -> prox;
            
        }
        dado = aux -> valor;

        free (aux);

        return dado;

    }

    return '\0';
}

