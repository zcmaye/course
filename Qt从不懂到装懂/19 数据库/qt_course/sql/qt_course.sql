-- ----------------------------
-- Table structure for users
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS users (
    id          INTEGER PRIMARY KEY AUTO_INCREMENT,  -- SQLite 用 AUTOINCREMENT
    username    VARCHAR(50)  NOT NULL UNIQUE,        -- 用户名，唯一
    nickname    VARCHAR(50)  NOT NULL,               -- 用户昵称
    password    VARCHAR(255) NOT NULL,               -- 密码哈希值
    email       VARCHAR(100) NOT NULL UNIQUE,        -- 邮箱，唯一
    phone       VARCHAR(20)  UNIQUE,                 -- 手机号（可选）
    real_name  VARCHAR(100),                        -- 真实姓名
    avatar      VARCHAR(500),                        -- 头像URL或路径
    role        VARCHAR(20)  DEFAULT 'user',         -- 角色: admin/user/guest
    status      TINYINT      DEFAULT 1,              -- 状态: 0禁用 1启用
    last_login  DATETIME,                            -- 最后登录时间
    created_at  DATETIME     DEFAULT CURRENT_TIMESTAMP,
    updated_at  DATETIME     DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- 创建索引提高查询性能
CREATE INDEX idx_username ON users(username);
CREATE INDEX idx_email    ON users(email);
CREATE INDEX idx_status   ON users(status);

INSERT INTO users (username, nickname, password, email, phone, real_name, avatar, role, status, last_login, created_at, updated_at) VALUES
('admin', '管理员', 'pwd123456', 'admin@test.com', '13800000001', '张建国', '/avatar/1.png', 'admin', 1, '2024-01-15 10:00:00', '2024-01-01 09:00:00', '2024-01-15 10:00:00'),
('zhang_san', '张三', 'pwd123456', 'zhangsan@test.com', '13800000002', '张三', '/avatar/2.png', 'user', 1, '2024-01-14 15:30:00', '2024-01-02 10:00:00', '2024-01-14 15:30:00'),
('li_si', '李四', 'pwd123456', 'lisi@test.com', '13800000003', '李四', '/avatar/3.png', 'user', 1, '2024-01-13 09:15:00', '2024-01-03 14:00:00', '2024-01-13 09:15:00'),
('wang_wu', '王五', 'pwd123456', 'wangwu@test.com', '13800000004', '王五', '/avatar/4.png', 'user', 1, '2024-01-12 20:00:00', '2024-01-04 11:00:00', '2024-01-12 20:00:00'),
('zhao_liu', '赵六', 'pwd123456', 'zhaoliu@test.com', '13800000005', '赵六', '/avatar/5.png', 'user', 0, '2024-01-10 08:45:00', '2024-01-05 09:30:00', '2024-01-10 08:45:00'),
('sun_qi', '孙七', 'pwd123456', 'sunqi@test.com', '13800000006', '孙七', '/avatar/6.png', 'user', 1, '2024-01-11 17:20:00', '2024-01-06 16:00:00', '2024-01-11 17:20:00'),
('zhou_ba', '周八', 'pwd123456', 'zhouba@test.com', '13800000007', '周八', '/avatar/7.png', 'guest', 1, NULL, '2024-01-07 13:00:00', '2024-01-07 13:00:00'),
('wu_jiu', '吴九', 'pwd123456', 'wujiu@test.com', '13800000008', '吴九', '/avatar/8.png', 'user', 1, '2024-01-14 11:00:00', '2024-01-08 10:00:00', '2024-01-14 11:00:00'),
('zheng_shi', '郑十', 'pwd123456', 'zhengshi@test.com', '13800000009', '郑十', '/avatar/9.png', 'user', 0, '2024-01-05 14:30:00', '2024-01-09 15:00:00', '2024-01-09 15:00:00'),
('test_user', '测试员', 'pwd123456', 'test@test.com', '13800000010', '测试员', '/avatar/10.png', 'user', 1, '2024-01-15 09:00:00', '2024-01-10 08:00:00', '2024-01-15 09:00:00');