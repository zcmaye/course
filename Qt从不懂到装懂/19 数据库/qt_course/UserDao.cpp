#include "UserDao.h"
#include <QDebug>

#define INSERT_SQL \
        "INSERT INTO users (username, nickname, password, email, phone, "\
        "real_name, avatar, role, status, last_login, created_at, updated_at) "\
        "VALUES (:username, :nickname, :password, :email, :phone, "\
        ":real_name, :avatar, :role, :status, :last_login, :created_at, :updated_at)"

#define UPDATE_SQL \
        "UPDATE users SET username = :username, nickname = :nickname, "\
        "password = :password, email = :email, phone = :phone, "\
        "real_name = :real_name, avatar = :avatar, role = :role, "\
        "status = :status, last_login = :last_login, updated_at = :updated_at "\
        "WHERE id = :id"
 

UserDao::UserDao(const QSqlDatabase& db) 
    : m_db(db) 
{}

bool UserDao::createTable() {
    QString createSQL = 
        "CREATE TABLE IF NOT EXISTS users ("
        "    id          INTEGER PRIMARY KEY AUTO_INCREMENT,"
        "    username    VARCHAR(50)  NOT NULL UNIQUE,"
        "    nickname    VARCHAR(50)  NOT NULL,"
        "    password    VARCHAR(255) NOT NULL,"
        "    email       VARCHAR(100) NOT NULL UNIQUE,"
        "    phone       VARCHAR(20)  UNIQUE,"
        "    real_name   VARCHAR(100),"
        "    avatar      VARCHAR(500),"
        "    role        VARCHAR(20)  DEFAULT 'user',"
        "    status      TINYINT      DEFAULT 1,"
        "    last_login  DATETIME,"
        "    created_at  DATETIME     DEFAULT CURRENT_TIMESTAMP,"
        "    updated_at  DATETIME     DEFAULT CURRENT_TIMESTAMP"
        ")";
    
    QSqlQuery query(m_db);
    if (!query.exec(createSQL)) {
        qDebug() << "创建表失败:" << query.lastError().text();
        return false;
    }
    
    // 创建索引
    query.exec("CREATE INDEX idx_username ON users(username)");
    query.exec("CREATE INDEX idx_email ON users(email)");
    query.exec("CREATE INDEX idx_status ON users(status)");
    
    return true;
}

bool UserDao::insertUser(const std::shared_ptr<User>& user) {

    QSqlQuery query(m_db);
    query.prepare(INSERT_SQL);

    // 使用辅助函数绑定数据
    if (!bindUserToQuery(*user, query, true)) {
        qDebug() << "绑定参数失败";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "插入用户失败:" << query.lastError().text();
        return false;
    }

    // 获取自动生成的 ID（对于自增主键）
    user->id = query.lastInsertId().toInt();

    return true;
}

bool UserDao::updateUser(const std::shared_ptr<User>& user) {
    QSqlQuery query(m_db);
    query.prepare(UPDATE_SQL);

    // 使用辅助函数绑定数据
    if (!bindUserToQuery(*user, query, false)) {
        qDebug() << "绑定参数失败";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "更新用户失败:" << query.lastError().text();
        return false;
    }

    return true;
}

bool UserDao::deleteUser(int userId) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    
    if (!query.exec()) {
        qDebug() << "删除用户失败:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<std::shared_ptr<User>> UserDao::getAllUsers() {
    QList<std::shared_ptr<User>> users;
    QSqlQuery query("SELECT * FROM users ORDER BY id", m_db);
    
    while (query.next()) {
        users.append(resultToUser(query));
    }
    
    return users;
}

std::shared_ptr<User> UserDao::getUserById(int userId) {
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    
    if (query.exec() && query.next()) {
        return resultToUser(query);
    }
    
    return nullptr;
}

std::shared_ptr<User> UserDao::getUserByUsername(const QString& username) {
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);
    
    if (query.exec() && query.next()) {
        return resultToUser(query);
    }
    
    return nullptr;
}

std::shared_ptr<User> UserDao::getUserByEmail(const QString& email) {
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM users WHERE email = :email");
    query.bindValue(":email", email);
    
    if (query.exec() && query.next()) {
        return resultToUser(query);
    }
    
    return nullptr;
}

bool UserDao::userExists(const QString& username, const QString& email) {
    QSqlQuery query(m_db);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username OR email = :email");
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    return false;
}

bool UserDao::insertMultipleUsers(const QList<std::shared_ptr<User>>& users)
{
	if (users.isEmpty()) {
		qDebug() << "用户列表为空，无需插入";
		return true;
	}

	// 开始事务
	if (!m_db.transaction()) {
		qDebug() << "开启事务失败:" << m_db.lastError().text();
		return false;
	}

	// 准备 SQL 语句
	QSqlQuery query(m_db);
	query.prepare(INSERT_SQL);

	int successCount = 0;

	// 批量插入
	for (const std::shared_ptr<User>& user : users) {
        bindUserToQuery(*user, query);

		if (query.exec()) {
			successCount++;
		}
		else {
			qDebug() << "插入用户失败:" << user->username << query.lastError().text();
		}
	}

	// 提交或回滚事务
	if (successCount == users.size()) {
		if (!m_db.commit()) {
			qDebug() << "提交事务失败:" << m_db.lastError().text();
			m_db.rollback();
			return false;
		}
		qDebug() << "批量插入成功，共插入" << successCount << "个用户";
		return true;
	}
	else {
		m_db.rollback();
		qDebug() << "批量插入失败，成功:" << successCount << "/" << users.size();
		return false;
	}
	return false;
}

bool UserDao::updateLastLogin(int userId, const QDateTime& loginTime) {
	QSqlQuery query(m_db);
	query.prepare("UPDATE users SET last_login = :last_login WHERE id = :id");
	query.bindValue(":id", userId);
	query.bindValue(":last_login", loginTime);

	return query.exec();
}

std::shared_ptr<User> UserDao::resultToUser(const QSqlQuery& query) {
	auto user = std::make_shared<User>();
	user->id = query.value("id").toInt();
	user->username = query.value("username").toString();
	user->nickname = query.value("nickname").toString();
	user->password = query.value("password").toString();
	user->email = query.value("email").toString();
	user->phone = query.value("phone").toString();
	user->realName = query.value("real_name").toString();
	user->avatar = query.value("avatar").toString();
	user->role = User::stringToRole(query.value("role").toString());
	user->status = static_cast<UserStatus>(query.value("status").toInt());
	user->lastLogin = query.value("last_login").toDateTime();
	user->createdAt = query.value("created_at").toDateTime();
	user->updatedAt = query.value("updated_at").toDateTime();

	return user;
}

bool UserDao::bindUserToQuery(User& user, QSqlQuery& query, bool isInsert)
{
	// 绑定通用字段
	query.bindValue(":username", user.username);
	query.bindValue(":nickname", user.nickname);
	query.bindValue(":password", user.password);
	query.bindValue(":email", user.email);
	query.bindValue(":phone", user.phone);
	query.bindValue(":real_name", user.realName);
	query.bindValue(":avatar", user.avatar);
	query.bindValue(":role", User::roleToString(user.role));
	query.bindValue(":status", static_cast<int>(user.status));
	query.bindValue(":last_login", user.lastLogin);

	if (isInsert) {
		// 插入操作：需要设置创建时间和更新时间
		query.bindValue(":created_at", user.createdAt);
		query.bindValue(":updated_at", user.updatedAt);
	}
	else {
		// 更新操作：只需要设置更新时间，并绑定 ID
		query.bindValue(":updated_at", QDateTime::currentDateTime());
		query.bindValue(":id", user.id);
	}

	return true;
}
