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