CC=g++
CPPFLAGS=-c -g -Wall `root-config --cflags` -I/usr/include/eigen3/ -I./include -I/usr/include
LDFLAGS=`root-config --glibs` -L/usr/lib/x86_64-linux-gnu -lgsl -lgslcblas -lm
#SOURCES= ./src/main.cpp ./src/function.cpp
OBJECTS=main.o diffusion.o
EXECUTABLE=test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

diffusion.o: ./src/diffusion.cpp
	$(CC) ./src/diffusion.cpp $(CPPFLAGS) -o $@

main.o: ./src/main.cpp
	$(CC) ./src/main.cpp $(CPPFLAGS) -o $@

clean:
	rm ./*~ ./*.o ./main
