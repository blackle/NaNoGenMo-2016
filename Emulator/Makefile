CC = g++
CFLAGS = -g -O2
LINKER = g++
LFLAGS = -fuse-ld=gold

OBJS = main.o GameBoard.o

main : $(OBJS)
	$(LINKER) $(LFLAGS) -o $@ $^

%.o : %.cpp %.h Makefile
	$(CC) $(CFLAGS) -c $*.cpp

clean :
	rm main $(OBJS)