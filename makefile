compile runme: main.o
	@gcc -o runme main.o -Wall
main.o: main.c
	@gcc -c main.c -Wall
run:
	@./runme
clean:
	rm *.o
	rm runme
