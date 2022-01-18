CC = gcc -std=c99
CFLAGS = -g -Wall
TARGET = movies

output: main.o util.o movie.o menu.o
	$(CC) $(CFLAGS) main.o util.o movie.o menu.o -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

movie.o: movie.c movie.h
	$(CC) $(CFLAGS) -c movie.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c

clean:
	rm -f *.o $(TARGET)

run:
	./$(TARGET) $(file)

check:
	valgrind --leak-check=yes ./$(TARGET) $(file)