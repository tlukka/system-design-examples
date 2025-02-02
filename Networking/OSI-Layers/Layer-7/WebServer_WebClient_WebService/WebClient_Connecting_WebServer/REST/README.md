**REST / (Representation State Transfer) APIs**
- [REST API](#api)
- [How REST API Works >> MOST IMPORTANT](#how)
- [Restful Methods/APIs/Verbs](#m)
- [Comparisons: (REST vs HTTP), (REST vs SOAP)](#vs)
- [Constraints for RESTFUL application](#c)
- **Code Implementations**
   - [Python flask-restful](/Languages/ScriptingLanguages/Python/web-frameworks/flask-restful)
   - [Rust Actix_web Http Server exposing REST APIs](/Languages/Programming_Languages/Rust/Frameworks/Actix_web)


## REST / (Representation State Transfer) APIs
**Restful Web Server/Application?** Web application that implements [HTTP CRUD methods](/Networking/OSI-Layers/Layer-7/Protocols/HTTP/README.md#mea) in Restful way. Eg: Twitter, facebook are implemented using restful APIs.
- When web-client calls Restful APIs then Web-Server can return [JSON](/Languages/ScriptingLanguages/JavaScript) or HTML or [XML](/Languages/Markup_Language).
- [Good Youtube Video](https://www.youtube.com/watch?v=SLwpqD8n3d0)
<a name=api></a>
### REST API
Same as [HTTP CRUD methods](/Networking/OSI-Layers/Layer-7/Protocols/HTTP/README.md#mea)
<a name=how></a>
### How REST Works?
```c
1. Web server(abc.com) defines Resources(Eg: Customers, movies, cars etc) and exposes a service/End point eg:(https://abc.com/api/movies), where
   abc.com  : Domain
   api      : Convention(mostly used by companies) to expose RESTful services
   movies   : Resource 
2. Web client will use above END POINT(https://abc.com/api/movies) to talk to Web service to perform CRUD Operations on Resource
3. Perform CRUD Operations on Resource.   

   Web Client                                         Web Service
   GET www.abc.com/api/movies HTTP/1.1       --------->           Query list of movies
                           <-[ {id:1,'movie1'}, {id:2,'movie2'} ]-

   GET www.abc.com/api/movies/1 HTTP/1.1    --------->         return id=1 movie
                                       <-[ {id:1,'movie1'} ]-
   
   POST www.abc.com/api/movies {id:3, 'movie3'} HTTP/1.1  --------->  Add object [ {id:1,'movie1'}, {id:2,'movie2'}, {id:3,'movie3'} ]
   PUT www.abc.com/api/movies/1 {id:1, 'movie11'} HTTP/1.1 ---------> Updates db [ {id:1,'movie11'}, {id:2,'movie2'}, {id:3,'movie3'} ]
   DELETE www.abc.com/api/movies/1 HTTP/1.1             ---------> Delete object [ {id:2,'movie2'}, {id:3,'movie3'} ]
                        

   Client	                        	                Web Service
 http://<ip-address>/api/resource-name
                                          Implement APIs GET(){..} POST(){..} PUT(){..} DELETE(){..}
                     <---data----
```
**Why Restful**
- *1. Rest makes Web Service OS Independent:* Web applications can reside on different operating systems, some could be on Windows, and others could be on Linux.
- *2. Rest makes Web Service language independent:* Web services can be implemented in any language(C++,RUST etc)
- *3. On Cloud:* RESTful applications are moved can reside on cloud. Azure and Amazon provide a lot of API's based on the Restful architecture. 

<a name=m></a>
### Restful Methods/APIs/Verbs
Web Client call these [HTTP CRUD methods](/Networking/OSI-Layers/Layer-7/Protocols/HTTP/README.md#mea) and response returned over HTTP.
```c
  - POST: This will create a new record in web service
  - GET: Get list of all records in web service
  - PUT: Update a record in web service
  - DELETE: delete 1 record in web service
```

<a name=vs></a>
## Comparisons
**REST vs [HTTP](/Networking/OSI-Layers/Layer-7/Protocols/HTTP/)**

||REST|HTTP|
|---|---|---|
|What|Set of rules|L7 protocol|
|Focus|Resource|Methods to get|

**REST vs SOAP(Simple Object Access Protocol)**

||REST|SOAP|
|---|---|---|
|Why|To access web service|Same|
|Flexible|More|Less, hard to use|
|Relies on|JSON,XML,CSV,RSS|XML, CORBA(Common Object Request Broker Architecture) rely on binary messaging|
|Advgs over soap|small learning curve, smaller messages||

<a name=c></a>
### Constraints for RESTFUL application
- **a. Uniform interface:**
  - client request must include a resource identifier. The response the server returns include enough information so the client can modify the resource.
- **b. Client - server separation:** 
  - The client and the server act independently, each on its own, and the interaction between them is only in the form of requests, initiated by the client only.
- **c. Stateless:** Server does not store information about client who uses the APIs.
- **d. Layered system:** 
  - Between the client who requests a representation of a resource’s state, and the server who sends the response back, there might be a number of servers in the middle.These servers might provide a security, caching, load-balancing layers or                 other functionality. 
- **e. Cacheable:** 
  - Data sent by server contains information about whether or not the data is cacheable. If the data is cacheable, it might contain sort of a version number. Since the client knows which version of the data it has the client can avoid requesting the                         same data again.
- **f. Code-on-demand(optional):** 
  - The client can request code from the server, and then the response from the server will contain some code, usually in the form of a script. The client then can execute that code.




