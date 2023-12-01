CFLAGS = -Wall -Wpedantic -std=c11 -g
CC = clang

vm: vm.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f vm
	rm -rf *.dSYM
