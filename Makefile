CC=g++ -std=c++0x -O3
CFLAGS=-c -Wall -Wextra
SOURCES=main.cpp lattice.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ising

prefix=./

all: $(SOURCES) $(EXECUTABLE) install clean

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm *.o $(EXECUTABLE)

install: ${EXECUTABLE}
	install -m 0755 ${EXECUTABLE} $(prefix)/bin/${EXECUTABLE}

.PHONY: install
