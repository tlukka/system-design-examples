**DNS / Domain Name Service**
- [Adv, Disadv of DNS](#ad)
- Name Resolution
  - [1. Forward Lookup](#fl)
  - [2. Reverse Lookup](#rl)
- **Terms**
  - [CyberSquatting](#cs)
  - Domain Name
  - DNS Queries
  - DNS Zone
  - Name server
    - Recursive
    - Authoritative DNS Server
  - [Resource Records](#rr)



## DNS / Domain Name Service / Port 53
- Protocol for converting hostname to IP address and viceversa. 
- DNS uses udp by default, fall back to tcp if on udp cannot communicate.

### Adv, Disadv of DNS
- **Advantages of DNS**
  - *1.* To send packet across network we need IP Address and only DNS can provide.
  - *2.* No need for memorizing IP addresses
- **Disadv**
  - *1.* Registry only controlled by [ICANN](Terms) which can become bais to some country/organization.
  - *2.* [DNS Messages](DNS_Messages) does not have information of client asking the information, hacker can bisect the message and send his own message.
  - *3.* [TLD's](Terms) can be bottleneck.

### Name resolution
The process of looking up a hostname and finding corresponding IP address.

<a name=fl></a>
#### 1. Forward Lookup (hostname to IP conversion)
- [DNS Query](DNS_Messages), [Recursive DNS Server, Root Nameserver, Authoritative NameServer](Terms)
<img src=forward-lookup.JPG width=900 />

<a name=rl></a>
#### 2. Reverse Lookup (IP to hostname)
- **Why?** Case-1: Spam received in mailbox, From-IP header is parsed. Now Email client wants to know from where this Email arrived? Is this IP Address authentic or spam. So Machine enquires ISP for reverse query, giving IP address and asking for URL(if exists)).
<img src=reverse-lookup.png width=600 />



## Terms
<a name=cs></a>
### CyberSquatting
Selling a domain to interested party at much higher price.

<a name=dq></a>
### DNS Queries Types
- **1. Recursive?** Recursive NS perform recursive queries to other nameservers and returns complete result to DNS client. Done by Local DNS server.
- **2. Iterative/Non-Recursive?** Root nameservers does not collects all information rather they return partial information and continue to next query. This is called iterative.

<a name=ns></a>
### Name server / Nameserver
- Computer responsible for a particular domain, ie responding to that domain queries. One zone can have 1 or more name servers. 

#### Types of NS
- **1. Primary NS?** Zone have 1 primary name server which gets its information from DNS zone file on its disk.
- **2. Secondary NS?** Get their information from the primary name server, maybe internet facing.
- **3. Root NS?** Server which have IP-Addresses of nameservers handling [TLDs](/Networking/OSI-Layers/Layer5/Protocols/DNS/Terms/Domain_Name). eg: .com, .org
- **4. Authoritative NS?** Server authoritative for particular domain. Eg: nandini.com is handled by 4.4.4.4
- **5. Recursive NS?** NS which takes query from client and returns complete result, does not return partial results.
- **6.Caching NS?** Server sitting at front of Clients, doing DNS queries on behalf of clients, storing results locally in cache. As Cache grows its efficiency improves as it can answer lot from cache.
  - Problem2: Cache Poisoning: Hackers fills in cache of caching nameserver from stale/wrong/bad entries.    Solution: DNSSEC(DNS Security Extension) validation: Doing authentication, integration check of resource records before placing on cache.

<a name=ra></a>
### Recursive, Authoritative DNS Server
- RECURSIVE DNS SERVER? Recursive means referring to itself. This DNS server caches the DNS records and sends DNS query further if record is not found.
- AUTHORITATIVE DNS SERVER? This server holds information about domain(eg: google.com) and delivers it to internet.

<a name=rr></a>
## Resource Records / RR
- Data/Information about particular domain. For single host most common resource record is IP Address. 
- Format:
```c
DOMAINNAME    TIMETOLIVE(sec)    CLASS(IN:for internet)    TYPE_OF_RR    VALUE

DOMAINNAME: Domain to which this RR applies. Each domain can have RRs of multiple domains. This filed is primary search key for search.
TTL: How stable RR is. Eg: 86400(1 day)
VALUE: Value of RR can be Number, domain name or string.
```

### Types of RR
#### A Record
4byte-IP to hostname mapping. Every internet have 1 or more IP addresses. All are returned.     
```c
# host A google.com;  dig hostname;  nslookup hostname
```
#### AAAA RECORD
128bit-IPv6 to hostname map.  (google.com, 2404:6800:4003:c00::65)
#### CNAME RECORD
Stores Alternate name(alias) of domain. Example
```c
test.com 86400 IN CNAME test1.com     //test.com and test1.com both belongs to same host. 
# host    -v    -t  A ca.example.com
```
#### MX RECORD (Value 15) 
Host responsible for handling incoming mails for zone. A preference value and the host name for a mail server/exchanger that will service this zone. 
#### NS(NAME SERVER) RECORD (Value 2)
Defines Name server for domain or subdomain.
#### PTR RECORD(Value 12) //For Reverse Lookup
- We need to create PTR record for each IP Address. This Stores hostname corresponding to reverse-dns-name.
#### SOA(Start of Authority) (value 6)
Provides name of primary source of information about name server’s zone. Eg(Email of admin etc).    
```c
# host -v -t SOA example.com
```
#### SPF RECORD
Which machines in domain are authorized to send/receive Email in domain. This helps in identifying junk/forged mails.
#### SRV RECORD (Value 33)
Defines services available in domain. Example, ldap, http, sip etc.. 
```c
DNS Client                                              DNS-Server
# host -v  -t SRV _ldap._tcp.example.com; 
dig SRV _ldap._tcp.lab.example.net;
                            <- 389    server0.example.com---
```                            
#### TXT RECORD (value 13)
Human readable information associated with domain name.
```c
spf1 ip4:72.51.34.34 ip4:70.33.254.29 -all--
```

####  DNS Zone File
Plain text file which stores resource records of particular domain. Zone file always start with a Start of Authority (SOA) record.
```c
; Authoritative data for test.com
    test.com.     86400    IN    SOA        star boss (9527,7200,7200,241920,86400)
    star                   IN    A          130.37.56.201       //IP Address of star.test.com is <>
    flits         86400    IN    A          130.37.16.112       //flits.test.com has IP address <>
    test.com.     86400    IN    MX         1 rambo                //Email should be 1st sent to rambo@test.com
    test.com.     86400    IN    MX         2 sambo                //if rambo@test.com fails sambo should be tried as 2nd choice
    test.com.     86400    IN    NS         star
    www           86400    IN    CNAME      star.cs.vu.nl        //www is aliased to star.cs.vu.nl
10.30.20.10.in-addr.arpa.  IN    PTR        host.domain.com
```
