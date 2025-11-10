#include "nSystem.h"
#include "escrutador.h"

int decidido= FALSE;

int elector(Escrutador esc, int delay, int voto) {
  nSleep(delay);
  nPrintf("Votando %d\n", voto);
  votar(esc, voto);
  if (!decidido) {
    nPrintf("Resultado decidido!\n");
    decidido= TRUE;
  }
}

int nMain(int argc, char **argv) {
  nTask t1, t2, t3, t4, t5;
  Escrutador esc= fabricarEscrutador(5);
 
  t1= nEmitTask(elector, esc, 1000, 1); /* Vota dentro de 1 segundo */
  t2= nEmitTask(elector, esc, 2000, 1); /* Vota dentro de 2 segundos */
  t3= nEmitTask(elector, esc, 3000, 0); /* Vota dentro de 3 segundos */
  t4= nEmitTask(elector, esc, 4000, 1); /* Vota dentro de 4 segundos */
  nSleep(3500); /* En 3.5 segundos, t4 todavia no ha votado */
  if (decidido) {
    nPrintf("El resultado no deberia estar decidido todavia.\n");
    nPrintf("Su tarea no funciona correctamente.\n");
    nExitSystem(1);
  }
  /* Cuando t4 vote, el resultado quedara decidido y por lo tanto
   * t1, t2, t3 y t4 deberan terminar.
   */
  nWaitTask(t1);
  nWaitTask(t2);
  nWaitTask(t3);
  nWaitTask(t4);
  
  {
    int resultados[2];
    int ini= nGetTime();
    /* La tarea t5 emitira el ultimo voto dentro de 1 segundo */
    t5= nEmitTask(elector, esc, 1000, 1);
    /* entregarResultados debe bloquearse hasta que t5 vote */
    entregarResultados(esc, resultados);
    if (nGetTime()-ini<1000) {
      nPrintf("entregarResultados debe esperar el ultimo voto.\n");
      nPrintf("Su tarea no funciona correctamente.\n");
      nExitSystem(1);
    }
    if (resultados[0]!=1 || resultados[1]!=4) {
      nPrintf("Los resultados son incorrectos.\n");
      nPrintf("Su tarea no funciona correctamente.\n");
      nExitSystem(1);
    }
    nPrintf("votos 0=%d, votos 1=%d\n", resultados[0], resultados[1]);
    nWaitTask(t5);
  }

  destruirEscrutador(esc);

  nPrintf("Ok, su tarea funciona correctamente\n");
  return 0;
}
