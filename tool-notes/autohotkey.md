# autoHotKey的基本语法

## 热键

### 基本语法

- `原键::替换后的键`





### 基本热键映射

- \# -> win键
- ! -> alt键
- \+ -> shift键
- ~ ->**不屏蔽热键本身的功能**

- [L-R]Button ->鼠标左右键
- Wheel[Up-Down] ->鼠标滚轮上下滑动
- 

## 热键替换

### 基本语法

- ` ::原字符::替换后的字符`
- 较长时可以用return终止当前语句
- **默认需要使用终止符号来替换**

> 终止符号默认有：**-()[]{}':;"/\,.?!\`n \`t**（注意 \`n 是回车,\`t 是 Tab，且在它们之间还有一个原义的空格）
>
> > **如果不需要终止符号，需要加上*号 **
> >
> > > 例如：:**c\***:j@::john@somedomain.com *; 区分大小写且“不需要终止符”。*

- 如果需要替换完之后在末尾加上空格或者tab，需要在末尾加上反引号`

### 可选项

- 基本用法：在原字符前的两个引号中间插入选项符
- [**\***]    表示不需要终止符
- **B0**    表示不适用自动退格来擦除输入的缩写
- **C**       表示区分大小写
  - C0  表示不区分大小写