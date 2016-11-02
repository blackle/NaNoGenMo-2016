CC = g++
CFLAGS = -g -O2 -std=c++11
LINKER = g++
LFLAGS = -fuse-ld=gold

OBJS = main.o GameBoard.o TerritoryTracker.o GameState.o

main : $(OBJS)
	$(LINKER) $(LFLAGS) -o $@ $^

%.o : %.cpp %.h Makefile
	$(CC) $(CFLAGS) -c $*.cpp

clean :
	rm main $(OBJS)