useHeap.exe: useHeap.o heap.o hash.o
	g++ -o useHeap.exe useHeap.o heap.o hash.o

useHeap.o: ./sources/useHeap.cpp
	g++ -c ./sources/useHeap.cpp

heap.o: ./sources/heap.cpp ./headers/heap.h
	g++ -c ./sources/heap.cpp

hash.o: ./sources/hash.cpp ./headers/hash.h
	g++ -c ./sources/hash.cpp

debug:
	g++ -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups

