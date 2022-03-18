CC=g++

OBJ1=jacobi_iter.cpp
OBJ2=gs_iter.cpp

jacobi: $(OBJ1)
	$(CC) -O3 -o $@ $^

gs: $(OBJ2)
	$(CC) -O3 -o $@ $^

.PHONY: clean

clean:
	rm -f gs jacobi