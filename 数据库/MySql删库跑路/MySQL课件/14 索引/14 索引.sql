## 索引操作
### 查看索引
#### 一，SHOW INDEX
SHOW INDEX FROM emp;
#### 二，EXPLAIN
EXPLAIN SELECT * FROM emp WHERE empno = 7934;
#### 三，information_schema
SELECT * FROM INFORMATION_SCHEMA.STATISTICS WHERE TABLE_SCHEMA = 'hdy' AND TABLE_NAME = 'emp';

### 创建索引
#### 1,普通索引
CREATE TABLE book(
  id INT PRIMARY KEY AUTO_INCREMENT,
  bname VARCHAR(128) NOT NULL ,
  author VARCHAR(128) NOT NULL,
  `desc` VARCHAR(256),
  price DECIMAL(7,2),
  INDEX(bname),
  INDEX idx_author(author)
);
SHOW INDEX FROM book;
-- 添加索引
ALTER TABLE book ADD INDEX idx_price(price); 
-- 创建索引
CREATE INDEX idx_desc ON book(`desc` DESC);
-- 删除掉索引
ALTER TABLE book DROP INDEX idx_desc;
-- DROP INDEX
DROP INDEX idx_price ON book;

#### 2,创建唯一索引
ALTER TABLE book ADD UNIQUE idx_price(price);

#### 3,创建主键索引 PRIMARY KEY

#### 4,创建多列索引
CREATE TABLE stu(
  id INT,
  name VARCHAR(32),
  age TINYINT,
  remark VARCHAR(256),
  INDEX multi_idx(id,name,age)
);
SHOW INDEX FROM stu;

EXPLAIN SELECT * FROM stu WHERE age = 1 AND name = 'hello' AND id = 1;

#### 5，全文索引
CREATE TABLE comments(
  id INT,
  `comment` TEXT,
  FULLTEXT INDEX futext_idx_comment(comment)
);

SHOW INDEX FROM comments;

## 倒序索引
-- 测试没有降序索引的情况
CREATE TABLE ts1(	
    a INT,
		b INT,
		INDEX idx_a_b(a,b)
		);


-- 测试有降序索引的情况
CREATE TABLE ts2(	
    a INT,
		b INT,
		INDEX idx_a_b(a,b DESC)
		);
    
DELIMITER //
CREATE PROCEDURE ts1_insert() 
BEGIN
	DECLARE i INT DEFAULT 1; 	 -- 变量要定义在最开始
	START TRANSACTION;			 -- 开始事务要放在定义变量之后
	WHILE i <= 800 DO
		INSERT INTO ts1 SELECT RAND()*80000,RAND()*80000; 
		SET i = i + 1;
	END WHILE;
	COMMIT; 
END //
DELIMITER ;

DELIMITER //
CREATE PROCEDURE ts2_insert() 
BEGIN
	DECLARE i INT DEFAULT 1; 	 -- 变量要定义在最开始
	START TRANSACTION;			 -- 开始事务要放在定义变量之后
	WHILE i <= 800 DO
		INSERT INTO ts2 SELECT RAND()*80000,RAND()*80000; 
		SET i = i + 1;
	END WHILE;
	COMMIT; 
END //
DELIMITER ;

#调用
CALL ts1_insert();
CALL ts2_insert();

EXPLAIN SELECT * FROM ts1 ORDER BY a,b DESC LIMIT 5;
EXPLAIN SELECT * FROM ts2 ORDER BY a,b DESC LIMIT 5;


## 隐藏索引
SHOW INDEX FROM ts1;
EXPLAIN SELECT * FROM ts1 ORDER BY a,b DESC LIMIT 5;

-- 隐藏掉索引
ALTER TABLE ts1 ALTER INDEX idx_a_b INVISIBLE;
ALTER TABLE ts1 ALTER INDEX idx_a_b VISIBLE;

-- 让隐藏索引对查询优化器课件
SELECT @@GLOBAL.optimizer_switch;
/*
index_merge=on,index_merge_union=on,index_merge_sort_union=on,index_merge_intersection=on,engine_condition_pushdown=on,index_condition_pushdown=on,mrr=on,mrr_cost_based=on,block_nested_loop=on,batched_key_access=off,materialization=on,semijoin=on,loosescan=on,firstmatch=on,duplicateweedout=on,subquery_materialization_cost_based=on,use_index_extensions=on,condition_fanout_filter=on,derived_merge=on,use_invisible_indexes=off,skip_scan=on,hash_join=on,subquery_to_derived=off,prefer_ordering_index=on,hypergraph_optimizer=off,derived_condition_pushdown=on,hash_set_operations=on
*/
set session optimizer_switch="use_invisible_indexes=on"; 
set session optimizer_switch="use_invisible_indexes=off"; 


## 索引设计原则
### 插入测试数据
CALL insert_course(100);
CALL insert_stu(1000000);

SELECT COUNT(*),COUNT(DISTINCT course_id) FROM course;
SELECT COUNT(*) FROM student_info;


-- 1. 字段的数值有唯一性的限制
-- 2. 频繁作为 WHERE 查询条件的字段
SHOW INDEX FROM student_info;

-- 没有给student_id加索引之前： 0.245s
ALTER TABLE student_info ADD INDEX idx_sid(student_id); -- 3.679s
-- 给student_id加索引之后：     0.000s
SELECT course_id,class_id,create_time,student_id FROM student_info WHERE student_id = 123110;

-- 3. 经常GROUPBY和ORDER BY 的列
-- student_id有索引：0.002s
SELECT student_id,COUNT(*) AS num FROM student_info GROUP BY student_id LIMIT 100000;
-- 隐藏掉student_id的索引: 0.690s
ALTER TABLE student_info ALTER INDEX idx_sid INVISIBLE;

-- **再测试GROUP BY和ORDER BY同时出现的情况：**
EXPLAIN SELECT student_id,COUNT(*) AS num FROM student_info 
GROUP BY student_id
ORDER BY create_time DESC
LIMIT 100; 
-- 没有索引的情况   -- 0.885s
-- student_id有索引 -- 2.686s
-- student_id、create_time联合索引的情况 -- 0.321s
ALTER TABLE student_info ADD INDEX idx_sid_create_tm(student_id,create_time DESC);
ALTER TABLE student_info DROP INDEX idx_sid_create_tm;
-- 单独建立索引 -- 最终指挥选择一个索引，2.686s
ALTER TABLE student_info ALTER INDEX idx_sid VISIBLE;
ALTER TABLE student_info ADD INDEX idx_create_tm(create_time) VISIBLE;

SHOW INDEX FROM student_info;

-- 修改sql_mode
SELECT @@sql_mode;
SET @@sql_mode = 'STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
-- 4. UPDATE、DELETE 的 WHERE 条件列
UPDATE student_info SET student_id = 10002
WHERE name='462eed';
-- name没有索引：0.766s
-- name有索引：  0.000s
ALTER TABLE student_info ADD INDEX idx_name(name);

-- 5. DISTINCT字段需要创建索引
SHOW INDEX FROM student_info;

SELECT DISTINCT(student_id) FROM `student_info`;
-- student_id有索引：0.003s
-- student_id没索引：0.618s
ALTER TABLE student_info ALTER INDEX idx_sid INVISIBLE;

-- 6. 多表 JOIN连接操作时，创建索引注意事项
SELECT c.course_id, name, si.student_id, course_name FROM student_info si JOIN course c
ON si.course_id = c.course_id WHERE name = 'zdUlvu';
-- name有索引：0.000s
-- name没有索引：0.227s
ALTER TABLE student_info ALTER INDEX idx_name INVISIBLE;


SELECT c.course_id, name, si.student_id, course_name FROM student_info si JOIN course c
ON si.course_id = c.course_id WHERE name = 'zdUlvu';
-- course_id没有索引：0.228s 0.231s
-- 两张表的连接字段course_id都有索引的情况：22.908s  等值连接： 0.249s
ALTER TABLE course ADD INDEX idx_cid(course_id);
ALTER TABLE student_info ADD INDEX idx_cid(course_id);
ALTER TABLE course ALTER INDEX idx_cid INVISIBLE;
ALTER TABLE student_info ALTER INDEX idx_cid INVISIBLE;

SHOW INDEX FROM student_info;
SHOW INDEX FROM course;


