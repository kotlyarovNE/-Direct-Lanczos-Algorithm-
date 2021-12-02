CC = g++
CFLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wcast-align -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

all: a.out

a.out: main.o input_A_b.o LANCZOS_ALG.o all_functions.h
	$(CC) $(CFLAGS) main.o input_A_b.o LANCZOS_ALG.o all_functions.h -o a.out

main.o: main.cpp
	$(CC) -c $(CFLAGS) -c main.cpp 

input_A_b.o: input_A_b.cpp 
	$(CC) -c $(CFLAGS) -c input_A_b.cpp 

LANCZOS_ALG.o: LANCZOS_ALG.cpp 
	$(CC) -c $(CFLAGS) -c LANCZOS_ALG.cpp 

clean:
	rm -f *.o a.out