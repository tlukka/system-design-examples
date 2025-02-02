**Proxy**
- **Types or Proxy**
  - [1. Forward/Web/Server Proxy](#fow)
    - [Why needed](#whyf)
  - [2. Reverse Proxy](#rev)
    - [Why needed](#whyr)
  - [3. Explicit Proxy](#exp)
  - [4. Transparent Proxy](#tra)

## Proxy
- This is a server to which requests(http(web traffic) or ip) can be sent instead of origin server.
- For example User types in "google.com", instead of sending http request to google server, We send request to proxy server.

## Types of Proxy
<a name=fow></a>
### 1. Forward/Web/Server Proxy
Node sitting in front of client machines. When user computer make requests to sites/services on Internet, the proxy server intercepts those requests and then communicates with web servers on behalf of clients.
```c
    User-Computer-1 ------>
    User-Computer-2 ------>  Forward-Proxy            internet            Destination-server(www.test.com)
    User-Computer-3 ------>
```  
<a name=whyf></a>
#### Why Forward Proxy needed
- *a.* User Restrictions: Some schools/companies use firewalls to give limited access to Internet(eg: blocked for some sites). 
- *b.* To protect their identity online: In some cases, users want increased anonymity online.

<a name=rev></a>
### 2. Reverse Proxy 
Node sitting in front of 1 or more web servers. User requests will reach Reverse proxy. RP will query WS and send response to users.
```c
    User-Computer-1 --->                                                                        Origin/Web-Server-1
                                                     internet                Reverse-Proxy      Origin/Web-Server-2
    User-Computer-2 --->                                                                        Origin/Web-Server-3
```
<a name=whyr></a>
#### Why reverse Proxy needed?
- *a. Load Balancing:* A website receiving millions of connections need to distribute load among different backend servers, reverse proxy can provide a load balancing solution
- *b. Attack Protection:* Origin server's IP addresses are not exposed to attackers, making it difficult to intrude. Eg: DDOS attacks
- *c. Caching:* RP can cache data, resulting in faster performance.
- *d. SSL Encryption:* encryption/decryption is expensive at origin server. RP can be configured to decrypt all incoming and encrypt all outgoing responses, freeing up valuable resources on the origin server.

<a name=exp></a>
### 3. Explicit Proxy
- Client Browser is explicitly configured to use a proxy server, meaning the browser knows that all requests will go through a proxy. 
- The browser is given the IP address and port number of the proxy service.
- Browser can be configured to use [PAC file](/Networking/OSI-Layers/Layer-7/Protocols/HTTP/#pac), which again uses explicit proxy.
- The disadvantage to explicit proxy is that each desktop must be properly configured to use the proxy, which might not be feasible in a large organization.

<a name=tra></a>
### 4. Transparent Proxy
- Client Browser does not know the traffic is being processed by a proxy other than the origin server.
- To enable the Transparent Proxy we must create a service and define it as transparent. The service is configured to intercept traffic for a specified port, or for all IP addresses on that port.
