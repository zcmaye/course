## 透明窗口(不规则窗口)

[透明窗体](https://blog.csdn.net/zzwdkxx/article/details/30034403)

### 窗口拖动

### 窗口拉伸

## 圆形头像 

[圆形头像](https://zhuanlan.zhihu.com/p/131260375)

```cpp
QLabel *label = new QLabel("hello",this);;
label->move(100,100);

//label->setMask(QRegion(0,0,250,250,QRegion::RegionType::Ellipse));
label->setMask(QBitmap("://images/mask.jpg"));
label->setPixmap(QPixmap("://images/zay.png").scaled(250,250,Qt::AspectRatioMode::KeepAspectRatio));
//在圆形头像和矩形头像之间切换
QPushButton*newBtn = new QPushButton("显示原矩形头像",this);
newBtn->move(100,0);
newBtn->setCheckable(true);
connect(newBtn,&QPushButton::clicked,this,[=](bool check)
{
    if(check)
    {
        label->clearMask();
        newBtn->setText("显示矩形头像");
    }
    else
    {
        label->setMask(QBitmap("://images/mask.jpg"));
        newBtn->setText("显示圆形头像");
    }
});
```



## windowModified(窗口文档是否修改)

就是窗口的标题上加个*号(在wps里就可以看到修改的文档会加个\*)

## 窗口翻转特效

[窗口翻转特效](https://blog.csdn.net/wanghualin033/article/details/78619222)



## 窗口任务栏隐藏

有时候有特殊需求，不希望在任务栏上出现应用程序的图标。该怎么办呢？

其实可以通过设置窗口标志来实现。

调用QWidget的setWindowFlags()函数。 设置为Qt::Tool、Qt::SubWindow、Qt::Popup可以达到目的。



但是这样做会有副作用：

设置Qt::Popup不能设置保持窗口在顶层和底层。

设置Qt::SubWindow的窗口没有标题栏，没有关闭按钮，也不能进行拉伸。这些功能需要自己实现。

设置Qt::Tool窗口可以拉伸也有关闭按钮，但是点击关闭按钮，程序并不退出。



## 代码编辑器库

[Qscitinlla 官网 ](https://qscintilla.com/#home)           

[CSDN](https://blog.csdn.net/weixin_38326893/article/details/80001548)

[PyQt5](https://blog.csdn.net/caojianhua2018/article/details/102454748)



## QScreen



# 拖放

> Drag and Drop

拖放提供了一种简单的可视化机制，用户可以使用它在应用程序之间和应用程序内部传输信息。拖放在功能上类似于剪贴板的剪切和粘贴机制。

## 拖放类

这些类处理拖放和必要的mime类型编码和解码。

| 类              | 描述                                       |
| --------------- | ------------------------------------------ |
| QDrag           | 支持基于mime的拖放数据传输                 |
| QDragEnterEvent | 当拖放操作进入小部件时发送到该小部件的事件 |
| QDragLeaveEvent | 当拖放操作离开小部件时发送给该小部件的事件 |
| QDragMoveEvent  | 在进行拖放操作时发送的事件                 |
| QDropEvent      | 当拖放操作完成时发送的事件                 |

## 拖动

要开始拖动，创建一个QDrag对象，并调用它的exec()函数。在大多数应用程序中，最好是在按下鼠标按钮并移动光标一定距离后才开始拖放操作。然而，从小部件中启用拖放的最简单的方法是重新实现小部件的mousePressEvent()并开始拖放操作:

```cpp
 void MainWindow::mousePressEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton
         && iconLabel->geometry().contains(event->pos())) {

         QDrag *drag = new QDrag(this);
         QMimeData *mimeData = new QMimeData;

         mimeData->setText(commentEdit->toPlainText());
         drag->setMimeData(mimeData);
         drag->setPixmap(iconPixmap);

         Qt::DropAction dropAction = drag->exec();
         ...
     }
 }
```

尽管用户可能需要一些时间来完成拖拽操作，但就应用程序而言，exec()函数是一个返回若干值之一的阻塞函数。这些表示操作是如何结束的，下面将详细说明。

注意，exec()函数不会阻塞主事件循环。

对于需要区分鼠标点击和拖动的小部件，重新实现小部件的mousePressEvent()函数来记录拖动的起始位置是很有用的:

```cpp
 void DragWidget::mousePressEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton)
         dragStartPosition = event->pos();
 }
```

稍后，在mouseMoveEvent()中，我们可以确定是否应该开始拖动，并构造一个拖动对象来处理操作：

```cpp
 void DragWidget::mouseMoveEvent(QMouseEvent *event)
 {
     if (!(event->buttons() & Qt::LeftButton))
         return;
     if ((event->pos() - dragStartPosition).manhattanLength()
          < QApplication::startDragDistance())
         return;

     QDrag *drag = new QDrag(this);
     QMimeData *mimeData = new QMimeData;

     mimeData->setData(mimeType, data);
     drag->setMimeData(mimeData);

     Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
     ...
 }
```

这种特殊的方法使用QPoint::manhattanLength()函数来粗略估计鼠标单击发生的位置和当前光标位置之间的距离。此函数效率较高。

## 释放

为了能够接收在小部件上丢弃的媒体，为小部件调用setAcceptDrops(true)，并重新实现dragEnterEvent()和dropEvent()事件处理函数。

例如，下面的代码在QWidget子类的构造函数中启用了释放事件，从而可以有效地实现释放事件处理程序:

```cpp
 Window::Window(QWidget *parent)
     : QWidget(parent)
 {
     ...
     setAcceptDrops(true);
 }
```

dragEnterEvent()函数通常用于通知Qt小部件接受的数据类型。如果你想在dragMoveEvent()和dropEvent()的重实现中接收QDragMoveEvent或QDropEvent，你必须重新实现这个函数。

下面的代码展示了如何重新实现dragEnterEvent()来告诉拖放系统我们只能处理纯文本:

```cpp
 void Window::dragEnterEvent(QDragEnterEvent *event)
 {
     if (event->mimeData()->hasFormat("text/plain"))
         event->acceptProposedAction();
 }
```

dropEvent()用于解包已释放的数据并以适合您的应用程序的方式处理它。

在以下代码中，事件中提供的文本被传递给QTextBrowser, QComboBox被用来描述数据的MIME类型列表填充:

```cpp
 void Window::dropEvent(QDropEvent *event)
 {
     textBrowser->setPlainText(event->mimeData()->text());
     mimeTypeCombo->clear();
     mimeTypeCombo->addItems(event->mimeData()->formats());

     event->acceptProposedAction();
 }
```

在本例中，我们接受提议的操作，而不检查它是什么。在真实的应用程序中，如果操作不相关，可能需要从dropEvent()函数返回，而不接受提议的操作或处理数据。例如，如果我们的应用程序中不支持到外部源的链接，我们可以选择忽略Qt::LinkAction操作。

### 重写建议的操作

我们也可以忽略建议的操作，并对数据执行一些其他操作。为此，我们将在调用accept()之前使用Qt::DropAction中的首选操作调用事件对象的setDropAction()。这确保使用替换的删除操作而不是建议的操作。

对于更复杂的应用程序，重新实现dragMoveEvent()和dragLeaveEvent()将使小部件的某些部分对拖放事件敏感，并使您对应用程序中的拖放有更多的控制。

### 子类化复杂的小部件

某些标准Qt小部件为拖放提供了自己的支持。在子类化这些小部件时，可能需要在dragEnterEvent()和dropEvent()之外重新实现dragMoveEvent()，以防止基类提供默认的拖放处理，并处理您感兴趣的任何特殊情况。

## 拖放操作

在最简单的情况下，拖放操作的目标接收被拖放数据的副本，源决定是否删除原始数据。这是通过CopyAction操作来描述的。目标还可以选择处理其他操作，特别是MoveAction和LinkAction操作。如果源调用QDrag::exec()，并返回MoveAction，则源负责删除任何原始数据(如果它选择这样做的话)。由源小部件创建的QMimeData和QDrag对象不应该被删除——它们会被Qt销毁。这通常通过保持对数据的引用来实现。

如果目标理解LinkAction操作，它应该存储自己对原始信息的引用;源不需要对数据执行任何进一步的处理。最常见的拖放操作是在同一个小部件内执行Move操作时;有关此功能的更多信息，请参阅Drop Actions部分。

拖动操作的另一个主要用途是在使用引用类型(如text/uri-list)时，其中拖动的数据实际上是对文件或对象的引用。

## 添加新的拖放类型

拖放不仅限于文本和图像。任何类型的信息都可以通过拖放操作进行传输。要在应用程序之间拖动信息，应用程序必须能够相互指示它们可以接受哪些数据格式以及它们可以产生哪些数据格式。这是通过使用MIME类型实现的。由源构造的QDrag对象包含一个MIME类型列表，它用来表示数据(从最合适的顺序到最不合适的顺序)，而拖放目标使用其中之一来访问数据。对于公共数据类型，便利函数透明地处理使用的MIME类型，但对于自定义数据类型，必须显式地声明它们。

要为QDrag便利函数没有覆盖的信息类型实现拖放操作，第一步也是最重要的一步是寻找合适的现有格式:(IANA)在信息科学研究所(ISI)提供了[MIME媒体类型的分层列表]([Media Types (iana.org)](https://www.iana.org/assignments/media-types/media-types.xhtml))。使用标准MIME类型可以最大限度地提高应用程序与其他软件的互操作性。

要支持额外的媒体类型，只需使用setData()函数设置QMimeData对象中的数据，提供完整的MIME类型和以适当格式包含数据的QByteArray。下面的代码从标签中获取一个像素图，并将其存储为QMimeData对象中的一个可移植网络图形(PNG)文件:

```cpp
     QByteArray output;
     QBuffer outputBuffer(&output);
     outputBuffer.open(QIODevice::WriteOnly);
     imageLabel->pixmap().toImage().save(&outputBuffer, "PNG");
     mimeData->setData("image/png", output);
```

当然，在这种情况下，我们可以简单地使用setImageData()来提供各种格式的图像数据:

```cpp
     mimeData->setImageData(QVariant(*imageLabel->pixmap()));
```

在这种情况下，QByteArray方法仍然很有用，因为它对QMimeData对象中存储的数据量提供了更好的控制。

注意，项目视图中使用的自定义数据类型必须声明为元对象，并且必须实现它们的流操作符。

## 释放操作

在剪贴板模型中，用户可以剪切或复制源信息，然后再粘贴它。类似地，在拖放模型中，用户可以拖动信息的副本，也可以将信息本身拖到一个新位置(移动它)。拖放模型给程序员带来了额外的复杂性:在操作完成之前，程序不知道用户是想剪切还是复制信息。当在应用程序之间拖动信息时，这通常没有影响，但在应用程序中，检查使用了哪个拖放操作是很重要的。

我们可以为小部件重新实现mouseMoveEvent()，并使用可能的拖放操作组合启动拖放操作。例如，我们可能想要确保拖动总是移动小部件中的对象:

```cpp
 void DragWidget::mouseMoveEvent(QMouseEvent *event)
 {
     if (!(event->buttons() & Qt::LeftButton))
         return;
     if ((event->pos() - dragStartPosition).manhattanLength()
          < QApplication::startDragDistance())
         return;

     QDrag *drag = new QDrag(this);
     QMimeData *mimeData = new QMimeData;

     mimeData->setData(mimeType, data);
     drag->setMimeData(mimeData);

     Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
     ...
 }
```

如果信息被放到另一个应用程序中，exec()函数返回的操作可能默认为CopyAction，但如果信息被放到同一个应用程序中的另一个小部件中，则可能获得不同的释放操作。

建议的释放操作可以在小部件的dragMoveEvent()函数中进行筛选。但是，可以在dragEnterEvent()中接受所有建议的操作，并让用户稍后决定接受哪个操作

```cpp
 void DragWidget::dragEnterEvent(QDragEnterEvent *event)
 {
     event->acceptProposedAction();
 }
```

当在小部件中出现拖放时，将调用dropEvent()处理程序函数，我们可以依次处理每个可能的操作。首先，我们处理同一个小部件内的拖放操作:

```cpp
 void DragWidget::dropEvent(QDropEvent *event)
 {
     if (event->source() == this && event->possibleActions() & Qt::MoveAction)
         return;
```

在这种情况下，我们拒绝处理move操作。我们接受的每一种掉落动作都会被检查并相应处理:

```cpp
     if (event->proposedAction() == Qt::MoveAction) {
         event->acceptProposedAction();
         // Process the data from the event.
     } else if (event->proposedAction() == Qt::CopyAction) {
         event->acceptProposedAction();
         // Process the data from the event.
     } else {
         // Ignore the drop.
         return;
     }
     ...
 }
```

注意，我们在上面的代码中检查了单个的释放操作。正如上面关于覆盖建议的操作一节中所提到的，有时需要覆盖建议的释放操作，并从可能的释放操作的选择中选择不同的操作。为此，您需要检查每个操作是否存在于事件的possibleActions()提供的值中，使用setDropAction()设置释放操作，并调用accept()。

## 释放矩形

小部件的dragMoveEvent()可用于将拖放限制在小部件的某些部分，方法是只在光标位于这些区域内时接受提议的拖放操作。例如，当光标位于子控件(dropFrame)上时，以下代码接受任何建议的释放操作:

```cpp
 void Window::dragMoveEvent(QDragMoveEvent *event)
 {
     if (event->mimeData()->hasFormat("text/plain")
         && event->answerRect().intersects(dropFrame->geometry()))

         event->acceptProposedAction();
 }
```

如果需要在拖放操作期间提供可视化反馈、滚动窗口或任何合适的操作，也可以使用dragMoveEvent()。

## 剪切板

应用程序还可以通过在剪贴板上放置数据来相互通信。要访问它，您需要从QApplication对象获得一个QClipboard对象。

QMimeData类用于表示传输到剪贴板和从剪贴板传输的数据。要将数据放在剪贴板上，可以使用setText()、setImage()和setPixmap()方便通用数据类型的函数。这些函数类似于在QMimeData类中找到的函数，除了它们还接受一个额外的参数来控制数据的存储位置：如果指定了Clipboard，则将数据放在剪贴板上;如果指定了Selection，则将数据放在鼠标选择中(仅在X11上)。默认情况下，数据放在剪贴板上。

例如，我们可以用以下代码将QLineEdit的内容复制到剪贴板:

```cpp
     QGuiApplication::clipboard()->setText(lineEdit->text(), QClipboard::Clipboard);
```

具有不同MIME类型的数据也可以放在剪贴板上。构造一个QMimeData对象，并使用setData()函数按照上一节中描述的方式设置数据;然后，可以使用setMimeData()函数将该对象放在剪贴板上。

QClipboard类可以通过其datachhanged()信号将其包含的数据的更改通知应用程序。例如，我们可以通过将这个信号连接到小部件中的插槽来监视剪贴板:

```cpp
     connect(clipboard, &QClipboard::dataChanged,this, &ClipWindow::updateClipboard);
```

连接到该信号的插槽可以使用可用于表示的MIME类型之一读取剪贴板上的数据:

```cpp
 void ClipWindow::updateClipboard()
 {
     mimeTypeCombo->clear();

     QStringList formats = clipboard->mimeData()->formats();
     if (formats.isEmpty())
         return;

     for (const auto &format : formats) {
         QByteArray data = clipboard->mimeData()->data(format);
         // ...
     }
 }
```

可以在X11上使用selectionChanged()信号来监视鼠标选择。

## 与其他应用程序互操作

在X11上，使用公共XDND协议，而在Windows上Qt使用OLE标准，Qt for macOS使用Cocoa Drag Manager。在X11上，XDND使用MIME，因此不需要翻译。Qt API在任何平台上都是一样的。在Windows上，支持MIME的应用程序可以通过使用MIME类型的剪贴板格式名进行通信。已经有一些Windows应用程序为它们的剪贴板格式使用MIME命名约定。

可以通过在Windows上重新实现QWinMime或在macOS上重新实现QMacPasteboardMime来注册用于转换专有剪贴板格式的自定义类。