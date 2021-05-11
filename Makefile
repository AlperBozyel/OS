CC=gcc
CFLAGS=-Wall

PROJECT=gsu_shell
OBJECTS=parser.o

$(PROJECT): $(PROJECT).c $(OBJECTS)

%.o: %.c %.h

doc:
	doxygen

clean:
	rm -rf *.o $(PROJECT)
