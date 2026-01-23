# 变量
## 系统变量
### 查看变量
-- #查看全局系统变量
SHOW GLOBAL VARIABLES;  -- 624个全局变量
-- #查看会话系统变量
SHOW SESSION VARIABLES; -- 648个会话变量 

### 模糊查询包含指定单词的变量
-- #模糊查询全局系统变量
SHOW GLOBAL VARIABLES LIKE '%file%';
-- #会话
SHOW SESSION VARIABLES LIKE '%file%';

### 查看指定变量的值
-- #全局变量
SELECT @@GLOBAL.max_connections;
SELECT @@GLOBAL.character_set_client;

-- #会话变量
-- 1238 - Variable 'max_connections' is a GLOBAL variable
-- max_connections变量是一个全局变量，不是一个会话变量，所以查不到！！！
SELECT @@SESSION.max_connections;
-- character_set_client这个变量既是会话变量也是全局变量
SELECT @@SESSION.character_set_client;

### 修改系统变量
#### 修改配置文件，然后重启mysql服务
SELECT @@GLOBAL.max_connections;  -- 151

#### 不用重启，直接通过语句来修改
SET GLOBAL max_connections = 10;

#### 修改会话系统变量，那么关闭会话之后，会重置
SET SESSION character_set_client = 'gbk';
SELECT @@SESSION.character_set_client;

#### 全局的变量，可以直接通过语句来进行持久化！(修改了之后把数据同步到配置文件种)
SET PERSIST max_connections = 128;

## 用户自定义变量
### 用户会话变量
#### 定义
-- #1，使用=或:=
SET @num1 = 1;
SET @num2 := 2;
SET @ret = @num1 + @num2;
SELECT @num1,'+',@num2,'=',@ret;

-- #2，在SELECT语句中使用,使用:=或INTO
SELECT @tmp_sal := sal FROM emp WHERE empno = 7788;
SELECT @tmp_sal,@tt;

-- #2，在SELECT语句中使用,使用:=或INTO
SELECT sal INTO @tmp_sal1 FROM emp WHERE empno = 7788;
SELECT @tmp_sal1;

### 局部变量，只能用在BEGIN...END之间，而且必须写在其他语句之前
-- 声明局部变量，并分别赋值为emp表中empno为7369的ename和sal。
DROP PROCEDURE IF EXISTS proc_ename_sal;
CREATE PROCEDURE proc_ename_sal()
BEGIN
  -- 先定义变量
  DECLARE _ename VARCHAR(32);
  DECLARE _sal DECIMAL(7,2) DEFAULT 0;
  
  -- 查询emp表中empno为7369的员工的姓名和薪资
  -- 1,用不同的方式给变量赋值，报错
  --   1222 - The used SELECT statements have a different number of columns
  -- SELECT @_ename := ename,sal INTO @_sal FROM emp WHERE empno = 7369;
  -- 2,都使用:=赋值，没有问题
  -- SELECT @_ename := ename,@_sal := sal FROM emp WHERE empno = 7369;
  -- 3,直接使用INTO
  SELECT ename,sal INTO @_ename,@_sal FROM emp WHERE empno = 7369;
  
  -- 查看变量的值
  SELECT CONCAT(@_ename,'薪资是',@_sal) AS info;
END;

CALL proc_ename_sal();

## 流程控制
### 条件判断
-- 声明存储过程“proc_update_sal_by_eno”，定义IN参数eno，输入员工编号。判断该员工 薪资如果低于5000元并且入职时间超过5年，就涨薪500元；否则就不变。
SELECT * FROM emp;
DESC emp;

DROP PROCEDURE proc_update_sal_by_eno;
CREATE PROCEDURE proc_update_sal_by_eno(IN eno SMALLINT)
BEGIN
  -- 定义变量
  DECLARE e_sal DECIMAL(7,2) DEFAULT 0;
  DECLARE e_year INT DEFAULT 0;
  
  -- 查看编号为eno的员工的薪资和入职年数
  SELECT sal,TIMESTAMPDIFF(YEAR,hiredate,NOW()) hiredate INTO e_sal,e_year FROM emp WHERE empno = eno;
  
  -- 判断
  IF e_sal < 5000 AND e_year > 5 
    THEN UPDATE emp SET sal = sal + 500 WHERE empno = eno;
  END IF;
END;

CALL proc_update_sal_by_eno(7369);

-- 声明存储过程“proc_update_sal_by_eno2”，定义IN参数eno，输入员工编号。判断该员工  薪资如果低于6000元，就更新薪资为6000元；薪资如果大于等于6000元且低于8000的，但是奖金 比例为NULL的，就更新奖金比例为0.01；其他的涨薪100元。
DELIMITER //
CREATE PROCEDURE proc_update_sal_by_eno2(IN eno SMALLINT)
BEGIN
  -- 定义变量
  DECLARE e_sal DECIMAL(7,2) DEFAULT 0;
  DECLARE e_comm SMALLINT DEFAULT 0;
  
  -- 查询薪资和奖金
  SELECT sal,comm INTO e_sal,e_comm FROM emp WHERE empno = eno;
  
  -- 判断
  IF e_sal < 6000 
    THEN UPDATE emp SET sal = 6000 WHERE empno = eno;
    SET @witch := 1;
  ELSEIF e_sal >= 6000 AND e_sal < 8000 AND e_comm IS NULL
    THEN UPDATE emp SET comm = sal * 0.01 WHERE empno = eno;
    SET @witch := 2;
  ELSE
    UPDATE emp SET sal = sal +100 WHERE empno = eno;
    SET @witch := 3;
  END IF;
END//
DELIMITER;

CALL proc_update_sal_by_eno2(7369);
CALL proc_update_sal_by_eno2(7788);
CALL proc_update_sal_by_eno2(7839);
SELECT @witch;
SELECT * FROM emp;

### LOOP循环
-- 使用LOOP语句进行循环操作，id值小于10时将重复执行循环过程。
DROP PROCEDURE proc_text_loop;
CREATE PROCEDURE proc_text_loop()
BEGIN
  DECLARE n INT DEFAULT 0;
  
  add_loop:LOOP
    SET n = n + 1;
    IF n >= 10
      THEN LEAVE add_loop;  -- 跳出add_loop循环
    END IF;
  END LOOP add_loop;
  
  SELECT n;
END;

CALL proc_text_loop();

### WHILE循环
-- 使用LOOP语句进行循环操作，id值小于10时将重复执行循环过程。
CREATE PROCEDURE proc_test_while()
BEGIN
  DECLARE n INT DEFAULT 0;
  
  add_while: WHILE n < 10 DO
    SET n = n + 1;
  END WHILE add_while;
  
  SELECT n;
END;

CALL proc_test_while();

### REPEAT循环
-- 使用LOOP语句进行循环操作，id值小于10时将重复执行循环过程。
DROP PROCEDURE proc_test_repeat;
CREATE PROCEDURE proc_test_repeat()
BEGIN
  DECLARE n INT DEFAULT 0;
  
  add_repeat: REPEAT
    SET n = n + 1;
  UNTIL n >= 10 -- 条件成立退出循环
  END REPEAT add_repeat;
  
  SELECT n;
END;
CALL proc_test_repeat();



## 定义条件与处理程序
DESC emp;

### 案例分析
-- 1,修改emp表的sal字段，加上NOT NULL约束
ALTER TABLE emp MODIFY sal DECIMAL(7,2) NOT NULL;

-- 2,写一个存储过程，来测试错误
DROP PROCEDURE IF EXISTS proc_update_sal;
CREATE PROCEDURE proc_update_sal()
BEGIN
  -- 定义条件
  DECLARE NotNull CONDITION FOR 1048;
  -- DECLARE NotNull CONDITION FOR SQLSTATE '23000';
  -- 定义错误处理程序
  -- DECLARE CONTINUE HANDLER FOR 1048 SET @msg = 'sal 不允许插入NULL值';
  -- DECLARE CONTINUE HANDLER FOR SQLSTATE '23000' SET @msg = 'sal 不允许插入NULL值';
  DECLARE CONTINUE HANDLER FOR NotNull SET @msg = 'sal 不允许插入NULL值';
  
  SET @x = 1;
  UPDATE emp SET sal = NULL WHERE ename = 'SMITH';
  SET @x = 2;
  SIGNAL SQLSTATE '12345' SET MESSAGE_TEXT = '主动中断';
  UPDATE emp SET sal = 200 WHERE ename = 'SMITH';
  SET @x = 3;
END;
-- ERROR 1048 (23000): Column 'sal' cannot be null
CALL proc_update_sal();
SELECT @x,@msg;
SELECT * FROM emp;


# 游标
SELECT empno,ename,sal FROM emp WHERE sal > 4500;
-- 游标基本使用
CREATE PROCEDURE proc_test_cursor()
BEGIN
  -- 定义变量
  DECLARE emp_no SMALLINT;
  DECLARE emp_name VARCHAR(32);
  DECLARE emp_sal DECIMAL(7,2);
  
  -- 定义游标
  DECLARE cursor_1 CURSOR FOR SELECT empno,ename,sal FROM emp WHERE sal > 4500;
  
  -- 打开游标
  OPEN cursor_1;
  
  -- 抓取数据
  FETCH cursor_1 INTO emp_no,emp_name,emp_sal;
  
  SELECT emp_no,emp_name,emp_sal;
  
  -- 关闭游标
  CLOSE cursor_1;
END;

CALL proc_test_cursor();

-- 通过游标获取所有数据
DROP PROCEDURE IF EXISTS proc_test_cursor_while;
CREATE PROCEDURE proc_test_cursor_while()
BEGIN
  -- 定义变量
  DECLARE emp_no SMALLINT;
  DECLARE emp_name VARCHAR(32);
  DECLARE emp_sal DECIMAL(7,2);
  DECLARE isExit BOOLEAN DEFAULT FALSE;
  
  -- 定义游标
  DECLARE cursor_1 CURSOR FOR SELECT empno,ename,sal FROM emp WHERE sal > 4500;
  
  -- 定义一个处理程序，当游标遍历完毕后，直接继续就可以了
  DECLARE CONTINUE HANDLER FOR 1329 
  BEGIN
    SET isExit := TRUE;
  END;
  
  -- 打开游标
  OPEN cursor_1;
  
  -- 循环抓取数据
  WHILE NOT isExit DO
    FETCH cursor_1 INTO emp_no,emp_name,emp_sal;
    SELECT emp_no,emp_name,emp_sal;
  END WHILE;
  
  -- 关闭游标
  CLOSE cursor_1;
END;
-- 如果游标没有更多数据可以返回了，则会报一个错误
-- ERROR 1329 (02000): No data - zero rows fetched, selected, or processed
CALL proc_test_cursor_while();


-- 测试杀死存储过程
DROP PROCEDURE IF EXISTS proc_test_cursor_forever;
CREATE PROCEDURE proc_test_cursor_forever()
BEGIN
  -- 定义变量
  DECLARE emp_no SMALLINT;
  DECLARE emp_name VARCHAR(32);
  DECLARE emp_sal DECIMAL(7,2);
  DECLARE isExit BOOLEAN DEFAULT FALSE;
  
  -- 定义游标
  DECLARE cursor_1 CURSOR FOR SELECT empno,ename,sal FROM emp WHERE sal > 4500;
  
  -- 定义一个处理程序，当游标遍历完毕后，直接继续就可以了
  DECLARE CONTINUE HANDLER FOR 1329 
  BEGIN
    SET isExit := TRUE;
  END;
  
  -- 打开游标
  OPEN cursor_1;
  
  -- 循环抓取数据
  WHILE TRUE DO
    FETCH cursor_1 INTO emp_no,emp_name,emp_sal;
    SELECT emp_no,emp_name,emp_sal;
  END WHILE;
  
  -- 关闭游标
  CLOSE cursor_1;
END;

-- CALL proc_test_cursor_forever();

SHOW PROCESSLIST;
KILL 8;
KILL 9;
KILL 10;