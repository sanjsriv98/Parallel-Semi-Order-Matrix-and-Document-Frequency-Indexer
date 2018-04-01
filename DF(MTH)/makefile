run: exe
	./exe

exe: _Dict.o _FTW.o _MinHeap.o _Trie.o
	g++ -o exe -g _FTW.o _Dict.o _MinHeap.o _Trie.o

_FTW.o:_FTW.cpp _FTW.h	_Dict.h _MinHeap.h
	g++ -g -c  _FTW.cpp

_Dict.o: _Dict.cpp _Dict.h _MinHeap.h
	g++ -g -c  _Dict.cpp

_MinHeap.o: _MinHeap.cpp _MinHeap.h _Trie.h
	g++ -g -c  _MinHeap.cpp

_Trie.o:_Trie.c _Trie.h _MinHeap.h
	g++ -g -c _Trie.c

clean:
	rm exe *.o 