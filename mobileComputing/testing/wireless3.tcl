# Define options
set opt(chan)   Channel/WirelessChannel        ;# channel type
set opt(prop)   Propagation/TwoRayGround       ;# radio-propagation model
set opt(netif)  Phy/WirelessPhy                ;# network interface type
set opt(mac)    Mac/802_11                     ;# MAC type
set opt(ifq)    Queue/DropTail/PriQueue        ;# interface queue type
set opt(ll)     LL                             ;# link layer type
set opt(ant)    Antenna/OmniAntenna            ;# antenna model
set opt(ifqlen)         50                     ;# max packet in ifq
set opt(nn)             1                      ;# number of mobilenodes
set opt(adhocRouting)   DSDV                   ;# routing protocol

set opt(cp)     ""                             ;# cp file not used
set opt(sc)     ""                             ;# node movement file.

set opt(x)      500                            ;# x coordinate of topology
set opt(y)      500                            ;# y coordinate of topology
set opt(seed)   0.0                            ;# random seed
set opt(stop)   200                            ;# time to stop simulation

set opt(ftp1-start)      50.0

set num_wired_nodes      2

# create simulator instance
set ns   [new Simulator]

# set up for hierarchical routing
$ns node-config -addressType hierarchical

AddrParams set domain_num_ 3           ;# number of domains
lappend cluster_num 2 1 1              ;# number of clusters in each domain
AddrParams set cluster_num_ $cluster_num
lappend eilastlevel 1 1 2 1            ;# number of nodes in each cluster
AddrParams set nodes_num_ $eilastlevel ;# of each domain

set tracefd  [open wiredAndWireless.tr w]
$ns trace-all $tracefd

set namtrace [open wiredAndWireless.nam w]
$ns namtrace-all-wireless $namtrace $opt(x) $opt(y)

# Create topography object
set topo   [new Topography]

# define topology
$topo load_flatgrid $opt(x) $opt(y)

# create God
#   2 for HA and FA
create-god [expr $opt(nn) + 2]

#create wired nodes
set temp {0.0.0 0.1.0}           ;# hierarchical addresses
for {set i 0} {$i < $num_wired_nodes} {incr i} {
    set W($i) [$ns node [lindex $temp $i]]
}

# Configure for ForeignAgent and HomeAgent nodes
$ns node-config -mobileIP ON \
                 -adhocRouting $opt(adhocRouting) \
                 -llType $opt(ll) \
                 -macType $opt(mac) \
                 -ifqType $opt(ifq) \
                 -ifqLen $opt(ifqlen) \
                 -antType $opt(ant) \
                 -propType $opt(prop) \
                 -phyType $opt(netif) \
                 -channelType $opt(chan) \
		 -topoInstance $topo \
                 -wiredRouting ON \
		 -agentTrace ON \
                 -routerTrace OFF \
                 -macTrace OFF

# Create HA and FA
set HA [$ns node 1.0.0]
$HA random-motion 0

set FA [$ns node 2.0.0]
$FA random-motion 0

# Position (fixed) for base-station nodes (HA & FA).
$HA set X_ 100.0
$HA set Y_ 100.0
$HA set Z_ 0.0

$FA set X_ 300.0
$FA set Y_ 100.0
$FA set Z_ 0.0

# create a mobilenode that would be moving between HA and FA.
# note address of MH indicates its in the same domain as HA.
$ns node-config -wiredRouting OFF

set MH [$ns node 1.0.1]
set node_(0) $MH
set HAaddress [AddrParams addr2id [$HA node-addr]]
[$MH set regagent_] set home_agent_ $HAaddress

# movement of the MH
$MH set X_ 50.0
$MH set Y_ 5.0
$MH set Z_ 0.0

# MH starts to move towards FA
$ns at 30.0 "$MH setdest 300.0 5.0 0.0"
# goes back to HA
$ns at 130.0 "$MH setdest 5.0 5.0 0.0"

# create links between wired and BaseStation nodes
$ns duplex-link $W(0) $W(1) 5Mb 2ms DropTail
$ns duplex-link $W(1) $HA 5Mb 2ms DropTail
$ns duplex-link $W(1) $FA 5Mb 2ms DropTail

$ns duplex-link-op $W(0) $W(1) orient down
$ns duplex-link-op $W(1) $HA orient left-down
$ns duplex-link-op $W(1) $FA orient right-down

# setup TCP connections between a wired node and the MobileHost

set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
set sink1 [new Agent/TCPSink]
$ns attach-agent $W(0) $tcp1
$ns attach-agent $MH $sink1
$ns connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ns at $opt(ftp1-start) "$ftp1 start"

set opt(cp) "none"
set opt(sc) "none"

# Define initial node position in nam

for {set i 0} {$i < $opt(nn)} {incr i} {
    $ns initial_node_pos $node_($i) 20
}

# Tell all nodes when the siulation ends
for {set i 0} {$i < $opt(nn) } {incr i} {
    $ns at $opt(stop).0 "$node_($i) reset";
}
$ns at $opt(stop).0 "$HA reset";
$ns at $opt(stop).0 "$FA reset";

$ns at $opt(stop).0002 "puts \"NS EXITING...\" ; $ns halt"
$ns at $opt(stop).0001 "stop"
proc stop {} {
    global ns tracefd namtrace
    close $tracefd
    close $namtrace
}

# some useful headers for tracefile
puts $tracefd "M 0.0 nn $opt(nn) x $opt(x) y $opt(y) rp \
	$opt(adhocRouting)"
puts $tracefd "M 0.0 sc $opt(sc) cp $opt(cp) seed $opt(seed)"
puts $tracefd "M 0.0 prop $opt(prop) ant $opt(ant)"

puts "Starting Simulation..."
$ns run
