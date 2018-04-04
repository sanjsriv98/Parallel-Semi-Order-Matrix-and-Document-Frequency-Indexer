run: exe
	./exe

gdb: exe
	gdb exe

exe: driver.o _FTW.o _Hash.o _MinHeap.o 
	g++ -o exe driver.o _FTW.o _Hash.o _MinHeap.o -fopenmp

driver.o: driver.cpp _FTW.h
	g++ -c -g driver.cpp -fopenmp

_FTW.o:_FTW.cpp _FTW.h _MinHeap.h _Hash.h
	g++ -c -g _FTW.cpp -fopenmp

_MinHeap.o: _MinHeap.cpp _MinHeap.h _Hash.h
	g++ -c -g _MinHeap.cpp -fopenmp

_Hash.o: _Hash.cpp _Hash.h
	g++ -c -g _Hash.cpp  -fopenmp

clean:
	rm exe *.o 
