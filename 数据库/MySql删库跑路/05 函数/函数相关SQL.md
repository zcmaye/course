## 字符串函数

1. 把员工姓名首字母大写

```mysql
SELECT CONCAT(UPPER(LEFT(ename,1)),LOWER(SUBSTR(ename,2))) FROM emp;
```

2. 查询出姓名长度是5的所有员工信息

```mysql
SELECT * FROM emp WHERE CHAR_LENGTH(ename)=5;
```

3. 查询出员工姓名前三个字母是‘JAM’的员工

```mysql
SELECT * FROM emp WHERE SUBSTR(ename,1,3)='JAM';
```

4. 查询所有员工信息，但是不显示姓名的前三个字母

```mysql
SELECT ename 原始姓名,SUBSTR(ename,3) FROM emp;
# 只显示后三个字符
SELECT ename 原始姓名,SUBSTR(ename,-3) FROM emp;
```

5. 填充

```mysql
SELECT LPAD('Maye',10,'*'),RPAD('Maye',10,'*'),
LPAD(RPAD('Maye',10,'*'),16,'*');
```

![image-20220310142242551](assets/image-20220310142242551.png)