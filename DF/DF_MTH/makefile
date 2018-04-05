run: exe
	./exe

run1:exe
	./exe 10 96 $(dir)
	./exe 10 48 $(dir)
	

run2:exe
	./exe 10 64 $(dir)
	./exe 10 32 $(dir)
	

run3:exe
	./exe 10 16 $(dir)
	./exe 10 8 $(dir)
	
run4:exe
	./exe 10 4 $(dir)
	./exe 10 1 $(dir)

exe:  _Dict.o _FTW.o _MinHeap.o _Trie.o driver.o
	g++ -o exe -g driver.o _FTW.o _Dict.o _MinHeap.o _Trie.o -fopenmp 

driver.o: driver.cpp _FTW.h _Dict.h _MinHeap.h
	g++ -g -c  driver.cpp -fopenmp 

_FTW.o:_FTW.cpp _FTW.h	_Dict.h _MinHeap.h
	g++ -g -c  _FTW.cpp -fopenmp 

_Dict.o: _Dict.cpp _Dict.h _MinHeap.h
	g++ -g -c  _Dict.cpp -fopenmp 

_MinHeap.o: _MinHeap.cpp _MinHeap.h _Trie.h
	g++ -g -c  _MinHeap.cpp -fopenmp 

_Trie.o:_Trie.cpp _Trie.h _MinHeap.h
	g++ -g -c _Trie.cpp -fopenmp 

clean:
	rm exe *.o 
