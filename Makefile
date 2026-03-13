TARGET = libcds

CC = gcc
CFLAGS += -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal -std=c11

INCLUDE = ./include
BIN = ./bin
LIB = ./lib
LD_LIBRARY_PATH += $(LIB)

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
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDE)

bin/%.o: test/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -I$(INCLUDE)

##### Debug Targets

debug: CFLAGS += -g
debug: all

##### Testing Targets

test: lib $(TEST)/$(TEST_TARGET)

$(TEST)/$(TEST_TARGET): LDLIBS += -L$(LIB) -Wl,-rpath=$(LIB) -lcds -lcheck -lm -lrt -lsubunit -pthread -lcrypto
$(TEST)/$(TEST_TARGET): CFLAGS += -I$(INCLUDE)
$(TEST)/$(TEST_TARGET): $(TEST_OBJS)

lint:
	$(LINT) -i $(SRCS) $(TEST_SRCS)

checklint:
	$(LINT) --dry-run -Werror $(SRCS) $(TEST_SRCS)

##### Cleanup Targets

clean: clean-test
	$(RM) $(LIB)/*.a *.o *.so $(SRC)/*.o $(BIN)/* 

clean-objs:
	$(RM) bin/*.o

clean-test:
	$(RM) $(TEST)/*.o $(TEST)/$(TEST_TARGET)

##### Default Executions

$(shell mkdir -p $(BIN) $(LIB))
