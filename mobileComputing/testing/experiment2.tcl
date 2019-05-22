#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows
$ns color 1 Blue
$ns color 2 Red

#Open the nam trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#Open the trace file
set nd [open out.tr w]
$ns trace-all $nd

#Define the finish procedure
proc finish {} {
    global ns nf nd
    $ns flush-trace

    #Close the trace file
    close $nf
    close $nd

    #Execute nam on the trace file
    exec nam out.nam &

    exit 0
}

#Create six nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

#Label the nodes
$n0 label "Ping0"
$n4 label "Ping4"
$n5 label "Ping5"
$n6 label "Ping6"
$n2 label "Router"

#Create links between the nodes
$ns duplex-link $n0 $n2 100 Mb 300 ms DropTail
$ns duplex-link $n1 $n2 1 Mb 300 ms DropTail
$ns duplex-link $n3 $n2 1 Mb 300 ms DropTail
$ns duplex-link $n5 $n2 100 Mb 300 ms DropTail
$ns duplex-link $n2 $n4 1 Mb 300 ms DropTail
$ns duplex-link $n2 $n6 1 Mb 300 ms DropTail

#Set queue limits
$ns queue-limit $n0 $n2 5
$ns queue-limit $n2 $n4 3
$ns queue-limit $n2 $n6 2
$ns queue-limit $n5 $n2 5

set Ping0 [new Agent/Ping]
$ns attach-agent $n0 $Ping0

set Ping4 [new Agent/Ping]
$ns attach-agent $n4 $Ping4

set Ping6 [new Agent/Ping]
$ns attach-agent $n6 $Ping6

$Ping0 set packetSize_ 50000
$Ping0 set interval_ 0.0001

$Ping0 set packetSize_ 60000
$Ping0 set interval_ 0.00001

$Ping0 set class_ 1
$Ping5 set class_ 2

$ns connect $Ping0 $Ping4
$ns connect $Ping5 $Ping6

Agent/Ping instproc recv {from rtt} {
  $self instvar node_
  puts "node[$node_id] received ping answer from $from with round-trip-time $rtt"
}

$ns at 0.1 "$Ping0 send"
$ns at 0.2 "$Ping0 send"
$ns at 0.3 "$Ping0 send"
$ns at 0.4 "$Ping0 send"
$ns at 0.5 "$Ping0 send"
$ns at 0.6 "$Ping0 send"
$ns at 0.7 "$Ping0 send"
$ns at 0.8 "$Ping0 send"
$ns at 0.9 "$Ping0 send"

$ns at 1.1 "$Ping0 send"
$ns at 1.2 "$Ping0 send"
$ns at 1.3 "$Ping0 send"
$ns at 1.4 "$Ping0 send"
$ns at 1.5 "$Ping0 send"
$ns at 1.6 "$Ping0 send"
$ns at 1.7 "$Ping0 send"
$ns at 1.8 "$Ping0 send"

$ns at 0.1 "$Ping5 send"
$ns at 0.2 "$Ping5 send"
$ns at 0.3 "$Ping5 send"
$ns at 0.4 "$Ping5 send"
$ns at 0.5 "$Ping5 send"
$ns at 0.6 "$Ping5 send"
$ns at 0.7 "$Ping5 send"
$ns at 0.8 "$Ping5 send"
$ns at 0.9 "$Ping5 send"

$ns at 1.1 "$Ping5 send"
$ns at 1.2 "$Ping5 send"
$ns at 1.3 "$Ping5 send"
$ns at 1.4 "$Ping5 send"
$ns at 1.5 "$Ping5 send"
$ns at 1.6 "$Ping5 send"
$ns at 1.7 "$Ping5 send"
$ns at 1.8 "$Ping5 send"

$ns at 5.0 "finish"
$ns run
