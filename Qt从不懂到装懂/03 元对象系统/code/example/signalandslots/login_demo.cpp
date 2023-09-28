#include<QApplication>
#include<QWidget>
#include<QLineEdit>
#include<QPushButton>

class Login : public QWidget
{
	Q_OBJECT
public:
	Login(QWidget* parent = nullptr)
		:QWidget(parent)
		,m_usernameEdit(new QLineEdit(this))
		,m_passwordEdit(new QLineEdit(this))
		,m_loginBtn(new QPushButton(this))
	{
		resize(430, 330);
		m_usernameEdit->move((width() - m_usernameEdit->width()) / 2, 50);
		m_passwordEdit->move((width() - m_passwordEdit->width()) / 2, 100);

		m_loginBtn->setText("登录");
		m_loginBtn->move((width() - m_loginBtn->width()) / 2, 150);

		connect(m_loginBtn, &QPushButton::clicked, this, &Login::on_loginBtn_clicked);
	}

	void on_loginBtn_clicked()
	{
		QString username = m_usernameEdit->text();
		QString password = m_passwordEdit->text();
		
		emit loginSuccess(username, password);
		emit loginSuccess();
		qDebug() << username << password;
	}
signals:
	void loginSuccess(const QString& username,const QString& passwrod);
	void loginSuccess();
private:
	QLineEdit* m_usernameEdit{};
	QLineEdit* m_passwordEdit{};
	QPushButton* m_loginBtn{};
};


class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr)
		:QWidget(parent)
		,m_login(new Login)
	{
		m_login->show();
		this->hide();

		connect(m_login,QOverload<>::of(&Login::loginSuccess), [=]
			{
				this->show();
				m_login->close();
			});
		connect(m_login, QOverload<>::of(&Login::loginSuccess),this,&MainWindow::on_loginSuccess);


		connect(m_login, &QObject::destroyed, [] {qDebug() << "m_login destroyed"; });
	}
	~MainWindow() { delete m_login; }

public slots:
	void on_loginSuccess()
	{
		qDebug() << "登录成功~";
	}
private:
	Login* m_login{};
};

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	//w.show();
	return a.exec();
}

#include "login_demo.moc"