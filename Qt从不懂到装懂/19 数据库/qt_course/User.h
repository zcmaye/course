#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>
#include <QDebug>

// 用户角色枚举
enum class UserRole {
    Admin = 0,   // 管理员
    User,        // 普通用户
    Guest        // 访客
};

// 用户状态枚举
enum class UserStatus {
    Disabled = 0,  // 禁用
    Enabled = 1    // 启用
};

// 用户结构体
struct User {
    int id;                       // 用户ID
    QString username;             // 用户名（唯一）
    QString nickname;             // 用户昵称
    QString password;             // 密码哈希值
    QString email;                // 邮箱（唯一）
    QString phone;                // 手机号
    QString realName;             // 真实姓名
    QString avatar;               // 头像URL或路径
    UserRole role;                // 角色
    UserStatus status;            // 状态
    QDateTime lastLogin;          // 最后登录时间
    QDateTime createdAt;          // 创建时间
    QDateTime updatedAt;          // 更新时间

    // 构造函数
    User() : id(0), role(UserRole::User), status(UserStatus::Enabled) {}

    // 带参数的构造函数
    User(int id, const QString& username, const QString& nickname, 
         const QString& password, const QString& email, const QString& phone,
         const QString& realName, const QString& avatar, UserRole role,
         UserStatus status, const QDateTime& lastLogin, 
         const QDateTime& createdAt, const QDateTime& updatedAt)
        : id(id), username(username), nickname(nickname), password(password),
          email(email), phone(phone), realName(realName), avatar(avatar),
          role(role), status(status), lastLogin(lastLogin),
          createdAt(createdAt), updatedAt(updatedAt) {}

    // 辅助方法
    bool isValid() const { return id > 0 && !username.isEmpty() && !email.isEmpty(); }
    bool isAdmin() const { return role == UserRole::Admin; }
    bool isActive() const { return status == UserStatus::Enabled; }
    
    // 角色转字符串
    static QString roleToString(UserRole role) {
        switch (role) {
            case UserRole::Admin: return "admin";
            case UserRole::User:  return "user";
            case UserRole::Guest: return "guest";
            default:              return "unknown";
        }
    }
    
    // 字符串转角色
    static UserRole stringToRole(const QString& roleStr) {
        if (roleStr == "admin") return UserRole::Admin;
        if (roleStr == "user")  return UserRole::User;
        if (roleStr == "guest") return UserRole::Guest;
        return UserRole::User; // 默认普通用户
    }
    
    // 状态转字符串
    static QString statusToString(UserStatus status) {
        return status == UserStatus::Enabled ? "enabled" : "disabled";
    }
    
    // 字符串转状态
    static UserStatus stringToStatus(const QString& statusStr) {
        return statusStr == "enabled" ? UserStatus::Enabled : UserStatus::Disabled;
    }

    // 打印调试信息
    void debugPrint() const {
        qDebug() << "User{"
                 << "id:" << id
                 << ", username:" << username
                 << ", nickname:" << nickname
                 << ", email:" << email
                 << ", phone:" << phone
                 << ", realName:" << realName
                 << ", role:" << roleToString(role)
                 << ", status:" << statusToString(status)
                 << ", lastLogin:" << lastLogin.toString("yyyy-MM-dd HH:mm:ss")
                 << ", createdAt:" << createdAt.toString("yyyy-MM-dd HH:mm:ss")
                 << ", updatedAt:" << updatedAt.toString("yyyy-MM-dd HH:mm:ss")
                 << "}";
    }
};

#endif // USER_H