- [Availabilty zones](#az)
- [Region](#gr)
- [Edge Location](#el)
- [GovCloud](#gc)
- [VPC(Virtual Private Cloud)](#vpc)
   - [Subnets](#sn)
   - [Internet gateway](#ig)
   - [Virtual private gateway](#vpg)
   - [AWS Direct Connect](#adc)
   - [VPC Flow Logs](#fl)
- [Transit Gateway](#tg)
- [Reserved](#r)
- [Recommendations](#rec)
- [Serverless](#sl)

<a name=az></a>
### Availabilty zones
- Single or Group of data centers owned by AWS is called AZ. Naming convention {Geographic location}{letter}. Example AZs for us-east are: us-east-1a, us-east-1b
- Latency between AZ's is <10ms, AZ are located 10s of miles apart from each other.
- A best practice is to run a application across at least 2 Availability Zones in a Region.
```c
   ---------------------------------  Region   ---------------------------------
   
   |-----------AZ-1---------------|             |-----------AZ-2---------------|
   | Data-center1  Data-center2   | < 10 ms     | Data-center-n  Data-center-m |
   |------------------------------|             |------------------------------|
```

<a name=gr></a>
### [Geographic Region](https://aws.amazon.com/about-aws/global-infrastructure/regions_az/?p=ngi&loc=2)
- AWS region consists of multiple, isolated, physically seperated [Availablity Zones](#az)
- **Largest Region of AWS is US-EAST(ie North Virginia)**, new services becomes available here 1st.
|<img src=regions_and_az.JPG width=400 height=200 />|<img src=north-america-political-map.jpg width=400 height=200 />|

#### Properties
- Data stored in region is not replicated outside of that region unless customers replicates to other regions.

#### In which region should I place my service / Factors to consider before choosing a region
- _1. Compliance with data governance and legal requirements:_ Depending on your company and location, you might need to run your application in specific areas. For example, if your company requires all of its data to reside within the boundaries of the UK, you would choose the London Region.
- _2. Proximity to your customers:_ Selecting a Region that is close to your customers will help you to get content to them faster.
- _3. Available services within a Region:_ Sometimes, the closest Region might not have all the features that you want to offer to customers. Eg: Amazon Braket (AWS quantum computing platform) is not yet available in every AWS Region around the world, so choose that region in which service is available.
- _4. Pricing:_ Suppose that you are considering running applications in both the United States and Brazil. The way Brazil’s tax structure is set up, it might cost 50% more to run wrt US.


<a name=el></a>
### Edge Location
These are also Datacenters but located very near to customer, wrt to actual datacenter which hosts the customer's data. [Cloudfront](/System-Design/Concepts/AWS/Network/CloudFront) pulls the data and pushes to customer.

**[WORLD MAP](https://geology.com/world/world-map.shtml)**

<a name=gc></a>
### GovCloud Region
- [Geographic Region](#gr) for highly sensative data storage. Eg: US DOD, US DOJ(dept of justice) etc. Presently only 2 GovCloud Regions: US-West, US-East.
- Person using GovCloud need to be US citizen and located in US only.

<a name=vpc></a>
## Amazon VPC(Virtual Private Cloud)
VPC is a isolated section in AWS Cloud. Then we can have resources inside VPC. VPC can be in multiple [AZ](#az)
<img src=ACL_security_group.JPG width=600 />
<a name=sn></a>
### Subnets 
- All resources are organized into subnets. Subnet is a section of a VPC that can contain resources(eg: Amazon EC2 instances)
- **Types of Subnets:**
   - **1. Public:** contain resources that need to be accessible by the public, such as an online store’s website.
   - **2. Private:** contain resources that should be accessible only through private network, such as a DB that contains customers’ personal information.
#### Network ACL
- Every packet that comes into/goes from subnet is checked against N/W ACL. N/W ACL is a firewall which applies rules to incoming/outgoing packets and allows/denies them into subnet.
- N/W ACLs are stateless ie every packet is checked against a rule, no state is maintained.
- Similar work is done by *[Security Group](/System-Design/Concepts/AWS/compute/EC2)* but SG are stateful.
- **ACL Types**
  - _1. Default ACL:_ Every AWS account has default N/W ACL. By default all inbound and outbound traffic are allowed, but you can modify it by adding your own rules.
  - _2. Custom ACL:_ We can create Custom ACL as well. By default all inbound and outbound traffic is denied until you add rules to specify which traffic to allow.

||N/W ACL|Security Group|
|---|---|---|
|What|Firewall at boundary of subnet|Firewall at boundary of EC2 instance|
|Stateful|no|yes|
|Outbound traffic checking|yes|no|

<a name=ig></a>
#### Internet gateway
To allow public traffic from internet to access VPC, a IG is needed to be attached to VPC.
```c
                        <--------------------AWS Datacenter------------------------>
                              |------------Company-A-VPC--------------|
                              |        |---------subnet1----------|   |
                              |        |         resources        |   |
client   {internet}    InternetG/W   N/W ACL      EC2             |   |
                              |        |--------------------------|   |
                              |---------------------------------------|
```
<a name=vpg></a>
#### Virtual private gateway
if VPC have some private reources(Eg: EC2 instances) then VPG is used to access them
```c
<-------------------------------AWS Datacenter------->
   |--------------Company-A VPC---------------|
   | |-----subnet1-------|                    |
   | | pvt resource1(DB) |                    |
   | | EC2          Virtual Pvt G/W ----------- VPN Connection ------- (Internet) ------ Client
   | |                   |                    |
   | |-------------------|                    |
   |                                          |
   |------------------------------------------|
```
<a name=adc></a>
#### AWS Direct Connect
This helps to establish a dedicated private connection between Client's datacenter and a VPC. ie this is direct line.
```c
<------------------AWS Datacenter------->
   |--------------Company-A VPC--------|
   | |-----subnet1-------|             |
   | | pvt resource1(DB) |             |
   | | EC2          Virtual Pvt G/W    |     AWS Direct Connect --- (Client Datacenter)
   | |                   |             |
   | |-------------------|             |
   |                                   |
   |-----------------------------------|
```

<a name=fl></a>
#### VPC Flow Logs
- Capture information about the IP traffic going to/from network interfaces in VPC.
- Flow log data can be published to CloudWatch Logs or Amazon S3. Flow logs can help you with a number of tasks, such as:
   - Diagnosing overly restrictive security group rules
   - Monitoring the traffic that is reaching your instance
   - Determining the direction of the traffic to and from the network interfaces
- Flow log data is collected outside of the path of your network traffic, and therefore does not affect network throughput or latency. You can create or delete flow logs without any risk of impact to network performance.

<a name=tg></a>
### Transit Gateway
This service connects customer's [Virtual Private Clouds (VPCs)](#vpc) and their on-premises networks to a single gateway.
<img src=transit_gateway.png width=600/>

<a name=r></a>
### Which services can be reserved?
- Discounts(up to 75%) can be availed by reservation in advance. Some of the services which can be reserved: EC2, DynamoDB, ElastiCache, RDS, and RedShift.

<a name=rec></a>
### Recommendations
- _1. Where possible, Replace EC2 with AWS managed services(Eg: lambda):_ 
   - You should be free from capacity decisions hence you only pay for actual processing time.

<a name=sl></a>
### Serverless
- Unlike [EC2](/System-Design/Concepts/AWS/) which is a VM which you need to create and run code on it. Serverless means you do not need to create VM. You can directly upload your code(to webservice) and it will start running.
- That means server(or EC2) instance is already created by AWS for you.
- Examples of serverless Architectures: Lambda, DynamoDB, Fargate

<a name=sf></a>
### Step Function
- Step functions helps in coordinating multiple AWS services into serverless workflows so we can build and update apps quickly.
- Step Functions lets you build visual workflows that enable fast translation of business requirements into technical requirements.
