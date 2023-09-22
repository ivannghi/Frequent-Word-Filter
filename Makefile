CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

all: fw

fw: fw.c
	$(CC) $(CFLAGS) fw.c -o fw

test:
	./fw -n 10 file1.txt > result.txt
	diff result.txt expected.txt

clean:
	rm -f fw result.txt
