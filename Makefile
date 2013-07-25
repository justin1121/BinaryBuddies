CCFLAGS = -g -Wall
LDFLAGS = -lpthread
EXEC=bbdemo

$(EXEC): bbuddies.o demo.o buddytree.o
	gcc $(CCFLAGS) $(LDFLAGS) -o $(EXEC) bbuddies.o demo.o buddytree.o

demo.o: demo.c bbuddies.h
	gcc $(CCFLAGS) -c demo.c

bbuddies.o: bbuddies.c bbuddies.h buddytree.h
	gcc $(CCFLAGS) -c bbuddies.c

buddytree.o: buddytree.c buddytree.h
	gcc $(CCFLAGS) -c buddytree.c

clean:
	rm -f buddytree.o bbuddies.o demo.o $(EXEC)

