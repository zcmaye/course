#include<QApplication>
#include<QWidget>
#include<QTextEdit>
#include<QDebug>
#include<QPushButton>
#include<QFile>
//#pragma comment(linker,"/subsystem:console /entry:mainCRTStartup")

class TextColor
{
public:
    QString  textname;
    QRgb color;

    TextColor() {};
    TextColor(const QString& name, QRgb color)
        :textname(name)
        ,color(color)
    {

    }
    bool operator==(const TextColor& tc)const
    {
        return this->textname == tc.textname;
    }
    bool operator<(const TextColor& tc)const
    {
        return this->color < tc.color;
    }
};

class TextEdit : public QTextEdit
{
public:
    TextEdit(QWidget* parent = nullptr)
        :QTextEdit(parent)
    {
        //connect(this, &TextEdit::textChanged, this, &TextEdit::autoFormat);
        map[TextColor("keyword", qRgb(51, 0, 255))] << "void" << "int" << "char" << "unsigned" << "signed" << "float" << "double"<<"while"
            <<"for"<<"do"<<"nullptr"<<"public"<<"private"<<"procted"<<"auto"<<"this"<<"class"<<"if"<<"else"<<"switch"
            <<"return"<<"const";
        map[TextColor("预处理", qRgb(128, 128, 148))] << "#include" << "#define" << "#if" << "#elif" << "#else" << "#endif"
            << "#ifdef" << "#ifndef";
    }
    void autoFormat()
    {
        auto dom = this->document();
        auto tcf2 = this->currentCharFormat();
        QTextCursor cur(dom);
        while (!cur.isNull() && !cur.atEnd())
        {
            cur = dom->find("main", cur, QTextDocument::FindWholeWords);

            QTextCharFormat tcf1;
            tcf1.setForeground(Qt::red);
            cur.setCharFormat(tcf1);
        }
        cur.movePosition(QTextCursor::End);
        cur.setCharFormat(tcf2);
    }
    void autoFormatAll()
    {
        auto dom = this->document();
        auto tcf2 = this->currentCharFormat();
        QTextCursor cur(dom);

        auto keys = map.keys();
        for (auto key : keys)
        {
            for (auto str : map[key])
            {
                cur = QTextCursor(dom);
                QTextCharFormat tcf1;
                tcf1.setForeground(QBrush(key.color));
                qInfo() << cur.isNull() << cur.atEnd();
                while (!cur.isNull() && !cur.atEnd())
                {
                    cur = dom->find(str, cur, QTextDocument::FindWholeWords);
                    cur.setCharFormat(tcf1);
                }
            }
            //for (int i = 0; i < map[key].size(); i++)
            //{
            //    qInfo() << map[key][i] << i;
            //    cur = QTextCursor(dom);
            //    QTextCharFormat tcf1;
            //    tcf1.setForeground(QBrush(qRgb(51, 0, 255)));
            //    qInfo() << cur.isNull() << cur.atEnd();
            //    while (!cur.isNull() && !cur.atEnd())
            //    {
            //        cur = dom->find(map["keyword"][i], cur, QTextDocument::FindWholeWords);
            //        cur.setCharFormat(tcf1);
            //    }
            //}
            
        }

        cur.movePosition(QTextCursor::End);
        cur.setCharFormat(tcf2);
    }
    QMap<TextColor, QStringList> map;
};

class Widget : public QWidget 
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr)
        :QWidget(parent)
    {
        setup_Ui();
    }
    void setup_Ui()
    {
        textEdit = new TextEdit(this);
        textEdit->move(50, 50);
        resize(640, 480);
        
        textEdit->setPlainText("Maye");
        textEdit->resize(640, 480);

        auto btn = new QPushButton("Run", this);
        connect(btn, &QPushButton::clicked, this, &Widget::test);

    }
    void test()
    {
        textEdit->setFontPointSize(30);
        //textEdit->insertPlainText("main");
        textEdit->autoFormatAll();



        return;
        auto tc = textEdit->textCursor();
        QTextCharFormat tcf;
        tcf.setTextOutline(QPen(Qt::red, 5));
        tc.insertText("<p>我不是真真的快乐！</p>",tcf);
        textEdit->setTextCursor(tc);
        
        return;
        QFile file("E:\\GitHub\\course\\C&C++\\C语言从入门到放弃\\01 进制转换\\进制转换.md");
        if (file.open(QIODevice::ReadOnly))
        {
            textEdit->setMarkdown(file.readAll());
        }
        return;
        textEdit->clear();
        return;
        //textEdit->setText("<h1>我是Maye</h1>");
        //textEdit->setText("# 我是Maye  ## 函数是什么  + 1  + 2  [百度一下](https://www.baidu.com)");
        textEdit->setText("<h1>我是Maye</h1> 你是混蛋");
        qInfo() << textEdit->toHtml();

       return;

        textEdit->setMarkdown("## 函数\n\n### 函数是什么\n+ one\n+ two\n     1. 123\n    2. sdfsd\n+ three  \n<img src='https://www.baidu.com/img/flexible/logo/pc/index_gray.png'/>");
        qInfo() << textEdit->toMarkdown();
        return;

        //textEdit->setHtml("<h1>顽石老师</h1>");
        textEdit->insertHtml("<a href='www.baidu.com'>百度一下</a>");
        qInfo() << textEdit->toHtml();

        return;

        //textEdit->setPlainText("<h1>顽石老师</h1>");
        textEdit->insertPlainText("<h1>顽石老师</h1>");
        qInfo() << textEdit->toPlainText();

        return;
        
        //占位文本
        textEdit->setPlaceholderText("请输入个人简介");
        qInfo() << textEdit->placeholderText();
    }

private:
    TextEdit* textEdit;
};

int main(int argc,char*argv[])
{
    QApplication a(argc,argv);
    Widget w;
    w.show();

    return a.exec();
}

#include "main.moc"