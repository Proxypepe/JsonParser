CC=g++ -std=c++17
TARGET=main
OBJS=main.o DataType.o Lexer.o Json.o


compile: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.cpp   DataType.h Lexer.h Json.h
	$(CC) -c main.cpp

DataType.o: DataType.cpp DataType.h 
	$(CC) -c DataType.cpp

Lexer.o: Lexer.cpp Lexer.h
	$(CC) -c Lexer.cpp

.PHONY: clean
clean:
	rm -rf *.o  main

.PHONY: run
run:
	./main
