exec = bin/sems-c
obj = obj/sems-c.o
src = src/sems-c.c

CC = mpic++
CFLAGS := -fopenmp -O3

all: sems-c

clean:
	rm -rf bin/ obj/ 

sems-c: $(src) $(obj) | bin
	$(CC) $(CFLAGS) -o $(exec) $(obj)
	chmod -R 751 bin/

obj/%.o: src/%.cpp | obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p $@

bin:
	mkdir -p $@
