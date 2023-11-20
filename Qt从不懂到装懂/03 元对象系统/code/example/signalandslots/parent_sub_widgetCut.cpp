#include<QApplication>
#include<QWidget>
#include<QPushButton>

class SubWidget : public QWidget
{
	Q_OBJECT
public:
	SubWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("子窗口");
		resize(640, 480);
		auto btn = new QPushButton("切换到主窗口", this);
		connect(btn, &QPushButton::clicked, this,&SubWidget::showMainWidget);

	}
signals:
	void showMainWidget();
};


class Widget :public QWidget
{
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr)
		:QWidget(parent)
		,subWidget(new SubWidget)
	{
		setWindowTitle("主窗口");
		resize(640, 480);

		auto btn = new QPushButton("切换到子窗口", this);
		connect(btn, &QPushButton::clicked, [=]
			{
				this->hide();
				subWidget->show();
			});
		connect(subWidget, &SubWidget::showMainWidget, [=]
			{
				this->show();
				subWidget->hide();
			});
	}
	SubWidget* subWidget{};
};

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Widget w;
	w.show();
	
	return a.exec();
}

#include "parent_sub_widgetCut.moc"
