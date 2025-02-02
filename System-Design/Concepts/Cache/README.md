- [1. What is Cache](#what)
- [2. Types of Caches (Write thru, Write Around, Write Back)](#types)
- [3. Where Caches can be placed](#where)
- [4. DB Cache Examples](#caches)
- [5. Problems with Caches](#prob)

<a name=what></a>
## 1. Cache
- **What data should be cached?** 
  - Mostly used, less frequently changing data is stored in cache. (Eg: Metadata, configuration data, Historical data sets for reports)
  - Cache lies near to requester so that requester need not to go hard-disk to retrieve data. This reduces latency.
- **What should not be cached?** Data that is frequently/actively changing.
```c
App/Webserver <--->[Cache]<-->[Database]
```
- **Examples?** Web browser, Web proxy, Application server, Web server caches, CDN
- **Stores:** User sessions, user profile, some historical data.
 
<a name=types></a>
## 2. Types of Caches
|Method|What|Disadvantage|Advantage|
|---|---|---|---|
|1. Write Thru Cache|Data written to cache and DB both|Latency is high|2 copies stored|
|2. Write Around Cache|Write goes directly to DB. Operation is considered completed only after writing to DB|Reading recent data is  cache miss & need to be read from DB. High latency|Cache flooding avoided|
|3. Write Back Cache|Write done to cache only. Cache writes the info to DB(asynchronously).|Data availability risk(cache may fail)|Low latency, High throughput|

<a name=types></a>
## [3. Where Caches can be placed?](Where_Cache_Can_Be_Placed)

<a name=caches></a>
## [4. Cache Examples](DB_Caches)
 - Memcached, Redis, AWS_Elastic_Cache

<a name=prob></a>
## 5. Problem with Caching
  - [Consistency Problem](/System-Design/Concepts/Bottlenecks_of_Distributed_Systems/Bottlenecks.md)
