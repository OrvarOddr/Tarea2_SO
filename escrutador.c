// Tarea 2 - Sistemas Operativos 2025
// Integrantes: Alejandro Ortiz - Beatriz Duran - Antonia Merino
// Profesores: Luis Gajardo / Martita Munoz
// ------------------------------------------------------------
// Implementacion de un sistema de votacion usando mensajes.
// Cada tarea vota 0 o 1, y el escrutador devuelve el resultado
// apenas una opcion alcanza mayoria. En caso de empate devuelve -1.
// ------------------------------------------------------------

#include "nSystem.h"
#include "escrutador.h"

typedef struct {
  int tipo;        // 0 = voto, 1 = resultados, 2 = destruir
  int voto;        // usado si tipo = 0
  int *resultados; // usado si tipo = 1
} Msg;

static void servidor(Escrutador esc);

Escrutador fabricarEscrutador(int N) {
  Escrutador esc = (Escrutador) nMalloc(sizeof(*esc));
  esc->n = N;
  esc->votos0 = 0;
  esc->votos1 = 0;
  esc->recibidos = 0;
  esc->decidido = FALSE;
  esc->ganador = -1;
  esc->tarea = nEmitTask(servidor, esc);
  return esc;
}

static void servidor(Escrutador esc) {
  int from;
  Msg msg;

  while (TRUE) {
    nReceive(&from, &msg, sizeof(msg));

    if (msg.tipo == 0) { // votar()
      esc->recibidos++;

      if (msg.voto == 0)
        esc->votos0++;
      else
        esc->votos1++;

      if (!esc->decidido) {
        int mayoria = esc->n / 2 + 1;
        if (esc->votos0 >= mayoria) {
          esc->decidido = TRUE;
          esc->ganador = 0;
        } else if (esc->votos1 >= mayoria) {
          esc->decidido = TRUE;
          esc->ganador = 1;
        } else if (esc->recibidos == esc->n && esc->votos0 == esc->votos1) {
          esc->decidido = TRUE;
          esc->ganador = -1;
        }
      }

      nReply(from, &(esc->ganador), sizeof(int));
    }

    else if (msg.tipo == 1) { // entregarResultados()
      while (esc->recibidos < esc->n)
        nSleep(100); // espera corta

      msg.resultados[0] = esc->votos0;
      msg.resultados[1] = esc->votos1;
      nReply(from, NULL, 0);
    }

    else if (msg.tipo == 2) { // destruirEscrutador()
      nReply(from, NULL, 0);
      break;
    }
  }

  nFree(esc);
}

int votar(Escrutador esc, int voto) {
  Msg msg;
  int resultado;
  msg.tipo = 0;
  msg.voto = voto;
  msg.resultados = NULL;
  nSend(esc->tarea, &msg, sizeof(msg), &resultado, sizeof(int));
  return resultado;
}

void entregarResultados(Escrutador esc, int resultados[]) {
  Msg msg;
  msg.tipo = 1;
  msg.resultados = resultados;
  nSend(esc->tarea, &msg, sizeof(msg), NULL, 0);
}

void destruirEscrutador(Escrutador esc) {
  Msg msg;
  msg.tipo = 2;
  nSend(esc->tarea, &msg, sizeof(msg), NULL, 0);
}