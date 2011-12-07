target: target.c p_linker.so
	gcc -g -z now -Wl,--dynamic-linker=./p_linker.so -o target target.c

#p_linker.so: p_linker.c
#	gcc -g -nostdlib -nostartfiles -Wl,-z,combreloc -Wl,-z,relro -Wl,--hash-style=both -shared -Wl,-e,_ld_start -Wl,-Bsymbolic p_linker.c -o p_linker.so

p_linker.so: p_linker.o
	ld -shared -Bsymbolic -z now -e _ld_start -o p_linker.so p_linker.o
#	ld -shared -e _ld_start -o p_linker.so p_linker.o
#	ld -nostdlib -nostartfiles -shared -Wl,-e _ld_start -o p_linker.so p_linker.o

p_linker.o: p_linker.c
	gcc -g -c p_linker.c

dump:
	objdump -D target > target.dump
	objdump -D p_linker.so > p_linker.so.dump
	objdump -D p_linker.o > p_linker.dump

clean:
	rm -rf *.o *.so *.dump target