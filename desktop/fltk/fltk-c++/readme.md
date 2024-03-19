# Compiling

## Using Makefile

generate GUI sources

```sh
fluid -c gui.fl
```

create compile_commands.json

```sh
bear -- make
```

clean and compile binary

```sh
make clean
make all
```

## Using CMake

create build folder and compile_commands.json

```sh
cmake -B build
cp -vf build/compile_commands.json ./
```

clean and compile binary

```sh
cmake --build build
```

## Run binary

Unset loaded library for memleak checker

```sh
unset LD_PRELOAD
```

run binary

```sh
./build/appname
```

