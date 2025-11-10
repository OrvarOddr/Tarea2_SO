LIBNSYS= $(NSYSTEM)/lib/libnSys.a

CFLAGS= -ggdb -I$(NSYSTEM)/include -I$(NSYSTEM)/src
LFLAGS= -ggdb

all: verificador

.SUFFIXES:
.SUFFIXES: .o .c .s

.c.o .s.o:
	gcc -c $(CFLAGS) $<

verificador: verificador.o escrutador.o
	gcc $(LFLAGS) verificador.o escrutador.o -o $@ $(LIBNSYS)

clean:
	rm -f *.o *~

cleanall:
	rm -f *.o *~ verificador
