# 1. table列：表名
-- 查询的每一行记录都对应着一个单表
EXPLAIN SELECT * FROM emp;

-- emp驱动表 dept被驱动表
EXPLAIN SELECT * FROM emp JOIN dept USING(deptno);

# 2. id列：查询标识符表示查询顺序，id越大优先级越高，越先执行
-- 每个SELECT关键字都对应一个唯一的id
EXPLAIN SELECT * FROM emp;

-- 多表联合查询的ID都是一样的，表示执行顺序在同一级别
EXPLAIN SELECT * FROM emp JOIN dept USING(deptno);

-- 有子查询的ID，一般主查询id为1，子查询为2
EXPLAIN SELECT * FROM emp 
WHERE deptno IN(
  SELECT deptno FROM dept
) OR ename = 'c++';

-- !!!查询优化器可能对涉及子查询的语句进行重写，转变为多表查询的操作!!!
EXPLAIN SELECT * FROM emp WHERE EXISTS (
  SELECT 1 FROM dept WHERE dname LIKE '%c%'
);

-- uinon 去重ID情况
-- UNION 会产生一个临时表，然后对临时表进行去重查询
EXPLAIN 
SELECT * FROM emp e1 WHERE empno <= 1050
UNION 
SELECT * FROM emp e2 WHERE empno > 1050;

-- UNION ALL 不会产生临时表，直接将结果联合在一起
EXPLAIN 
SELECT * FROM emp e1 WHERE empno <= 1050
UNION ALL
SELECT * FROM emp e2 WHERE empno > 1050;


# 3. select_type列：查询类型，确定小查询在整个大查询中扮演一个什么角色
-- 查询语句中不包含UNION或者子查询的都算作是SIMPLE类型
EXPLAIN SELECT * FROM emp;

-- 多表连接查询也是SIMPLE类型
EXPLAIN SELECT * FROM emp JOIN dept USING(deptno);

-- 对于包含UNION、UNION ALL或者子查询的查询来说，它是由几个小查询组成的，其中主查询的类型是PRIMARY
-- UNION 右边的查询值是UNION
-- UNION 会产生一个临时表，进行去重，对于这个临时表的查询就是UNION RESULT
EXPLAIN 
SELECT * FROM emp e1 WHERE empno <= 1050
UNION 
SELECT * FROM emp e2 WHERE empno > 1050;

-- 子查询的类型值是SUBQUERY
EXPLAIN SELECT * FROM emp 
WHERE deptno IN(
  SELECT deptno FROM dept
) OR ename = 'c++';

-- 相关子查询的类型值是SUBQUERY
EXPLAIN SELECT * FROM dept d
WHERE (
  SELECT COUNT(*) FROM emp WHERE deptno = d.deptno
) > 1;

-- 递归公用表表达式
EXPLAIN WITH RECURSIVE cte AS
(
	SELECT empno,ename,mgr,1 AS n FROM emp WHERE  ename = 'JONES'	-- 初始查询
	UNION ALL
	SELECT a.empno,a.ename,a.mgr,n+1 FROM emp AS a JOIN cte ON (a.mgr = cte.empno) -- 递归查询，找出以递归公用表表达式的人为领导的人
)
SELECT empno,ename,mgr,n FROM cte;

# 4. type列：连接类型/访问类型
-- 当表中只有一条记录，并且该表使用的存储引擎的统计是精确的，比如MyISAM、Memory，那么访问类型就是system
CREATE TABLE t(i INT) ENGINE = 'MyISAM';
INSERT INTO t VALUES(1);

EXPLAIN SELECT * FROM t;

-- 换成InnoDB,就变成了ALL，也就是全表扫描
CREATE TABLE tt(i INT) ENGINE = 'InnoDB';
INSERT INTO tt VALUES(1);

EXPLAIN SELECT * FROM tt;

-- 当我们根据主键或者唯一索引列与常数进行等值匹配时，对但表的访问方法就是const
EXPLAIN SELECT * FROM emp WHERE empno = 7369; -- const，效率较高，性能不错

EXPLAIN SELECT * FROM emp WHERE job = 'SALESMAN'; -- ALL,因为job不是主键也不是唯一键

-- 在连接查询时，如果被驱动表是通过主键或者唯一二级索引列等值匹配的方式进行访问的
-- （如果该主键或者唯一二级索引是联合索引的话，所有的索引列都必须进行等值比较），则
-- 对该被驱动表的访问方法就是eq_ref
EXPLAIN SELECT * FROM emp e JOIN emp mgr ON e.mgr = mgr.empno;

-- 当通过普通的二级索引列与常量进行等值匹配时来查询某个表，那么对该表的访问方法就可能是`ref`
SHOW INDEX FROM emp;
ALTER TABLE  emp ADD INDEX idx_ename(ename);    -- 给name列加上索引
EXPLAIN SELECT * FROM emp WHERE ename = 'maye'; -- ref

-- 当对普通二级索引进行等值匹配查询，该索引列的值也可以是`NUL`值时，那么对该表的访问方法，就可能是'ref_or_null
EXPLAIN SELECT * FROM emp WHERE ename = 'maye' OR ename IS NULL; -- ref_or_null

-- 当一个查询的 WHERE 子句中有多个范围条件，并且这些条件可以通过不同的索引进行筛选时，MySQL 可能会选择使用多个索引，然后将结果合并。使用场景如下：
-- 1,OR 条件：WHERE key1 = 10 OR key2 = 20
-- 2,AND 条件：WHERE key1 = 10 AND key2 = 20（在某些情况下）
-- 3,多个范围条件：WHERE key1 < 10 OR key2 > 20
EXPLAIN SELECT * FROM emp WHERE empno = 7369 OR ename = 'maye';

-- 如果使用索引获取某些范围区间的记录，那么就可能使用到range访问类型
EXPLAIN SELECT * FROM emp WHERE empno IN (7369,77,88);
EXPLAIN SELECT * FROM emp WHERE empno BETWEEN 7777 AND 8888;

-- 当我们可以使用索引覆盖，但需要扫描全部的索引记录时，该表的访问方法就是丶index`
-- 也就是说条件部分是联合索引的某个字段，而且查询的字段只有联合索引中的字段或者主键，这个查询的方法就是index
ALTER TABLE  emp ADD INDEX idx_ename_job_hdate(ename,job,hiredate); 
EXPLAIN SELECT empno,ename,job FROM emp WHERE hiredate = '2011-05-01';

# 5. possible_keys和key：可能用到的索引和实际上使用的索引
EXPLAIN SELECT job FROM emp WHERE ename = 'maye';

EXPLAIN SELECT job FROM emp WHERE empno > 7788 AND  ename = 'maye';

EXPLAIN SELECT job FROM emp WHERE empno = 7788 OR  ename = 'maye';
EXPLAIN SELECT job FROM emp WHERE empno = 7369 AND  ename = 'SMITH';


# 6，key_len：实际使用到的索引长度（即：字节数)
-- 帮你检查是否充分的利用上了索引，值越大越好,主要针对联合索引，有一定参考意义
EXPLAIN SELECT * FROM emp WHERE empno = 7788; -- 2 SMAILLINT

ALTER TABLE emp ADD INDEX idx_sal(sal);
EXPLAIN SELECT * FROM emp WHERE sal = 8000;  -- 4 INT

-- utf8mb4一个字符最多4个字节，所以ename是10 * 4=40，能为空需要1个字节,字符串长度也需要2个字节，所以索引长度为43
EXPLAIN SELECT * FROM emp WHERE ename = 'maye'; -- 43

-- 联合索引
-- 如果联合索引第一个字段就没有查找到记录，那么后面的索引就不会使用了
EXPLAIN SELECT * FROM emp WHERE ename = 'maye' AND job = 'SALESMAN' AND hiredate = '2011-05-01'; -- 43
EXPLAIN SELECT * FROM emp WHERE ename = 'smith' AND job = 'CLERK' AND hiredate = '2010-12-17'; -- 43
SHOW INDEX FROM emp;
DESC emp;

# 7, ref列：当使用索引列等值查询时，与索引列进行等值匹配的对象信息。比如只是一个常数或者是某个列。
EXPLAIN SELECT * FROM emp WHERE empno = 7788; -- const
EXPLAIN SELECT * FROM emp LEFT JOIN dept USING(deptno); -- hdy.emp.deptno
EXPLAIN SELECT * FROM emp e1 LEFT JOIN emp e2 ON LOWER(e1.ename) = e2.ename; -- func


# 8, rows列：预估需要读取的记录条数，值越小越好
EXPLAIN SELECT * FROM emp WHERE empno > 7788;

EXPLAIN SELECT * FROM emp WHERE mgr = 7934;

# 9, filtered列：存储引擎返回的数据，经过 MySQL 服务器层用 WHERE 条件过滤后，剩余行数的百分比估计值。
-- 计算公式：filtered = (过滤后剩余行数(满足过滤条件的行数) ÷ 存储引擎返回行数) × 100%
-- 表示通过表条件筛选出的行的百分比估计。当filtered值为100时，意味着没有行被过滤，即所有行都符合条件。filtered值低于100表示有更多的行被过滤掉了。
-- filtered值实际上反映了索引的过滤效果。一个较低的filtered值通常意味着需要一个更好的索引。例如，如果type为all，表示全表扫描了19条记录，但filtered只有0.1%，这意味着只有1条记录符合搜索条件。如果添加一个索引可以直接搜索出这1条数据，那么filtered就可以提升到100%

-- 如果使用的是索引执行的单表扫描，那么计算时需要估计出满足除使用到对应索引的搜索条件外的其他搜索条件的记录有多少条。
EXPLAIN SELECT * FROM emp WHERE empno > 7788 AND sal > 6000;


-- 对于单表查询来说，这个filtered列的值没什么意义，我们更关注在连接查询中驱动表对应的执行计划记录的filtered值，它决定了被驱动表要执行的次数（即：rows*filtered）
EXPLAIN SELECT * FROM emp JOIN dept USING(deptno) WHERE dept.dname = 'SALES';

# 10.Extra列：一些额外信息
-- 没有表时：No tables used
EXPLAIN SELECT 1;

-- 查询语句WHERE条件永远为FALSE时:Impossible WHERE
EXPLAIN SELECT * FROM emp WHERE FALSE;

-- 当我们使用全表扫描来执行对某个表的查询，并且该语句的`WHERE子句中有针对该表的搜索条件时，并且条件字段没有任何索引：Using where
EXPLAIN SELECT * FROM emp WHERE comm IS NULL;

-- 当使用索引访问来执行对某个表的查询，并且该语句的`WHERE子句中有除了该索引包含的列之外的其他搜索条件时，并且结果能查询到记录时：NULL
EXPLAIN SELECT * FROM emp WHERE empno = 7369 AND comm IS NULL;

-- 不能查询到记录时：no matching row in const table
EXPLAIN SELECT * FROM emp WHERE empno = 7368 AND comm IS NULL;
-- Impossible WHERE noticed after reading const tables
EXPLAIN SELECT * FROM emp WHERE empno = 7369 AND comm IS NOT NULL;

-- 根据索引反向排序：Backward index scan
EXPLAIN SELECT * FROM emp ORDER BY empno DESC;
-- 根据没有索引的字段进行排序：Using filesort
EXPLAIN SELECT * FROM emp ORDER BY sal DESC;

