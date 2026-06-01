#ifndef ALUNO_H
#define ALUNO_H


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
long* first_fit(Processo *processos, int num_processos);

#endif