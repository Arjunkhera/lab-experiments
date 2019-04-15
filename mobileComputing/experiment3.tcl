
set ns [new Simulator]

#Open a new file for NAMTRACE
set nf [open out.nam w]
$ns namtrace-all $nf

#Open a new file to log TRACE
set tf [open out.tr w]
$ns trace-all $tf

#Body of the 'finish' procedure
proc finish {} {
        global ns nf tf

        $ns flush-trace
        close $nf
	      close $tf

        exec nam out.nam &
        exec awk -f exp3.awk out.tr &
        exec awk -f exp3.awk tcp0.tr &
        exec awk -f exp3.awk tcp1.tr &
        exit 0
}

#Create Nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]

#Create a Local Area Network (LAN) of 10 Nodes
$ns make-lan "$n0 $n1 $n2 $n3 $n4 $n5 $n6 $n7 $n8 $n9" 100Mb 50ms  LL Queue/DropTail Mac/802_3

#Create TCP Agent between node 0 and node 3
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0

#Open a new file to log Congestion Window data
set cfile0 [open tcp0.tr w]
$tcp0 attach $cfile0
$tcp0 trace cwnd_

#Create FTP Application for TCP Agent
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

#Specify TCP packet size
Agent/TCP set packetSize_ 1000

#Create TCP Agent between node 1 and node 3
set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1
$ns connect $tcp1 $sink1

#Open a new file to log Congestion Window data
set cfile1 [open tcp1.tr w]
$tcp1 attach $cfile1
$tcp1 trace cwnd_

#Create Telnet Application for TCP Agent
set telnet0 [new Application/Telnet]
$telnet0 set interval_ 0.005
$telnet0 attach-agent $tcp1

#Start and Stop FTP Traffic
$ns at 0.75 "$ftp0 start"
$ns at 4.75 "$ftp0 stop"

set n6 [$ns node]

#Start and Stop Telnet traffic
$ns at 0.5 "$telnet0 start"
$ns at 4.5 "$telnet0 stop"

#Stop the simulation
$ns at 5.0 "finish"

#Run the simulation
$ns run
