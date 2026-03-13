CC = gcc
CFLAGS += -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal -std=c11
LD_LIBRARY_PATH += ./bin

INCLUDE = ./src
BIN = ./bin

SRCS = $(wildcard src/*.c)
TEST_SRCS = test/test_utils.c
OBJS = $(SRCS:src/%.c=bin/%.o)
TEST_OBJS = $(TEST_SRCS:test/%.c=bin/%.o)

LINT = clang-format

.PHONY: all clean test debug lint

all: lib

lib:
	@echo "make lib: Not implemented yet."

test: test/test_all

debug: CFLAGS += -g
debug: all

test/test_all: LDLIBS += -lcheck -lm -lrt -lsubunit -pthread -lcrypto
test/test_all: CFLAGS += -I$(INCLUDE)
test/test_all: $(TEST_OBJS) $(OBJS)

bin/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

bin/%.o: test/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

lint:
	$(LINT) -i $(SRCS) $(TEST_SRCS)

clean:
	$(RM) *.o *.so src/*.o bin/* test/*.o test/test_all

$(shell mkdir -p $(BIN))