#include <QtCore/QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "UserDao.h"

QSqlDatabase getConnection()
{
    // 检查是否已经存在一个名为qt_course_con的有效数据库连接
    QSqlDatabase db = QSqlDatabase::database("qt_course_con");
    //有效直接返回
    if (db.isValid()) {
        return db;
    }
    //无效需要 添加一个名为 "qt_course_con" 的 MySQL 数据库连接
	db = QSqlDatabase::addDatabase("QMYSQL","qt_course_con");
	db.setHostName("127.0.0.1");	 // 数据库服务器的地址
	db.setPort(3306);				 // 数据库服务器的端口，MySQL默认为3306
	db.setDatabaseName("qt_course");		 // 你想要连接的数据库名
	db.setUserName("root");          // 数据库登录用户名
	db.setPassword("mysql1228.");		// 数据库登录密码

	if (db.open()) {
		qDebug() << "MySQL 数据库连接成功！";
	}
	else {
		qDebug() << "连接失败：" << db.lastError().text();
	}
    return db;
}

void test_user_dao() {
    // 创建助手类
    UserDao userDao(getConnection());
    
    // 创建表
    userDao.createTable();
    
    // 创建新用户
    auto newUser = std::make_shared<User>();
    newUser->username = "zhangsan";
    newUser->nickname = "张三";
    newUser->password = "hashed_password_here";
    newUser->email = "zhangsan@example.com";
    newUser->phone = "13800138000";
    newUser->realName = "张三";
    newUser->role = UserRole::User;
    newUser->status = UserStatus::Enabled;
    newUser->createdAt = QDateTime::currentDateTime();
    newUser->updatedAt = QDateTime::currentDateTime();
    
    // 插入用户
    if (userDao.insertUser(newUser)) {
        qDebug() << "用户插入成功!";
    }
    
    // 查询用户
    auto user = userDao.getUserByUsername("zhangsan");
    if (user) {
        user->debugPrint();
        
        // 更新最后登录时间
        userDao.updateLastLogin(user->id, QDateTime::currentDateTime());
    }
    
    // 获取所有用户
    auto allUsers = userDao.getAllUsers();
    qDebug() << "总用户数:" << allUsers.size();
}

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

	test_user_dao();

	return app.exec();
}
