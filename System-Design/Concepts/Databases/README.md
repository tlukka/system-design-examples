- [SQL vs NoSQL](#sn)
- [Object vs Block vs File Storage](#obf)
- [Database vs Datawarehouse](#dd)
- **[IMDB / In Memory / Embedded DB](#i)**


## Comparisons
<a name=sn></a>
### SQL/Relational/Structured vs noSQL/nonRelational/unStructured
Today most organization are using SQL+noSQL DB combinations. 2019 stats:   MySQL + MongoDB: 34.15%,  MySQL + PostgreSQL: 9.76%

|DB| SQL, Relational, Structured | noSQL, nonRelational, unStructured |
|---|---|---|
|Examples |Amazon(Aurora, RDS), MySQL, postgreSQL, mariaDB|Semistructured: Amazon (S3, dynamoDB), Apache Cassandra<br> Unstructured: Amazon S3, Apache CouchDB, MongoDB|
|Types |ORDBMS(Object RDBMS):RDBMS build on OOD.Eg:PostGreSQL <br> RDBMS: mySQL|a. KEY-VALUE DB:<br> - redis, Amazon dynamoDB, Voldemort, sled(rust) <br> b. WIDE-COLUMN DB:<br> - Stores data as columns instead of rows. Eg: Cassandra, HBase <br> c. DOCUMENT DB: <br> - Data is stored in documents(XML, JSON, binary) Eg: mongoDB, Amazon dynamoDB. <br> d. GRAPH DB: <br> Data is stored in form of graph.Eg: Neo4J, HyperGraphDB| 
|Storage format | Table(Records searched using primary key) | <key, value> or xml or json or objects |
|Huge data support | no(becomes slow) | yes |
|Storage | May be on 1 or multiple servers | Always on multiple low cost nodes[commodity hardware] |
|Scaling | Vertical | Horizontal, cheaper, raw data can be pushed:no schema, pro |
|Tech Support | Good, query-writing:simple | Poor, query-writing:complex |
|Schema | fixed | not fixed. defining schema for unstructured data is very tough |

<a name=obf></a>
### Object vs Block vs File storage

|DB | Object | Block | File |
|---|---|---|---|
|Examples | Amazon S3,ceph, openstack swift    | Amazon EBS, SAN-Arrays   |  Amazon EFS |
|Stores |Object{unique_key,metaData+data}| raw blocks(xfs,ext4 etc). Only part that changed need to be updated. | data in file, with limited meta-data |
|Disadv|When ever there is small change in object(eg:video), whole object needed to be reuploaded. if object is 80GB then lot of time wasted in uploading|||
|Adv||Only part that is changed need to uploaded. if block is 80GB and small part is changed, then uploading takes very less time||
|Scaling | Easy | Tough(on high volume becomes unmanagable) | |
|Suitable for |objects can be: images,videos,text files,docs,photos,songs |files,docs | |
|Consistency | Eventual consistent | Strongly consistent| |
|Use cases |Occasional Changes & Storage|Making large RW changes in file and storing frequently.| |


<a name=dd></a>
### Database vs Datawarehouse
```c
                 |     Database                            | Datawarehouse
-----------------|-----------------------------------------|-------------------
Purpose          | Stores customer data                    | helps analyze data
Contians         | related data                            | Historical & commutative data
Orientation      | application-oriented-collection of data | subject-oriented collection of data
Uses             | Online Transactional Processing (OLTP)  |  Online Analytical Processing (OLAP)
Modelling Techniques | ER modeling techniques              | data modeling
used 
```

<a name=i></a>
## IMDB(In Memory DB) / MMDB(Main Memory DB) / Embedded DB
Stores all data in main memory/RAM not on hard-disk. 
- Examples: VoltDB, [Redis](/System-Design/Concepts/Cache).
  - Why Redis is cache & imdb both? Redis has features of a Cache plus processing/querying capabilities. Redis supports multiple data structures and you can query the data in the Redis (examples like get last 10 accessed items, get the most used item etc).
- *Advantages:* Faster. Since disk access is always slower than RAM
- *Applications?* Where response time is critical. Eg: Telecom equiments, Jet communications etc
- *Disadvantages:* 
  - _1. Availability Problem?_ Since RAM is volatile(Means data is lost as power is gone or some failure). Solution:
```c
1a. Snapshot files OR checkpoint images, which record the state of the database at a given moment in time.
1b. Transaction logging, which records changes to the database in a journal file
1c. Replication
```
  - _2. Expensive:_ RAM is always costlier than Disk, Huge amounts cannot be stored here.
- **IMDB vs [DBCache](/System-Design/Concepts/Cache):** DBCache stores: Mostly used, less frequently changing data is stored in cache. IMDB stores: Frequently changing data.

