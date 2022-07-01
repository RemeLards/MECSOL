CC=gcc
CFLAGS = -Wall
OBJECTS = math_integral.o my_strings.o
BINARY = mathi.exe

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $<

clean:
	rm *.o $(BINARY)
