# Qt内存回收机制

## 一、简介

C++中 new 和 delete 必须配对使用：delete少了，则内存泄露，多了麻烦更大。Qt中使用了new却很少delete，因为Qt实现了其独特的内存管理机制。

Qt内存管理机制：QObject 在对象树中组织自己。 当您以另一个对象作为父对象创建 QObject 时，该对象将自动将自身添加到父对象的 children() 列表中。 父级获得对象的所有权； 即，它将自动删除其析构函数中的子级。 您可以使用 findChild() 或 findChildren() 来查找子对象。

## 二、关联图

在Qt中，最基础和核心的类是：QObject，QObject内部有一个名为children的QObjectList列表，会保存所有子对象，还有一个指针parent，用来指向父对象，当自己析构时，会先把自己从parent列表中删除并且析构所有的children。

![img](assets/35081b7e738c4725bb7075189052f4d6.png)

## 三、详解

### 1、内存管理

（1）QObject及其派生类的对象，如果其parent非nullptr，那么其parent析构时会析构该对象。

（2）父子关系：父对象、子对象、父子关系。这是Qt中所特有的，与类的继承关系无关，传递参数是与parent有关（基类、派生类，或父类、子类，这是对于派生体系来说的，与parent无关）。

### 2、内存问题例子

```cpp
#include <QPushButton>

Widget::Widget(QWidget *parent)
{
    QLabel *label = new QLabel("Hello Qt!");
    label->show();
}
```

**分析：**`label 既没有指定parent，也没有对其调用delete，所以会造成内存泄漏。`

**改进方式：**

+ 分配对象到栈上而不是堆上

```cpp
#include <QLabel>

Widget::Widget(QWidget *parent)
{
    QLabel label("Hello Qt!");
    label.show();
}
```

**分析：**构造函数执行完毕，对象生命周期结束会被自动析构，窗口上的控件消失不见

+ 使用指定父对象的方式自动管理内存

```cpp
class MyPushButton:public QPushButton
{
public:
    using QPushButton::QPushButton;

    ~MyPushButton()
    {
        qDebug()<<"MyPushButton 析构~";
    }
};

Widget::Widget(QWidget *parent)
{
    QPushButton* btn2 = new MyPushButton("第二个按钮",this);
    btn2->move(100,0);
}
//运行之后关掉窗口，应用程序输出显示：MyPushButton 析构~
```





# 玩个按钮(设置父对象)

QPushButton是Qt中常用的一个类

```cpp
QPushButton* btn = new QPushButton;
//show和setparent同时调用会让按钮显示在窗口中间
btn->show();			//显示控件
btn->setParent(this);	//将小部件的父组件设置为parent，小部件被移动到其父部件的(0,0)位置 
btn->setText("第一个按钮");

//通过构造函数指定父控件会让窗口以子控件的大小进行显示
QPushButton* btn2 = new QPushButton("第二个按钮",this);
//移动按钮到指定位置
btn2->move(100,0);
//重新调整窗口大小
this->resize(640,480);
//设置窗口标题
this->setWindowTitle("第一个窗口");
```





