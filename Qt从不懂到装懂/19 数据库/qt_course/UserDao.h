// user_database_userDao.h
#ifndef USER_DATABASE_HELPER_H
#define USER_DATABASE_HELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "user.h"

class UserDao {
public:
    explicit UserDao(const QSqlDatabase& db);
    
    // CRUD 操作
    bool createTable();                                          // 创建表
    bool insertUser(const std::shared_ptr<User>& user);          // 插入用户
    bool updateUser(const std::shared_ptr<User>& user);          // 更新用户
    bool deleteUser(int userId);                                 // 删除用户
    QList<std::shared_ptr<User>> getAllUsers();                  // 获取所有用户
    std::shared_ptr<User> getUserById(int userId);               // 根据ID获取用户
    std::shared_ptr<User> getUserByUsername(const QString& username);   // 根据用户名获取
    std::shared_ptr<User> getUserByEmail(const QString& email);         // 根据邮箱获取
    bool userExists(const QString& username, const QString& email);     // 检查用户是否存在
    
    // 批量操作
    bool insertMultipleUsers(const QList<std::shared_ptr<User>>& users);             // 批量插入
    bool updateLastLogin(int userId, const QDateTime& loginTime);   // 更新最后登录时间
    
private:
    QSqlDatabase m_db;
    
    // 辅助方法
    // 将查询结果转换为User对象
    std::shared_ptr<User> resultToUser(const QSqlQuery& query);
    // 将User对象绑定到查询中
    bool bindUserToQuery(User& user, QSqlQuery& query, bool isInsert = true);
};

#endif // USER_DATABASE_HELPER_H