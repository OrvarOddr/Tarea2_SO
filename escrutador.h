typedef struct {
  /* definir la estructura aca */
}
  *Escrutador;

Escrutador fabricarEscrutador(int N);
int votar(Escrutador esc, int voto);
void entregarResultados(Escrutador esc, int resultados[]);
void destruirEscrutador(Escrutador esc);
