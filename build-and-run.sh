clang --std=c23 src/main.c -g -O0 -c -o build/main.o
clang build/main.o -g -o bin/program.exe
./bin/program.exe
