.SUFFIXES:
CC = g++
CFLAGS = -g -O3 -std=c++11
LINKER = g++
LFLAGS = -fuse-ld=gold -pthread

OBJS = GameBoard.o TerritoryTracker.o GameState.o MoveList.o

statistics : statistics.o $(OBJS)
	$(LINKER) $(LFLAGS) -o $@ $^

main : main.o $(OBJS)
	$(LINKER) $(LFLAGS) -o $@ $^

%.o : %.cpp %.h Makefile
	$(CC) $(CFLAGS) -c $*.cpp

clean :
	rm main $(OBJS)