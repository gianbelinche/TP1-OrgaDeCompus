CC = gcc
CFLAGS = -g -std=c99 -O0 -Wall -Werror 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = main.c life.c parseador_archivo.c version_conway_c.c creador_archivo_pbm.c vecinos.c
MFILES = main.c life.c parseador_archivo.c version_conway_MIPS.c creador_archivo_pbm.c vecinos.S
HFILES = life.h parseador_archivo.h version_conway_otro.h creador_archivo_pbm.h vecinos.h
PCFILES = pruebas.c life.c parseador_archivo.c version_conway_c.c creador_archivo_pbm.c vecinos.c
PMFILES = pruebas.c life.c parseador_archivo.c version_conway_MIPS.c creador_archivo_pbm.c vecinos.S
TBFILES = creador_tableros_main.c creador_tableros.c
EXEC_S = conway
EXEC_P = pruebas
EXEC_P = tablero

c: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

mips: $(MFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(MFILES)

pruebas-c: $(PCFILES)
	$(CC) $(CFLAGS) -o $(EXEC_P) $(PCFILES)	

pruebas-mips: $(PMFILES)
	$(CC) $(CFLAGS) -o $(EXEC_P) $(PMFILES)		

tablero: $(TBFILES)
	$(CC) $(CFLAGS) -o $(EXEC_P) $(TBFILES)

clean:
	$(RM) *.o $(EXEC_S)
