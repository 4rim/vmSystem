$CFLAGS=-Wall -Wpedantic -C11 -g
$CC=clang

vm: vm.c
	$(CC) -o $@ $<

clean:
	rm vm
