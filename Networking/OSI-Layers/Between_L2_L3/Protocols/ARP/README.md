**ARP / Address resolution Protocol**
- [Example Scenario](#e)
- [Packet Format](#p)
- [Messages in ARP](#m)
- **Terms**
  - [ARP Spoofing](#s)


## ARP
- Before sending packet on same LAN, router/switch finds that does it has [MAC Address]() corresponding to Dest IP Address? 
```c
  If (router does not have MAC)
    sends ARP message on LAN to know MAC Address of destination node where packet needs to be sent.
 ```
- ARP protocol works in Request-response fashion. ARP always works in same LAN, ie nodes connected to same switch.

<a name=e></a>
### Example Scenario
There are 3 Computers on Office LAN(newly connected). host1 want to sent pkt to host3. [CAM Table]()
```console
          Switch
   port1   port2    port3
   /        \            \
hostA       hostB       hostC
192.168.0.1   .2         .3


      Host-A                                 
A want to send pkt to C
A knows C's IP via DNS or Routing Table
if(ARP_Cache_table has MAC of C) {
} else {
  Broadcast ARP REQ
  with dstMAC=ff:ff:ff:ff:ff:ff
}  
  ------------ARP-REQ-------------------------->      SWITCH
|srcIP=.|dstIP=.3|srcMAC=.|dstMAC=ff:ff:ff:ff:ff:ff|
                                                    Build CAM Table
                                                    Port    MAC-Address
                                                    port1    hostA
                                    Forward ARP-REQ on all remaining interfaces
                                                                                
                                                                                Host-B
                                                                     Discard pkt(dstIP != mine)
                                                                     
                                                                                              HOST-C
                                                                                            dstIP=MyIP Yes
                                                                                       Insert MAC-A in my cache
                                                          <------------ARP-REP-----------------
                                                          |srcIP=.|dstIP=..|srcMAC=......:C|dstMAC=.|
          <--------------Forward--------------------------                                                          
```

<a name=p></a>
### ARP Packet Format
```c
| Hardware-Type(2 byte) | Protocol-Type(2 byte) | Hardware-Address-Len(1 byte) | Protocol-Address-Len(1 byte) | Operation | Sender MAC Address (6 byte) | Sender Protocol (4byte) | Receiver MAC Address (6 byte) | Receiver Protocol (4 byte) |
```
- **Fields**
```c
Field  	          Meaning 
H/W Type    	  Protocol Type. Eg: Ethernet 1 
Protocol Type 	Protocol which generates ARP Req. Eg: IPv4. Value 0x0800 
H/W Len 	      MAC Address Length. Value 6 
ProtocolLength 	Length of Address used by Upper Layer Protocol. Eg: IPv4 is 1 
Operation 	    Operation that sender is performing. 1=Request. 2=Reply 
Sender H/W or MAC Address 	 
Sender Protocol Address 	 
Target H/W or MAC Address 	 
Target Protocol Address 	 
```

<a name=m></a>
### Messages in ARP
- **ARP Probe** 	
  - When a node comes into LAN, it wants to make sure that IP address which i would be using (suppose: 192.168.9.1) is not used by any other node in this LAN network. 
  - So node sends a ARP Probe ie packet with SrcIP=0
- **ARP Announcements** 	 https://en.wikipedia.org/wiki/Address_Resolution_Protocol

## Terms
<a name=s></a>
### ARP Spoofing (This is ARP Vuneariblity)
**What**
  - Node sends ARP Request to know MAC Address for IP Address(a.b.c.d). A Malicious Node is sitting on LAN. 
  - It sends falsified ARP response (in reply to ARP request). Now, any packets intended for IP(a.b.c.d) would be received by Malicious intruder sitting in LAN.
- **Detect/Avoid ARP Spoofing?**
  - *1. Packet Filtering:* 
    - Packet filters inspect packets transmitted across network. Eg: Wireshark. Packet filters are capable of identifying/blocking packets with conflicting Source address information.
  - *2. Using ARP Spoofing Detection S/Ws:* 
    - There are many softwares which detect spoofed packets. These work on detecting & certifying data before transmitting & blocking data that appears spoofed. Eg; XARP, wireshark, 
  - *3. Encryption data before sending:* TLS, SSH, HTTPS are secure communication protocols. Data can be encrypted before sending & authenticated on reception.
