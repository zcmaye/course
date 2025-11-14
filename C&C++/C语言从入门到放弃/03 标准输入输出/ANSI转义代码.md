# ANSI转义代码

ANSI转义代码（ANSI escape code）是一种在文本终端中控制格式、颜色和其他输出选项的代码。它们通常以ESC字符（十进制27、八进制033、十六进制0x1B）开始，后跟一个左方括号和一系列参数，最后以一个字母结束。这些代码允许开发者在终端中创建丰富多彩的文本界面，提高用户体验。

## 语法

ANSI转义代码的基本结构如下：

```bash
\033 + "[" + <参数> + <字母>
```

其中，`\033`代表ESC字符，`[`是控制序列引导符（CSI），`<参数>`是由分号分隔的数字序列，`<字母>`是指定的功能代码。

## 常用功能

ANSI转义代码提供了多种功能，例如移动光标、清除屏幕部分内容、滚动窗口等。

### 光标控制

#### 1. 光标移动

| 代码              | 功能               | 示例                           |
| :---------------- | :----------------- | :----------------------------- |
| `\033[<n>A`       | 光标上移n行        | `\033[2A` 上移2行              |
| `\033[<n>B`       | 光标下移n行        | `\033[1B` 下移1行              |
| `\033[<n>C`       | 光标右移n列        | `\033[5C` 右移5列              |
| `\033[<n>D`       | 光标左移n列        | `\033[3D` 左移3列              |
| `\033[<行>;<列>H` | 光标定位到指定位置 | `\033[10;5H` 移动到第10行第5列 |
| `\033[<行>;<列>f` | 同上               | `\033[5;20f` 移动到第5行第20列 |

+ 移动光标函数

```c
/**
 * 设置光标位置.
 * 
 * \param x 横坐标(从1开始)
 * \param y	纵坐标(从1开始)
 */
inline void setCursorPos(int x, int y) {
	printf("\033[%d;%dH",x,y);
}
```

#### 2. 光标保存与恢复

| 代码     | 功能                   |
| :------- | :--------------------- |
| `\033[s` | 保存当前光标位置       |
| `\033[u` | 恢复之前保存的光标位置 |

+ 保存和恢复光标函数

```c
/**
 * 保存光标位置.
 */
inline void saveCursorPos() {
	printf("\033[s"); // save cursor position
}

/**
 * 恢复到上次保存的位置,如果没有保存则光标回到控制台左上角，即(1,1)位置.
 */
inline void restoreCursorPos() {
	printf("\033[u"); // restore cursor position
}

```

#### 3. 光标可见性

| 代码        | 功能     |
| :---------- | :------- |
| `\033[?25l` | 隐藏光标 |
| `\033[?25h` | 显示光标 |

+ 设置光标可见性函数

```c
/**
 * 设置光标是否可见.
 * 
 * \param visible 0:不可见,1:可见
 */
inline void setCursorVisible(int visible) {
	printf("\033[?25%c", visible ? 'h' : 'l');
}
```

#### 4. 清屏与删除

| 代码                | 功能                   |
| :------------------ | :--------------------- |
| `\033[2J`           | 清屏并移动光标到左上角 |
| `\033[K`或`\033[0K` | 清除从光标到行尾的内容 |
| `\033[1K`           | 删除从行首到光标       |
| `\033[2K`           | 删除整行               |

+ 清除内容，光标位置不变

```c
inline void clearScreen() {
	printf("\033[2J");
}
inline void clearToEndOfScreen() {
	printf("\033[J");
}
inline void clearToStartOfScreen() {
	printf("\033[1J");
}

inline void clearLine() {
	printf("\033[2K");
}
inline void clearToEndOfLine() {
	printf("\033[K");
}
inline void clearToStartOfLine() {
	printf("\033[1K");
}

```



### 颜色和样式

ANSI转义序列中，颜色和样式控制也是一项重要功能。它们通常以`\033[`开头，后跟一个或多个数字（用分号分隔），最后以字母`m`结束。这些序列用于设置文本的颜色、背景色和样式（如粗体、下划线等）。

#### 样式

##### 文本样式代码

| 代码 | 样式         | 说明                                   |
| :--- | :----------- | :------------------------------------- |
| `0`  | 重置所有属性 | 恢复正常显示                           |
| `1`  | 粗体/高亮    | 加粗文本或提高亮度                     |
| `2`  | 弱化         | 降低亮度（不常用，就是正常显示的文本） |
| `3`  | 斜体         | 斜体文本(貌似不生效)                   |
| `4`  | 下划线       | 文本下划线                             |
| `5`  | 慢速闪烁     | 文本缓慢闪烁                           |
| `6`  | 快速闪烁     | 文本快速闪烁                           |
| `7`  | 反显         | 前景色和背景色互换                     |
| `8`  | 隐藏         | 隐藏文本（密码输入）                   |
| `9`  | 删除线       | 文本中间划线(貌似不生效)               |

+ 粗体/高亮

```c
printf("\033[1m");			//加粗
printf("hello 你好\n");		//高亮的文字
printf("\033[0m");			//关闭高亮
printf("hello 你好\n");		//正常的文字
```

#### 颜色

##### 基础颜色代码

**前景色（文本颜色）**

| 代码 | 颜色 | 代码 | 颜色   |
| :--- | :--- | :--- | :----- |
| `30` | 黑色 | `90` | 亮黑色 |
| `31` | 红色 | `91` | 亮红色 |
| `32` | 绿色 | `92` | 亮绿色 |
| `33` | 黄色 | `93` | 亮黄色 |
| `34` | 蓝色 | `94` | 亮蓝色 |
| `35` | 洋红 | `95` | 亮洋红 |
| `36` | 青色 | `96` | 亮青色 |
| `37` | 白色 | `97` | 亮白色 |

+ 颜色测试

```c
	for (int i = 30; i <= 37; i++) {
		printf("\033[%dm hello", i);
	}
	printf("\n");
	for (int i = 90; i <= 97; i++) {
		printf("\033[%dm hello", i);
	}
```

**背景色**

| 代码 | 颜色 | 代码  | 颜色   |
| :--- | :--- | :---- | :----- |
| `40` | 黑色 | `100` | 亮黑色 |
| `41` | 红色 | `101` | 亮红色 |
| `42` | 绿色 | `102` | 亮绿色 |
| `43` | 黄色 | `103` | 亮黄色 |
| `44` | 蓝色 | `104` | 亮蓝色 |
| `45` | 洋红 | `105` | 亮洋红 |
| `46` | 青色 | `106` | 亮青色 |
| `47` | 白色 | `107` | 亮白色 |

+ 颜色测试

```c
	printf("\n");
	for (int i = 40; i <= 47; i++) {
		printf("\033[%dm", i);
		printf(" hello ");
	}
	printf("\n");
	for (int i = 100; i <= 107; i++) {
		printf("\033[%dm hello", i);
	}
```

#### 搭配使用

+ 同时使用前景色和背景色

```c
	for (int i = 30; i <= 37; i++) {
		printf("\033[%d;%dm", i, 47 - (i - 30));
		printf("hello 你好\n");
	}
	clearStyle();
```

+ 样式、背景、前景色同时使用

```c
	printf("\033[4;%d;%dm hello",FG_Red, BG_Yellow);
```

#### 函数

##### 颜色枚举

```c
enum ConsoleColor {
	FG_Black = 30,		//黑色
	FG_Red = 31,		//红色
	FG_Green = 32,		//绿色
	FG_Yellow = 33,		//黄色
	FG_Blue = 34,		//蓝色
	FG_Magenta = 35,	//洋红
	FG_Cyan = 36,		//青色
	FG_White = 37,		//白色	
	FG_LightBlack = 90,		//亮黑色
	FG_LightRed = 91,		//亮红色
	FG_LightGreen = 92,		//亮绿色
	FG_LightYellow = 93,	//亮黄色
	FG_LightBlue = 94,		//亮蓝色
	FG_LightMagenta = 95,	//亮洋红
	FG_LightCyan = 96,		//亮青色
	FG_LightWhite = 97,		//亮白色	
	
	BG_Black = 40,		//黑色
	BG_Red = 41,		//红色
	BG_Green = 42,		//绿色
	BG_Yellow = 43,		//黄色
	BG_Blue = 44,		//蓝色
	BG_Magenta = 45,	//洋红
	BG_Cyan = 46,		//青色
	BG_White = 47,		//白色	
	BG_LightBlack = 100,		//亮黑色
	BG_LightRed = 101,		//亮红色
	BG_LightGreen = 102,		//亮绿色
	BG_LightYellow = 103,	//亮黄色
	BG_LightBlue = 104,		//亮蓝色
	BG_LightMagenta = 105,	//亮洋红
	BG_LightCyan = 106,		//亮青色
	BG_LightWhite = 107,		//亮白色	
};
```

##### 设置颜色

```c
inline void setColor(enum ConsoleColor color) {
	printf("\033[%dm", color);
}
```

##### 样式结构

```c
typedef struct ConsoleStyle {
	int style;
	enum ConsoleColor fgColor;	/*!前景颜色*/
	enum ConsoleColor bgColor;	/*!背景颜色*/
}ConsoleStyle;
```

##### 设置清理样式

```c
ConsoleStyle getDefaultStyle() {
	ConsoleStyle style = { 0,FG_Black ,BG_White };
	return style;
}

inline void setStyle(ConsoleStyle* style) {
	printf("\033[%d;%d;%dm", style->style, style->fgColor, style->bgColor);
}
inline void clearStyle() {
	printf("\033[0m");
}
```

##### 输出文本

```c
inline void putText(const char* text, int x, int y) {
	printf("\033[%d;%dH%s\033[0m", x, y, text);
}

inline void putTextPro(const char* text, int x, int y, ConsoleStyle* style) {
	printf("\033[%d;%dH\033[%d;%d;%dm%s\033[0m", x, y, style->style, style->fgColor, style->bgColor, text);
}

inline void putTextEx(const char* text, int x, int y,enum ConsoleColor fgColor, enum ConsoleColor bgColor) {
	printf("\033[%d;%dH\033[%d;%dm%s\033[0m", x, y, fgColor, bgColor, text);
}
```

测试：

```c
	putText("hello", 10, 10);

	ConsoleStyle style = getDefaultStyle();
	style.style = 4;
	style.fgColor = FG_Yellow;
	style.bgColor = BG_Cyan;
	putTextPro("hello", 11, 10,&style);

	putTextEx("hello", 12, 10, FG_Red, BG_Yellow);
```

