CC = g++
CPPFLAGS = -g -pedantic -Wall
CFLAGS = -pedantic
CLINK = -lglut -lGL -lGLU -lGLEW

all: psi

psi: main.o psi.o
	$(CC) $(CPPFLAGS) main.o psi.o -o elektron

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

psi.o: psi.cpp
	$(CC) $(CPPFLAGS) -c psi.cpp

del:
	rm *.dat *.out *.png *.gif

clean:
	rm -rf *.o *.dat *.out *.png *.gif elektron
