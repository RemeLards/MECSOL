CC=gcc
CFLAGS = -Wall
OBJECTS = my_math.o my_strings.o trabmecsol.o
BINARY = trab.exe

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o $(BINARY)
