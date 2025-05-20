# PySide6

## 简介

PySide6 是 Python 的一个 GUI 框架，它是 Qt 框架的 Python 绑定。Qt 是一个强大的跨平台应用程序开发框架，可用于创建桌面、移动和嵌入式应用程序。PySide6 允许开发者使用 Python 语言来利用 Qt 的功能。

## 特点

- **跨平台支持**：可以在 Windows、macOS、Linux 等多个操作系统上运行。
- **丰富的 GUI 组件**：提供了各种界面元素，如按钮、文本框、下拉菜单等。
- **信号与槽机制**：用于对象间的通信，实现事件驱动编程。
- **强大的布局管理**：帮助开发者创建灵活且响应式的界面。

## 下载

使用pip安装PySide6：

```shell
pip install pyside6
```

包大小大概为500多M，需要保证磁盘空间足够！

# 使用

## 1. 基本框架

导入模块:

```python
from PySide6.QtWidgets import QApplication,QWidget
```

创建应用程序对象和窗口对象：

```python
if __name__ == '__main__':
	app = QApplication()
    w = QWidget()
    w.show()
    app.exec()
```

`QApplication`是应用程序类，在Qt程序中有只能有一个`QApplication`对象，如果想要在别的模块中访问app单例，可以使用`QApplication.instance()`方法获取。

`QWidget`是所有用户界面对象的基类，用于创建窗口、对话框、按钮等可视化组件。