CC=gcc
CFLAGS = -Wall
OBJECTS = math_integral.o my_strings.o trabmecsol.o
BINARY = mathi.exe

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $<

clean:
	del *.o $(BINARY)
