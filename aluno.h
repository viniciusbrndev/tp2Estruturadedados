#ifndef ALUNO_H
#define ALUNO_H
#include <stdbool.h>

typedef struct{
    int tempo_aloc;
    int tempo_desaloc;
    long tam;
} Processo;

typedef struct{
    int tempo;
    int tipo;
    int processo;
} Evento;

typedef struct{
    long inicio;
    long tam;
} Intervalo;

typedef struct celula{
    Intervalo data;
    struct celula *prox;
}Celula;

typedef struct lista Lista;
Processo* alocaVetProcess(int tam);
RES alocaProcesso(Processo *proc, Lista* pMem, long *alocs, int idProcess);
RES desalocaProcesso(Processo *proc, Lista* pMem, long *alocs, int idProcess);
bool defragMemory(Lista *pLista);
RES comparaEvento(Evento e1, Evento e2);
void merge(Evento *events,int ini, int fim, int m);
void ordenaEventos(Evento*v, int ini, int fim);
long* first_fit(Processo *processos, int num_processos);

#endif