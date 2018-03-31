run: exe
	./exe < input 

gdb: exe
	gdb ./exe

exe: driver.o
	g++ -g driver.o -o exe -fopenmp

driver.o : driver.cpp semiorder.h
	g++ -c -g driver.cpp -fopenmp

clean:
	rm exe *.o