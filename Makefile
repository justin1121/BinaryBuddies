CCFLAGS = -g -Wall
LDFLAGS = -lpthread
EXEC=bbdemo

$(EXEC): bbuddies.o demo.o
	gcc $(CCFLAGS) $(LDFLAGS) -o $(EXEC) bbuddies.o demo.o

demo.o: demo.c bbuddies.h
	gcc $(CCFLAGS) -c demo.c

bbuddies.o: bbuddies.c bbuddies.h
	gcc $(CCFLAGS) -c bbuddies.c

clean:
	rm -f bbuddies.o demo.o $(EXEC)

