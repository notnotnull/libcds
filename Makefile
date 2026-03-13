CFLAGS += -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal -std=c11
LD_LIBRARY_PATH += ./bin

INCLUDE = ./src
BIN = ./bin

.PHONY: all clean test lib debug

all: test/test_all

test: test/test_all

debug: CFLAGS += -g
debug: all

test/test_all: LDLIBS += -lcheck -lm -lrt -lsubunit -pthread -lcrypto
test/test_all: CFLAGS += -I$(INCLUDE)
test/test_all: bin/test_utils.o bin/ll.o bin/dll.o bin/queue.o bin/stack.o \
bin/pqueue.o bin/bst.o bin/ht.o bin/cll.o bin/wgraph.o

bin/test_utils.o:
	gcc -c test/test_utils.c -o bin/test_utils.o $(CFLAGS)

bin/ll.o:
	gcc -c src/ll.c -o bin/ll.o $(CFLAGS)

bin/dll.o:
	gcc -c src/dll.c -o bin/dll.o $(CFLAGS)

bin/queue.o:
	gcc -c src/queue.c -o bin/queue.o $(CFLAGS)

bin/stack.o:
	gcc -c src/stack.c -o bin/stack.o $(CFLAGS)

bin/pqueue.o:
	gcc -c src/pqueue.c -o bin/pqueue.o $(CFLAGS)

bin/bst.o:
	gcc -c src/bst.c -o bin/bst.o $(CFLAGS)

bin/ht.o:
	gcc -c src/ht.c -o bin/ht.o $(CFLAGS)

bin/cll.o:
	gcc -c src/cll.c -o bin/cll.o $(CFLAGS)

bin/wgraph.o:
	gcc -c src/wgraph.c -o bin/wgraph.o $(CFLAGS)

clean:
	$(RM) *.o *.so src/*.o bin/* test/*.o test/test_all

$(shell mkdir -p $(BIN))