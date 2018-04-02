run: exe
	./exe

gdb: exe
	gdb exe

exe: _FTW.o _Hash.o quickSort.o 
	g++ -o exe _FTW.o _Hash.o quickSort.o -fopenmp

_FTW.o:_FTW.cpp _FTW.h quickSort.h _Hash.h
	g++ -c -g _FTW.cpp -fopenmp

quickSort.o: quickSort.cpp quickSort.h _Hash.h
	g++ -c -g quickSort.cpp -fopenmp

_Hash.o: _Hash.cpp _Hash.h
	g++ -c -g _Hash.cpp  -fopenmp

clean:
	rm exe *.o 
