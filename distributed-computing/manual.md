## General Instructions

1. All the programs have been implemented in C using POSIX system calls.
2. Run the files from the same directory where stored

## Specific Instructions

1. **Pipes**

pipesingle.c
```bash
gcc pipesingle.c -o test
./test
```

pipedouble.c
```bash
gcc pipedouble.c -o test
./test
```

2. **Named Pipe | FIFO**

```bash
gcc fifoserver.c -o server
./server
gcc fifoclient.c -o client
./client
```

3. **Message Queues**

```bash
gcc msgqwriter.c -o writer
./writer
gcc msgqreader.c -o reader
./reader
```
4. **Shared Memory**

```bash
gcc sharedmemorywriter.c -o writer
./writer
gcc sharedmemoryreader.c -o reader
./reader
```

5. **Sockets**

```bash
gcc socketserver.c -o server
./server
gcc sockerclient.c -o client
./client
```
