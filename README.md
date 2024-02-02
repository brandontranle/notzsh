## UID: 805993439

## Pipe Up

This program demonstrates the execution of shell commands, connected by pipes, such that the output of each command becomes the input for the next.

## Building

This program is built or updated by running:
```
make
```

## Running

Example 1:
```
./pipe ls cat wc
7   7   63
```
<img width="283" alt="image" src="https://github.com/brandontranle/notzsh/assets/111268644/dc364485-8697-4c96-9295-0f1e30e8cb52">

Example 2:
```
./pipe ps cat aux wc
6 24 180
```
<img width="266" alt="image-1" src="https://github.com/brandontranle/notzsh/assets/111268644/69d04fa2-ddff-415c-9977-a34738971766">


## Cleaning up
This program can be cleaned using:
```
make clean
```
