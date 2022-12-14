# web项目--锁机制

## 基础知识

### RAII

- RAII全称是“Resource Acquisition is Initialization”，直译过来是**“资源获取即初始化”**.
- **在构造函数中申请分配资源，在析构函数中释放资源**。因为C++的语言机制保证了，当一个对象创建的时候，自动调用构造函数，当对象超出作用域的时候会自动调用析构函数。所以，在RAII的指导下，我们应该使用类来管理资源，将资源和对象的生命周期绑定
- RAII的核心思想是**将资源或者状态与对象的生命周期绑定**，通过C++的语言机制，实现资源和状态的安全管理,智能指针是RAII最好的例子



### 信号量

- **用于多线程同步**

只支持两种操作 : 

- P(申请信号量操作)

  申请时如果信号量 的值大于1, 则 - 1

  如果信号量的值为0, 则**挂起**

- V(返还信号量操作)

  返还时如果有等待信号量的线程, 则**唤醒**

  如果没有则信号量  +1



- 信号量的取值可以是任何自然数，最常用的，最简单的信号量是二进制信号量，只有0和1两个值.

> - sem_init函数用于初始化一个未命名的信号量
> - sem_destory函数用于销毁信号量
> - sem_wait函数将以原子操作方式将信号量减一,信号量为0时,sem_wait阻塞
> - sem_post函数以原子操作方式将信号量加一,信号量大于0时,唤醒调用sem_post的线程



---

### 互斥量

- **用于多线程互斥**

- 只有 0 和 1两种状态

- **加锁和解锁操作必须是同一进程**



- 互斥锁,也成互斥量,可以保护关键代码段,以确保独占式访问.当进入关键代码段,获得互斥锁将其加锁;离开关键代码段,唤醒等待该互斥锁的线程.

> - pthread_mutex_init函数用于初始化互斥锁
> - pthread_mutex_destory函数用于销毁互斥锁
> - pthread_mutex_lock函数以原子操作方式给互斥锁加锁
> - pthread_mutex_unlock函数以原子操作方式给互斥锁解锁



---

#### 提问

- **信号量和互斥量(互斥锁有什么区别)?**

​	信号量是为了同步, 互斥量是为了互斥;

 互斥量只能保证**同一时刻只能有一个进程访问资源, 具有唯一性和排他性**, 但无法限制访问者的先后顺序

 信号量**在互斥的基础上,通过其他机制实现访问者对资源的有序访问**, 如 : 挂起队列

​	

​	互斥量只有 0 和 1两种状态, 信号量可以是任何自然数

​	

​	**互斥的加锁和解锁只能由同一进程操作, 而信号量可以由不同的进程获得**



-----

### 条件变量

- 线程同步时可能会出现 : 

​	一个线程需要等另一个线程完成一个条件才可继续往下执行, 当前运行时条件还不成立, 所以应该先阻塞该进程, 当另一个线程完成了该条件, 再将之前阻塞的线程唤醒; 

​	完成这样的操作, 所用到的通信方式即使用条件变量

- 条件变量提供了一种线程间的通知机制,当某个共享数据达到某个值时,唤醒等待这个共享数据的线程.

> - pthread_cond_init函数用于初始化条件变量
> - pthread_cond_destory函数销毁条件变量
> - pthread_cond_broadcast函数以广播的方式唤醒**所有**等待目标条件变量的线程
> - pthread_cond_wait函数用于等待目标条件变量.该函数调用时需要传入 **mutex参数(加锁的互斥锁)** ,函数执行时,先把调用线程放入条件变量的请求队列,然后将互斥锁mutex解锁,当函数成功返回为0时,互斥锁会再次被锁上. **也就是说函数内部会有一次解锁和加锁操作**.



- *条件变量总是搭配互斥锁使用*

- ***经典的用于解决生产者消费者问题***



---

### **锁机制的功能**

- 实现多线程同步，通过锁机制，确保任一时刻只能有一个线程能进入关键代码段.

#### **封装的功能**

- 类中主要是Linux下三种锁进行封装，将锁的创建于销毁函数封装在类的构造与析构函数中，实现RAII机制



```c++
 1class sem{
 2    public:
 3        //构造函数
 4        sem()
 5        {
 6            //信号量初始化
 7            if(sem_init(&m_sem,0,0)!=0){
 8                throw std::exception();
 9            }
10        }
11        //析构函数
12        ~sem()
13        {
14            //信号量销毁
15            sem_destroy(&m_sem);
16        }
17    private:
18        sem_t m_sem;
19};
```



- 将重复使用的代码封装为函数，减少代码的重复，使其更简洁



```c++
 1   //条件变量的使用机制需要配合锁来使用
 2   //内部会有一次加锁和解锁
 3   //封装起来会使得更加简洁
 4   bool wait()
 5   {
 6       int ret=0;
 7       pthread_mutex_lock(&m_mutex);
 8       ret=pthread_cond_wait(&m_cond,&m_mutex);
 9       pthread_mutex_unlock(&m_mutex);
10       return ret==0;
11   }
12   bool signal()
13   {
14       return pthread_cond_signal(&m_cond)==0;
15   }
```