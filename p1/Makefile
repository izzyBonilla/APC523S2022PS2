CC=g++
OBJ_1=lg_interp.cpp
OBJ_2=lg_err.cpp

interp: $(OBJ_1)
	$(CC) -O3 -o $@ $^

interp_err: $(OBJ_2)
	$(CC) -O3 -fopenmp -o $@ $^


.PHONY: clean

clean:
	rm -f interp
	rm -f interp_err
