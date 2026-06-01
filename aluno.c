#include <stdlib.h>
#include "aluno.h"
#include <stdbool.h>

#define ALLOCATION_EVENT 0
#define DEALLOCATION_EVENT 1

struct lista{
    int tamMax;
    Celula* cab;
    Celula* fim;
};
typedef enum{
    ALOCOU,
    DESALOC,
    FULL,
    ERRO,
}RES;

Lista* criaLista(int tam_max){
    Lista* pTemp = (Lista*)malloc(sizeof(Lista));
    if(pTemp){
        pTemp->cab = (Celula*)malloc(sizeof(Celula));
        pTemp->tamMax = tam_max;
        if(!pTemp->cab){
            free(pTemp);
            pTemp = NULL;
        }

        pTemp->cab->data.inicio = 0;
        pTemp->cab->data.tam = 0;
        Celula *memory = (Celula*)malloc(sizeof(Celula));
        if(!memory){
            free(pTemp->cab);
            free(pTemp);
            return NULL;
        }
        memory->data.inicio = 0;
        memory->data.tam = tam_max;
        memory->prox = NULL;
        pTemp->cab->prox = memory;
        pTemp->fim = memory;
    }
    return pTemp;
}

Processo* alocaVetProcess(int tam){
    if(tam <= 0)
        return NULL;
    Processo *pTemp = (Processo*)malloc(sizeof(Processo)*tam);
    if(!pTemp)
        pTemp = NULL;
    return pTemp;
}



RES alocaProcesso(Processo *proc, Lista* pMem, long *alocs, int idProcess){
    if(!proc || !pMem || !alocs)
        return ERRO;
    Celula *aux = pMem->cab->prox;
    Celula *ant = pMem->cab;
    while(aux != NULL && aux->data.tam < proc->tam){
        ant = aux;      
        aux = aux->prox;    //caminhando na lista
    }
    if(!aux)
        return FULL; //toda e memória foi consumida e nenhum bloco foi liberado
    
    alocs[idProcess] = aux->data.inicio;
    //separando os espaços na memória

    //atualiza o inicio do bloco (alocando memória)
    aux->data.inicio = aux->data.inicio + proc[idProcess].tam;
    //atualiza o tamanho restante do bloco
    aux->data.tam = aux->data.tam - proc[idProcess].tam; 

    if(aux->data.tam == 0){
        ant->prox = aux->prox;
        if(pMem->fim == aux)
            pMem->fim = ant;
        free(aux);
    }
    return ALOCOU;
}
RES desalocaProcesso(Processo *proc, Lista* pMem, long *alocs, int idProcess){
    if(!proc || !pMem || !alocs)
        return ERRO;
    Celula* aux = pMem->cab->prox;
    if(!aux->prox){
        aux->prox = (Celula*)malloc(sizeof(Celula));
        aux = aux->prox;
        aux->prox = NULL;
        aux->data.inicio = *alocs;
        aux->data.tam = proc->tam;
        pMem->fim = aux;
    }
    while(*alocs > aux->data.inicio && aux->prox)
        aux = aux->prox;
    Celula *prox = aux->prox;
    Celula *novo = (Celula*)malloc(sizeof(Celula));
    novo->prox = prox;
    novo->data.inicio = *alocs;
    novo->data.tam = proc->tam;
    aux->prox = novo;
    return DESALOC;
}



bool ordenaEventos(Evento*v, int ini, int fim){

}
long* first_fit(Processo *processos, int num_processos) {
    long *alocacoes = (long *)malloc(num_processos*sizeof(long));
    Evento *eventos = (Evento*)malloc(sizeof(Evento) * num_processos * 2);
    long max_tam = 0;
    for (int i = 0; i < num_processos; ++i) {
        // Evento de alocacao
        eventos[2*i].tempo = processos[i].tempo_aloc;
        eventos[2*i].tipo = ALLOCATION_EVENT;
        eventos[2*i].processo = i;

        // Evento de desalocacao
        eventos[2*i+1].tempo = processos[i].tempo_desaloc;
        eventos[2*i+1].tipo = DEALLOCATION_EVENT;
        eventos[2*i+1].processo = i;

        max_tam += processos[i].tam;
    }

    // Insira aqui sua implementação
    Lista* memory = criaLista(max_tam);
    int aux;
    for(int i = 0; i < num_processos*2; i++){
        aux = eventos[i].processo; //Qual processo está sendo modificado
        if(eventos[i].tipo == ALLOCATION_EVENT)
            if(alocaProcesso(processos, memory, alocacoes, aux) == FULL){
                printf("Memória Cheia!\n");
            }
                
        else{
            desalocaProcesso(processos, memory, alocacoes, aux);
        }
    }






    return alocacoes;
}