prog_3.exe: prog_3_main.o heap.o hash.o graph.o
	g++ -o prog_3.exe prog_3_main.o heap.o hash.o graph.o

prog_3_main.o: ./sources/prog_3_main.cpp
	g++ -c ./sources/prog_3_main.cpp

heap.o: ./sources/heap.cpp ./headers/heap.h
	g++ -c ./sources/heap.cpp

hash.o: ./sources/hash.cpp ./headers/hash.h
	g++ -c ./sources/hash.cpp

graph.o: ./sources/graph.cpp ./headers/graph.h
	g++ -c ./sources/graph.cpp

debug:
	g++ -g -o prog_3_Debug.exe ./sources/prog_3_main.cpp ./sources/heap.cpp ./sources/hash.cpp ./sources/graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups

