TARGET = libcds

CC = gcc
CFLAGS += -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal -std=c11

INCLUDE = ./src
BIN = ./bin
LIB = ./lib

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=bin/%.o)

TEST_TARGET = test_all
TEST = ./test
TEST_OBJS = $(TEST_SRCS:test/%.c=bin/%.o)
TEST_SRCS = test/test_utils.c
LINT = clang-format

.PHONY: archive so test debug lint clean clean-objs

##### Library Targets

archive: $(LIB)/$(TARGET).a

so: $(LIB)/$(TARGET).so

$(LIB)/$(TARGET).a: $(OBJS)
	ar rcs $@ $^

$(LIB)/$(TARGET).so: CFLAGS += -fPIC
$(LIB)/$(TARGET).so: $(OBJS)
	$(CC) -shared -o $@ $^

##### Object Targets

bin/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

bin/%.o: test/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

##### Debug Targets

debug: CFLAGS += -g
debug: all

##### Testing Targets

test: lib $(TEST)/$(TEST_TARGET)

$(TEST)/$(TEST_TARGET): LDLIBS += -L$(LIB) -lcds -lcheck -lm -lrt -lsubunit -pthread -lcrypto
$(TEST)/$(TEST_TARGET): CFLAGS += -I$(INCLUDE)
$(TEST)/$(TEST_TARGET): $(TEST_OBJS)

lint:
	$(LINT) -i $(SRCS) $(TEST_SRCS)

checklint:
	$(LINT) --dry-run -Werror $(SRCS) $(TEST_SRCS)

##### Cleanup Targets

clean:
	$(RM) $(LIB)/*.a *.o *.so src/*.o bin/* test/*.o test/test_all

clean-objs:
	$(RM) bin/*.o

##### Default Executions

$(shell mkdir -p $(BIN) $(LIB))
