CC=gcc
CFLAGS = -Wall
OBJECTS = my_math.o my_strings.o trabmecsol.o menu.o pbPlots.o supportLib.o -lm
BINARY = trab.exe

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

clean:
	del *.o *.png $(BINARY) 
