run: exe2
	./exe2 4 < input4

run2: exe
	./exe 1 < input2
	./exe 2 < input2
	./exe 4 < input2
	./exe 8 < input2
	./exe 16 < input2
	./exe 32 < input2
	./exe 64 < input2
	./exe 128 < input2


run3: exe
	./exe 1 < input3
	./exe 2 < input3
	./exe 4 < input3
	./exe 8 < input3
	./exe 16 < input3
	./exe 32 < input3
	./exe 64 < input3
	./exe 128 < input3

run4: exe
	./exe 1 < input4
	./exe 2 < input4
	./exe 4 < input4
	./exe 8 < input4
	./exe 16 < input4
	./exe 32 < input4
	./exe 64 < input4
	./exe 128 < input4

run5: exe
	./exe 1 < input5
	./exe 2 < input5
	./exe 4 < input5
	./exe 8 < input5
	./exe 16 < input5
	./exe 32 < input5
	./exe 64 < input5
	./exe 128 < input5

gdb: exe
	gdb ./exe

exe: driver.o
	g++ -g driver.o -o exe -fopenmp

driver.o : driver.cpp semiorder.h
	g++ -c -g driver.cpp -fopenmp

exe2: driver2.o
	g++ -g driver2.o -o exe2 -fopenmp

driver2.o : driver2.cpp semiorder2.h
	g++ -c -g driver2.cpp -fopenmp

inputmat2:
	python makeSOM.py > input2

inputmat3:
	python makeSOM.py > input3

inputmat4:
	python makeSOM.py > input4

inputmat5:
	python makeSOM.py > input5

clean:
	rm ex* *.o