# 内存管理--C++关键字

## 目录

[new](#new)

[new[]](#new[])

[operator new](#operator new)

[new()](#new())

[delete](#delete)

[delete[]](#delete[])

[operator delete](#operator delete)

[为什么new[]和delete[]需要成对使用?](#为什么new[]和delete[]需要成对使用?)

[总结](#总结)

---

## new

- 使用示例  :   `int* ptr = new int;`

- 申请该对象大小的内存   ***(由operator new)***来完成

- 将内存绑定到声明的指针变量

- 通过该指针变量调用其构造函数 **使用new时带有参数,则传递相应的参数**

  *该操作(通过指针调用其构造函数) 只能由编译器调用*

- 不可重载

---

## new[]

- 使用示例 : `int* ptr = new int[size];`
- 申请size * 对象大小的内存 ***(由operator new)***来完成
- 将内存绑定到声明的指针变量
- 通过该变量,**调用size**次构造函数,**传递时带有参数,则传递相应的参数**
- 不可重载

---

## operator new

- 使用示例 : `int* temp = operator new(sizeof(int));`
- 内部实际是调用mallloc函数
- 可以发生重载

---

## new()

- 使用示例 : `int* ptr2 = new(ptr)int`

- 使用new()表示***由程序员自己来决定地址空间的首地址***

  指定的首地址在示例中,即ptr的地址

- 申请空间的大小为对应的类型大小,示例中的类型为int, 则对应的大小为4字节

---

## delete

- 使用示例 : `delelte ptr;`
- 调用该指针对应对象的析构函数
- 释放该指针的内存空间

---

## delete[]

- 使用示例:`delete[] arrayPtr`
- 调用该指针下所有对象的析构函数
- 释放该指针所对应的空间

----

## operator delete

- 使用示例 : `delete intPtr(4);`
- 释放该指针,需要大小一致
- 内部调用free函数
- 可以发生重载

---

## 为什么new[]和delete[]需要成对使用

- 避免产生内存泄漏

  ***内存泄漏的产生根本原因不在于本身对象没有被释放***,而是当本身对象内含指针时,并且由其析构函数来delete该指针时,造成内存泄漏

- 核心是因为**delete来删除数组对象**时, 只有第一个对象所对应的析构函数被调用

  而使用delete[]释放数组对象,数组中每一个对象的析构函数都会被调用

---

## 总结

|   申请内存   |    释放内存     | 是否可重载 |
| :----------: | :-------------: | :--------: |
|     new      |     delete      |     否     |
|    new[]     |    delete[]     |     否     |
|    new()     |   标准未提供    |     否     |
| operator new | operator delete |     是     |