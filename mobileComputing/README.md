# Mobile Computing Lab

This folder contains the codes for experiments of the Mobile Computing Lab.  
These have been done using ns2 on Ubuntu.  

## How to Run the programs

Simply the run the file using ns in the terminal
```bash 
ns nameOfFile
```

*To find the count of dropped and recieved packets*
```bash
make stats
```

*To delete the output files*
```bash
make clean
```

## List of Experiments 

    - [ ] Implement Point to Point Network for three nodes and find number of dropped packets
    - [ ] Implement transmission of Ping Messages and Traceroute for network of 6 nodes. Find number of dropped packets, hops and intermediate node ids
    - [ ] Implement Ethernent Lan using n nodes. Set multiple traffic nodes and plot congestion window for different source/destination
    - [ ] Implement and study the performance of GSM using MAC layer
    - [ ] Implement and study the performance of CDMA using stack
    - [ ] Simulate AdHoc Mobile Network

## Resources

1. [A great place to begin learning about ns2](https://www.isi.edu/nsnam/ns/tutorial/nsintro.html) 
2. Check out the manual. Type `man ns` and check out the commands. Easy to follow and understand.
