run: exe
	./exe

exe: _Dict.o _FTW.o _MinHeap.o _Trie.o
	g++ -o exe -g _FTW.o _Dict.o _MinHeap.o _Trie.o -fopenmp -std=c++11

_FTW.o:_FTW.cpp _FTW.h	_Dict.h _MinHeap.h
	g++ -g -c  _FTW.cpp -fopenmp -std=c++11

_Dict.o: _Dict.cpp _Dict.h _MinHeap.h
	g++ -g -c  _Dict.cpp -fopenmp -std=c++11

_MinHeap.o: _MinHeap.cpp _MinHeap.h _Trie.h
	g++ -g -c  _MinHeap.cpp -fopenmp -std=c++11

_Trie.o:_Trie.cpp _Trie.h _MinHeap.h
	g++ -g -c _Trie.cpp -fopenmp -std=c++11

clean:
	rm exe *.o 