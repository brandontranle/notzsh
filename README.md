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
![Alt text](image.png)

Example 2:
```
./pipe ps cat aux wc
6 24 180
```
![Alt text](image-1.png)

## Cleaning up
This program can be cleaned using:
```
make clean
```
