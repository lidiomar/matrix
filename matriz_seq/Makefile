# GNU Makefile

CC = gcc
CCFLAGS = -Wall
LDFLAGS =
TARGET = main_matriz gera_matriz matriz_map
EXE = ./gera_matriz

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c -O3 $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o -O3 $@

main_matriz: main_matriz.c matriz.o tools.o
	$(CC) $(CCFLAGS) matriz.o tools.o main_matriz.c -O3 -o $@ $(LDFLAGS)

gera_matriz: matriz.o tools.o gera_matriz.c
	$(CC) $(CCFLAGS) matriz.o tools.o gera_matriz.c -O3 -o $@ $(LDFLAGS)

matriz_map: gera_matriz
	$(EXE) 3 3 > /dev/null
	$(EXE) 10 10 > /dev/null
	$(EXE) 100 100 > /dev/null
	$(EXE) 500 500 > /dev/null

clean:
	rm -f *.o *~ $(TARGET) *.map