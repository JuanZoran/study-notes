# 网络编程学习--socket函数

## socket函数介绍

- **linux**下 : `int socket (int 协议族, int 传输类型, int 计算机传输类型)`

- **windows**下: `SOCKET socket(int 协议族, int 传输数据类型, int 计算机传输类型)`



### 参数介绍

- 参数1 : 协议族

  指定**SOCKET使用的协议族** : 如ipv4, ipv6..等

- 参数2 : 传输数据类型

  指定**socket使用的传输数据格式** : 如面向连接的可靠传输, 不面向连接的非可靠传输等 

- 参数3 : 计算机传输的类型

  一般可以置为空, 用来**确定传输协议 **: 如TCP, UDP等

  一般前两个参数即可确定传输协议, 该参数是为了在同一协议族下有多个相同传输数据格式的传输方式时来确定具体传输类型的