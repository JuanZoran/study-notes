# vim插件使用

### vim-easymotion

- 设置leader键
  - 已经设置为”；“
- <leader> <leadrer> s 字符，可以全局搜索字符
- <leader><leader>f字符，可以向后搜索字符,F可以向前搜索字符



---

## vim-surround

- cs+搜索目标+替换目标，可以替换周围的符号
- ds+目标 可以删除周围的引号括号之类
- b代表小括号 B代表大括号
- ysiw【要添加的符号】在字符串两边添加符号
- dst 删除之前添加的标签

---

## 大小写转换

- ~ 将当前字母大小写转换
- n~ 将后面n个字母大小写转换
- g~~ 将当前行大小写字母转换
- gUU 将当前行转换成大写字母
- guu 将当前行转换成小写字母
- gu[i和a都可以]w 将当前单词转换成小写字母
- gU[i和a都可以]w 将当前单词转换成大写字母

---

## 多光标模式

- vscode的多光标cmd + d， 在vim中可以用gb来达到同样的功能 **需要按两下**
- +c可以更改选中的单词，加大写i可以单词前插入， 