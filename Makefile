target: target.c linker.so
	gcc -Wl,--dynamic-linker=./linker.so -o target target.c

linker.so: begin.o linker.o
	ld -shared -Bsymbolic -e _ld_start -o linker.so begin.o linker.o

begin.o: begin.S
	gcc -c begin.S

linker.o: linker.c
	gcc -c linker.c

dump:
	objdump -D target > target.dump
	objdump -D linker.so > linker.so.dump
	objdump -D linker.o > linker.dump
	objdump -D begin.o > begin.dump

clean:
	rm *.o *.so *.dump target