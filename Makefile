CC = gcc
CFLAGS = -g -std=c99 -O0 -Wall -Werror 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = main.c life.c parseador_archivo.c version_conway_c.c creador_archivo_pbm.c vecinos.c
MFILES = main.c life.c parseador_archivo.c version_conway_MIPS.c creador_archivo_pbm.c vecinos.S
HFILES = life.h parseador_archivo.h version_conway_otro.h creador_archivo_pbm.h vecinos.h
PCFILES = pruebas.c life.c parseador_archivo.c version_conway_c.c creador_archivo_pbm.c vecinos.c
PMFILES = pruebas.c life.c parseador_archivo.c version_conway_MIPS.c creador_archivo_pbm.c vecinos.S
EXEC_S = conway
EXEC_P = pruebas

c: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

mips: $(MFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(MFILES)

pruebas_c: $(PCFILES)
	$(CC) $(CFLAGS) -o $(EXEC_P) $(PCFILES)	

pruebas_mips: $(PMFILES)
	$(CC) $(CFLAGS) -o $(EXEC_P) $(PMFILES)		

clean:
	$(RM) *.o $(EXEC_S)
