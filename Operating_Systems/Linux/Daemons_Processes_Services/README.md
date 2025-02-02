- [Daemon](#d)
- [Service](#s)
- [Process](#p)
  - [Converting Process to service](#cov)

<a name=d></a>
## Daemon
Process running in background to perform system tasks. 

<a name=s></a>
## Service
1 or more daemon/processes combined together for servicing the user. Eg: File server, Apache/httpd service(shows 5-6 processes in ps), sshd, systemd
```c
# ps -aux|grep systemd
      PID   %cpu  %mem   vsz    rss  tty  state  start-time   command
root     1   0.0  0.0  193844  5808   ?    Ss    2020  1:11  /usr/lib/systemd/systemd --switched-root --system
root    632  0.0  0.0  390601  5782   ?    Ss    2020  1:11  /usr/lib/systemd/systemd-journald     //Event Logging with journald
root    669  0.0  0.0  112121  1212   ?    Ss    2020  1:11  /usr/lib/systemd/systemd-udevd
root    904  0.0  0.0  129492  8589   ?    Ss    2020  1:11  /usr/lib/systemd/systemd-logind
```        

<a name=p></a>
## Process
1 or more threads of execution together.
<a name=con></a>
#### Converting Process to service
```c
# g++ test.cpp -o AmitService -std=c++11
int main(){        
    cout<<"Sleeping for 9 sec";    
    this::thread::sleep_for(chrono::microseconds(9*10pow6));    
    cout<<"Awake";    
}
# vim /etc/systemd/system/AmitService.service
    [Unit]
    Description=Test Service
    After=network.target
    StartLimitIntervalSec=0
    [Service]
    Type=simple
    Restart=always
    RestartSec=1
    User=amit
    ExecStart=/usr/bin/env /home/amit/code/test.cpp
    [Install]
    WantedBy=multi-user.target
# systemctl start|enable|status|disable AmitService
# cat /var/log/message                        //Check Logs
```
