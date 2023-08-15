# JSON

JSON(JavaScript Object Notation, JS 对象简谱) 是一种轻量级的数据交换格式。它基于 ECMAScript (欧洲计算机协会制定的js规范)的一个子集，采用完全独立于编程语言的文本格式来存储和表示数据。简洁和清晰的层次结构使得 JSON 成为理想的数据交换语言。 易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效率。

## 格式

JSON是一个标记符的序列。这套标记符包含六个**构造字符**、**字符串**、**数字**和三个**字面名**。

+ 1，六个构造字符
  + 开始和结束数组：[  ]
  + 开始和结束对象：{  }
  + 名称分隔：:	 (冒号)
  + 值分隔：,		(逗号)

+ 2，字符串用双引号包含
+ 3，数字直接表示，不用引号包含
+ 4，三个字面量
  + true
  + flase
  + null

JSON是一个序列化的**对象**或**数组**。

+ **对象**由花括号括起来的逗号分割的成员构成，成员是字符串键和值(**值**可以是**对象**、**数组**、**数字**、**字符串**或者三个**字面值**(false、null、true)中的一个)组成

  ```json
  {"name":"maye","age":18,"address":{"country":"china","city":"changsha"}}
  ```

+ **数组**是由方括号括起来的一组值构成

  ```json
  {"city":["长沙","南京","北京"]}
  ```

## Json解析

在Qt库中，为JSON的相关操作提供了完整的类支持，包括QJsonValue，QJsonObject，QJsonArray，QJsonDocument和QJsonParseError。

+ QJsonValue类表示json格式中的一个值；

+ QJsonObject表示一个json对象；

+ QJsonArray顾名思义表示一个json数组；

+ QJsonDocument主要用来读写json文档；

+ 而QJsonParseError是用来表示json解析过程中出现的错误的方便类。

### QJsonDocument

QJsonDocument是一个包装完整JSON文档的类，可以从UTF-8编码的基于文本的表示中读取该文档，并将其写入其中。 

JSON文档可以使用QJsonDocument::fromJson()将其基于文本的表示形式转换为QJsonDocument。toJson()将其转换回文本。解析器非常快速和有效，并将JSON转换为Qt使用的二进制表示。

 ```cpp
//创建Json文档对象
QJsonDocument jdoc = QJsonDocument::fromJson(R"({"name":"maye","age":18,"citys":["长沙","常德"],"father":{"name":"老张","age":null}})");
//获取Json文本,可选格式[Indented(有格式有排版) | Compact(压缩的，去掉了空白字符)]
qInfo() << jdoc.toJson();      
 ```

### QJsonParseError

QJsonParseError类用于报告JSON解析过程中的错误。

使用唯一的成员函数`errorString()`获取错误字符串，使用成员变量`error`获取错误码，使用成员变量`offset`获取错误位置。

```cpp
//创建Json错误对象
QJsonParseError jerr;
//创建Json文档对象
QJsonDocument jdoc = QJsonDocument::fromJson(R"({"name":null})", &jerr);
//判断是否解析成功
if (jerr.error != QJsonParseError::NoError)
{
    qWarning("json parse failed:%s", qUtf8Printable(jerr.errorString()));
    return;
}
```



### QJsonObject

JSON对象是键值对的列表，其中键是唯一的字符串，值由QJsonValue表示。

QJsonObject可以与QVariantMap进行转换。您可以使用size()、insert()和remove()查询(key, value)对的数量，并使用标准的c++迭代器模式遍历其内容。

```cpp
for(QJsonObject::const_iterator it = obj.constBegin();it != obj.constEnd() ;it++)
{
     qDebug()<<it.key()<< it.value();
}
for(QJsonValue val : obj)
{
     qDebug()<<val;
}
```

QJsonObject是一个隐式共享类，只要它没有被修改，它就与创建它的文档共享数据。  

### QJsonArray

JSON数组是一个值列表。可以通过从数组中插入和删除QJsonValue来操作该列表。

QJsonArray可以与QVariantList进行转换。您可以使用size()、insert()和removeAt()条目从它中查询条目的数量，并使用标准的C++迭代器模式迭代其内容。

```cpp
for(QJsonValue val : jarray)
{
}

for (int i = 0; i < jarray.size(); i++)
{
    qInfo() << jarray.at(i).toString();
}
```

QJsonArray是一个隐式共享类，只要它没有被修改，它就与创建它的文档共享数据。  

### QJsonValue

JSON是一种存储结构化数据的格式。它有6种基本数据类型:

+ `bool` QJsonValue::Bool
+ `double` QJsonValue::Double
+ `string` QJsonValue::String
+ `array` QJsonValue::Array
+ `object` QJsonValue::Object
+ `null` QJsonValue::Null

值可以表示上述任何一种数据类型。此外，QJsonValue有一个特殊标志来表示未定义的值。这可以用isUndefined()查询。  

值的类型可以用type()或访问器查询，如isBool()， isString()等。同样，可以使用toool()、toString()等方法将值转换为存储在其中的类型。

值在内部是严格类型的，与QVariant相反，它不会尝试进行任何隐式类型转换。这意味着转换为未存储在值中的类型将返回默认构造的返回值。

### 示例

```cpp
void parseJson()
{
        //创建Json错误对象
        QJsonParseError jerr;
        //创建Json文档对象
        QJsonDocument jdoc = QJsonDocument::fromJson(R"({"name":"maye","age":18,"citys":["长沙","常德"],"father":{"name":"老张","age":null}})",&jerr);
        qInfo() << jdoc.toJson(QJsonDocument::JsonFormat::Compact);

        //判断是否解析成功
        if (jerr.error != QJsonParseError::NoError)
        {
            qWarning("json parse failed:%s", qUtf8Printable(jerr.errorString()));
            return;
        }
        //获取Json根对象
        QJsonObject root = jdoc.object();
        /*{
            //获取所有key（不会输出子对象的key）
            qInfo() << root.keys();
            //根据key获取value
            qInfo() << root.value("age");
            //根据key查找value
            qInfo() << root.find("name").value();
            //判断是否包含key
            qInfo() << root.contains("name");
            //遍历所有value
            for (auto v : root)
            {
                qInfo() << v;
            }

            //JsonValue
            qInfo() << root.value("age").toInt();
        }
        */

        //获取所有对象
        {
            if (root.contains("name"))
            {
                qInfo()<< root.value("name").toString();
            }
            if (root.contains("age"))
            {
                qInfo() << root.value("age").toInt();
            }
            if (root.contains("citys"))
            {
                //解析数组
                auto jvalue =  root.value("citys");
                if (jvalue.isArray())
                {
                    auto jarray = jvalue.toArray();
                    for (int i = 0; i < jarray.size(); i++)
                    {
                        qInfo() << jarray.at(i).toString();
                    }
                }
                //qInfo() << root.value("age").toInt();
            }
            if (root.contains("father"))
            {
                //解析对象
                QJsonValue jvalue = root.value("father");
                if (jvalue.isObject())
                {
                    QJsonObject jobj = jvalue.toObject();
                    if (jobj.contains("name"))
                    {
                        qInfo() << jobj.value("name").toString();
                    }

                }                  
            }
        }
}
```



## Json生成

生成也是用上面的类，需要注意的是：生成json时会自动把key排序

```cpp
void Widget::writeJson(const QString &filename)
{
    QJsonDocument json;

    //构建一个主对象
    QJsonObject obj;
    obj.insert("year","2019");
    obj.insert("month","10");
    obj.insert("day","29");
    obj.insert("weather","晴");
    //构建一个数组
    QJsonArray array ={"北京","天津"};
    array.append("上海");
    obj.insert("city",array);
    //构建一个子对象
    QJsonObject subObj;
    subObj.insert("one",1);
    subObj.insert("two",2);
    obj.insert("list",subObj);

    //给jsonDocument设置主对象
    json.setObject(obj);
    //保存
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
         qWarning("文件打开失败");
         return;
    }
    QByteArray jsonText = json.toJson();
    file.write(jsonText);
}
```

结果：

```cpp
{
    "city": [
        "北京",
        "天津",
        "上海"
    ],
    "day": "29",
    "list": {
        "one": 1,
        "two": 2
    },
    "month": "10",
    "weather": "晴",
    "year": "2019"
}
```

# XML

## 简介

可扩展标记语言，[标准通用标记语言](通用标言是1986年国际标准化组织出版发布的一个信息管理方面的国际标准)(Extensible Markup Language)的子集，简称XML，是一种定义电子文档结构和描述其内容的国际标准语言，被设计用来传输和存储数据。

可扩展标记语言与Access]，Oracle]和SQL Server等数据库不同，数据库提供了更强有力的数据存储和分析能力，例如：数据索引、排序、查找、相关一致性等，可扩展标记语言仅仅是存储数据。事实上它与其他数据表现形式最大的不同是：可扩展标记语言极其简单，这是一个看上去有点琐细的优点，但正是这点使它与众不同。

XML的简单易于在任何应用程序中读/写数据，这使XML很快成为数据交换的唯一公共语言，虽然不同的应用软件也支持其他的数据交换格式，但不久之后它们都将支持XML，那就意味着程序可以更容易的与[Windows]()、[Mac OS]()、[Linux]()以及其他平台下产生的信息结合，然后可以很容易加载XML数据到程序中并分析它，并以XML格式输出结果。

## 与HTML的区别

(1)可扩展性方面：HTML不允许用户自行定义他们自己的标识或属性，而在XML中，用户能够根据需要自行定义新的标识及属性名，以便更好地从语义上修饰数据。 

(2)结构性方面：HTML不支持深层的结构描述，XML的文件结构嵌套可以复杂到任意程度，能表示面向对象的等级层次。 

(3)可校验性方面：HTML没有提供规范文件以支持应用软件对HTML文件进行结构校验，而XML文件可以包括一个语法描述，使应用程序可以对此文件进行结构校验。

总之，XML使用一个简单而又灵活的标准格式，为基于Web的应用提供了一个描述数据和交换数据的有效手段。但是，XML并非是用来取代HTML的。HTML着重如何描述将文件显示在浏览器中，而XML，它着重描述如何将数据以结构化方式表示。

## 格式

**为了避免错误，需要规定 XML 编码，或者将 XML 文档存为 Unicode。**

[W3school XML教程](https://www.w3school.com.cn/xml/index.asp)

XML文件格式是纯文本格式，在许多方面类似于HTML，XML由XML元素组成，每个XML元素包括一个开始标记<>，一个结束标记</>以及两个标记之间的内容，例如，可以将XML元素标记为价格、订单编号或名称。标记是对文档存储格式和逻辑结构的描述。在形式上，标记中可能包括注释、引用、字符数据段、起始标记、结束标记、空元素、文档类型声明( DTD)和序言。

**具体规则如下：**

+ 1、必须有声明语句。 

XML声明是XML文档的第一句，其格式如下： 

```css
<?xml version="1.0" encoding="utf-8"?>
```

+ 2、注意大小写

在XML文档中，大小写是有区别的。“A”和“a”是不同的标记。注意在写元素时，前后标记的大小写要保持一致。最好养成一种习惯，或者全部大写，或者全部小写，或者大写第一个字母，这样可以减少因为大小写不匹配而产生的文档错误。  

+ 3、XML文档有且只有一个根元素

良好格式的XML文档必须有一个根元素，就是紧接着声明后面建立的第一个元素，其他元素都是这个根元素的子元素，根元素完全包括文档中其他所有的元素。根元素的起始标记要放在所有其他元素的起始标记之前；根元素的结束标记要放在所有其他元素的结束标记之后。 

+ 4、属性值使用引号

在HTML代码里面，属性值可以加引号，也可以不加。但是XML规定，所有属性值必须加引号（可以是单引号，也可以是双引号，建议使用双引号），否则将被视为错误。 

+ 5、所有的标记必须有相应的结束标记

在HTML中，标记可以不成对出现，而在XML中，所有标记必须成对出现，有一个开始标记，就必须有一个结束标记，否则将被视为错误。 

+ 6、所有的空标记也必须被关闭

空标记是指标记对之间没有内容的标记， 由于空标记不含任何内容，所以空标记不需要开始标签和结束标签，空标记“<”标识开始，以“/>”标识结束，如：比如<door color="red"/> 

[xml&json](https://www.cnblogs.com/SanMaoSpace/p/3139186.html)

## XML解析

Qt 提供了三种读取 XML 文档的方法：

+ QXmlStreamReader：一种快速的基于流的方式访问良格式 XML 文档，特别适合于实现一次解析器（所谓“一次解析器”，可以理解成我们只需读取文档一次，然后像一个遍历器从头到尾一次性处理 XML 文档，期间不会有反复的情况，也就是不会读完第一个标签，然后读第二个，读完第二个又返回去读第一个，这是不允许的）；
+ DOM（Document Object Model）：将整个 XML 文档读入内存，构建成一个树结构，允许程序在树结构上向前向后移动导航，这是与另外两种方式最大的区别，也就是允许实现多次解析器（对应于前面所说的一次解析器）。DOM 方式带来的问题是需要一次性将整个 XML 文档读入内存，因此会占用很大内存；

有如下XML文档，描述了登录数据库所需要的信息，通过解析可以获取信息以登录数据库。

```xml
<?xml version="1.0" encoding="utf-8"?>
<root>
    <HostName>localhost</HostName>
    <Port>3306</Port>
    <UserName>root</UserName>
    <PassWord>123456789</PassWord>
    <DatabaseName>Maye</DatabaseName>
</root>
```

上面的xml不带属性，下面的xml是Qt ui文件部分代码

```xml
<?xml version="1.0" encoding="utf-8"?>
<ui>
    <widget class="QWidget" name="MainWindow">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>989</width>
                <height>594</height>
            </rect>
        </property>
    </widget>
</ui>
```



### QXmlStreamReader

QXmlStreamReader提供了一个简单的流API来解析格式良好的XML。QXmlStreamReader从QIODevice(参见setDevice())或原始QByteArray(参见addData())读取数据。

Qt提供了QXmlStreamWriter用于编写XML。

流读取器的基本概念是将XML文档报告为令牌流。使用QXmlStreamReader，应用程序代码本身驱动循环，并根据需要一个接一个地从阅读器中提取令牌。这是通过调用readNext()来完成的，读取器从输入流中读取，直到完成下一个标记，然后返回tokenType()。然后可以使用一组方便的函数(包括isStartElement()和text())来检查令牌，以获得有关已读取内容的信息。这种拉式方法的最大优点是可以使用它构建递归下降解析器，这意味着可以轻松地将XML解析代码分割为不同的方法或类。这使得在解析XML时很容易跟踪应用程序自身的状态。

典型的QXmlStreamReader循环如下所示:

```cpp
QXmlStreamReader xml;
...
while (!xml.atEnd()) 
{
	xml.readNext ();
	... //处理
｝
if (xml.hasError()) 
{
	... //执行错误处理
｝
```

如果在解析时发生错误，atEnd()和hasError()返回true, error()返回发生的错误。函数errorString()、lineNumber()、columnNumber()和characterOffset()用于构造适当的错误或警告消息。为了简化应用程序代码，QXmlStreamReader包含一个raiseError()机制，该机制允许您引发自定义错误，从而触发上述相同的错误处理。



```cpp
void Widget::parseXml(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qWarning("%s 文件打开失败",filename.toUtf8().data());
        return;
    }

    //定义解析器对象
    QXmlStreamReader xmlReader(&file);

    //解析xml，直到结束或发送错误
    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType type = xmlReader.readNext();
        //是申明：<?xml version="1.0" encoding="utf-8"?>
        if(type == QXmlStreamReader::TokenType::StartDocument)
        {
            qDebug() <<xmlReader.documentVersion()<<xmlReader.documentEncoding();
        }
        else if (type == QXmlStreamReader::TokenType::StartElement)
        {
            //读取元素名和元素文本
            if(xmlReader.name() == "HostName")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "Port")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "UserName")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "PassWord")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else if(xmlReader.name() == "DatabaseName")
            {
                qDebug()<<xmlReader.name()<<xmlReader.readElementText();
            }
            else
            {
                //读取，直到当前元素的结尾，跳过任何子节点。此函数对于跳过未知元素非常有用。
                xmlReader.skipCurrentElement();
            }
        }
    }
}
```

### QDomDocument

#### 简介

QDomDocument类表示整个XML文档。从概念上讲，它是文档树的根，并提供对文档数据的主要访问。

由于元素、文本节点、注释、处理指令等不能存在于文档的上下文之外，因此文档类还包含创建这些对象所需的工厂函数。创建的节点对象有一个ownerDocument()函数，该函数将节点对象与创建节点的上下文中的文档关联起来。最常使用的DOM类是QDomNode、QDomDocument、QDomElement和QDomText。

解析后的XML在内部由对象树表示，可以使用各种QDom类访问这些对象树。所有QDom类只引用内部树中的对象。一旦最后一个引用它们的QDom对象或QDomDocument本身被删除，DOM树中的内部对象就会被删除。

> 注意:如果XML文档很大，DOM树最终可能会保留大量内存。对于这样的文档，QXmlStreamReader或QXmlQuery类可能是更好的解决方案。



>  DOM 是由 W3C 提出的一种处理 XML 文档的标准接口。Qt 实现了 DOM Level 2 级别的不验证读写 XML 文档的方法。DOM 一次性读入整个 XML 文档，在内存中构造为一棵树（被称为 DOM 树）。我们能够在这棵树上进行导航，比如移动到下一节点或者返回上一节点，也可以对这棵树进行修改，或者是直接将这颗树保存为硬盘上的一个 XML 文件。

#### 使用

首先，需要加载`Xml`模块。

然后，包含头文件`#include<QDomDocument>`。



```cpp
    void parseXml()
    {
        QFile file("./MainWindow.ui");
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << file.fileName() << "open failed:" << file.errorString();
        }

        //错误信息
        QString errMsg;
        int errLine;
        int errCol;

        QDomDocument dom;
        //给dom设置内容
        bool ok = dom.setContent(&file, false, &errMsg, &errLine, &errCol);
        if (!ok)
        {
            qWarning("xml parse failed:%s",qUtf8Printable(errMsg));
            return;
        }
        //获取版本信息和编码
        qInfo() << dom.firstChild().nodeName() << dom.firstChild().nodeValue();

        //返回文档中名称为tagname的所有元素
        QDomNodeList nList = dom.elementsByTagName("string");
        for (int i = 0; i < nList.size(); i++)
        {
            qInfo() << nList.at(i).toElement().text();
        }

        //获取dom的根标签<ui>
        QDomElement root = dom.documentElement();
        //获取标签名和标签对应的文本
        //qInfo() << root.tagName()<<root.text();
        if (root.tagName() != "ui")
        {
            qWarning("根元素不是ui，xml文档有误~");
            return;
        }
        //获取根元素的第一个子元素
        QDomElement node = root.firstChild().toElement();
        //遍历node的直接子元素
        while (!node.isNull())
        {
            qInfo() << node.tagName();
            printNode(node);
            //if (node.tagName() == "widget")
            //{
            //    QDomElement subNode = node.firstChild().toElement();
            //    while (!subNode.isNull())
            //    {
            //        qInfo() << "---" << subNode.tagName();
            //        subNode = subNode.nextSibling().toElement();
            //    }
            //}
            node = node.nextSibling().toElement();
        }

    }
    void printNode(QDomElement node)
    {
        QDomElement subNode = node.firstChild().toElement();
        while (!subNode.isNull())
        {
            qInfo() << "---" << subNode.tagName();
            printNode(subNode);
            subNode = subNode.nextSibling().toElement();
        }
    }
```

### 两种解析方式比较

**1、DOM解析XML文档的特点**

基于DOM的解析器的核心是在内存中建立和XML文档相对应的树状结构。XML文件的标记、标记中的文本数据和实体等都是内存中的树状结构的某个节点相对应。

优点：可以方便地操作内存中的树状节点

缺点：如果XML文件较大，或者只需要解析XML文档的一部分数据，就会占用大量的内存空间

**2、流方式解析XML文档的特点**
QXmlStreamReader使用了递增式的解析器，适合于在整个XML文档中查找给定的标签、读入无法放入内存的大文件以及处理XML的自定义数据。

优点：快速、方便，分块读取XML文件，可读取大文件

缺点：递增式解析器，只能顺序遍历XML文件的元素，不能随机访问

QXmlStreamWriter类提供了简单流接口的XML写入器，写入XML文档只需要调用相应的记号写入函数来写入相关数据。

优点：快速、方便

缺点：只能按顺序写入元素，不能删除、修改



## XML生成

至于生成 XML 文档，Qt 同样提供了三种方式：

+ QXmlStreamWriter，与QXmlStreamReader相对应；
+ DOM 方式，首先在内存中生成 DOM 树，然后将 DOM 树写入文件。不过，除非我们程序的数据结构中本来就维护着一个 DOM 树，否则，临时生成树再写入肯定比较麻烦；
+ 纯手工生成 XML 文档，显然，这是最复杂的一种方式。
  

### QXmlStreamWriter

QXmlStreamWriter类提供了一个带有简单流API的XML编写器。  

QXmlStreamWriter是用于编写XML的QXmlStreamReader的对等物。 像它的相关类一样，它操作由setDevice()指定的QIODevice。 这个API简单明了:对于您想要编写的每个XML标签或事件，编写器提供一个专门的函数。  

```cpp
void Widget::writeXml(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning("文件打开失败");
        return ;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);         //设置自动格式化(有缩进有换行，否则都是在同一行)

    writer.writeStartDocument("1.0");
    writer.writeStartElement("ui");
    writer.writeAttribute("effect","描述界面");

    writer.writeStartElement("widget");
    writer.writeAttribute("class","QWidget");
    writer.writeAttribute("name","MainWindow");
    writer.writeComment("helo");				//写注释
    writer.writeStartElement("property");
    writer.writeAttribute("name","property");

    writer.writeStartElement("rect");
    writer.writeTextElement("x","0");
    writer.writeTextElement("y","0");
    writer.writeTextElement("width","640");
    writer.writeTextElement("height","480");
    writer.writeEndElement();   // end widget
    writer.writeEndElement();   // end property
    writer.writeEndElement();   // end rect

    writer.writeEndElement();   //end ui
    writer.writeEndDocument();
    file.close();
}
```

### DOM（Document Object Model）

```cpp
//创建属性
QDomAttr createAttribute(const QString &name)
//为可以插入到文档中的字符串值创建一个新的CDATA部分，例如使用QDomNode::appendChild()   
QDomCDATASection createCDATASection(const QString &value)
//为可以插入到文档中的字符串值创建一个新的注释，例如使用QDomNode::appendChild()      
QDomComment createComment(const QString &value)
//创建一个新的文档片段，可以用来保存文档的部分，例如，当对文档树进行复杂操作时。      
QDomDocumentFragment createDocumentFragment()
//创建一个名为tagName的新元素，可以插入到DOM树中，例如使用QDomNode::appendChild()。      
QDomElement createElement(const QString &tagName)
//创建一个名为name的新实体引用，可以插入到文档中，例如使用QDomNode::appendChild()。  
QDomEntityReference createEntityReference(const QString &name)
//创建一个可以插入到文档中的新的处理指令，例如使用QDomNode::appendChild()。 该函数将处理指令的目标设置为目标，将数据设置为数据。      
QDomProcessingInstruction createProcessingInstruction(const QString &target, const QString &data)
//为可以插入到文档树中的字符串值创建一个文本节点，例如使用QDomNode::appendChild()。      
QDomText createTextNode(const QString &value)
```



# JSON与XML的区别比较

## 1.定义介绍

**(1)，XML定义**

扩展标记语言 (Extensible Markup Language, XML) ，用于标记电子文件使其具有结构性的标记语言，可以用来标记数据、定义数据类型，是一种允许用户对自己的标记语言进行定义的源语言。 XML使用DTD(document type definition)文档类型定义来组织数据;格式统一，跨平台和语言，早已成为业界公认的标准。XML是标准通用标记语言 (SGML) 的子集，非常适合 Web 传输。XML 提供统一的方法来描述和交换独立于应用程序或供应商的结构化数据。

**(2)，JSON定义**

JSON(JavaScript Object Notation)一种轻量级的数据交换格式，具有良好的可读和便于快速编写的特性。可在不同平台之间进行数据交换。JSON采用兼容性很高的、完全独立于语言文本格式，同时也具备类似于C语言的习惯(包括C, C++, C#, Java, JavaScript, Perl, Python等)体系的行为。这些特性使JSON成为理想的数据交换语言。

## 2.XML和JSON优缺点

**(1)，XML的优缺点**

**<1>.XML的优点**
　　A.格式统一，符合标准；
　　B.容易与其他系统进行远程交互，数据共享比较方便。

**<2>.XML的缺点**
　　A.XML文件庞大，文件格式复杂，传输占带宽；
　　B.服务器端和客户端都需要花费大量代码来解析XML，导致服务器端和客户端代码变得异常复杂且不易维护；
　　C.客户端不同浏览器之间解析XML的方式不一致，需要重复编写很多代码；
　　D.服务器端和客户端解析XML花费较多的资源和时间。

**(2).JSON的优缺点**

**<1>.JSON的优点：**
　　A.数据格式比较简单，易于读写，格式都是压缩的，占用带宽小；
　　B.易于解析，客户端JavaScript可以简单的通过eval()进行JSON数据的读取；
　　C.支持多种语言，包括ActionScript, C, C#, ColdFusion, Java, JavaScript, Perl, PHP, Python, Ruby等服务器端语言，便于服务器端的解析；
　　D.在PHP世界，已经有PHP-JSON和JSON-PHP出现了，偏于PHP序列化后的程序直接调用，PHP服务器端的对象、数组等能直接生成JSON格式，便于客户端的访问提取；
　　E.因为JSON格式能直接为服务器端代码使用，大大简化了服务器端和客户端的代码开发量，且完成任务不变，并且易于维护。

**<2>.JSON的缺点**
　　A.没有XML格式这么推广的深入人心和喜用广泛，没有XML那么通用性；
　　B.JSON格式目前在Web Service中推广还属于初级阶段。

## 3.XML和JSON的优缺点对比

<font style="color:blue">(1).可读性方面。</font>

JSON和XML的数据可读性基本相同，JSON和XML的可读性可谓不相上下，一边是建议的语法，一边是规范的标签形式，XML可读性较好些。

<font style="color:blue">(2).可扩展性方面。</font>

XML天生有很好的扩展性，JSON当然也有，没有什么是XML能扩展，JSON不能的。

<font style="color:blue">(3).编码难度方面。</font>

XML有丰富的编码工具，比如Dom4j、JDom等，JSON也有json.org提供的工具，但是JSON的编码明显比XML容易许多，即使不借助工具也能写出JSON的代码，可是要写好XML就不太容易了。

<font style="color:blue">(4).解码难度方面。</font>

XML的解析得考虑子节点父节点，让人头昏眼花，而JSON的解析难度几乎为0。这一点XML输的真是没话说。

<font style="color:blue">(5).流行度方面。</font>

XML已经被业界广泛的使用，而JSON才刚刚开始，但是在Ajax这个特定的领域，未来的发展一定是XML让位于JSON。到时Ajax应该变成Ajaj(Asynchronous Javascript and JSON)了。

<font style="color:blue">(6).解析手段方面。</font>

JSON和XML同样拥有丰富的解析手段。

<font style="color:blue">(7).数据体积方面。</font>

JSON相对于XML来讲，数据的体积小，传递的速度更快些。

<font style="color:blue">(8).数据交互方面。</font>

JSON与JavaScript的交互更加方便，更容易解析处理，更好的数据交互。

<font style="color:blue">(9).数据描述方面。</font>

JSON对数据的描述性比XML较差。

<font style="color:blue">(10).传输速度方面。</font>

JSON的速度要远远快于XML。

## 4.XML与JSON数据格式比较

**(1).关于轻量级和重量级**

轻量级和重量级是相对来说的，那么XML相对于JSON的重量级体现在哪呢?应该体现在解析上，XML目前设计了两种解析方式：DOM和 SAX。

<1>.DOM

DOM是把一个数据交换格式XML看成一个DOM对象，需要把XML文件整个读入内存，这一点上JSON和XML的原理是一样的，但是XML要考虑父节点和子节点，这一点上JSON的解析难度要小很多，因为JSON构建于两种结构：key/value，键值对的集合;值的有序集合，可理解为数组；

<2>.SAX

SAX不需要整个读入文档就可以对解析出的内容进行处理，是一种逐步解析的方法。程序也可以随时终止解析。这样，一个大的文档就可以逐步的、一点一点的展现出来，所以SAX适合于大规模的解析。这一点，JSON目前是做不到得。

所以，JSON和XML的轻/重量级的区别在于：

+ JSON只提供整体解析方案，而这种方法只在解析较少的数据时才能起到良好的效果；

+ XML提供了对大规模数据的逐步解析方案，这种方案很适合于对大量数据的处理。

**(2).关于数据格式编码及解析难度**

<1>.在编码方面。

虽然XML和JSON都有各自的编码工具，但是JSON的编码要比XML简单，即使不借助工具，也可以写出JSON代码，但要写出好的XML代码就有点困难;与XML一样，JSON也是基于文本的，且它们都使用Unicode编码，且其与数据交换格式XML一样具有可读性。

主观上来看，JSON更为清晰且冗余更少些。JSON网站提供了对JSON语法的严格描述，只是描述较简短。从总体来看，XML比较适合于标记文档，而JSON却更适于进行数据交换处理。

<2>.在解析方面。

在普通的web应用领域，开发者经常为XML的解析伤脑筋，无论是服务器端生成或处理XML，还是客户端用 JavaScript 解析XML，都常常导致复杂的代码，极低的开发效率。

实际上，对于大多数Web应用来说，他们根本不需要复杂的XML来传输数据，XML宣称的扩展性在此就很少具有优势,许多Ajax应用甚至直接返回HTML片段来构建动态Web页面。和返回XML并解析它相比，返回HTML片段大大降低了系统的复杂性，但同时缺少了一定的灵活性。同XML或 HTML片段相比，数据交换格式JSON 提供了更好的简单性和灵活性。在Web Serivice应用中，至少就目前来说XML仍有不可动摇的地位。

**(3).实例比较**

XML和JSON都使用结构化方法来标记数据，下面来做一个简单的比较。
<1>.用XML表示中国部分省市数据如下：

```xml
<?xml version="1.0" encoding="utf-8" ?>
<country>
  <name>中国</name>
  <province>
    <name>黑龙江</name>
    <citys>
      <city>哈尔滨</city>
      <city>大庆</city>
    </citys>  　　
  </province>
  <province>
    <name>广东</name>
    <citys>
      <city>广州</city>
      <city>深圳</city>
      <city>珠海</city>
    </citys> 　　
  </province>
  <province>
    <name>台湾</name>
    <citys>
      　<city>台北</city>
      　<city>高雄</city>
    </citys>　
  </province>
  <province>
    <name>新疆</name>
    <citys>
      <city>乌鲁木齐</city>
    </citys>
  </province>
</country>
```

<2>.用JSON表示中国部分省市数据如下：

```json
{
      name: "中国",
      provinces: [
      { name: "黑龙江", citys:["哈尔滨", "大庆"] },
      { name: "广东", citys:["广州", "深圳", "珠海"] },
      { name: "台湾", citys:["台北", "高雄"] },
      { name: "新疆", citys: ["乌鲁木齐"] }
      ]
}
```

编码的可读性来说，XML有明显的优势，毕竟人类的语言更贴近这样的说明结构。JSON读起来更像一个数据块，读起来就比较费解了。不过，我们读起来费解的语言，恰恰是适合机器阅读。

编码的手写难度来说，XML还是舒服一些，好读当然就好写。不过写出来的字符JSON就明显少很多。去掉空白制表以及换行的话，JSON就是密密麻麻的有用数据，而XML却包含很多重复的标记字符。
