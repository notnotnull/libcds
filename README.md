[![Check Test](https://github.com/notnotnull/libcds/actions/workflows/check.yml/badge.svg)](https://github.com/notnotnull/libcds/actions/workflows/check.yml) [![Clang Format](https://github.com/notnotnull/libcds/actions/workflows/clang.yml/badge.svg)](https://github.com/notnotnull/libcds/actions/workflows/clang.yml) [![Valgrind](https://github.com/notnotnull/libcds/actions/workflows/valgrind.yml/badge.svg)](https://github.com/notnotnull/libcds/actions/workflows/valgrind.yml)

# LIBC DS

C Data Structures Library

## Dependencies

```bash
apt install build-essential \
    check \
    libssl-dev \
    valgrind \
    clang-format
```

## Build

```bash
make so
```
> Build the library as a shared-object.

```bash
make archive
```
> Build the library as an archive.

## Test

```bash
make test
```

```bash
test/test_all
```

## Memory Check

```bash
make test
```

```bash
valgrind test/test_all
```
