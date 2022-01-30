# TCP-Socket-Communication-server---putty-



HOW TO EXECUTE:



1. run your  project

2. open the putty
  * fill in the  IP, Port section
  * choose connection type as "RAW"
  * open
 
 
 
![tcp-putty - execution](https://user-images.githubusercontent.com/61898376/151284687-e108252d-6b2f-484c-8267-68054347014c.png)




RESULT:

when you input some word, server sends that word again.

ex: in: Zarina --> out: Zarina!



![tcp-putty - execution](https://user-images.githubusercontent.com/61898376/151289667-27fcd97a-a01c-43ce-88df-3cb1418184dd.png)

------

TIPS(??)

declaring "Host IP(127.0.0.1)" in sockaddr_in sockAddr;

* let's first use INADDR_ANY  while declaring sockAddr structure IP address:
```
sockaddr_in sockAddr;
memset(&sockAddr, 0, sizeof(sockAddr));
sockAddr.sin_family = AF_INET;
sockAddr.sin_port   = PORT;
sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
```
* using string local IP address

*for it we need to #include <WS2tcpip.h> 
```
const char* IP = "127.0.0.1";
sockaddr_in sockAddr;
memset(&sockAddr, 0, sizeof(sockAddr));
sockAddr.sin_family = AF_INET;
sockAddr.sin_port = PORT;
inet_pton(AF_INET, IP, &(sockAddr.sin_addr));
```
