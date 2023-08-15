# 数据查询

### 基本查询

1，查询指定字段 ename，job，sal的数据
```mysql
select ename,job,sal from emp;
```

2，查询所有字段

```mysql
select empno,ename,job,mgr,hiredate,sal,comm,deptno from emp;
select * from emp;			#不直观 影响效率 遵循开发规范最好不要写* 吧所有字段写出了，一目了然
```

3,查询所有员工的职位，并起别名

```mysql
select job as '工作' from emp;
select job '工作' from emp;		#as可以省略
```

4，查询员工的的职位有哪些(不要重复)

```mysql
SELECT DISTINCT job FROM emp;
```

5，查询 员工工资乘以10之后的结果

```mysql
 SELECT ename,sal,sal*10 FROM emp;
```



### 条件查询

1. 查询工资等于3000的员工

```mysql
SELECT * FROM emp WHERE sal=3000;
```

2. 查询工资小于1000的员工

```mysql
SELECT * FROM emp WHERE sal<1000;
```

3. 查询工资小于等于1000的员工

```mysql
SELECT * FROM emp WHERE sal<=1000;
```

4. 查询没有奖金的员工

```mysql
SELECT * FROM emp WHERE comm IS NULL;
```

5. 查询有奖金的员工

```mysql
SELECT * FROM emp WHERE comm IS NOT NULL;
```

6. 查询工资在1200到1800之间的员工(包含1200和1800岁)

```mysql
SELECT * FROM emp WHERE sal>=1200 && sal<=1800;
SELECT * FROM emp WHERE sal>=1200 AND sal<=1800;
SELECT * FROM emp WHERE sal BETWEEN 1200 AND 1800;
```

7. 查询职位为推销员，且工资小于1500的员工

```mysql
SELECT * FROM emp WHERE job='salesman' AND sal < 1500;
```

8. 查询工资为800 或 3000 或 5000的员工

```mysql
SELECT * FROM emp WHERE sal=800 OR sal=3000 OR sal=5000;
SELECT * FROM emp WHERE sal IN(800,3000,5000);
```

9. 查询姓名为四个字的员工

```mysql
SELECT * FROM emp WHERE ename LIKE '____';
```

10. 查询姓名最后一位是S的员工

```mysql
SELECT * FROM emp WHERE ename LIKE '%S';
```

### 聚合函数(统计函数)



### 分组查询

1. 统计出每个工作岗位的人数

```mysql
SELECT job,COUNT(*) FROM emp GROUP BY job;
```

2. 统计出每种职位的最低和最高工资

```mysql
SELECT job,MIN(sal),MAX(sal) FROM emp GROUP BY job;
```

3. 显示不同职位薪资少于1500的人数

```mysql
SELECT job,COUNT(*) FROM emp WHERE sal<1500 GROUP BY job HAVING COUNT(*)>3;
```

4. 显示非销售人员(salesman)工作名称以及从事同一工作的员工的月工资的总和，并且要满足从事同一工作的员工的月工资合计大于等于**5000**。

```mysql
#先查找所有非销售人员的工作名称
SELECT job FROM emp WHERE job!='salesman';

#再对工作进行分组，统计各个职位的总工资
SELECT job,SUM(sal) FROM emp WHERE job!='salesman' GROUP BY job;

#最后加上HAVING对月工资大于5000的进行筛选
SELECT job,SUM(sal) FROM emp WHERE job!='salesman' 
GROUP BY job
HAVING SUM(sal)>5000;
```



### 排序查询

1. 根据姓名对员工进行排序(升序)

```mysql
SELECT * FROM emp ORDER BY ename;
```

2. 查询入职时间大于1981年6月6日的员工信息，并按照入职时间降序排列

```mysql
SELECT * FROM emp WHERE hiredate>'1981-6-6' ORDER BY hiredate DESC;
```

3. 根据工作职位，进行升序排列，职位相同的情况下，再根据入职时间降序排列

```mysql
SELECT * FROM emp ORDER BY job ASC,hiredate DESC;
```

4. 查询工资不在1000到2000之间的员工的姓名和工资，工资按降序排列

```mysql
SELECT * FROM emp WHERE sal NOT BETWEEN 1000 AND 2000 ORDER BY sal DESC;
```

5. 按工作职位进行分组，查看每个工作职位的人数，工作职位按升序排列

```mysql
SELECT job,COUNT(*) FROM emp GROUP BY job ORDER BY job ASC;
```



