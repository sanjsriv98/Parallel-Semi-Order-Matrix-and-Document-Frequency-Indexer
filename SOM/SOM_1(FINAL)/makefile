exe: driver.o
	g++ -g driver.o -o exe -fopenmp

runall: run1 run2 run3 run4

run: exe
	./exe 4 < ../input4

run1: exe
	./exe 1 < ../input1
	./exe 2 < ../input1
	./exe 4 < ../input1
	./exe 8 < ../input1
	./exe 16 < ../input1
	./exe 32 < ../input1
	./exe 48 < ../input1
	./exe 64 < ../input1
	./exe 96 < ../input1

run2: exe
	./exe 1 < ../input2
	./exe 2 < ../input2
	./exe 4 < ../input2
	./exe 8 < ../input2
	./exe 16 < ../input2
	./exe 32 < ../input2
	./exe 48 < ../input2
	./exe 64 < ../input2
	./exe 96 < ../input2


run3: exe
	./exe 1 < ../input3
	./exe 2 < ../input3
	./exe 4 < ../input3
	./exe 8 < ../input3
	./exe 16 < ../input3
	./exe 32 < ../input3
	./exe 48 < ../input3
	./exe 64 < ../input3
	./exe 96 < ../input3

run4: exe
	./exe 1 < ../input4
	./exe 2 < ../input4
	./exe 4 < ../input4
	./exe 8 < ../input4
	./exe 16 < ../input4
	./exe 32 < ../input4
	./exe 48 < ../input4
	./exe 64 < ../input4
	./exe 96 < ../input4

run5: exe
	./exe 1 < ../input5
	./exe 2 < ../input5
	./exe 4 < ../input5
	./exe 8 < ../input5
	./exe 16 < ../input5
	./exe 32 < ../input5
	./exe 48 < ../input5
	./exe 64 < ../input5
	./exe 96 < ../input5

gdb: exe
	gdb ./exe

driver.o : driver.cpp semiorder.h
	g++ -c -g driver.cpp -fopenmp

clean:
	rm exe *.o