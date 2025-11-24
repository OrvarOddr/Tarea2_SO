#ifndef ESCRUTADOR_H
#define ESCRUTADOR_H

#include "nSystem.h"

/* Definicion de la estructura del escrutador */
typedef struct {
  int n;           /* total de votantes */
  int votos0;
  int votos1;
  int recibidos;
  int decidido;
  int ganador;     /* 0, 1 o -1 si hay empate */
  nTask tarea;     /* tarea del escrutador */
} *Escrutador;

/* Prototipos de funciones */
Escrutador fabricarEscrutador(int N);
int votar(Escrutador esc, int voto);
void entregarResultados(Escrutador esc, int resultados[]);
void destruirEscrutador(Escrutador esc);

#endif /* ESCRUTADOR_H */