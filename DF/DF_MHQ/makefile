run: exe
	./exe

gdb: exe
	gdb exe

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
	
exe: _FTW.o _Hash.o quickSort.o driver.o 
	g++ -o exe driver.o _FTW.o _Hash.o quickSort.o -fopenmp

driver.o: driver.cpp _FTW.h
	g++ -c -g driver.cpp -fopenmp

_FTW.o:_FTW.cpp _FTW.h quickSort.h _Hash.h
	g++ -c -g _FTW.cpp -fopenmp

quickSort.o: quickSort.cpp quickSort.h _Hash.h
	g++ -c -g quickSort.cpp -fopenmp

_Hash.o: _Hash.cpp _Hash.h
	g++ -c -g _Hash.cpp  -fopenmp

clean:
	rm exe *.o 
