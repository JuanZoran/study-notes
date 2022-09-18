# 深入了解计算机系统--存储系统

## 随机访问存储器

- SRAM
- DRAM、

---

## 只读存储器（ROM）

- 磁盘（disk）
- 闪存（SSD）

---

## 高速缓存

### 高速缓存内部组成

- 有效位

> 为缓存行的的第一位
>
> > 提供这个位只是为了方便,实际上它并不是高级告诉缓存的一部分

- 组（S）
- 行（E）
- 块（B）
- 块大小（m）

### 地址组成

- 组索引

> 记录需要寻找的地址的组编号

- 标识符

> 记录当前组标识编号
>
> > 由于存在**存储器块的数目比高速缓存组数多**的情况 ，所以为了解决冲突，将对应的块编号对组数进行取模运算存入对应的高速缓存组当中，同时为了标识当前表示的存储块编号，引入标识符用来**区分块的编号**

- 块偏移

> 缓存中的块其实就相当于索引的value部分,真正存储的地址内容放在块中
>
> 同时块一般含有多个字节数据,其空间又是连续的,所以可以视为**一个数组**
>
> > 块偏移是从缓存(**块可以视为一个数组**)中取到对应的数据(**组索引和标识符用来匹配所寻找的地址缓存中是否存在**)



### 地址计算方法

- 计算块偏移

> 首先**将所需要寻找的地址除以块字节数**,得到的余数即是块偏移的大小
>
> > 因为缓存取数据是以块为单位,每次缓存不命中时,缓存会向下一级缓存申请整个块的数据

- 计算标识符

> 块偏移计算中得到的商除以存储器数目(也就是**组数目**), 此次计算得到的商即是标识符的大小
>
> > 块偏移计算中得到的商,其实就是作为索引部分的值,也就是该块的编号
> >
> > > 将取得地址数据的过程可以视为从一个表格中寻找所需要的数据的过程,其中
> > >
> > > - 标识符->对应的表格中的第几列
> > > - 组索引->对应表格中的分类栏

- 计算组索引

> 计算标识符中得到的余数,即是组索引的大小



### 寻址过程的模拟

- 寻找对应的组是否有效(观察有效位是否为1)
- 比对该组的标识符是否对应寻找地址
- 上述两步均为真,则通过块偏移取得数据返回
- 寻址失败,向下一级缓存询问该地址,并添加进缓存中

---

## 缓存的作用

- 因为不同存储器的价格和容量不同,存储器性能和cpu性能差距太大
- 每一级缓存都可以视为上一级的内存

  
