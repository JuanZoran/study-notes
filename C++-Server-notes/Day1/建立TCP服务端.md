# 使用Socket API建立简易的TCP服务端

## 目录

- [建立一个socket](#建立一个socket)
- [绑定接受客户端连接的端口bind](#绑定接受客户端连接的端口bind)
- [监听网络端口listen](#监听网络端口listen)
- [等待接受客户端连接accept](#[等待接受客户端连接accept)
- [向客户端发送一条数据send](#向客户端发送一条数据send)
- [关闭socket](#关闭socket)
- [代码展示](#代码展示)



### 建立一个socket

- 使用socket函数返回**SOCKET** 对象

  - 返回值：设置完成的SOCKET对象

  - 参数1：IP协议类型

    - [^AF_INET]:IPV4

    - [^AF_INET6]:IPV6

  - 参数2：传输的数据报类型

    - [^SOCK_STREAM]:流格式SOCKET

      > 流格式套接字（Stream Sockets）也叫“面向连接的套接字”，在代码中使用 SOCK_STREAM 表示。
      >
      > SOCK_STREAM 是一种可靠的、双向的通信数据流，数据可以准确无误地到达另一台计算机，如果损坏或丢失，则会重新发送。
      >
      > 流格式套接字有自己的纠错机制，在此我们就不讨论了。
      >
      > **SOCK_STREAM 有以下几个特征：**
      >
      > - 数据在传输过程中不会消失；
      > - 数据是按照顺序传输的；
      > - 数据的发送和接收不是同步的（不存在数据边界）
      > - 基于TCP协议

    - [^SOCK_DGRAM]:数据报格式SOCKET

      > 数据报格式套接字（Datagram Sockets）也叫“无连接的套接字”，在代码中使用 SOCK_DGRAM 表示。
      >
      > 计算机只管传输数据，不作数据校验，如果数据在传输中损坏，或者没有到达另一台计算机，是没有办法补救的。也就是说，数据错了就错了，无法重传。
      >
      > 因为数据报套接字所做的校验工作少，所以在传输效率方面比流格式套接字要高。
      >
      > **可以将 SOCK_DGRAM 比喻成高速移动的摩托车快递，它有以下特征：**
      >
      > - 强调快速传输而非传输顺序；
      > - 传输的数据可能丢失也可能损毁；
      > - 限制每次传输的数据大小；
      > - 数据的发送和接收是同步的（存在数据边界）
      > - 基于UDP协议

  - 参数3：传输协议

    - [^IPPROTO_TCP]:TCP协议

    - [^IPPROTO_UDP]:UDP协议

### 绑定接受客户端连接的端口bind

- 使用bind函数连接客服端的**IP地址及端口**

  - 返回值：绑定结果的状态

    > 失败返回0，但是一般为了代码的可读性，使用给定的宏 SOCKET_ERROR

  - 参数1：SOCKET接口

    > 填入上一步使用socket函数返回的SOCKET对象即可

  - 参数2：可被绑定的端口

    > 使用`sockaddr_in`创建可被绑定的地址对象

    > > - 设置端口协议: `(创建的对象名).sin_family = 上一步选择的IP协议类型`
    > >
    > > - 分 配 端 口 号:`(创建的对象名).sin_port =  htons(设定的端口号)` 
    > >
    > > > **htons**:
    > > >
    > > > 端口号在传输过程中为2字节的unsigned short类型
    > > >
    > > > 网络传输中的short类型经过特殊处理，与内置的类型不同，则需要htons函数进行转换
    > > >
    > > > htons = host to net unsigned short
    > >
    > > - 设定IP地址:`(创建的对象名).sin_addr.S.un.S.addr = (设定的IP)` 
    > >
    > > > 其中“127.0.0.1”意味着本地主机的地址，一般用于本地测试
    > > >
    > > > 同时windows提供了宏定义 INADDR_ANY，表示使用主机任意IP地址

### 监听网络端口listen

- 使用listen函数监听网络端口

  - 返回值：监听状态

    > 同bind函数一样，建议使用SOCKET_ERROR判断监听结果

  - 参数1：SOCKET接口

    > 填入第一步使用socket函数返回的SOCKET对象即可

  - 参数2：backlog

    > 这个参数涉及到一些网络的细节。进程处理一个一个连接请求的时候，可能还存在其它的连接请求。因为TCP连接是一个过程，所以可能存在一种半连接的状态，有时由于同时尝试连接的用户过多，使得服务器进程无法快速地完成连接请求。如果这个情况出现了，服务器进程希望内核如何处理呢？内核会在自己的进程空间里维护一个队列以跟踪这些完成的连接但服务器进程还没有接手处理或正在进行的连接，这样的一个队列内核不可能让其任意大，所以必须有一个大小的上限。这个backlog告诉内核使用这个数值作为上限。
    >
    > 毫无疑问，服务器进程不能随便指定一个数值，内核有一个许可的范围。这个范围是实现相关的。很难有某种统一，一般这个值会小30以内

### 等待接受客户端连接accept

- 使用accept函数接收客户端的请求

  - 返回值：接收到的**客户端**对象

    > 如果失败，会返回一个INVALID_SOCKET对象
    >
    > 可以使用通过查看返回对象内的sin_addr成员，来读取客户端ip地址
    >
    > > 同端口设置一样，需要使用转换函数`inet_ntoa([接收的对象名].sin_addr)`转换成字符串类型
    > >
    > > 该函数在vs中已经被弃用
    > >
    > > 在**第一行**中添加宏定义`#define _WINSOCK_DEPRECATED_NO_WARNINGS`可消除警告

  - 参数1：SOCKET接口

  - 参数2：用于存放请求的客户端的地址

    > 传入一个新的SOCKET地址对象（建议初始化为空）

  - 参数3：客户端的大小

    > 使用sizeof（客服端的类型），需要传入**int***的变量

### 向客户端发送一条数据send

- 使用send函数向客户端返回数据

  - 返回值

  - 参数1：**客户端**的SOCKET对象

    > accpet函数接收返回的SOCKET对象

  - 参数2：传送的数据(**const char***类型)

  - 参数3：传送的数据的大小

  - 参数4：默认值填0

### 关闭socket

- 使用closesocket关闭创建的socket
  - 参数1：第一步创建的SOCKET对象

---

### 代码展示

```C++
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

#pragma comment(lib, "ws2_32.lib")
//#define _WINSOCK_DEPRECATED_NO_WARNINGS


int main() {
	WORD ver = MAKEWORD(2, 2);
	WSADATA wsa;
	WSAStartup(ver, &wsa);
	//建立一个socket接口
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//使用bind绑定接受客户端连接的网络端口
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);				//host to net unsigned short
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;     //inet_addr("127.0.0.1");
	
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin))) {
		cout << "绑定失败" << endl;
	}
	else {
		cout << "绑定成功！" << endl;
	}

	//使用listen监听网络端口
	const int maxLinkNum = 5;
	if (SOCKET_ERROR == listen(_sock, maxLinkNum)) {
		cout << "监听失败" << endl;
	}
	else {
		cout << "监听成功！" << endl;
	}

	//accept等待客户端进行链接
	SOCKADDR_IN cAddr = {};
	int cAddrLen = sizeof(SOCKADDR_IN);
	SOCKET _cSock = INVALID_SOCKET;
	char msg[] = "Hello Socket!";

	while (true) {
		_cSock = accept(_sock, (SOCKADDR*)&cAddr, &cAddrLen);
		if (_cSock == INVALID_SOCKET) {
			cout << "接受的地址无效" << endl;
		}
		cout << "新客户端加入：IP = " << inet_ntoa(cAddr.sin_addr) << endl;
		//send向客户端返回数据
		send(_cSock, msg, strlen(msg) + 1, 0);
	}

	//关闭socket
	closesocket(_sock);

	WSACleanup();
	return 0;
}
```





