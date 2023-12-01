# vmSystem

## About

**Note that this was written on MacOS Monterrey (12.4) with Apple clang
version 13.1.6.**

This is a small, educational program meant to test-and-check students'
understanding of virtual memory. Specifically, multi-level page systems.

The main program is written in C, however there is also an unfinished shell
script that is supposed to do pretty much the same thing (written for zsh).

## Installing and building

Simply download this git repo to your local machine, and run:

```
cd vmSystem && make
```
Run
```
chmod +x vm.sh
```
to give the file executable permissions, and then the usual `./vm`. If you
want to run the zshell script for some reason, you can run:
```
zsh vm.sh
```

Note that this particular script may not be compatible with bash/other shells
like fish, dash, etc.

