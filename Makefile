build: 
	gcc file.c list.c main.c -o fsminishell -lm

run: 
	./fsminishell

clean:
	rm -f fsminishell main.o
