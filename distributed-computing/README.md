# Distributed Computing Lab

This repository contains the codes for the experiments of Distributed Computing Lab.  

## How to Run the programs

Check manual.md

## List of experiments

- [x] Implementation of interprocess communication using pipes:one way
- [x] Implementation of interprocess communication using pipes:two way
- [x] Implementation of interprocess communication using fifo
- [x] Implementation of interprocess communication using message queues
- [ ] Implementation of interprocess communication using semaphores
- [x] Implementation of interprocess communication using shared memory
- [x] Implementation of interprocess communication using sockets
- [ ] Implementation of remote process communication

## To Do

- [ ] semaphores
- [ ] remote procedure call
- [ ] If possible, add programs that display the utility of these ipc calls rather than

## Resources

1. **When to use what?**

Pipes only work for related process, like parent and child.  
The rest can work for unrelated processes.

2. **math.h would not work**

link the lm library
```bash
gcc test.c -o test -lm
```

2. **Need to include stdlib.h for using exit**

It would work otherwise but would throw warnings

[SO](https://stackoverflow.com/questions/2406986/c-warning-implicit-declaration-of-function-exit)

3. **Awesome intro to sockets**

[socket tutorial](http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html)
