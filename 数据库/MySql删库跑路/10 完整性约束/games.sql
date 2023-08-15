-- 删除数据库
DROP DATABASE IF EXISTS games;

-- 创建数据库
CREATE DATABASE IF NOT EXISTS games;

-- 选择数据库
USE games;

-- 创建表
DROP TABLE IF EXISTS sporter;
CREATE TABLE sporter
(
	sporterno INT,
	name 			VARCHAR(30) NOT NULL,
	gender 		CHAR				NOT NULL,
	deptname 	VARCHAR(30)	NOT NULL,
	CONSTRAINT pk_sporterno PRIMARY KEY(sporterno),
	CONSTRAINT ck_gender CHECK(gender IN('男','女'))
)COMMENT '运动员表';

DROP TABLE IF EXISTS item;
CREATE TABLE item
(
	itemno 		INT AUTO_INCREMENT,
	itemname 	VARCHAR(30)	NOT NULL,
	loc 			VARCHAR(30)	NOT NULL,
	CONSTRAINT pk_itemno PRIMARY KEY(itemno) 
)COMMENT '运动项目表';

DROP TABLE IF EXISTS grade;
CREATE TABLE grade
(
	sporterno INT,
	itemno INT,
	mark INT,
	CONSTRAINT fk_sporterno FOREIGN KEY(sporterno) REFERENCES sporter(sporterno),
	CONSTRAINT fk_itemno FOREIGN KEY(itemno) REFERENCES item(itemno)
)COMMENT '远动员积分表';


--  添加测试数据
INSERT INTO sporter(sporterno,name,gender,deptname) VALUES(1001,'九夏','男','计算机系');
INSERT INTO sporter(sporterno,name,gender,deptname) VALUES(1002,'莫影','男','数学系');
INSERT INTO sporter(sporterno,name,gender,deptname) VALUES(1003,'里奇','男','计算机系');
INSERT INTO sporter(sporterno,name,gender,deptname) VALUES(1004,'顽石','男','物理系');
INSERT INTO sporter(sporterno,name,gender,deptname) VALUES(1005,'空弦','女','心理系');
INSERT INTO sporter(sporterno,name,gender,deptname) VALUES(1006,'苏苏','女','数学系');

INSERT INTO item(itemno,itemname,loc) VALUES(1,'男子五千米','一操场');
INSERT INTO item(itemno,itemname,loc) VALUES(2,'男子标枪','一操场');
INSERT INTO item(itemno,itemname,loc) VALUES(3,'男子跳远','二操场');
INSERT INTO item(itemno,itemname,loc) VALUES(4,'女子跳高','二操场');
INSERT INTO item(itemno,itemname,loc) VALUES(5,'女子三千米','三操场');

INSERT INTO grade(sporterno,itemno,mark) VALUES(1001,1,6);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1002,1,4);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1003,1,2);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1004,1,0);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1001,3,4);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1002,3,6);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1004,3,2);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1003,3,0);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1005,4,6);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1006,4,4);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1001,4,2);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1002,4,0);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1003,2,6);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1005,2,4);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1006,2,2);
INSERT INTO grade(sporterno,itemno,mark) VALUES(1001,2,0);


