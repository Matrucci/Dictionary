a.out: main.o genericBinTree.o dictionary.o genericSort.o intFunctions.o
	gcc -std=c99 main.o genericBinTree.o dictionary.o genericSort.o intFunctions.o
main.o: main.c
	gcc -c -std=c99 main.c
dictionary.o: dictionary.c dictionary.h
	gcc -c -std=c99 dictionary.c
genericBinTree.o: genericBinTree.c genericBinTree.h
	gcc -c -std=c99 genericBinTree.c
genericSort.o: genericSort.c genericSort.h
	gcc -c -std=c99 queue.c
intFunctions.o: intFunctions.c intFunctions.h
	gcc -c -std=c99 intFunctions.c
clean:
	rm -f *.o a.out
run: a.out
	./a.out
