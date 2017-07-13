exec = bin/sems-c
obj = obj/sems-c.o obj/args.o obj/parser.o obj/clean.o
src = src/sems-c.c src/args.c src/parser.c src/clean.c

// CC = mpic++
CC = gcc
// CFLAGS := -fopenmp -O3 -Wall -W
CFLAGS :=

all: sems-c

clean:
	rm -rf bin/ obj/ 

sems-c: $(src) $(obj) | bin
	$(CC) $(CFLAGS) -o $(exec) $(obj)
	chmod -R 751 bin/

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p $@

bin:
	mkdir -p $@
