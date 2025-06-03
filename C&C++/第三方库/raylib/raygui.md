# raygui

Raygui是一个简单且易于使用的即时模式gui库。

`raygui` 被设计为raylib的辅助模块，用于使用raylib图形风格（简单的颜色，普通的矩形形状，宽边框…）创建简单的GUI界面。

> *注意：raygui是一个单文件头文件库（尽管其内部依赖于raylib），因此，函数定义和实现位于同一个文件* `raygui.h` *，当在模块中包含* `raygui.h` *时，* `RAYGUI_IMPLEMENTATION` *必须预先定义以包含* `raygui.h` *的实现部分，但只能在一个编译单元中，其他模块也可以包含* `raygui.h` *但* `RAYGUI_IMPLEMENTATION` *不得再次定义。*