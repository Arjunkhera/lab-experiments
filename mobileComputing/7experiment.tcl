#Define options
global opt

set opt(chan)           Channel/WirelessChannel
set opt(prop)           Propagation/TwoRayGround
set opt(netif)          Phy/WirelessPhy
set opt(mac)            Mac/802_11
set opt(ifq)            Queue/DropTail/PriQueue
set opt(ll)             LL
set opt(ant)            Antenna/OmniAntenna
set opt(x)              500
set opt(y)              500
set opt(ifqlen)         50
set opt(tr)             out.tr
set opt(namtr)          out.nam
set opt(nn)             3
set opt(adhocRouting)   DSDV
set opt(cp)             ""
#set opt(sc)             "../mobility/scene/scen-3-test"
set opt(stop)           50
set num_wired_nodes     2
set num_bs_nodes        1

#Setup the simulator
set ns [new Simulator]

#Setup the trace file
set tracefd  [open $opt(tr) w]
$ns trace-all $tracefd

#Setup the namtrace file
set namtracefd [open $opt(namtr) w]
$ns namtrace-all $namtracefd

#Setup the topography
set topo [new Topography]
$topo load_flatgrid $opt(x) $opt(y)

#GOD needs to know the number of all wireless interfaces
create-god [expr $opt(nn) + $num_bs_nodes]

#Setup for hierarchical routing
$ns node-config -addressType hierarchical

#Domains
AddrParams set domain_num_ 2

#Clusters
lappend cluster_num 2 1
AddrParams set cluster_num_ $cluster_num

#Nodes
lappend eilastlevel 1 1 4
AddrParams set nodes_num_ $eilastlevel

#Create wired nodes
set temp {0.0.0 0.1.0}
for {set i 0} {$i < $num_wired_nodes} {incr i} {
    set W($i) [$ns node [lindex $temp $i]]
}

#Setup the configuration parameters
$ns node-config  -adhocRouting $opt(adhocRouting) \
                 -llType $opt(ll) \
                 -macType $opt(mac) \
                 -ifqType $opt(ifq) \
                 -ifqLen $opt(ifqlen) \
                 -antType $opt(ant) \
                 -propInstance [new $opt(prop)] \
                 -phyType $opt(netif) \
                 -channel [new $opt(chan)] \
                 -topoInstance $topo \
                 -wiredRouting ON \
                 -agentTrace ON \
                 -routerTrace OFF \
                 -macTrace OFF

#Create Base Station
set temp {1.0.0 1.0.1 1.0.2 1.0.3}
set BS(0) [$ns node [lindex $temp 0]]
$BS(0) random-motion 0

#Setup the coordinates of Base station
$BS(0) set X_ 150.0
$BS(0) set Y_ 150.0
$BS(0) set Z_ 0.0

#Configure for mobilenodes
$ns node-config -wiredRouting OFF

for {set j 0} {$j < $opt(nn)} {incr j} {
  set node_($j) [ $ns node [lindex $temp \ [expr $j+1]] ]
  $node_($j) base-station [AddrParams addr2id [$BS(0) node-addr]]
  $node_($j) random-motion 0
}

# Provide initial location of mobilenodes
$node_(0) set X_ 50.0
$node_(0) set Y_ 50.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 5.0
$node_(1) set Y_ 5.0
$node_(1) set Z_ 0.0

$node_(2) set X_ 100.0
$node_(2) set Y_ 5.0
$node_(2) set Z_ 0.0

#Create links between wired and BS nodes
$ns duplex-link $W(0) $W(1) 5Mb 2ms DropTail
$ns duplex-link $W(1) $BS(0) 5Mb 2ms DropTail

$ns duplex-link-op $W(0) $W(1) orient down
$ns duplex-link-op $W(1) $BS(0) orient left-down

#Setup TCP connection
set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
set sink1 [new Agent/TCPSink]

$ns attach-agent $node_(0) $tcp1
$ns attach-agent $W(0) $sink1
$ns connect $tcp1 $sink1

#Setup FTP connection
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ns at 15 "$ftp1 start"

#Setup TCP connection
set tcp2 [new Agent/TCP]
$tcp2 set class_ 2
set sink2 [new Agent/TCPSink]

$ns attach-agent $node_(1) $tcp2
$ns attach-agent $W(0) $sink2
$ns connect $tcp2 $sink2

#Setup FTP connection
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ns at 10 "$ftp2 start"

for {set i 0} {$i < $opt(nn)} {incr i} {
  $ns initial_node_pos $node_($i) 20
}

#Reset the wireless nodes
for {set i } {$i < $opt(nn) } {incr i} {
  $ns at $opt(stop) "$node_($i) reset";
}

#Reset the base station
$ns at $opt(stop) "$BS(0) reset";

$ns at $opt(stop) "stop"
$ns at $opt(stop) "puts \"NS EXITING...\" ; $ns halt"

proc stop {} {
   global ns tracefd namtracefd
   $ns flush-trace

   close $tracefd
   close $namtracefd

   exec nam out.nam &
}

#Start the simulation
puts "Starting Simulation..."
$ns run
