#ifndef ESCRUTADOR_H
#define ESCRUTADOR_H

#include "nSystem.h"

/* La estructura COMPLETA va aquí */
typedef struct {
  int n;           // total de votantes
  int votos0;
  int votos1;
  int recibidos;
  int decidido;
  int ganador;     // 0, 1 o -1 si empate
  nTask tarea;     // tarea del escrutador
} *Escrutador;

/* Solo las firmas de funciones */
Escrutador fabricarEscrutador(int N);
int votar(Escrutador esc, int voto);
void entregarResultados(Escrutador esc, int resultados[]);
void destruirEscrutador(Escrutador esc);

#endif