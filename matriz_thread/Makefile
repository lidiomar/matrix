# GNU Makefile

CC = gcc
CCFLAGS = -Wall
LDFLAGS =
TARGET = main_matriz_thread gera_matriz
#EXE = ./gera_matriz

all: $(TARGET)

matriz_thread.o: matriz_thread.c
	$(CC) $(CCFLAGS) -O3 -c matriz_thread.c -o matriz_thread.o

tools.o: tools.c
	$(CC) $(CCFLAGS) -O3 -c tools.c -o tools.o

main_matriz_thread: main_matriz_thread.c matriz_thread.o tools.o
	$(CC) $(CCFLAGS) matriz_thread.o tools.o main_matriz_thread.c -o $@ $(LDFLAGS)

gera_matriz: matriz_thread.o tools.o gera_matriz.c
	$(CC) $(CCFLAGS) matriz_thread.o tools.o gera_matriz.c -o $@ $(LDFLAGS)

#matriz_map: gera_matriz
	#$(EXE) 3 3 > /dev/null
	#$(EXE) 10 10 > /dev/null
	#$(EXE) 100 100 > /dev/null
	#$(EXE) 500 500 > /dev/null

clean:
	rm -f *.o *~ $(TARGET) *.map