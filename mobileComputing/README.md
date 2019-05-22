# Mobile Computing Lab

1. This folder contains the codes for experiments of the Mobile Computing Lab.  
2. These have been done using ns2 on Ubuntu.  

## How to Run the programs

**You can use make to run the programs**
```
# Here 1 represents the experiment number
make run name="1"

# To run the awk file if given in the experiment, currently in 1 and 4
make stat name="1"

# To delete the output files
make clean
```

Or, you can simply the run the file using ns in the terminal
```bash
ns nameOfFile
```

And the awk files as follows
```bash
awk -f nameOfAwkFile.awk nameOfTraceFile.tr
```

## List of Experiments

    - [x] Implement Point to Point Network for three nodes and find number of dropped packets
    - [x] Implement transmission of Ping Messages and Traceroute for network of 6 nodes. Find number of dropped packets, hops and intermediate node ids
    - [x] Implement Ethernent Lan using n nodes. Set multiple traffic nodes and plot congestion window for different source/destination
    - [x] Implement and study the performance of GSM using MAC layer
    - [ ] Implement and study the performance of CDMA using stack
    - [x] Simulate AdHoc Mobile Network
    - [x] Simulate Research Paper

## Resources

1. [A great place to begin learning about ns2](https://www.isi.edu/nsnam/ns/tutorial/nsintro.html)
2. [Check this pdf out. Very good started content](http://www-sop.inria.fr/members/Eitan.Altman/COURS-NS/n3.pdf)
3. Check out the manual. Type `man ns` and check out the commands. Easy to follow and understand.
