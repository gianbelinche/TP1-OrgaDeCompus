CC = gcc
CFLAGS = -g -std=c99 -O0 -Wall -Werror 
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = main.c life.c parseador_archivo.c version_conway_c.c creador_archivo_pbm.c vecinos.c
MFILES = main.c life.c parseador_archivo.c version_conway_MIPS.c creador_archivo_pbm.c vecinos.S
HFILES = life.h parseador_archivo.h version_conway_otro.h creador_archivo_pbm.h vecinos.h
EXEC_S = conway

c: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

mips: $(MFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(MFILES)

clean:
	$(RM) *.o $(EXEC_S)
