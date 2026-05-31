#include <stdlib.h>
#include "aluno.h"


#define ALLOCATION_EVENT 0
#define DEALLOCATION_EVENT 1


long * first_fit(Processo *processos, int num_processos) {
    long * alocacoes = (long *)malloc(num_processos*sizeof(long));
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

    return alocacoes;
}