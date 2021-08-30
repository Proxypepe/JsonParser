CC=g++ -std=c++17
TARGET=main
OBJS=main.o DataType.o Lexer.o Json.o FileReader.o
GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

LD_FLAGS = -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread

compile: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LD_FLAGS)

main.o: main.cpp Json.h Test.h FileReader.h
	$(CC) -c -I $(GOOGLE_TEST_INCLUDE) main.cpp

DataType.o: DataType.cpp DataType.h 
	$(CC) -c DataType.cpp

Lexer.o: Lexer.cpp Lexer.h
	$(CC) -c Lexer.cpp

Json.o: Json.cpp Json.h
	$(CC) -c Json.cpp

FileReader.o: FileReader.cpp FileReader.h
	$(CC) -c FileReader.cpp

.PHONY: clean
clean:
	rm -rf *.o  main

.PHONY: run
run:
	./main

.PHONY: mem
mem:
	valgrind ./main
