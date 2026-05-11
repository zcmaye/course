# QHotKey

## 介绍

 QHotKey是一个类，可用于创建热键/全局快捷方式，也就是可在任何地方使用的快捷方式，而与应用程序状态无关。这意味着您的应用程序可以处于活动状态，非活动状态，最小化或根本不可见，并且仍会收到快捷方式。

## 特性

- 在Windows，Mac和X11上均可使用。
- 易于使用，可QKeySequence用于快捷输入。
- 支持几乎所有常用键(取决于操作系统和键盘布局)。
- 允许直接输入键/修饰键组合。
- 支持同一快捷方式的多个QHotkey实例（具有优化）。
- 线程安全-可以在所有线程上使用（请参阅线程安全部分）。
- 如果需要，允许使用本机键码和修饰符。

**注意：目前不支持**Wayland**，因为无法在Wayland中注册全局快捷方式。**

## 用法

通常的用法是为特定的热键创建QHotkey实例，注册它们，然后只要按下热键就可以简单地连接到发出的信号。

### 案例

  这个例子是全局监听`ctrl + alt + Q`组合键，触发后置顶退出程序操作。

```cpp
#include <QHotkey>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
 QApplication a(argc, argv);

 auto hotkey = new QHotkey(QKeySequence("ctrl+alt+Q"), true, &a);//The hotkey will be automatically registered
 qDebug() << "Is Registered: " << hotkey->isRegistered();

 QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
  qDebug() << "Hotkey Activated - the application will quit now";
  qApp->quit();
 });

 return a.exec();
}
```

