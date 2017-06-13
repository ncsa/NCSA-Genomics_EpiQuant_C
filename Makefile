exec = bin/sems-c
obj = obj/sems-c.o obj/args.o
src = src/sems-c.c src/args.c

CC = mpic++
CFLAGS := -fopenmp -O3 -Wall

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
