# GNU Makefile

CC = gcc
CCFLAGS = -Wall
LDFLAGS =
TARGET = main_ordenacao gera_matriz
#EXE = ./gera_matriz

all: $(TARGET)

ordenacao.o: ordenacao.c
	$(CC) $(CCFLAGS) -O3 -c ordenacao.c -Xpreprocessor -fopenmp -lomp -o ordenacao.o

tools.o: tools.c
	$(CC) $(CCFLAGS) -O3 -c tools.c -o tools.o

main_ordenacao: main_ordenacao.c ordenacao.o tools.o
	$(CC) $(CCFLAGS) ordenacao.o tools.o main_ordenacao.c -Xpreprocessor -fopenmp -lomp -o $@ $(LDFLAGS)

gera_matriz: ordenacao.o tools.o gera_matriz.c
	$(CC) $(CCFLAGS) ordenacao.o tools.o gera_matriz.c -Xpreprocessor -fopenmp -lomp -o $@ $(LDFLAGS)

#matriz_map: gera_matriz
	#$(EXE) 3 3 > /dev/null
	#$(EXE) 10 10 > /dev/null
	#$(EXE) 100 100 > /dev/null
	#$(EXE) 500 500 > /dev/null

clean:
	rm -f *.o *~ $(TARGET) *.map