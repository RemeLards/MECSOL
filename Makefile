CC=gcc
CFLAGS = -Wall
OBJECTS = my_math.o my_strings.o trabmecsol.o
BINARY = mathi.exe

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $<

clean:
	rm *.o $(BINARY)
